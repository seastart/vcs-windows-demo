#include "RoomControl.h"
#ifdef Q_OS_WIN
#include <Windows.h>
#endif
#include "Tools/Utils.h"
#include <QDebug>

#include "EnumDevice.h"
RoomControl* RoomControl::client = nullptr;

RoomControl::RoomControl()
	: roomOpen(false)
	, timer(nullptr)
	, message(nullptr)
	, output(-1)
	, room(nullptr)
	, cameraInput(-1)
	, audioInput(-1)
	, screenInput(-1)
	, isProbe(false)
{
	int ret = VCS_Init();

    qDebug() << __func__ << ret << VCS_Version();
	roomInfo.audioSample = 48000;
    bool open;
    roomInfo.Stimulation = open;
	roomInfo.audioChannel = 1;
	roomInfo.outputVideo = 1;
	roomInfo.cameraName = "";
	roomInfo.speakerName = DEFAULTDEVICE;
	roomInfo.microphoneName = DEFAULTDEVICE;
	roomInfo.dpi = 1;

	roomInfo.AudioEliminate = true;
	roomInfo.PeopleNoise = true;
	roomInfo.aceindex = 6;
	roomInfo.roomShareType = 0;
    roomInfo.openCamera = false;
    roomInfo.openMicrophone = false;
    roomInfo.openSpeaker = false;
    roomInfo.stream_mode = 1;
#ifdef Q_OS_WIN
	qDebug() << QString::fromLocal8Bit("监测当前是否是虚拟机系统.");
	roomInfo.visualSystem = Utils::GetVisualSystem();
	qDebug() << QString::fromLocal8Bit("系统监测结果：") << roomInfo.visualSystem;
#endif
	VCS_Probe_CallBack(ProbeEventFunc, this);

}

RoomControl::~RoomControl()
{
    qDebug() << __func__;
	VCS_Cleanup();
}

RoomControl* RoomControl::Get()
{
	if (!client)
	{
		client = new (std::nothrow) RoomControl();
	}

	return client;
}

int RoomControl::AudioStatusEventFunc(int iEvent, int wParam, int lParam, void* ptr, void* ctx)
{
    if (iEvent != VCS_RPT_AUDIOINF)
    {
        return 0;
    }
    RoomControl* p = (RoomControl*)ctx;
    emit p->AudioStatus((char*)ptr);
    return 0;
}


int RoomControl::DirectShareEventFunc(int clientId,const char* cbData, void* ctx)
{
    RoomControl* r = (RoomControl*)ctx;
    qDebug()<<__func__<<clientId<<cbData;
    return 0;
}

int RoomControl::ProbeEventFunc(void* eventData, int dataSize, void* ctx)
{
	RoomControl* p = (RoomControl*)ctx;
	std::string sring = std::string((const char*)eventData, dataSize);
	QJsonObject obj = JsonUtil::GetJsonObjectFromString(sring);
	if (!obj.isEmpty())
	{
		int type = 0;
		JsonUtil::GetValue(obj, "type", type);
		if (type == 0 || type == 4)
		{
			p->isProbe = false;
		}
	}
	emit p->ProbeEvent(sring);
	return 0;
}

void RoomControl::SetAccountInfo(int fps, int bitrate, int outWidth, int outHeight)
{
	qDebug() << __func__;

	QJsonDocument doc;
	QJsonObject obj;

	obj.insert("id", roomInfo.userId);
	obj.insert("name", roomInfo.name);
	obj.insert("nickname", roomInfo.nickName);
    obj.insert("extend_info", roomInfo.nickName+"(en)");
	obj.insert("role", roomInfo.role);
	obj.insert("stream_id", roomInfo.streamId);
	obj.insert("terminal_type", 1);
	obj.insert("vstate", roomInfo.openCamera ? 0 : 1);
	obj.insert("astate", roomInfo.openMicrophoneUpload);
	obj.insert("portrait", roomInfo.portrait);
	obj.insert("relative_portrait", roomInfo.portrait2);

	QJsonArray qj;
	QJsonObject stream1;

	stream1.insert("id", 1);
	stream1.insert("type", 1);
	stream1.insert("width", 320);
	stream1.insert("height", 240);
	stream1.insert("bitrate", bitrate);
	stream1.insert("fps", fps);
	stream1.insert("channel", 1);
	stream1.insert("channel_type", 0);
	qj.append(stream1);

	QJsonObject stream2;

	stream2.insert("id", 2);
	stream2.insert("type", 0);
	stream2.insert("width", outWidth);
	stream2.insert("height", outHeight);
	stream2.insert("bitrate", bitrate);
	stream2.insert("fps", fps);
	stream2.insert("channel", 1);
	stream2.insert("channel_type", 0);
	qj.append(stream2);

	obj.insert("streams", qj);
    doc.setObject(obj);
	QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));
	SetAccountInfo(dataToString.toStdString().c_str());
}

void RoomControl::SetAccountInfo(const char* account)
{
	qDebug() << __func__ << account;
	if (!room)
	{
		return;
	}

	VCS_SetAccountInfo(room, account, 1);
}

int RoomControl::OpenRoom()
{
	qDebug() << __func__;
	if (roomOpen)
	{
		return -1;
	}
	roomOpen = true;
	ClientWndList.clear();

	VCS_Room_Init();

    VCS_Stream_Multiple(roomInfo.stream_mode);

    qDebug() << "VCS_Room_Init"<<roomInfo.stream_mode;

    int fps = 25;
    int bitrate = 1500;

	int outWidth = 1280;
	int outHeight = 720;


	char likId[20];
    sprintf(likId, "%d", roomInfo.streamId);
	qDebug() << "likId" << likId;
	output = VCS_CreateOutput(
        likId,
        NULL,
        outWidth,
        outHeight,
        outWidth,
        outHeight,
        fps,
        bitrate,
        roomInfo.audioSample,
        NULL);

	qDebug() << "VCS_CreateOutput" << output;
	if (output < 0)
	{
		qDebug() << "VCS_CreateOutput" << output;
		return -2;
	}
	int i = roomInfo.AudioEliminate ? 1 : 0;
	VCS_SetOutputAec(output, roomInfo.aceindex);
    VCS_SetOptParams(VCS_USE_SOFTWARE_AEC, i, 0, NULL, NULL);

	VCS_OpenVoiceExci(true);

	VCS_SetXdelay(1);

    qDebug() << "VCS_SetXdelay true";
	VCS_SetOutputAgc(output, 16000);

	qDebug() << "VCS_SetOutputAgc 16000";


    qDebug() << "VCS_SetOutputAec 10";
	VCS_SetAudioSample(output, roomInfo.audioSample);

    qDebug() << "VCS_SetAudioSample" << roomInfo.audioSample;
	VCS_SetAudioChannels(output, roomInfo.audioChannel);

    qDebug() << "VCS_SetAudioChannels" << roomInfo.audioChannel;
	VCS_ShowOutput(output, 1);

    qDebug() << "VCS_ShowOutput" << 1;
	room = VCS_CreateRoom();

    qDebug() << "VCS_CreateRoom";
	VCS_SetMultiTrack(room, 1);

	VCS_MCUDefaultTrack(2);
	qDebug() << "VCS_SetMultiTrack" << 1;
	VCS_SetRoomPlc(room, 2);

    qDebug() << "VCS_SetRoomPlc" << 2;
    VCS_SetRoomEvent(room, RoomEventFunc, this);

    qDebug() << "VCS_SetRoomEvent";
	SetAccountInfo(fps, bitrate, outWidth, outHeight);

	QJsonDocument doc;
	QJsonObject obj;

	obj.insert("id", roomInfo.roomId);
	obj.insert("sdk_no", roomInfo.roomSdkNumber);
	doc.setObject(obj);

    QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));
	VCS_SetRoomInfo(room, dataToString.toStdString().c_str());

    qDebug() << "VCS_SetRoomInfo" << dataToString;
	VCS_SetSession(room, roomInfo.roomSession.toStdString().c_str());

	qDebug() << "VCS_SetSession" << roomInfo.roomSession;

	VCS_SetRoomServer(room, roomInfo.meetingHost.toStdString().c_str(), roomInfo.meetingPort);

	VCS_SetRoomMqtt(room, roomInfo.mqttServerId.toLocal8Bit());

	VCS_SetMediaServer(room, roomInfo.streamHost.toStdString().c_str(), roomInfo.streamPort);

    qDebug() << "VCS_SetMediaServer" << roomInfo.streamHost << roomInfo.streamPort;
	VCS_SetRoomOutput(room, output);

    qDebug() << "VCS_SetRoomOutput";
	int state = VCS_EnterRoom(room);
	OpenCloseDenVoice(roomInfo.PeopleNoise);
	qDebug() << "VCS_EnterRoom";
	if (state < 0)
	{
		return -3;
	}

    qDebug() << "VCS_EnableSendAudio" << 0 << 0;
	VCS_SetRoomXBitrate(room, 10);

	qDebug() << "VCS_SetRoomXBitrate" << 10;
	VCS_SetOptParams(VCS_OPT_XBITMODE, 0, 0, NULL, NULL);

	int iRetTemp = VCS_SetOptParams(VCS_OPT_MAXBITRATE, 3000, 0, NULL, NULL);

	SetStatInterval(10);

	VCS_SetOptParams(VCS_RESET_SIZE, 1280, 720, NULL, NULL);

    QString msg;
	if (OpenAudio(msg, 1))
    {
        qDebug() << __func__ << "error" << msg;
    }

	VCS_SetSpeakerOn(false);

	VCS_EnableSendVideo(room, 0, 0);

    qDebug() << "VCS_EnableSendVideo" << 0 << 0;
	VCS_EnableSendAudio(room, 0, 0);
	qDebug() << "VCS_SetSpeakerOn" << false;


    VCS_SetAudioEventStatusCallback(&RoomControl::AudioStatusEventFunc, this);
	return 0;
}

void RoomControl::CloseRoom()
{
	qDebug() << __func__;
	if (!roomOpen)
	{
		return;
	}
	roomOpen = false;




	VCS_SetCtrlDisplay(0x03, NULL);

	CloseCamera();
	CloseAudio();
	CloseShareScreen();

	qDebug() << "VCS_SetCtrlDisplay" << 3;
	if (room)
	{
		VCS_ExitRoom(room);
		qDebug() << "VCS_ExitRoom";
		room = nullptr;
	}

	VCS_Room_Cleanup();
	qDebug() << "VCS_Room_Cleanup";
	output = -1;
	cameraInput = -1;
	audioInput = -1;
	screenInput = -1;
	roomInfo.roomShareType = 0;
}

bool RoomControl::RoomOpen()
{
	return roomOpen;
}

void RoomControl::ResetCanvas(int& width, int& height, int& bitrate, int& fps, bool isShare)
{
	qDebug() << __func__;
	int xBitMode = 0;
	int prevpaused = 0;
	if (isShare)
	{
		fps = 10;
		xBitMode = 2;
		prevpaused = 1;
	}
	else
	{
		fps = 25;
    }
	if (height >= 1080)
	{
		bitrate = 2000;
	}
	else if (height >= 720)
	{
		bitrate = 1500;
	}
	else
	{
		bitrate = 800;
	}

	VCS_SetOptParams(VCS_OPT_XBITMODE, xBitMode, 0, NULL, NULL);

	VCS_SetOptParams(VCS_RESET_CPARAM, VCS_PARAM_FRAMES, fps, NULL, NULL);

	VCS_SetOptParams(VCS_RESET_CPARAM, VCS_PARAM_BITRATE, bitrate, NULL, NULL);

	VCS_SetOptParams(VCS_RESET_SIZE, width, height, NULL, NULL);

	VCS_SetOptParams(VCS_OPT_PREVPAUSED, prevpaused, 0, NULL, NULL);
}

int RoomControl::OpenCamera(void* winId, QString& msg)
{
	qDebug() << __func__;
	if (roomInfo.visualSystem)
	{
		msg = QString::fromLocal8Bit("检测到虚拟机版本过低，无法打开本地摄像头~");
		return 1;
	}
	if (roomInfo.noVideo)
	{
		msg = QString::fromLocal8Bit("检测到显卡异常，视频将无法正常显示；建议检查或尝试更新显卡驱动后，再重新入会确认。");
		return 1;
	}
#ifdef Q_OS_MAC
    int ret = MacosTool::VideoAuthorization();
    if(ret)
    {
        msg = QString::fromLocal8Bit("摄像头权限异常：") + ((ret  > 0) ? QString::fromLocal8Bit("未授权"):QString::fromLocal8Bit("用户拒绝"));
        return 2;
    }
#endif
    VideoDeviceList devices;
    EnumDevice::Video(devices);

	if (!devices.GetDeviceSize() || roomInfo.cameraName.isEmpty())
	{
		msg = QString::fromLocal8Bit("无可用摄像头设备");
		return 2;
	}
	if (devices.GetConflict())
	{
		msg = QString::fromLocal8Bit("摄像头设备冲突。");
		return 1;
	}
	qDebug() << __func__ << "select " << roomInfo.cameraName;
	VideoDevice videoDevice;
	if (!devices.DevContains(roomInfo.cameraName, videoDevice))
	{
		roomInfo.cameraName = "";
		EnumDevice::Video(devices);
		devices.DevContains(roomInfo.cameraName, videoDevice);
	}


	qDebug() << __func__ << "select cam index" << roomInfo.cameraResolution;
	if (videoDevice.GetResolutionCount() <= roomInfo.cameraResolution)
	{
		msg = QString::fromLocal8Bit("没有合适的分辨率");
		return 1;
	}
	Resolution resolution = videoDevice.GetResolution(roomInfo.cameraResolution);

	if (cameraInput >= 0)
	{
		msg = QString::fromLocal8Bit("摄像头以打开");
		return 0;
	}
	roomInfo.openCamera = true;
	int width = resolution.GetWidth();
	int height = resolution.GetHeight();
	int type = resolution.GetType();
	qDebug() << __func__ << "select cam width height" << width << height << type;
	int outWidth = width;
	int outHeight = height;
	int bitrate, fps;
	ResetCanvas(outWidth, outHeight, bitrate, fps, false);
#ifdef Q_OS_WIN
	if (resolution.GetType() == 2)
	{
		VCS_SetOptParams(0x105, 0x01, 0, NULL, NULL);
	}
	else
	{
		VCS_SetOptParams(0x105, 0x02, 0, NULL, NULL);
	}

	cameraInput = VCS_CreateInputVideo(videoDevice.GetName().toLocal8Bit(), width, height, fps, winId);
#else
    cameraInput = VCS_CreateInputVideo(videoDevice.GetDevId().toLocal8Bit(), width, height, fps, winId);
#endif
    qDebug() << "VCS_CreateInputVideo" << videoDevice.GetName()<<"id:"<<videoDevice.GetDevId().toLocal8Bit();
	if (cameraInput < 0)
	{
		msg = QString::fromLocal8Bit("开启摄像头异常");
		return 2;
	}
	VCS_SetSrcStreamVisible(cameraInput, true);
	qDebug() << "VCS_SetSrcStreamVisible";
	int left = 0, top = 0;

	VCS_AdjustPicture(
        outWidth,
        outHeight,
        width,
        height,
		&left,
		&top,
		&width,
		&height);

    qDebug() << "VCS_AdjustPicture";
	VCS_AddInput(
        output,
        cameraInput,
        left,
        top,
        width,
        height,
        0,
        1,
        1);

    qDebug() << "VCS_AddInput";
	VCS_UpdateOutput(output);

    qDebug() << "VCS_UpdateOutput";
	VCS_EnableSendVideo(room, 0, 1);

    qDebug() << "VCS_EnableSendVideo";
	SetAccountInfo(fps, bitrate, outWidth, outHeight);
	return 0;
}

void RoomControl::EnableSendVideo(int enable)
{

	qDebug() << "VCS_EnableSendVideo" << enable;
	VCS_EnableSendVideo(room, 0, enable);
}

void RoomControl::CloseCamera(int enable)
{
	qDebug() << __func__;
	if (cameraInput < 0)
	{
		EnableVideo(enable);
		return;
	}
	roomInfo.openCamera = false;

	VCS_CloseInput(cameraInput);

    qDebug() << "VCS_CloseInput";
	int ret = VCS_RemoveInput(output, cameraInput);

    qDebug() << "VCS_RemoveInput" << ret;
	VCS_UpdateOutput(output);
	qDebug() << "VCS_UpdateOutput";
	cameraInput = -1;
	if (!enable)
	{
		EnableVideo(enable);
	}
}

int RoomControl::OpenAudio(QString& msg, int upload)
{
	qDebug() << __func__;
	DeviceList devices;
	EnumDevice::Audio(devices);
	if (devices.GetDeviceSize() == 0)
	{
		msg = QString::fromLocal8Bit("无可用麦克风设备");
		return 1;
	}
	if (audioInput >= 0)
	{
		msg = QString::fromLocal8Bit("麦克风以打开");
		return 0;
	}
#ifdef Q_OS_WIN
	if (!VCS_MicPermissions())
	{
		msg = QString::fromLocal8Bit("无可用麦克风权限");
		return 2;
	}
#endif
	DeviceBase dev;
    QString uid = "";
    if (!devices.DevContains(roomInfo.microphoneName, dev))
	{
		roomInfo.microphoneName = DEFAULTDEVICE;
	}
	if (roomInfo.microphoneName == DEFAULTDEVICE)
	{
		roomInfo.microphoneTrueName = devices.GetDevault();
	}
	else
	{
		roomInfo.microphoneTrueName = dev.GetName();
	}

    qDebug() << "VCS_CreateInputAudio begin";
	audioInput = VCS_CreateInputAudio(roomInfo.microphoneTrueName.toLocal8Bit(), roomInfo.audioChannel, roomInfo.audioSample);

	qDebug() << "VCS_CreateInputAudio" << roomInfo.microphoneTrueName << "streamid:" << audioInput;
	if (audioInput < 0)
	{
		msg = QString::fromLocal8Bit("开启麦克风异常");
		return 1;
	}

	int left = 0, top = 0, height = 1, width = 1;

	VCS_AddInput(
        output,
        audioInput,
        left,
        top,
        width,
        height,
        1,
        0,
        1);

	VCS_UpdateOutput(output);

	qDebug() << "VCS_UpdateOutput";
	roomInfo.openMicrophone = true;
	EnableAudio(upload);

	return 0;
}

void RoomControl::CloseAudio(int upload)
{
	qDebug() << __func__;
	if (audioInput < 0)
	{
		return;
	}
	roomInfo.openMicrophone = false;
	roomInfo.microphoneTrueName = "";

	VCS_CloseInput(audioInput);

    qDebug() << "VCS_CloseInput";
	int ret = VCS_RemoveInput(output, audioInput);

    qDebug() << "VCS_RemoveInput" << ret;
	VCS_UpdateOutput(output);
	qDebug() << "VCS_UpdateOutput";
	audioInput = -1;

	EnableAudio(upload);
}

bool RoomControl::OpenSpeaker(QString& msg)
{
	if (roomInfo.openSpeaker)
	{
		msg = QString::fromLocal8Bit("扬声器以打开");
		return true;
	}
	qDebug() << __func__;
	DeviceList devices;
	EnumDevice::Speaker(devices);
	if (devices.GetDeviceSize() == 0)
	{
		msg = QString::fromLocal8Bit("无可用扬声器设备");
		VCS_Speak_Error_NoDeal(room);
		return false;
	}
	DeviceBase dev;
    if (!devices.DevContains(roomInfo.speakerName, dev))
	{
		roomInfo.speakerName = DEFAULTDEVICE;
	}
	if (roomInfo.speakerName == DEFAULTDEVICE)
	{
		roomInfo.speakerTrueName = devices.GetDevault();
	}
	else
	{
		roomInfo.speakerTrueName = dev.GetName();
	}

	VCS_SetSpeakerDevice(roomInfo.speakerTrueName.toLocal8Bit());

	qDebug() << "VCS_SetSpeakerDevice" << roomInfo.speakerTrueName;
	if (VCS_SetSpeakerOn(true) < 0)
	{
		msg = QString::fromLocal8Bit("开启扬声器异常");
		return false;
	}
	qDebug() << "VCS_SetSpeakerOn" << true;
	roomInfo.openSpeaker = true;
	return true;
}

void RoomControl::CloseSpeaker()
{
	qDebug() << __func__;
	roomInfo.openSpeaker = false;
	roomInfo.speakerTrueName = "";
	VCS_SetSpeakerOn(false);
	qDebug() << "VCS_SetSpeakerOn" << false;
}

bool RoomControl::Picker(int stream_id, int type)
{
	if (roomInfo.noVideo)
	{
		return false;
	}
	qDebug() << __func__;
	VCS_SetPicker(output, type, stream_id);
	qDebug() << "VCS_SetPicker" << type << stream_id;
	return true;
}

void RoomControl::UnPicker(int stream_id)
{
	qDebug() << __func__;
	VCS_SetPicker(output, 0, stream_id);
	qDebug() << "VCS_SetPicker" << 0 << stream_id;
}
void RoomControl::SetTrack(int stream_id,int mask)
{
    VCS_SetTrack(output,mask, stream_id);
}
void RoomControl::SetView(int stream_id,int track,void* winId)
{
    VCS_SetClientWnd(room, stream_id, track, winId);
}

void RoomControl::SetMember(int stream_id, void* winId, int mask)
{
	qDebug() << __func__ << mask << stream_id;
	if (winId == NULL || !room || mask == 0)
	{
		return;
	}

    if (_recvMemberMap.find(stream_id) == _recvMemberMap.end())
    {
        RecvFrameClass* rfc = new RecvFrameClass();
        _recvMemberMap[stream_id] = rfc;
        rfc->hwnd = winId;
    }
    if (_recvMemberMap.contains(stream_id))
    {
        if (_recvMemberMap[stream_id]->openfile) {

            fclose(_recvMemberMap[stream_id]->fp_h264);
            _recvMemberMap[stream_id]->openfile = false;
        }
    }

	VCS_SetTrack(output, mask, stream_id);

    qDebug() << "VCS_SetTrack" << mask << stream_id;
	std::vector<int> tracks;
	Utils::MaskToTrack(tracks, mask);

	int track = tracks[0];
    qDebug() << __func__ << track << winId;
	int ret = VCS_SetClientWnd(room, stream_id, track, winId);
	qDebug() << "VCS_SetClientWnd finish" << stream_id << track << ret;

	ClientWndList.append(stream_id);
	qDebug() << __func__ << ClientWndList;

}


int RoomControl::AddMember(int stream_id, void* winId, int mask, int oldMask)
{
	qDebug() << __func__;
	if (winId == NULL || !room || mask == 0)
	{
		return oldMask;
	}
	std::vector<int> tracks;
	Utils::MaskToTrack(tracks, mask);

	int track = tracks[0];

	mask = mask | oldMask;
	VCS_SetTrack(output, mask, stream_id);

	VCS_SetClientWnd(room, stream_id, track, winId);
	return mask;
}

void RoomControl::RemovePlayer(void* winId, int stream_id, int track)
{
	if (winId != nullptr)
	{
		int ret = -1;
		ret = VCS_RelaseDisplayerByUser(winId, stream_id, track);
		qDebug() << "VCS_RelaseDisplayerByUser" << winId << stream_id << ret;
	}
}

void RoomControl::RemoveMember(int stream_id, int mask)
{
	qDebug() << __func__ << ",streamid:" << stream_id;
	if (!room)
	{
		return;
	}

	if (mask == 0)
	{
		return;
	}

	std::vector<int> tracks;
	Utils::MaskToTrack(tracks, mask);
    int ret = -1;
	foreach(int track, tracks)
    {
		ret = VCS_SetClientWnd(room, stream_id, track, nullptr);
	}
	ClientWndList.removeAll(stream_id);
}

void RoomControl::StartShare(int type, const char* pic_url)
{
	qDebug() << __func__;
	VCS_StartShare(room, type, pic_url);
	qDebug() << "VCS_StartShare" << type << pic_url;
}
void RoomControl::StartShare2(int type, const char* pic_url, const char* pic2)
{
	qDebug() << __func__;
	VCS_StartShare2(room, type, pic_url, pic2);
	qDebug() << "VCS_StartShare" << type << pic_url;
}

void RoomControl::StopShare()
{
	qDebug() << __func__;
	VCS_StopSharing(room);
	qDebug() << "VCS_StopSharing";
}


void RoomControl::ShareScreen(CapsData& data, void* winId)
{
	qDebug() << __func__;
	if (screenInput >= 0)
	{
		return;
	}

	void* hCapWnd = (void*)atoll(data.hwnd().toLocal8Bit());

	if (!data.desktop())
	{
	}
    screenInput = VCS_CreateInputScreen2(
        winId,
        hCapWnd,
        data.rect().toLocal8Bit());




    qDebug() << __func__ << "ShareScreen:" << screenInput;
    int outWidth = 1920;
    int outHeight = 1080;
	int bitrate, fps;
	ResetCanvas(outWidth, outHeight, bitrate, fps, true);

	int left = 0, top = 0, width = 0, height = 0;

	VCS_AdjustPicture(
        outWidth,
        outHeight,
        1920,
        1080,
		&left,
		&top,
		&width,
		&height);

	VCS_AddInput(
        output,
        screenInput,
        left,
        top,
        width,
        height,
        0,
        1,
        1);

	VCS_UpdateOutput(output);

	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("astate", roomInfo.openMicrophoneUpload);
	obj.insert("vstate", roomInfo.openCamera ? 0 : 1);
	QJsonArray qj;

	QJsonObject stream1;

	stream1.insert("id", 2);
	stream1.insert("type", 0);
	stream1.insert("width", outWidth);
	stream1.insert("height", outHeight);
	stream1.insert("bitrate", bitrate);
	stream1.insert("fps", fps);
	stream1.insert("channel", 1);
	stream1.insert("channel_type", 5);
	qj.append(stream1);
	obj.insert("streams", qj);
	doc.setObject(obj);
	QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));
	SetAccountInfo(dataToString.toStdString().c_str());

	VCS_EnableSendVideo(room, 0, 1);


}

void RoomControl::CloseShareScreen(int enable)
{
	qDebug() << __func__;
	if (screenInput < 0)
	{
		return;
	}

	VCS_CloseInput(screenInput);

	qDebug() << "VCS_CloseInput";
	int ret = VCS_RemoveInput(output, screenInput);

	qDebug() << "VCS_RemoveInput" << ret;
	VCS_UpdateOutput(output);
	qDebug() << "VCS_UpdateOutput";
	screenInput = -1;
	if (!enable)
	{
		EnableVideo(enable);
	}
}

void RoomControl::EnableAudio(int open)
{
	qDebug() << __func__;
	VCS_EnableSendAudio(room, 0, (open == 0));
	roomInfo.openMicrophoneUpload = open;
	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("astate", open);
	doc.setObject(obj);
	QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));
	SetAccountInfo(dataToString.toStdString().c_str());
}

void RoomControl::EnableVideo(bool open)
{
	qDebug() << __func__;
	VCS_EnableSendVideo(room, 0, open);

	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("vstate", open ? 0 : 1);
	doc.setObject(obj);
	QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));
	SetAccountInfo(dataToString.toStdString().c_str());
}

void RoomControl::OnTimer()
{
	VCS_DisplayFrame();
}

int RoomControl::RoomEventFunc(HROOM client, int eventId, void* eventData, int dataSize, void* ctx)
{
	RoomControl* p = (RoomControl*)ctx;
	std::string sring = std::string((const char*)eventData, dataSize);
	switch (eventId)
	{
	case VCS_EVENT_MEDIA_CONNECTED:
	{
        VCS_NoPickAudio(1);
		VCS_SetPicker(p->output, 3, 0);
		break;
	}
	case VCS_EVENT_GRAPHICS_INVALID:
	{
		break;
	}
	case VCS_EVENT_DEBUG_LOG:
	{
        qDebug()<<("VCS_EVENT_DEBUG_LOG:" + QString::fromLocal8Bit(sring.c_str()));
        return 0;
	}
	}

	return emit p->RoomEvent(client, eventId, sring);
}


int RoomControl::SendChatMsg(QString msg, QString tar)
{
	qDebug() << __func__;
	const char* target = nullptr;
	if (!tar.isEmpty())
	{
		target = tar.toLocal8Bit();
	}
	int ret = VCS_Chat(room, target, 1, msg.toUtf8());
	return ret;
}

bool RoomControl::SetHostCtrlMic2(bool v)
{
	qDebug() << __func__ << v;
	int mic = v ? 1 : 0;
    int ret = VCS_HostCtrls(room, nullptr, &mic, nullptr);
	return ret;
}

bool RoomControl::SetHostCtrlMic(const char* tarid, int mic)
{
	qDebug() << __func__ << mic;
    int ret = VCS_HostCtrl(room, tarid, &mic, nullptr);
	return ret;
}

bool RoomControl::SetHostCtrlCam(const char* tarid, int Cam)
{
	qDebug() << __func__;
    int ret = VCS_HostCtrl(room, tarid, nullptr, &Cam);
	return ret;
}

void RoomControl::AdminKickout(std::string id)
{
	qDebug() << __func__;
    int ret = VCS_HostKickout(room, id.c_str());
}

void RoomControl::SetAccountNetWork(int delay, int rate, float first_lost, int signal)
{
	QJsonDocument doc;
	QJsonObject obj;
	obj.insert("delay", delay);
	obj.insert("up_rate", rate);
	obj.insert("up_lost", first_lost);
	obj.insert("net_level", signal);
	doc.setObject(obj);
	QString dataToString(doc.toJson(QJsonDocument::JsonFormat::Compact));

	VCS_SetAccountInfo(room, dataToString.toStdString().c_str(), 0);
}


void RoomControl::SetStatInterval(int interval)
{
	if (roomOpen)
	{
		VCS_SetStatInterval(room, interval);
	}
}

int RoomControl::RestartMeeting(std::string host, int port, std::string session)
{
	if (roomOpen)
	{
		return VCS_ReStartMeeting(room, host.c_str(), port, session.c_str());
	}
	return -1;
}

void RoomControl::SetAudioFirst(int stream_id, bool open)
{
	int isopen = open ? 1 : 0;
	VCS_SetOptParams(VCS_OPT_AUDIOPRIO, isopen, stream_id, NULL, NULL);
}

void RoomControl::SetHostWaterMark(bool open)
{
	int o = open ? 1 : 0;
	VCS_HostWaterMark(room, o);
}

int RoomControl::WaterMarkShow(bool open, void* handle, int wid, int hei, const char* name, const char* text)
{

	qDebug() << __func__ << open << handle;
	int o = open ? 1 : 0;
	if (roomInfo.dpi != 1)
	{
		wid = wid * roomInfo.dpi;
		hei = hei * roomInfo.dpi;
	}
	return VCS_WaterMark_Show(o, wid, hei, handle, name, text);
	qDebug() << __func__ << open << handle << "finish";
}

void RoomControl::DesktopImageShare(bool isOpenShare)
{
	int o = isOpenShare ? 4 : 3;
	VCS_StartShare(room, o, nullptr);
}

int RoomControl::HeadUp(bool type)
{
	int t = type ? 1 : 0;
	return VCS_HandUp(room, t);
}


int RoomControl::HostHeadUp(const char* targetid, int type, bool result)
{
    int t = result ? 0 : 1;
	return VCS_Host_HandUp(room, targetid, type, t);
}

int RoomControl::RoomMute(bool ret)
{
	int t = ret ? 1 : 0;
	return VCS_HostRoomCtrl(room, roomInfo.roomId.toLocal8Bit(), &t, nullptr);
}

int RoomControl::HostUsersMute(const char* users, bool ret)
{
	int t = ret ? 1 : 0;
	return VCS_HostCtrls(room, users, &t, nullptr);
}

char* RoomControl::SdkVersion() {
	return VCS_Version();
}

void RoomControl::SetMyRole(int role)
{
	roomInfo.role = role;
	SetAccountInfo(QString("{\"role\":%1}").arg(role).toStdString().c_str());
}

int RoomControl::RoomRecoveryHost(const char* target)
{
	return VCS_RoomRecoveryHost(room, target);
}

int RoomControl::SetViewPlus(void* hwnd, bool v)
{
	int type = v ? GENERAL_INTENSITY : NO_INTENSITY;
	return VCS_SetOptParams(VCS_SET_INTENSITY, type, 0, hwnd, NULL);
}


void RoomControl::StopStartPicker(bool ret)
{
	if (ret)
	{
		VCS_SetPicker(output, 0x4000, 0);
	}
	else
	{
		VCS_SetPicker(output, 0x4000, 1);
	}
}

void RoomControl::ReFlashHandle(void* hwnd)
{
	VCS_SetCtrlDisplay(VCS_REFRESH_WIND, hwnd);
}

void RoomControl::AudioModel(bool open)
{
	if (RoomControl::Get()->roomInfo.audioModel == open)
	{
		return;
	}
	RoomControl::Get()->roomInfo.audioModel = open;
	int v = open ? 1 : 0;
	VCS_AudioModel(room, v);
}

void RoomControl::HostUpdateNickName(QString id, QString NickName)
{
	VCS_HostSetMemberName(room, id.toLocal8Bit(), NickName.toStdString().c_str());
}

void RoomControl::MyUpdateNickName(QString NickName)
{
	RoomControl::Get()->roomInfo.nickName = NickName;
	VCS_SetNickName(room, NickName.toStdString().c_str());
}

int RoomControl::RoomMoveHost(QString user)
{
	return VCS_RoomMoveHost(room, user.toLocal8Bit());
}

int RoomControl::SetUnionHost(QString user, bool state)
{
	int o = state ? 1 : 0;
	return VCS_SetUnionHost(room, user.toLocal8Bit(), o);
}

int RoomControl::RoomRecoveryHost(QString target)
{
	return VCS_RoomRecoveryHost(room, target.toLocal8Bit());
}

int RoomControl::StartProbe(const char* data)
{

	int ret = VCS_Probe(data);
	if (!ret)
	{
		isProbe = true;
	}
	return ret;
}

void RoomControl::DeleteProbe()
{
	VCS_DeleteProbe();
}

void RoomControl::SetMcuDefaultTrick(int i)
{
	VCS_MCUDefaultTrack(i);
}

void RoomControl::InitMqtt(const char* host, const char* token)
{
	int ret = VCS_InitMqttServer(host, token);
	qDebug() << __func__ << ret;
}

bool RoomControl::SetMqttRoomServerid(const char* serverid)
{
	return !VCS_SetRoomMqtt(room, serverid);
}

bool RoomControl::SetMqttVcsServerid(const char* serverid)
{
	return !VCS_SetVcsMqtt(message, serverid);
}

void RoomControl::OpenCloseDenVoice(bool v)
{
	int i = v ? 1 : 0;
	VCS_SetOptParams(VCS_USE_F_DEN_VOICE, i, 0, NULL, NULL);
}


void RoomControl::GetAudioError()
{

	int ret = VCS_SetOptParams(VCS_CHK_ACAPTURE, 0, 0, NULL, NULL);
	qDebug() << __func__ << ret;
}
bool RoomControl::ReUpdateSpeaker(QString& msg)
{
	CloseSpeaker();
	VCS_SetSpeakerDevice("");
	roomInfo.openSpeaker = false;
	return OpenSpeaker(msg);
}

void RoomControl::SendVideoData(const unsigned char* streamData, int dataSize, long  pts, long dts, int trackId, int stmtype, int frmtype, int options)
{
	VCS_PushVideoEncoderStream(streamData, dataSize, pts, dts, trackId, stmtype, frmtype, options);
}

void RoomControl::SendAudioData(const unsigned char* streamData, int dataSize, long  ts, int stmtype, int frmtype, int options)
{
	VCS_PushAudioEncoderStream(streamData, dataSize, ts, stmtype, frmtype, options);
}
QString RoomControl::test()
{
    qDebug()<<__func__;
    char data[1000];
    EnumAudioDevices(data,1000);
    qDebug()<<__func__<<std::string(data).c_str();
    return QString::fromStdString(std::string(data));
}


void RoomControl::ReSetView(void* hwnd)
{
    VCS_ReFlashColorView(hwnd,255,0,0);
}

void RoomControl::Test(void* winId)
{

}

void RoomControl::OpenMessage(const char* account, const char* token, const char* address, int port, const char* serverid)
{
	qDebug() << __func__;
	if (message)
	{
		return;
	}

	message = VCS_CreateClient(account, token, address, port, MessageEventFunc, this);
	VCS_SetVcsMqtt(message, serverid);
	int ret = VCS_Open(message);
	qDebug() << __func__ << ret;
}

void RoomControl::CloseMessage()
{
	qDebug() << __func__;
	if (message)
	{
		VCS_Close(message);
		message = nullptr;
	}
}

void RoomControl::WaitingRoom(const char* account)
{
	VCS_WaitingRoom(message, account);
}

void RoomControl::Call(const char* roomNo, bool restart, const char* data)
{
	VCS_Call(message, roomNo, restart, data);
}



void RoomControl::Invite(const char* account, const char* roomNo)
{
	VCS_Invite(message, account, roomNo);
}
void RoomControl::InviteConfirm(const char* account, const char* initiator_id, const char* roomNo, bool res)
{
	int v = res ? VCS_INVITE_RSP_ACCEPTED : VCS_INVITE_RSP_REJECTED;
	VCS_InviteConfirm(message, initiator_id, account, roomNo, v);
}


int RoomControl::ShareFpiGet2()
{
	char data[1024];
	VCS_GetDisplayFpsInfo(data, 1024);
	qDebug() << __func__ << data;
	return 0;
}
int RoomControl::MyFpiGet()
{
	int frames = VCS_SetOptParams(0x103, 0, 0, NULL, NULL);
	return frames;
}
int RoomControl::ShareFpiGet(int stram)
{
	double fps = 0.0;
	char data[1024] = {0};
	VCS_GetDisplayFpsInfo(data, 1024);
	QJsonObject json = JsonUtil::GetJsonObjectFromString(data);
	qDebug() << __func__ << data;
	if (!json.isEmpty())
	{
		QJsonArray arr = json.value("fpsInfo").toArray();
		for (QJsonArray::iterator it = arr.begin(); it != arr.end(); ++it)
		{
			QJsonObject obj = (*it).toObject();
			QString sreamid = "";
			JsonUtil::GetValue(obj, "streamId", sreamid);
			if (sreamid.toInt() == stram)
			{
				QString s_fps;
				JsonUtil::GetValue(obj, "fps", s_fps);
                fps = s_fps.toDouble() + 0.5;
				break;
			}
		}
	}
	return (int)fps;
}


void RoomControl::ChangeShareRect()
{
	VCS_ChangeShareRect(screenInput, "-110,-100,500,500");
}

int RoomControl::MessageEventFunc(HCLIENT client, int eventId, void* eventData, int dataSize, void* ctx)
{
	RoomControl* p = (RoomControl*)ctx;
	std::string sring = std::string((const char*)eventData, dataSize);

	emit p->MessageEvent(client, eventId, sring);
	return 0;
}


void RoomControl::setMemberExtend_info(QString tar,QString s)
{
}


#define SAVEREMOTEILE
int index = 0;
int RoomControl::FrameEventFunc(int linkid, const av_frame_s* frm, void* ctx)
{
    qDebug()<<__func__;
    RoomControl* rc = (RoomControl*)ctx;
    int track = frm->track % 7;
    if (frm->medtype == 1)
    {

    }
    else if (frm->medtype == 2)
    {

        if (frm->stmtype == 0x1b)
        {
#ifdef SAVEREMOTEILE
            if (!rc->_recvMemberMap[linkid]->openfile)
            {
                index++;
                char filename[50] = { 0 };
                sprintf(filename, "%d_%d_%d.h264", linkid, track, index);
                rc->_recvMemberMap[linkid]->fp_h264 = fopen(filename, "wb+");
                rc->_recvMemberMap[linkid]->openfile = true;
            }

            fwrite(frm->bits, frm->bitslen, 1, rc->_recvMemberMap[linkid]->fp_h264);
            return 0;
#endif
        }
    }
    return 0;
}

void RoomControl::StartDirectShare(QString ip,const char* ss)
{
    qDebug()<<__func__<<ip<<ss;
}
void RoomControl::StopDirectShare()
{
}

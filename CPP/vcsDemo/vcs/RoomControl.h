#pragma once


#include <vcs.h>
#include <QObject>
#include <QTimer>
#include "DataModel/CapsData.h"
#include "DataModel/RoomData.h"
#include "DataModel/UserData.h"
#include "DataModel/NotifyRoomData.h"
#include <QList>
#ifdef Q_OS_MAC
#include "Tools/MacosTool.h"
#endif
class RecvFrameClass
{
public:

    void* hwnd = nullptr;
    bool iscreatebackbuffer = false;
    long dwIndex = 0;
    int hwnd_w;
    int hwnd_h;
    unsigned char* yuvdata = nullptr;
    bool openfile = false;
    int trackid = -1;
    FILE* fp_h264 = NULL;
};
class RoomInfo
{

public:
	void InitData() {
		isShowJoinLeaveMsg = false;
		outputShare = 0;
		noVideo = false;
		imageShareDialogShow = false;
		lockMeeting = false;
		roomAudio = -1;
		roomVideo = -1;
		openCamera = false;
		openMicrophone = false;
		openMicrophoneUpload = 1;
		openSpeaker = false;
		showWaterMark = false;
		audioModel = false;
	}

	void SetUserDataValue(UserData userData) {
		streamId = userData.account().room().sdk_no().toInt();
        userId = userData.account().id();
		name = userData.account().name();
		mobile = userData.account().mobile();
	};

	void SetRoomDataValue(RoomData data) {

		role = data.role();
		roomNo = data.room().no();
		roomId = data.room().id();
		roomSdkNumber = data.sdk_no();
		roomSession = data.session();
		meetingHost = data.meeting_host();
		meetingPort = data.meeting_port();
		streamHost = data.stream_host();
		streamPort = data.stream_port();
		mqttServerId = data.meeting_server_id();
		type = data.type();
		if (data.type() == 2)
		{
            LowerId = data.conf().id();
		}
		else
		{
            LowerId = data.account().id();
		}
		roomPass = data.room().password();
		confBegin = data.conf().begin_time();
		confEnd = data.conf().end_time();
		roomTitle = data.title();
		wbHost = data.wb_host();

	};

	bool openSpeaker;

	QString speakerName;
    QString speakerTrueName;
	bool openCamera;

    QString cameraName;
    int cameraResolution = -1;

	bool openMicrophone;
	int openMicrophoneUpload;

	QString microphoneName;
    QString microphoneTrueName;
	QString name;

	QString nickName;

	QString mobile;

	QString portrait;
	QString portrait2;

	int streamId;

    QString roomPass;
	int confBegin;
    int confEnd;
	QString userId;

	QString cropId;

    QString roomTitle;
    QString wbHost;
    QString roomNo;
	QString roomId;

	QString roomSdkNumber;

	QString roomSession;

	QString meetingHost;
	int meetingPort;

	QString streamHost;
	int streamPort;

	int audioSample;

	int audioChannel;

	int role;

	int type;

    QString LowerId;
    bool Stimulation;
    bool isShowJoinLeaveMsg;
    int outputVideo;
    int outputShare;
    bool noVideo;
	bool imageShareDialogShow;
    bool showWaterMark;
    bool lockMeeting;
    int roomAudio;
    int roomVideo;
    bool audioModel;
    bool visualSystem;
    double dpi;
	QString roomCreateId;
	QString roomCreateName;
	int roomShareType;
	QString mqttServerId;

	bool AudioEliminate;
	bool PeopleNoise;
	int aceindex;
    int stream_mode;
};

class RoomControl : public QObject
{
	Q_OBJECT

public:
	RoomControl();
	~RoomControl();

	static RoomControl* Get();

	RoomInfo roomInfo;

	QWidget* roomWidget;

	void SetAccountInfo(int fps, int bitrate, int outWidth, int outHeight);
	void SetAccountInfo(const char* account);

	int OpenRoom();

	void CloseRoom();

	bool RoomOpen();

	void ResetCanvas(int& width, int& height, int& bitrate, int& fps, bool isShare);

	int OpenCamera(void* winId, QString& msg);

	void CloseCamera(int enable = 0);

	void EnableSendVideo(int enable);

	int OpenAudio(QString& msg, int upload = 0);
    void CloseAudio(int upload = 1);

	bool OpenSpeaker(QString& msg);
	void CloseSpeaker();

	bool Picker(int stream_id, int type = 3);

	void UnPicker(int stream_id);

    void SetTrack(int stream_id,int track);
    void SetView(int stream_id,int track,void*);
    void SetMember(int stream_id, void* winId, int mask);
	int AddMember(int stream_id, void* winId, int mask, int oldMask);

    void RemovePlayer(void* winId, int stream_id, int mask);
	void RemoveMember(int stream_id, int mask);

	void StartShare(int type, const char* pic_url = nullptr);
	void StartShare2(int type, const char* pic_url = nullptr, const char* pic2 = nullptr);

	void StopShare();

	void ShareScreen(CapsData& data, void* winId = nullptr);

	void CloseShareScreen(int enable = 0);

	void EnableVideo(bool open);

	void EnableAudio(int open);

	int SendChatMsg(QString msg, QString tar = "");

	bool SetHostCtrlMic(const char*, int);
	bool SetHostCtrlMic2(bool v);
	bool SetHostCtrlCam(const char*, int);

	void AdminKickout(std::string id);

	void SetAccountNetWork(int delay, int rate, float first_lost, int signal);

	void SetStatInterval(int interval);

	int RestartMeeting(std::string host, int Port, std::string session);

	void SetAudioFirst(int stream_id, bool open);

	void DesktopImageShare(bool isOpenShare);

	void SetHostWaterMark(bool open);

	int WaterMarkShow(bool open, void* handle, int wid, int hei, const char* name, const char* text);
	int HeadUp(bool type);
	int HostHeadUp(const char* targetid, int type, bool result);
	int RoomMute(bool ret);
	int HostUsersMute(const char* users, bool ret);

	char* SdkVersion();

	void SetMyRole(int role);

	int RoomRecoveryHost(const char* target);

	int SetViewPlus(void* hwnd, bool open);

	void StopStartPicker(bool ret);

	void ReFlashHandle(void* hwnd);

	void AudioModel(bool open);

	void WaitingRoom(const char* c);
	void Call(const char* roomNo, bool restart, const char* data);

	void HostUpdateNickName(QString id, QString NickName);
	void MyUpdateNickName(QString NickName);
	int RoomMoveHost(QString user);
	int SetUnionHost(QString user, bool state);

	int RoomRecoveryHost(QString target);

	int StartProbe(const char* data);
	void DeleteProbe();

	void SetMcuDefaultTrick(int);
	void InitMqtt(const char* host, const char* token);

	bool SetMqttRoomServerid(const char* serverid);
	bool SetMqttVcsServerid(const char* serverid);
	void OpenCloseDenVoice(bool v);
	void GetAudioError();
	bool ReUpdateSpeaker(QString& msg);


	void SendVideoData(const unsigned char* streamData, int dataSize, long  pts, long dts, int trackId, int stmtype, int frmtype, int options);
	void SendAudioData(const unsigned char* streamData, int dataSize, long  ts, int stmtype, int frmtype, int options);

    QString test();
    void ReSetView(void*);
    void Test(void*);

    void setMemberExtend_info(QString tar,QString s);
    void StartDirectShare(QString ip,const char* s = nullptr);
    void StopDirectShare();
private slots:
	void OnTimer();
public:

    bool IsOpenMessage() { return message; }
	void OpenMessage(const char* account, const char* token, const char* address, int port, const char* serid);

	void CloseMessage();

	void Invite(const char* account, const char* roomNo);

	void Invite2(const char* account, const char* roomNo, const char* id);

	void InviteConfirm(const char* account, const char* initiator_id, const char* roomNo, bool res);
	int ShareFpiGet2();
	int MyFpiGet();
	int ShareFpiGet(int);
	void ChangeShareRect();

	bool GetIsProbe() { return isProbe; }


private:
	static RoomControl* client;

    QList<int> ClientWndList;
	bool roomOpen;

	bool isProbe;

	QTimer* timer;

	HCLIENT message;

	HOUTPUT output;

	HROOM room;

	HINPUT cameraInput;

	HINPUT audioInput;

	HINPUT screenInput;

	static int MessageEventFunc(HCLIENT client, int eventId, void* eventData, int dataSize, void* ctx);

	static int RoomEventFunc(HROOM client, int eventId, void* eventData, int dataSize, void* ctx);

	static int ProbeEventFunc(void* eventData, int dataSize, void* ctx);

    static int AudioStatusEventFunc(int iEvent, int wParam, int lParam, void* ptr, void* ctx);

    static int DirectShareEventFunc(int clientId,const char* cbData, void* ctx);
    static int FrameEventFunc(int linkid, const av_frame_s*, void* ctx);


    QMap<int,RecvFrameClass*> _recvMemberMap;
signals:
    int MessageEvent(HCLIENT hclient, int iEventid, std::string jsonString);
    int RoomEvent(HROOM hroom, int iEventId, std::string jsonString);
    int ProbeEvent(std::string jsonString);
    int AudioStatus(const char* data);
    int DirectShareEvent(int,QString data);
};

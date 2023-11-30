#ifndef VSC_H
#define VSC_H

typedef int HINPUT;         // 输入句柄
typedef int HOUTPUT;        // 输出句柄
typedef void* HROOM;        // 房间内的服务器连接句柄
typedef void* HCLIENT;      // 房间外的服务器连接句柄
typedef void* HANNOTATION;

// 错误码
#define VCS_R_OK                    0
#define VCS_R_ERROR                 1
#define VCS_R_CHECK_TOKEN_ERROR     2
#define VCS_R_ACCOUNT_NOTFOUND      3
#define VCS_R_ROOM_NOTFOUND         4

#define VCS_EVENT_ENTER             1   // 我进入房间 data: short result  0成功；
#define VCS_EVENT_EXIT              2   // 我退出房间 data: short result  0成功；
#define VCS_EVENT_NOTIFY_ROOM       3   // 房间信息变更   data: VCS_ROOM
#define VCS_EVENT_NOTIFY_ACCOUNT    4   // 其他成员帐号信息变更   data:VCA_ACCOUNT
#define VCS_EVENT_NOTIFY_KICKOUT    5   // 被提通知
#define VCS_EVENT_NOTIFY_ENTER      6   // 成员进入通知
#define VCS_EVENT_NOTIFY_EXIT       7   // 成员退出通知
#define VCS_EVENT_NOTIFY_BEGIN      8   // 会议开始通知
#define VCS_EVENT_NOTIFY_ENDED      9   // 会议结束通知
#define VCS_EVENT_NOTIFY_MYACCOUNT  10  // 我的帐号信息变更通知
#define VCS_EVENT_SEND_STATUS       11  // 上行网络状态
#define VCS_EVENT_RECV_STATUS       12  // 下线网络状态
#define VCS_EVENT_STREAM_CHANGED    13  // 码流变化通知
#define VCS_EVENT_STREAM_CTRL       14  // 主持人控制码流通知
#define VCS_EVENT_PASSTROUGH        15  // 透传通知
#define VCS_EVENT_CHAT              16  // 聊天消息
#define VCS_EVENT_HANDUP            17  // 举手消息处理
#define VCS_EVENT_RECOVERYHOST      18  // 收回主持人消息处理
#define VCS_EVENT_MOVEHOST          19  // 转移主持人消息处理
#define VCS_EVENT_UNIONHOST         20  // 设置联席主持人消息处理
#define VCS_EVENT_RECV_GEAR_CHANGE  21  // 接收综合档位改变
#define VCS_EVENT_RECV_AVERAGE_STATUS       22  // 平均接收
#define VCS_EVENT_MCU_CHANGE        23  // 后端mcu变化
#define VCS_EVENT_MCU_MCUSTATUS        24  
#define VCS_EVENT_DEBUG_LOG         100 // 调试信息
#define VCS_EVENT_START_SHARE       111 // 开始分享屏幕
#define VCS_EVENT_STOP_SHARING      112 // 停止分享屏幕
#define VCS_EVENT_REG_INVITE_NOTIFICATION       200     // 邀请入会通知
#define VCS_EVENT_REG_INVITE_CONFIRM            201     // 邀请入会回复
#define VCS_EVENT_WAITING_ROOM                  202     // 会议前握手广播
#define VCS_EVENT_WAITING_ROOM_UPDATE           203     // 状态更新广播
#define VCS_EVENT_PUSH_NOTIFICATION             204     // 应用内推送通知
#define VCS_EVENT_MEDIA_CONNECTED               205     // 流媒体连接成功
#define VCS_EVENT_MEDIA_RECONNECTED             205     // 流媒体连接成功
#define VCS_EVENT_CLIENT_CHAT                   206     // 应用内聊天
#define VCS_EVENT_CLIENT_CHAT_RSP               207     // 应用内聊天消息回执
#define VCS_EVENT_MEDIA_STREAM_RECV             208     // 收到流信息回调


#define VCS_SET_DEF_NOSEND 0x501  //系统初始化时设置音视频处于非上传状态

#define VCS_EVENT_REG_MEETING_BEGIN				209     // 会议开始通知（不需要在会议中）
#define VCS_EVENT_REG_MEETING_END				210     // 会议结束通知（不需要在会议中）
#define VCS_EVENT_REG_INVITE_CONF_NOTICE		211     // 会议白名单成员改变

#define VCS_EVENT_AUDIO_STATE_CHANGE			212
#define VCS_EVENT_VIDEO_STATE_CHANGE			213
#define VCS_EVENT_ROLE_STATE_CHANGE				214
#define VCS_EVENT_HANDUP_STATE_CHANGE			215
#define VCS_EVENT_MEMBER_ENTER_STATE			216
#define VCS_EVENT_MEMBER_CLOSE_STATE			217


#define VCS_EVENT_MQTT_CONTROL_RECONNECT		400


#define VCS_EVENT_NET_STATE                     300     // 网络状态
#define VCS_EVENT_FRAME_CHANGE                  301     
#define VCS_EVENT_AUDIO_CAP_ERROR               302		//麦克风采集异常
#define VCS_EVENT_CAMERA_CAP_ERROR              303		//摄像头采集异常

#define VCS_EVENT_GRAPHICS_INVALID              500  //显卡未安装
#define VCS_EVENT_DEV_CHANGED                   501  //设备改变事件
#define VCS_EVENT_DEV_DEF_CHANGED               502  //麦克风默认设备改变

#define VCS_EVENT_MEDIA_STREAM_CONNECT_SUCCESS		600		//连接流媒体成功（仅在调用VCS_EnterRoom 触发）
#define VCS_EVENT_MEDIA_STREAM_CONNECT_FAIL			601		//连接流媒体异常（仅在调用VCS_EnterRoom 触发）
#define VCS_EVENT_MEDIA_STREAM_CONNECT_RECONNECT	602		//从新连接上流媒体
#define VCS_EVENT_MEDIA_STREAM_CONNECT_LOST			603		//流媒体连接断开

#define VCS_SET_EXITRENDERTHREAD				0x10000	//释放渲染线程

#define VCS_DS_AVTIVE    0   // 正常
#define VCS_DS_CLOSED    1   // 关闭
#define VCS_DS_DISABLED  2   // 被主持人禁用

#define VCS_CR_MEMBER   0   // 普通成员
#define VCS_CR_Creator  1   // 创建人
#define VCS_CR_HOST     2   // 主持人

#define VCS_DEVICE_PC               1   // PC
#define VCS_DEVICE_ANDROID          2   // Android
#define VCS_DEVICE_IOS              3   // IOS
#define VCS_DEVICE_ANDROID_EMBEDDED 4   // 安卓一体机
#define VCS_DEVICE_EMBEDDED         5   // 录播主机

// 码流操作
#define OPERATION_ADD       1
#define OPERATION_REMOVE    0
#define OPERATION_UPDATE    2

#define VCS_INVITE_RSP_ACCEPTED 1
#define VCS_INVITE_RSP_REJECTED 2




#define VCS_PICKER_TRACKMASK_SYNC  0x1000   //选择轨道是否同步等关键帧


#define VCS_DEV_ADD 1
#define VCS_DEV_REMOVE 2
#define VCS_DEV_UPDATE 3

#define VCS_DEVTYPE_UNKNOWN 0
#define VCS_DEVTYPE_CAPTURER 1
#define VCS_DEVTYPE_RENDERER 2

#define VCS_DISPLAYCTL             0x4007  //控制显示[opt][VCS_SetOptParams 的第一个参数]
#define VCS_DISPLAYCTL_ROTATE      0x01  //控制显示旋转角度[wParam][VCS_SetOptParams 的第二个参数]
#define VCS_DISPLAYCTL_MIRROR      0x02  //控制显示镜像[wParam][VCS_SetOptParams 的第二个参数]
#define VCS_DISPLAYCTL_RESET       0x03  //恢复系统自动显示设置[wParam][VCS_SetOptParams 的第二个参数]

//下面是设置的值
#define VCS_R0    0     //[VCS_SetOptParams 的第三个参数]
#define VCS_R90   90    //[VCS_SetOptParams 的第三个参数]
#define VCS_R180  180   //[VCS_SetOptParams 的第三个参数]
#define VCS_R270  270   //[VCS_SetOptParams 的第三个参数]

#define VCS_GEN_MIRROR 0x01 //不镜像    //[VCS_SetOptParams 的第三个参数]
#define VCS_UD_MIRROR  0x02 //上下镜像  //[VCS_SetOptParams 的第三个参数]
#define VCS_LR_MIRROR  0x03 //左右镜像  //[VCS_SetOptParams 的第三个参数]

#define VCS_TRANS_NORMAL				0x01  //常规模式（SDK 推荐的工作模式,也是默认模式，“画布模式”支持采集多路视频（摄像头、桌面、文件或第三方流）以画中画的方式合成为单路视频发送，调用者可以随时更新画布布局。“画布模式”也支持采集多路音频，混音成单路音频编码发送。“画布模式”依赖于 transcoder 内置的画布能力。）
#define VCS_TRANS_JUST_FOR_SENDANDRECV	0x02 //纯数据收发模式,“纯数据收发模式”下，采集、播放以及编解码都由上层应用完成，SDK 只负责入会收发数据。
#define VCS_TRANS_MUTILSTREAMS			0x03 //多路流模式，“多流模式”支持发送多路独立的视频（以视频轨道号区分， 0 ~ 6），外加一路音频。独立编码发送
#define VCS_SET_TRANSMODE				0x500 //控制显示[opt][VCS_SetOptParams(VCS_SET_TRANSMODE,mode,0,NULL,NULL)]
//这三个模式必须再初始化（VCS_Init）后就要设置，不支持动态切换模式

typedef struct av_frame_s
{
	unsigned char* bits;	/* frame buffer */
	unsigned int bitslen;	/* frame length */
	unsigned int bitspos;   /* frame start pos within buffer */
	unsigned int medtype;	/* media type such as audio or video */
	unsigned int stmtype;   /* stream type such as h264, aac etc */
	unsigned int frmtype;   /* frame type such as key frame */
	unsigned int frmmisc;	/* misc character */
	unsigned int tmscale;	/* time scale for pts and dts */
	unsigned int frmsequ;	/* frame's sequence */
	long long pcr;			/* frame pcr */
	long long pts;			/* frame pts */
	long long dts;			/* frame dts */
	int dur;				/* frame duration */
	int track;				/* frame track */

	void* arg;

	int language;			/* frame language, add @ 2017/06/17 */

} av_frame_s;


// 视频数据结构
typedef struct __av_picture
{
	unsigned char* data[4];
	int stride[4];
	int width;
	int height;
	int fourcc;
	int framerate;

	int selfrelease; // please free me after call
	int continuebuf; // is continue buffer

	unsigned int stamp;
	unsigned int flag;
	unsigned int index;
	void* arg;
	int display_width;
	int display_height;
	int track;

} av_picture;

// 音频数据结构
// PCM data
typedef struct av_pcmbuff
{
	int channels;
	int samplerate;
	int track;
	unsigned int stamp;
	unsigned int flag;

	unsigned int pcmlen;
	unsigned char* pcmbuf;

	void* arg;

} av_pcmbuff;

// 房间事件回调
// iEvent: 事件ID
// pEventData: 事件数据,Json格式
// pContext: 回调上下文
// return: 
typedef int(*VCS_CBF_RoomEvent)(HROOM hroom, int iEvent, void* pEventData, int iDataSize, void* pContext);

typedef int(*VCS_PROBE_RoomEvent)(void* pEventData, int iDataSize, void* pContext);
// 数据回调
typedef int(*VCS_CBF_FrameEvent)(int clientId, int track, int canvas, void* pic, void* ctx);

// 音频回调
typedef int(*VCS_CBF_AudioEvent)(int clientId, void* cbData, void* ctx);
/*
	{
		"mid":"xxxx",//会议号，会议外就是空
		"uid":"xxxx",//userid
		"nickname":"mm"//账号-昵称
		"conf_log_id":"xxxx"//room/enter  conf().log_id();
		"trace_id":"xxx"//room/enter      
	}
	//type == 1 可以额外填写"vpn":1,0
*/
typedef int(*VCS_LogExtend_CallBack)(int type, char** cbData, int* size, void* ctx);
/*
	{
		"room_no":"xxxx",//会议号
		"conf_log_id":"xxxx"//room/enter  conf().log_id();
		"trace_id":"xxx"//room/enter      conf().trace_id();
		//.. 后期扩充
	}
*/
typedef int(*VCS_LogRealTimeExtend_CallBack)(char** cbData, int* size, void* ctx);
//上面2个回调用完后调用这个回调释放内存
typedef int(*VCS_LogExted_Free)(char** cbData);


// mqtt 回调
typedef int(*VCS_Mqtt_ConnectEvent)(int connectStatus, void* ctx);

// 音频事件回调的状态
#define VCS_RPT_AUDIOINF 0x22	// 音频用户对应的power
#define VCS_RPT_SPEECH_STATE 10 // 发言状态

// 音频事件回调
// iEvent:事件类型
// ptr:字符串
// ctx:上下文
typedef int(*VCS_CBF_AudioEventStatus)(int iEvent, int wParam, int lParam, void* ptr, void* ctx);

// display ctrl 透传(修复渲染问题)
typedef int(*DisplayCtrl)(int wParam, void* lParam, void* ctx);

typedef int(*VCS_CB_FrameEvent)(int clientId, const av_frame_s* cbData, void* ctx);
// SDK全局初始化，
// return: 0表示成功，<0表示失败 使用SDK前必须初始化
int __stdcall VCS_Init();

// SDK注销，自动清理所有内部资源,调用一次即
void __stdcall VCS_Cleanup();

// 创建输出
// mylinkId: 自己的房间id
// hWnd: 输出源绑定的窗口
// iWidth: outviewport
// iHeight: outviewport
// viewWidth: //viewport
// viewHeight: //viewport
// 当outviewport!=viewport 时 push到服务器的流进行scale
// iFps: 输出帧率
// iBitrate: 输出码率
// iSamplerate: 音频采样率
// pic: 设置垫片 NULL 不设置
// return: 成功返回输出ID,ID<0 失败
// 在这之间需要设置 服务器地址 房间号 AGC 等等
HOUTPUT __stdcall VCS_CreateOutput(const char* mylinkId, void* hWnd, int iWidth, int iHeight, int viewWidth, int viewHeight, int iFps, int iBitrate, int iSamplerate, const char* pic);

// 关闭输出
// hInput: 输出ID
void __stdcall VCS_CloseOutput(HOUTPUT hOutput);

// 是否显示合屏
// hOutput: 输出ID 参数无效
// iShow: 1-开始绘制; 0-停止绘制
// return: 0表示成功，<0表示失败
int __stdcall VCS_ShowOutput(HOUTPUT hOutput, int iShow);

// 设置AGC 重置AGC 需要重新初始化音频采集
// hOutput: 输出ID
// iAgc: 默认16000
// return: 0表示成功，<0表示失败
int __stdcall VCS_SetOutputAgc(HOUTPUT hOutput, int iAgc);

// 设置AEC 重置AEC 需要重新初始化音频采集
// hOutput: 输出ID
// iAec: 默认10
// return: 0表示成功，<0表示失败
int __stdcall VCS_SetOutputAec(HOUTPUT hOutput, int iAec);

// 在输出源中叠加输入源，此方案可在运行时动态添加，并且线程安全
// hOutput: 无效
// hInput: 源ID
// iLeft: 合屏位置（单位：像素）
// iTop:  合屏位置（单位：像素）
// iWidth: 目标宽（单位：像素）
// iHeight: 目标高（单位：像素）
// iAudio: 是否使用该输入源的audio(有声音源有效是 1-使用 0-不使用)
// iVideo: 是否使用该输入源的video(有声音源有效是 1-使用 0-不使用)
// iDeep: 缓存最少帧数目 这个是一个抖动源，
// 源音视频本身同步的很好，并且要求特别短延迟的源（例如摄像头采集），deep 设置为 1，也就画布针对该输入不再启用平滑缓存处理以减少延时；
// 对于一般的网络源，deep 设置为 0，由画布根据源的音视频同步情况自动调整，一般情况下，画布针对这种输入会启用平滑缓存（减少输入抖动），最少 8 帧左右，并且随着源异步情况会自动增加缓存；
// 对于屏幕采集这种没有音频的源, deep 推荐设置 3，也就缓存 3 帧。
// return: 0表示成功，<0表示失败
// 支持数量 4video+1audio
// audio iWidth=1  iHeight=1  iLeft=0  iTop=0
int __stdcall VCS_AddInput(HOUTPUT hOutput, HINPUT hInput, int iLeft, int iTop, int iWidth, int iHeight, int iAudio, int iVideo, int iDeep);

// 调整图像位置和尺寸
// w: 画布宽
// h: 画面高
// cx: 图像宽
// cy: 图像高
// iLeft:
// iTop:
// iWidth:
// iHeight:
void __stdcall VCS_AdjustPicture(int w, int h, int cx, int cy, int* iLeft, int* iTop, int* iWidth, int* iHeight);

// 修改输出源中叠加输入源
// hOutput: 输出句柄
// hInput: 出入句柄
// iLeft: 在输出源中叠加的位置（单位：像素）
// iTop: 在输出源中叠加的位置（单位：像素）
// iWidth: 在输出源中叠加的宽度（单位：像素）
// iHeight: 在输出源中叠加的高度（单位：像素）
// iAudio: 是否合成音频 1-合成；0-不合成
// iVideo: 是否合成视频 1-合成；0-不合成
// iDeep: 缓存最少帧数目
// return: 0表示成功，<0表示失败
// audio:iWidth=1 iHeight=1
int __stdcall VCS_UpdateInput(HOUTPUT hOutput, HINPUT hInput, int iLeft, int iTop, int iWidth, int iHeight, int iAudio, int iVideo, int iDeep);

// 在输出源中移除输入源 移除时对应的输入源会被关闭
// hOutput: 输出句柄
// hInput: 出入句柄
// return: 0表示成功，<0表示失败
int __stdcall VCS_RemoveInput(HOUTPUT hOutput, HINPUT hInput);

// 调整叠加合屏源Layout 只对视频源有效
// hOutput: 输出句柄
// szOrder: 输入源ID列席，用逗号分开 【1,2,20....】包含单独的audio
// return: 0表示成功，<0表示失败
int __stdcall VCS_SetViewLayoutInput(HOUTPUT hOutput, const char* szOrder);

// 更新输出 只有进行改更新时 最后推流到服务器的流才是更新后的out stream 在更新输入源是 必须调用该函数 使之生效
// hOutput: 输出句柄
// return: 0表示成功，<0表示失败
int __stdcall VCS_UpdateOutput(HOUTPUT hOutput);


// 打开秒表 用来测试使用
// iOpen: 1-打开；0-关闭
// return: 返回上次的状态，<0表示失败
int __stdcall VCS_OpenWatch(HOUTPUT hOutput, int iOpen);

// 支持"自适应"延迟
int __stdcall VCS_SetXdelay(int vcs_delay);

// 用于云端选择所需的用户流转发给与会者，命令格式：
// LMIC.picker=mask:linkmicId
// mask = 1 音频
// mask = 2 视频
// mask = 3 音视频
// mask =0 关闭转发
// client_id = 0 代表所有与会者
int __stdcall VCS_SetPicker(HOUTPUT hOutput, int mask, int client_id);

// No Picking Audio 接口
// stat:1 开启，无限制视频个数，由VCS_SetPicker来增加视频个数 
// stat:0 关闭，最多选择4方视频
int __stdcall VCS_NoPickAudio(int stat);

// 语音激励上报，用于服务端统计激励状态
// open:true 上报本地激励状态
// open:false 不上报本地激励状态
int __stdcall VCS_OpenVoiceExci(bool open);

// 杨声器开关
// on:true 开启
// on:false 关闭
int __stdcall VCS_SetSpeakerOn(bool on);

// 用于云端过滤特定用户的流不转发给与会者，命令格式：
// LMIC.filter=mask:linkmicId
// mask = 1 音频
// mask = 2 视频频
// mask = 3 音视频
// mask = 0 关闭过滤
// mask = 0x2000 保持激活当前，其他人停止转发
// client_id = 0 代表所有与会者
int __stdcall VCS_SetFilter(HOUTPUT hOutput, int mask, int client_id);

// 用于云端选择特定用户的特定的子码率（轨道）转发给与会者，命令格式：
// LMIC.track = mask:linkmicId
// mask：二进制选择掩码
// 1 1 1 1, 1 1 1 1
//               轨道 0
//             轨道 1
//           轨道 2
// 最多 7 个轨道
// 示例：
// mask = 1 选择转发视频轨 0
// mask = 2 选择转发视频轨 1
// mask = 5 选择转发视频轨 0 和 2
// client_id = 0 代表所有与会者
int __stdcall VCS_SetTrack(HOUTPUT hOutput, int mask, int client_id);

// 设置音频采样率
// sample: 采用率:22050/44100/48000
int __stdcall VCS_SetAudioSample(HOUTPUT hOutput, int sample);

// 设置音频通道数
// channels: 1-单声道；2-双声道
int __stdcall VCS_SetAudioChannels(HOUTPUT hOutput, int channels);

// 枚举视频设备列表
// szDevices: 设备列表文本，使用完之后需要VCS_Freep释放
// iSize: szDevices的内存字节数
// return: 返回szDevices的实际字节数
// dvideo = "XiaoMi USB 2.0 Webcam; 640X480; 160X120; 320X240; 1280X720";
// dvideo = "XiaoMi USB 2.0 Webcam; 640X480; 160X120; 320X240; 1280X720||KPwebcam; 640X480; 160X120; 320X240; 1280X720";
int __stdcall VCS_EnumVideoDevices(char** pszDevices, int* iSize);

// 枚举音频设备列表
// szDevices: 返回的音频设备列表字符串，使用完之后需要VCS_Freep释放
// iSize: szDevices的内存字节数
// return: 返回szDevices的实际字节数
// daudio = "麦克风(Realtek High Definition Audio)";
// daudio = "麦克风(Realtek High Definition Audio)||麦克风2(Realtek High Definition Audio)";
int __stdcall VCS_EnumAudioDevices(char** pszDevices, int* iSize);

// 枚举扬声器设备列表,使用完之后需要VCS_Freep释放
int __stdcall VCS_EnumSpeakerDevices(char** pszDevices, int* iSize);


// 枚举视频设备列表
// szDevices: 设备列表文本，使用完之后需要VCS_Freep释放
// iSize: szDevices的内存字节数
// return: 返回szDevices的实际字节数
// dvideo = "XiaoMi USB 2.0 Webcam; 640X480; 160X120; 320X240; 1280X720";
// dvideo = "XiaoMi USB 2.0 Webcam; 640X480; 160X120; 320X240; 1280X720||KPwebcam; 640X480; 160X120; 320X240; 1280X720";
int __stdcall VCS_EnumVideoDevices2(char** pszDevices, int* iSize);

// 枚举音频设备列表
// szDevices: 返回的音频设备列表字符串，使用完之后需要VCS_Freep释放
// iSize: szDevices的内存字节数
// return: 返回szDevices的实际字节数
// daudio = "麦克风(Realtek High Definition Audio)";
// daudio = "麦克风(Realtek High Definition Audio)||麦克风2(Realtek High Definition Audio)";
int __stdcall VCS_EnumAudioDevices2(char** pszDevices, int* iSize);

// 枚举扬声器设备列表,使用完之后需要VCS_Freep释放
int __stdcall VCS_EnumSpeakerDevices2(char** pszDevices, int* iSize);

// 设置扬声器
int __stdcall VCS_SetSpeakerDevice(const char* szDevice);

// 枚举当前所有的窗口句柄
// 枚举的结果中的capctx当不再需要时通过VCS_CloseWndCapture释放
// 返回的caps字符串当不再需要时通过VCS_Freep释放
int __stdcall EnumWndCaptures(char** caps);

// 绘制窗口缩略图
// capctx: 通过EnumWndCaptures方法获取
// hdc: 通过EnumWndCaptures方法获取
// x、y、cx、cy: 要绘制到hdc上的位置及宽高
void __stdcall VCS_DrawSnapshot(void* capctx, void* hdc, int x, int y, int cx, int cy);

// 释放窗口句柄
// capctx: 通过EnumWndCaptures方法获取的窗口句柄
void __stdcall VCS_CloseWndCapture(void* capctx);

// 是否显示源 在源初始化设置预览的时候设置有效 非DLL显示时无效
// streamId 创建输入源返回的ID
void __stdcall VCS_SetSrcStreamVisible(HINPUT input, bool show);

// camera 采集
// szDevice: 视频设备名称
// iWidth: 设备输入分辨率 //必须在camera 支持的分辨率中
// iHeight: 视频输入分辨率//必须在camera 支持的分辨率中
// iFps: 视频输入帧率
// return: 成功返回输入streamID，<0表示失败
// hWnd:指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示
HINPUT __stdcall VCS_CreateInputVideo(const char* szDevice, int iWidth, int iHeight, int iFps, void* hWnd);

// 创建音频输入句柄
// szDevice: 音频输入设备名称
// iChannel: 音频通道，1/2 channel=1;
// iSampleRate: 音频采样率  samplerate=48000
// return: 成功返回输入streamID，<0表示失败
HINPUT __stdcall VCS_CreateInputAudio(const char* szDevice, int iChannel, int iSampleRate);

// 创建屏幕输入句柄
// hWnd:指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示
// return: 成功返回输入句柄，<0表示失败
HINPUT __stdcall VCS_CreateInputScreen(void* hWnd);

// 创建屏幕、软件截图句柄
// hWnd: 指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示
// hCapWnd：要截图的窗口句柄，NULL表示截取整个桌面
// rect：窗口位置字符串 x,y,cx,cy  截取全屏下才有效
HINPUT __stdcall VCS_CreateInputScreen2(void* hWnd, void* hCapWnd, const char* rect);
HINPUT __stdcall VCS_CreateInputScreen3(void* hWnd, void* hCapWnd, const char* rect, const char* ext);

// 创建网络流输入，支持RTMP/HLS/RTSP等
// 支持: PC,Linux,iOS,Android
// szUrl: 网络流地址
// return: 成功返回输入句柄，<0表示失败
// hWnd:指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示
HINPUT __stdcall VCS_CreateInputUrl(const char* szUrl, void* hWnd);

// 创建本地文件输入 支持MP4 AVI
// 支持: PC,Linux,iOS,Android
// szFilepath: 文件绝对路径 [C:\\video\tv.mp4]
// return: 成功返回输入句柄，<0表示失败
// hWnd:指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示
HINPUT __stdcall VCS_CreateInputFile(const char* szFilepath, void* hWnd);

// 关闭输入源句柄
// hInput: 输入源句柄
// 成功返回-1 >0 未关闭 关闭对应的输入源
int __stdcall VCS_CloseInput(HINPUT hInput);

// 获取错误码
// return 最近发生的错误码
int __stdcall VCS_GetLastError();

// 设置错误码，支持TLS线程局部存储
// 支持: PC,Linux,iOS,Android
// iError: 错误码
void __stdcall VCS_SetLastError(int iError);

// 进入房间前调用
int __stdcall VCS_Room_Init();

// 退出房间后调用
void __stdcall VCS_Room_Cleanup();

// 创建房间句柄
// 支持: PC,Linux,iOS,Android
// szAddr: 会议服务器地址
// iPort: 会议服务器端口
// szRoomNo: 房间号
// szSessionId: 进入授权码【token】
// return: 成功返回房间号，NULL表示失败
HROOM __stdcall VCS_CreateRoom();

// 设置和获取房间信息
void __stdcall VCS_SetRoomInfo(HROOM hRoom, const char* room);
int __stdcall VCS_GetRoomInfo(HROOM hRoom, char** room, int* size);

// 设置和获取登录信息
//upload=1,立即上传，upload=0 延迟上传
void __stdcall VCS_SetAccountInfo(HROOM hRoom, const char* account, int upload);
int __stdcall VCS_GetAccountInfo(HROOM hRoom, char** account, int* size);

// 设置认证信息
void __stdcall VCS_SetSession(HROOM hRoom, const char* szSession);

// 设置服务器地址
void __stdcall VCS_SetRoomServer(HROOM hRoom, const char* szAddr, int iPort);
// 设置Mqtt服务器地址(mqtt 优先级高于普通服务器)
int __stdcall VCS_InitMqttServer(const char* szAddr, const char* token);
int __stdcall VCS_UnitMqttServer();
int __stdcall VCS_SetRoomMqtt(HROOM hRoom, const char* serverid);
int __stdcall VCS_SetVcsMqtt(HCLIENT hclient, const char* serverid);
int __stdcall VCS_SetMqttCallBack(VCS_Mqtt_ConnectEvent back,void* ext);

// 设置流媒体地址
void __stdcall VCS_SetMediaServer(HROOM hRoom, const char* szAddr, int iPort);

// 设置事件回调[可选设置]
// 使用请参照具体demo
// hRoom: 房间句柄
// cbfRoomEvent: 事件回调
// pContext: 回调上下文
// return: 0表示成功，<0表示失败
int __stdcall VCS_SetRoomEvent(HROOM hRoom, VCS_CBF_RoomEvent cbfRoomEvent, void* pContext);

// 设置房间的输出句柄
// hRoom: 房间句柄
// hOutput: 窗口
// return: 0表示成功，<0表示失败
int __stdcall VCS_SetRoomOutput(HROOM hRoom, HOUTPUT hOutput);

// 正式开始建立连接，进入房间
// 支持: PC,Linux,iOS,Android
// hRoom: 房间句柄
// myClientId: 设置自己在房间中的唯一标识
// return: 成功返回>=0,<0表示错误
int __stdcall VCS_EnterRoom(HROOM hRoom);

// 退出房间
// 支持: PC,Linux,iOS,Android
void __stdcall VCS_ExitRoom(HROOM hRoom);

// 退出房间（超时）
// 支持: PC,Linux,iOS,Android
// ms: 超时毫秒数，小于0表示一直等待
// return 0表示成功
int __stdcall VCS_TimedExitRoom(HROOM hRoom, int ms);

// 设置成员视频显示到窗口
// 使用请参照具体demo
// hRoom: 房间句柄
// iClientId: 成员连接ID
// iTrack:  轨道ID
// hWnd: 窗口句柄，NULL则停止绘制
// return: 1表示成功，<0表示失败
int __stdcall VCS_SetClientWnd(HROOM hRoom, int iClientId, int iTrack, void* hWnd);

// 发送广播消息
// 支持: PC,Linux,iOS,Android
// hRoom: 房间句柄
// iMyClientId: 自己的连接ID
// szMessage: 文本消息
// 使用请参照具体demo
int __stdcall VCS_SendMessage(HROOM hRoom, int iMyClientId, const char* szMessage);

// 设置自己是否发送视频
// 支持: PC,Linux,iOS,Android
// hRoom: 房间句柄
// iMyClientId: 自己的连接ID
// iEnabled: 1-启用；0-关闭
// return: 0表示成功，<0表示失败
// 使用请参照具体demo
int __stdcall VCS_EnableSendVideo(HROOM hRoom, int iMyClientId, int iEnabled);

// 设置自己是否发送音频
// 支持: PC,Linux,iOS,Android
// hRoom: 房间句柄
// iMyClientId: 自己的连接ID
// iEnabled: 1-启用；0-关闭
// return: >=0表示成功，<0表示失败
//使用请参照具体demo
int __stdcall VCS_EnableSendAudio(HROOM hRoom, int iMyClientId, int iEnabled);

// 设置自己是否接收对方视频
// 支持: PC,Linux,iOS,Android
// hRoom: 房间句柄
// iOtherClientId: 对方的连接ID，0表示所有在同一房间内除了自己的所有人
// iEnabled: 1-启用；0-关闭
// return: >=0表示成功，<0表示失败
int __stdcall VCS_EnableRecvVideo(HROOM hRoom, int iOtherClientId, int iEnabled);

// 设置自己是否接收对方音频
// 支持: PC,Linux,iOS,Android
// hRoom: 房间句柄
// iOtherClientId: 对方的连接ID，00表示所有在同一房间内除了自己的所有人
// iEnabled: 1-启用；0-关闭
// return: >=0表示成功，<0表示失败
int __stdcall VCS_EnableRecvAudio(HROOM hRoom, int iOtherClientId, int iEnabled);

// 系统时延设置网络抗抖动等级.(不允许动态设置)
// 支持: PC,Linux,iOS,Android
/*
		超短（0）单向延迟 120 ms 左右，这种模式下没有丢包补偿机制，并且编码关闭了 B 帧，一般不建议实际使用；
		短  （1）单向延迟 200 ms 左右，单次丢包补偿，B 帧为 1，双向对讲环境下可以使用；
		中  （2）单向延迟 350 ms 左右，两次丢包补偿，B 帧为 1，双向对讲环境下推荐使用；
		长  （3）单向延迟 600 ms 左右，三次丢包补偿，B 帧为 3，这种模式仅用于单向收看，双向对讲环境下不建议使用；
*/
// hOutput: 输出句柄
// iPlc: 补偿级别：0，1，2， 默认为1
// return: 返回 实际的iPlc
int __stdcall VCS_SetRoomPlc(HROOM hRoom, int iPlc);

// 设置码率自适应 在收到接连成功VCS_CONNECTED 后设置有效 该函数可以进行多次设置
// 支持: PC,Linux,iOS,Android
// hOutput: 输出句柄
// iSecond: 0-关闭自适应；开启[>=3]
// return: 1 成功
int __stdcall VCS_SetRoomXBitrate(HROOM hRoom, int iSecond);

// 获取上传的状态 speed delay Buffers Status Overflow
// 定时器 每一秒钟获取即可
void __stdcall VCS_GetUploadStatus();

// 获取接收流状态情况
// 定时器 每一秒钟获取即可
void __stdcall VCS_GetRecvStatus();

// 主持人禁用音视频
int __stdcall VCS_HostCtrl(HROOM hRoom, const char* szTargetId, int* iAudioState, int* iVideoState);

// 主持人踢人
int __stdcall VCS_HostKickout(HROOM hRoom, const char* szTargetId);

// 主持人打开/关闭电子白板
int __stdcall VCS_HostWhiteBoard(HROOM hRoom, int bOpen);

// 切换码流
int __stdcall VCS_StreamChange(HROOM hRoom, const char* strm, int o);

// 主持人切换码流
int __stdcall VCS_HostStreamChange(HROOM hRoom, const char* target_id, const char* strm, int o);

// 透传
int __stdcall VCS_Passthrough(HROOM hRoom, const char* target_id, const char* msg, int msg_size);

// 聊天消息  target_id：接收者ID  type：消息类型  msg：消息内容
int __stdcall VCS_Chat(HROOM hRoom, const char* target_id, int type, const char* msg);
int __stdcall VCS_Chat2(HROOM hRoom, const char* target_id,int id_size, int type, const char* msg,int msg_size);

// 开启双流
// multi: 1-开启；0-关闭
void __stdcall VCS_SetMultiTrack(HROOM hRoom, int multi);

// 开启音频Opus编码
// opus:1-开启；0-关闭
void __stdcall VCS_SetOpusCodec(HROOM hRoom, int opus);

//设置网络状态统计间隔，0-关闭 (单位:秒)
void __stdcall VCS_SetStatInterval(HROOM hRoom, int interval);

// 释放内存
void __stdcall VCS_Freep(void** p);

// 创建注册服务器连接句柄
HCLIENT __stdcall VCS_CreateClient(const char* account_id, const char* token, const char* address, int port,
	VCS_CBF_RoomEvent cbfRoomEvent, void* pContext);

int __stdcall VCS_ClientChat(HCLIENT hclient, const char* JsonMsg);

// 开始连接注册服务器
int __stdcall VCS_Open(HCLIENT hclient);

// 关闭服务器连接
void __stdcall VCS_Close(HCLIENT hclient);

// 发起邀请
int __stdcall VCS_Invite(HCLIENT hclient, const char* tar_id, const char* room_no);

//发起邀请2 initiator_id会在确认中带上。
int __stdcall VCS_Invite2(HCLIENT hclient, const char* tar_id, const char* room_no, const char* initiator_id);

// 邀请确认
int __stdcall VCS_InviteConfirm(HCLIENT hclient, const char* id, const char* initiator_id, const char* room_no, int resp);

// 呼叫 
// room_no: 房间号
// restart: true(重新呼叫) false(追加呼叫)
// accounts: 呼叫对象的集合(json数组，类型为josn结构体)
int __stdcall VCS_Call(HCLIENT hclient, const char* room_no, bool restart, const char* accounts);

//// 取消呼叫(弃用，用VCS_CallCancel2这个)
//// room_no: 房间号
//// target_id: 目标id(json数组，类型为string)
int __stdcall VCS_CallCancel(HCLIENT hclient, const char* room_no, const char* target_id);

// 取消呼叫
// room_no: 房间号
// target_id: 目标id(json数组，类型为string)
int __stdcall VCS_CallCancel2(HCLIENT hclient, const char* room_no, const char* cas);

// 会议室等候
// account: 呼叫对象(josn 结构体)
int __stdcall VCS_WaitingRoom(HCLIENT hclient, const char* account);

// 发送应用内推送
// receivers: 接收者用户ID集合(json数组，类型为string)
// message: 消息内容
int __stdcall VCS_PushRequest(HCLIENT hclient, const char* receivers, const char* message);

// 设置加载的dll目录(当加载不到dll时调用)
void __stdcall VCS_SetCurrentDir(const char* path);
//音柱信息回调
void __stdcall VCS_SetAudioEventStatusCallback(VCS_CBF_AudioEventStatus cbf, void* ctx);
//透传回调信息到SDK
int __stdcall VCS_SetCtrlDisplay(int wParam, void* lParam);

//透传回调信息回调设置
int __stdcall VCS_SetCtrlDisplayCallback(DisplayCtrl cb, void* ctx);

// 开始分享屏幕
// type:1-电子白板;2-图片;3-桌面窗口
// pic_url:分享图片时的图片地址
int __stdcall VCS_StartShare(HROOM hroom, int type, const char* pic_url);

// 开始分享屏幕
// type:1-电子白板;2-图片;3-桌面窗口
// pic_url:分享图片时的图片地址
// pic_url2:分享图片时的相对图片地址
int __stdcall VCS_StartShare2(HROOM hroom, int type, const char* pic_url, const char* pic_url2);
// 停止分享屏幕
int __stdcall VCS_StopSharing(HROOM hroom);

// 渲染事件
int __stdcall VCS_DisplayFrame();



struct anylive_setopt_s
{
	int lparam;
	int wparam;
	void* ptr;
};


#define VCS_DESTROY_WIND  401 // 窗口移除时通知SDK释放关联的显示资源
#define VCS_REFRESH_WIND  402 // 0x11 refresh window HWND

#define VCS_DYNA_SIZE    0x1001 // 启用动态更新画布大小、帧率和码率
#define VCS_RESET_SIZE   0x1002 // 重置画布大小【opt=VCS_RESET_SIZE,wparam=width,lparam=height】
#define VCS_RESET_CPARAM 0x1003 // 设置画布参数 【opt=VCS_RESET_CPARAM】 

#define VCS_PARAM_FRAMES  0x01 // 重置帧率
#define VCS_PARAM_BITRATE 0x02 // 重置码率

#define VCS_OPT_XBITPAUSE       0x01e //共享桌面时可以停止码率自适应
#define VCS_OPT_PREVPAUSED	    0x014   // pause preview track  //(小码率视频暂停/恢复)
#define VCS_OPT_MAXBITRATE      0x015  //设置最大码率[初始化SDK后,入会前设置 默认最大2000kps  单位kps]
#define VCS_OPT_XBITMODE        0x01f   // 2-共享屏幕模式    0-摄像头模式
#define VCS_OPT_AUDIOPRIO       0x030   // 音频优先 0关闭 1开启 带视频分享流stream id.
#define VCS_OPT_SCAPOPER        0x302 // screen caption operate
#define VCS_OPT_WATERMARK_XY    0x6000 //水印显示位置
#define VCS_OPT_WATERMARK_SIZE  0x6001 //水印显示大小
#define VCS_OPT_WATERMARK_INFO  0x6002 //水印参数
#define VCS_OPT_FRAMERATE   0x103  //增加编码帧率查询接口
#define VCS_OPT_ECPA        0x104  //ECPA 数据加密
#define VCS_OPT_CHROMA      0x105  //设置采集色域格式

#define VCS_CHK_ACAPTURE    0x305   // audio capture monitor   //音频采集测试  1 采集 2播放 3一起监测。
#define VCS_ACAPTURE_MSG	0x4E524157 // audio capture monitor info callback   // wparam: 0x01 [audio capture paused] 			// 0x11 [audio capture resumed]

#define MJPEG_CHROMA      0x01 //用 MJPG 采集图像
#define NOMAL_CHROMA      0x02 //其他格式

#define VCS_AUDIO_ENCODE_BITRATE 0x3000 //音频编码频率设置 默认32K init时调用。
#define VCS_FRAME_STATUS         0x4001 //流消息通知 
#define VCS_WRITELOG_CTRL        0x4003 //设置日志目录
#define VCS_STDOUT_TO_FILE		 0x7000 //黑窗口日志
#define VCS_USE_SOFTWARE_AEC	 0x4004 //软件回音消除
#define VCS_USE_F_DEN_VOICE		 0x4005 //人声消除
#define VCS_DISPLAY_RENDERGB	 0x4008 //播放器颜色刷新
#define VCS_EVENT_PROBE_INFO	 0x8

#define VCS_SET_INTENSITY 0x5000  //设置增强参数标志

#define LOW_INTENSITY     0x5050 //低强度
#define GENERAL_INTENSITY 0x5051 //一般强度
#define HIGH_INTENSITY    0x5052 //高强度
#define NO_INTENSITY      0x5053 //关闭增强
#define ANYLIVE_EVENT_PROBE_INFO


// 扩展参数接口，用于以后参数 和动作扩展，避免新功能还需要增加额外接口
int __stdcall VCS_SetOptParams(int opt, int wParam, int lParam, void* ptr, void* ctx);

//心跳超时等异常退出会议，重新入会，
//hroom 房间句柄
//host  重新入会后的服务器ip
//port  重新入会后的服务器端口号
//session 重新入会后的服务器session
//return 0 成功  -1 失败。
int __stdcall VCS_ReStartMeeting(HROOM hroom, const char* host, int port, const char* session);

//房间水印开关
//hroom 房间句柄
//open  是否开启水印
int __stdcall VCS_HostWaterMark(HROOM hroom, int open);

//窗口显示水印
//open          是否开启水印
//x             水印x 坐标（绝对坐标）
//y             水印y 坐标（绝对坐标）
//wid           水印宽
//hei           水印高
//handle        窗口句柄
//text          水印文字内容
int __stdcall VCS_WaterMark_Show(int open, int wid, int hei, void* handle, const char* text1, const char* text2);

//窗口显示水印
//open          是否开启水印
//x             水印x 坐标（绝对坐标）
//y             水印y 坐标（绝对坐标）
//wid           水印宽
//hei           水印高
//handle        窗口句柄
//text          水印文字内容
int __stdcall VCS_WaterMark_Show2(int open, int wid, int hei, void* handle, const char* text1, const char* text2, int fontsize);


//视频自定义插件
//此方法类似于VCS_CreateInputVideo,只负责视频初始化 返回的视频句柄后需要VCS_AddInput 等一系列操作。
//
// 目前视频暂时未测试,也没有对应的dll插件（不要调用）
//
//DeviceName  摄像头设备名称，通过 EnumVideoDevices获取
//iWidth   摄像头分辨率宽
//iHeight  摄像头分辨率高
//iFps  摄像头帧数
// handle  摄像头显示的窗口句柄
//return  返回视频句柄
int __stdcall VCS_CreateInputVideoByUrl(const char* DeviceName, int iWidth, int iHeight, int iFps, void* handle);

//音频采集自定义插件
//此方法类似于VCS_CreateInputAudio,只负责视麦克风始化 返回的采集句柄后需要VCS_AddInput 等一系列操作。
//目前调用后悔调用plugin/mycap_receiver.dll 进行采集声音，并传输声音，此dll 只采集声音并不对声音进行任何其他操作。
//DeviceName        摄像头设备名称，通过 EnumAudioDevices获取
//audioChannel,     声道数，1
//audioSample       采样频率，48000
//返回              返回采集句柄,（小于0 异常）
int __stdcall VCS_CreateInputAudioByUrl(const char* DeviceName, int audioChannel, int audioSample);

//主持人举手消息处理
//当主持人处理举手消息时调用,调用后指定目标成员将收到VCS_EVENT_HANDUP 事件消息，
//请在VCS_EVENT_HANDUP 做出相对于的同意拒绝处理
//hRoom                         房间句柄
//target_id                     目标用户id 
//type                          处理的举手类型 //0 正常不举手 // 1 禁言举手
//result                        主持人处理举手结果 0 同意，其他拒绝
//返回                          0 成功 -1房间句柄为空
int __stdcall VCS_Host_HandUp(HROOM hRoom, const char* target_id, int type, int result);

//成员发起举手
//hRoom                         房间句柄
//type                          举手类型 //0 正常不举手 // 1 禁言举手
//返回                          0 成功，-1房间句柄为空, -100设置信息异常，-101 更新状态异常
int __stdcall VCS_HandUp(HROOM hRoom, int type);

// 主持人禁用音视频(支持多个用户)
//hRoom                         房间句柄
//szTargetId                    需要控制的用户id，多个可以用;隔开
//iAudioState                   修改音频状态 NULL为不修改
//iVideoState                   修改视频状态 NULL为不修改
//返回                          0 成功,-1房间句柄为空，-2用户id为空
int __stdcall VCS_HostCtrls(HROOM hRoom, const char* szTargetId, int* iAudioState, int* iVideoState);

//主持人房间禁用音视频开关
//hRoom                         房间句柄     
//szTargetId                    会议id
//iAudioState                   修改音频状态 NULL为不修改
//iVideoState                   修改视频状态 NULL为不修改
//返回                          0 成功,-1房间句柄为空，
int __stdcall VCS_HostRoomCtrl(HROOM hRoom, const char* szTargetId, int* iAudioState, int* iVideoState);

//版本号
//返回            版本号信息
char* __stdcall VCS_Version();

//房间移交主持人
//设置后目标成员，与自己收到VCS_EVENT_NOTIFY_MYACCOUNT role角色变化。
//应用主动更新 VCS_SetAccountInfo role 信息
//hRoom                         房间句柄     
//szTargetId                    移交主持人的id
//返回                          0 成功,-1房间句柄为空，
int __stdcall VCS_RoomMoveHost(HROOM hRoom, const char* szTargetId);

//设置联席主持人
//设置后目标成员，与自己收到VCS_EVENT_NOTIFY_MYACCOUNT role角色变化。
//应用主动更新 VCS_SetAccountInfo role 信息
//hRoom                         房间句柄     
//szTargetId                    移交主持人的id
//state                         是否设置联席主持人
//返回                          0 成功,-1房间句柄为空，
int __stdcall VCS_SetUnionHost(HROOM hRoom, const char* szTargetId, int state);

//收回主持人
//会议发起人可以通过此方法收回主持人。
//设置后目标成员，与自己收到VCS_EVENT_NOTIFY_MYACCOUNT role角色变化。
//应用主动更新 VCS_SetAccountInfo role 信息
//hRoom                         房间句柄     
//szTargetId                    主持人id,为空表示回收所有主持人，无主持人也可以为空
//返回                          0 成功,-1房间句柄为空，
int __stdcall VCS_RoomRecoveryHost(HROOM hRoom, const char* szTargetId);

//语音模式
//设置为true 将不进行接收成员视频流（共享流除外）
//同时成员视频也将不能被打开，只保留音频
//open            //0 关闭 1启用
//返回            //0 成功 -1房间句柄为空
int __stdcall VCS_AudioModel(HROOM hRoom, int open);


int __stdcall EnumVideoDevices(char* szDevices, int iSize);
int __stdcall EnumAudioDevices(char* szDevices, int iSize);
int __stdcall EnumSpeakerDevices(char* szDevices, int iSize);

int __stdcall VCS_ChangeShareRect(HINPUT input, const char* url);

int __stdcall VCS_RelaseDisplayerByUser(void* hWnd, int streamId, int track);


int __stdcall VCS_Probe_CallBack(VCS_PROBE_RoomEvent Probe, void* ext);
int __stdcall VCS_Probe(const char* probe_data);
int __stdcall VCS_DeleteProbe();

int __stdcall VCS_GetDisplayFpsInfo(char* outinfo, int iSize);

int __stdcall VCS_SetNickName(HROOM hRoom, const char* nickname);
int __stdcall VCS_SetExtend(HROOM hRoom, const char* extend);
int __stdcall VCS_HostSetMemberName(HROOM hRoom, const char* tarid, const char* tar_nickname);
int __stdcall VCS_HostSetMemberExtend(HROOM hRoom, const char* tarid, const char* extend);
int __stdcall VCS_MCUDefaultTrack(int defaultTrackMask);
int __stdcall VCS_SetRelieveAstate(HROOM hRoom, int RelieveAstate);

int __stdcall VCS_MicPermissions();

int __stdcall VCS_Mic_Error_NoDeal(HROOM hRoom);
int __stdcall VCS_Speak_Error_NoDeal(HROOM hRoom);

int __stdcall VCS_Stream_Multiple(int open);

int __stdcall VCS_PushVideoEncoderStream(const unsigned char* streamData, int dataSize, long  pts, long dts, int trackId, int stmtype, int frmtype, int options);
int __stdcall VCS_PushAudioEncoderStream(const  unsigned char* streamData, int dataSize, long ts, int stmtype, int frmtype, int options);

int __stdcall VCS_CheckMqtt();
int __stdcall VCS_SetStreamLogPath(const char* path);

int __stdcall VCS_ReFlashColorView(void* hwnd, int r, int g, int b);
int __stdcall VCS_ReFlashLastView(void* hwnd);
int __stdcall VCS_SetFrameEvent(HROOM hRoom, VCS_CB_FrameEvent e, void* ext);
/*
{
	"host_name":"hiklink",//父级昵称
	"host_version":""//父级版本
	"app_version":""//你的版本
	"time":1231231,//开始时间（毫秒数）
	"upLoadInterval":60,//(非必填)秒，上传间隔默认60
	"upLoadSave":1,		//(非必填)1保存，2不保存 默认不保存
	"secret_key":"123",	//(非必填)默认123，压缩包密码
	//.. 后续扩充
}
*/
int __stdcall VCS_StartLogger(const char* url, const char* json, VCS_LogExtend_CallBack back, VCS_LogRealTimeExtend_CallBack back2, VCS_LogExted_Free freeback, void* ctx);
/*
request: //请求api
{
	"logType":"request",	//类型
	"method":"post",
	"scheme":"http",
	"host":"www.",
	"target":"xxx",
	"duration":"xxxx",		//url请求时长，
	"status_code":"xxx",	//utl 请求状态码
	"req":"xxx",			//url参数 ，例如pass=xxx&account=xxx
	"rsp_code":"xxx",		//url api 返回code
	"rsp_msg":"xxx",		//url api 返回msg(错的时候才有)
	"rsp_body":"xxx"
}

init:	//入会初始化
{
	"logType":"init",		//类型
	"audio_status":"x"		//入会麦克风 1开 0关
	"video_status":"x"		//入会摄像头 1开 0关
}

share:	//共享图片发送图片
{
	"logType":"share",		//类型
	"pic_url":"xxx"			//图片请求地址
	"duration":"xxx"		//图片时长
}

//主动点击事件
{
	"logType":"xxx",		//logType
	"module":"xxx"			//uname
	"body":"xxx"			//描述
	"st":"LogLevel"			//日志等级
}

*/
int __stdcall VCS_AppendLog(const char* json);
typedef int(*VCS_DirectShare_Event)(int clientId, const char* cbData, void* ctx);

#define VCS_DIRECTSHAREEVENT_LOG				(0x1000|0)	//调试信息
#define VCS_DIRECTSHAREEVENT_SHARE_STATE		(0x1000|1)	//共享状态
#define VCS_DIRECTSHAREEVENT_MEDIA_CLOSED       (0x1000|2)	//流媒体断了
#define VCS_DIRECTSHAREEVENT_MEDIA_FINISH       (0x1000|3)	//流媒体连接成功
#define VCS_DIRECTSHAREEVENT_SEND_STATUS		(0x1000|4)	//发送档位
#define VCS_DIRECTSHAREEVENT_RECV_KEY			(0x1000|5)	//收到盒子按键
#define VCS_DIRECTSHAREEVENT_CAP_ERROR			(0x1000|6)	//采集音频异常
int __stdcall VCS_SetDirectShareCallBack(VCS_DirectShare_Event e, void*);
/*
{
	"nickname":"test",			//投屏用户昵称，默认:test
	"bitrate" : 5000,			//投屏码率	默认:5000
	"fps" : 16,					//投屏帧率（不支持）默认:16
	"rect" : "0,0,1920,1080",	//投屏区域选择 默认:0,0,1920,1080
	"streamtimeout" : 120,		//流媒体超时时间	默认:120
	"sharePix" : 20,			//屏幕不动检测算法采样间隔  默认:20
	"audioCap" : 1,				//发送音频		默认:1
	"initwheel" : 1,			//监控鼠标滚轮	默认:1
	"recvControl" : 0,			//开关投屏设备反向控制 默认:0
	"lvbo" : 1,					//开关双向滤波	默认:1
	"upy" : 0,					//亮度增强		默认:10
	"mylinkId" : 12343323		//streamid，	默认8位随机数
	"ECPA":1					//投屏数据加密	默认0，（0不加密，1加密）
}
*/
int __stdcall VCS_DirectCreateShare(const char* ip, const char* json);
#define VCS_DIRECTSHARE_SETTING_RECT_I			(0x2000|1)	//修改采集尺寸（目前不支持）
#define VCS_DIRECTSHARE_SETTING_FPS_I			(0x2000|2)  //修改采集帧率（目前不支持）
#define VCS_DIRECTSHARE_SETTING_AUDIOCAP_I		(0x2000|3)  //修改是否采集系统音频
#define VCS_DIRECTSHARE_SETTING_RECVCONTROL_I	(0x2000|4)  //修改是否接收控制指令
#define VCS_DIRECTSHARE_SETTING_SAVE264_I		(0x2000|6)  //存储264
int __stdcall VCS_SetDirectShareSetting(int type, int idata, const char* sdata);
int __stdcall VCS_DirectCloseShare();
int __stdcall VCS_AutoAudioCapValue(int, const char* data);
int __stdcall VCS_CamPermissions();


#define VCS_RECORD_TYPE_R		0x01// recording   后 PCM
#define VCS_RECORD_TYPE_AEC		0x02// AEC 处理后     PCM
#define VCS_RECORD_TYPE_DEN		0x04// DEN 处理后     PCM
#define VCS_RECORD_TYPE_PRO		0x08// 所有处理后     PCM （最终送去编码的 PCM）
#define VCS_RECORD_TYPE_P		0x40// playbacking 前 PCM

#define VCS_RECORD_TYPE_RECV_AAC		0x100// 收流的aac
#define VCS_RECORD_TYPE_RECV_PCM		0x200// 收留解码的pcm

#define VCS_RECORD_TYPE_NON		0x00// 尽设置目录，不进行录制
#define VCS_RECORD_TYPE_ALL		(VCS_RECORD_TYPE_RECV_PCM|VCS_RECORD_TYPE_RECV_AAC|VCS_RECORD_TYPE_R|VCS_RECORD_TYPE_AEC|VCS_RECORD_TYPE_DEN|VCS_RECORD_TYPE_PRO|VCS_RECORD_TYPE_P)// 所有发送相关音频
int __stdcall VCS_SetMicRecord(int type, const char* path);
int __stdcall VCS_SetMicDynaRecordAEC(int open);

//异常回调
//code		错误码
//msg		错误描述
//ctx		上下文指针
typedef void(*CustomMqttFailure)(int code ,const char* msg, void* ctx);
//成功回调
//ctx		上下文指针
typedef void(*CustomMqttSuccess)(void* ctx);
//收到消息回调
//topic		收到的消息主题
//msg		消息内容
//msg		消息长度
//ctx		上下文指针
typedef void(*CustomMsgArrived)(const char* topic, const char* msg, int msg_size, void* ctx);
//设置消息回调
//back		回调函数
//ctx		上下文指针
int __stdcall VCS_SetCusomMsgArrivedListener(CustomMsgArrived back, void* ctx);
//设置主题订阅
//topic		订阅的主题
//qos		订阅等级
//failure	错误回调
//success	成功回调
//ext		上下文指针
int __stdcall VCS_SubscribeCustomTopic(const char* topic, int qos, CustomMqttFailure failure, CustomMqttSuccess success,void*ext);
//取消主题订阅
//topic		订阅的主题
int __stdcall VCS_UnSubscribeCustomTopic(const char* topic);
//发送消息
//msg		发送的消息
//msg_size	发送消息的长度
//qos		消息等级
//topic		主题
//failure	错误回调
//success	成功回调
//ext		上下文指针
int __stdcall VCS_PublishCustomMsg(const char* msg,int msg_size,int qos,const char* topic, CustomMqttFailure failure, CustomMqttSuccess success, void* ext);

int __stdcall VCS_PacketCreate(short command,const char* buf,int buf_size, char**out_packet,int* out_packet_size);
int __stdcall VCS_PacketParse(const char* in_packet,int in_packet_size, char**buf,int* buf_size,short* command,int* result);


#endif // !VSC_H

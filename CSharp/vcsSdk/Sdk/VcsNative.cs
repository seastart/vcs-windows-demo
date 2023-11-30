using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Sdk
{

    public class VcsNative
    {
        public const int VCS_R_OK = 0;
        public const int VCS_R_ERROR = 1;
        public const int VCS_R_CHECK_TOKEN_ERROR = 2;
        public const int VCS_R_ACCOUNT_NOTFOUND = 3;
        public const int VCS_R_ROOM_NOTFOUND = 4;

        public const int VCS_EVENT_ENTER = 1;                       //我进入房间      data: short result  0成功；
        public const int VCS_EVENT_EXIT = 2;                        //我退出房间       data: short result  0成功；
        public const int VCS_EVENT_NOTIFY_ROOM = 3;                 //房间信息变更   data: VCS_ROOM
        public const int VCS_EVENT_NOTIFY_ACCOUNT = 4;              //帐号信息变更   data:VCA_ACCOUNT
        public const int VCS_EVENT_NOTIFY_KICKOUT = 5;              //被提通知
        public const int VCS_EVENT_NOTIFY_ENTER = 6;                //成员进入通知
        public const int VCS_EVENT_NOTIFY_EXIT = 7;                 //成员退出通知
        public const int VCS_EVENT_NOTIFY_BEGIN = 8;                //会议开始通知
        public const int VCS_EVENT_NOTIFY_ENDED = 9;                //会议结束通知
        public const int VCS_EVENT_NOTIFY_MYACCOUNT = 10;           //我的信息变更通知
        public const int VCS_EVENT_SEND_STATUS = 11;                //上行网络状态
        public const int VCS_EVENT_RECV_STATUS = 12;                //下线网络状态
        public const int VCS_EVENT_STREAM_CHANGED = 13;             //码流变化通知
        public const int VCS_EVENT_STREAM_CTRL = 14;                //主持人控制码流通知
        public const int VCS_EVENT_PASSTROUGH = 15;                 //透传通知
        public const int VCS_EVENT_CHAT = 16;                       //聊天消息
        public const int VCS_EVENT_HANDUP = 17;                     //举手消息处理
        public const int VCS_EVENT_DEBUG_LOG = 100;                 //调试信息
        public const int VCS_EVENT_REG_INVITE_NOTIFICATION = 200;   //邀请入会通知
        public const int VCS_EVENT_REG_INVITE_CONFIRM = 201;        //邀请入会回复
        public const int VCS_EVENT_MEDIA_CONNECTED = 205;           //流媒体连接成功
        public const int VCS_EVENT_MEDIA_STREAM_RECV = 208;           //流媒体连接成功
        public const int VCS_EVENT_NET_STATE = 300;                 //网络状态

        public const int VCS_EVENT_GRAPHICS_INVALID = 500;          //显卡未安装
        public const int VCS_EVENT_DEV_CHANGED = 501;               //设备驱动改变

        public const int VCS_DS_AVTIVE = 0;     //正常
        public const int VCS_DS_CLOSED = 1;     //关闭
        public const int VCS_DS_DISABLED = 2;       //被主持人禁用

        public const int VCS_CR_MEMBER = 0; //普通成员
        public const int VCS_CR_Creator = 1;    //创建人
        public const int VCS_CR_HOST = 2;   //主持人

        public const int VCS_DEVICE_PC = 1;         //PC
        public const int VCS_DEVICE_ANDROID = 2;            //Android
        public const int VCS_DEVICE_IOS = 3;            //IOS
        public const int VCS_DEVICE_ANDROID_EMBEDDED = 4;       //安卓一体机
        public const int VCS_DEVICE_EMBEDDED = 5;           //录播主机

        //码流操作
        public const int OPERATION_ADD = 1;
        public const int OPERATION_REMOVE = 0;
        public const int OPERATION_UPDATE = 2;

        public const int VCS_INVITE_RSP_ACCEPTED = 1;
        public const int VCS_INVITE_RSP_REJECTED = 2;


        public const int VCS_DESTROY_WIND = 401; // 窗口移除时通知SDK释放关联的显示资源
        public const int VCS_REFRESH_WIND = 402; // 0x11 refresh window HWND
        public const int VCS_DYNA_SIZE = 0x1001; // 启用动态更新画布大小、帧率和码率
        public const int VCS_RESET_SIZE = 0x1002; // 重置画布大小【opt=VCS_RESET_SIZE,wparam=width,lparam=height】
        public const int VCS_RESET_CPARAM = 0x1003; // 设置画布参数 【opt=VCS_RESET_CPARAM】 
        public const int VCS_PARAM_FRAMES = 0x01; // 重置帧率
        public const int VCS_PARAM_BITRATE = 0x02; // 重置码率
        public const int VCS_OPT_XBITPAUSE = 0x01e; //共享桌面时可以停止码率自适应
        public const int VCS_OPT_PREVPAUSED = 0x014;   // pause preview track  //(小码率视频暂停/恢复)
        public const int VCS_OPT_MAXBITRATE = 0x015;  //设置最大码率[初始化SDK后,入会前设置 默认最大2000kps  单位kps]
        public const int VCS_OPT_XBITMODE = 0x01f;   // 2-共享屏幕模式    0-摄像头模式
        public const int VCS_OPT_AUDIOPRIO = 0x030;   // 音频优先 0关闭 1开启 带视频分享流stream id.
        public const int VCS_OPT_WATERMARK_XY = 0x6000; //水印显示位置
        public const int VCS_OPT_WATERMARK_SIZE = 0x6001; //水印显示大小
        public const int VCS_OPT_WATERMARK_INFO = 0x6002; //水印参数
        public const int VCS_AUDIO_ENCODE_BITRATE = 0x3000; //音频编码频率设置 默认32K init时调用。
        //显示增强
        public const int VCS_SET_INTENSITY = 0x5000;  //设置增强参数标志
        public const int LOW_INTENSITY = 0x5050; //低强度
        public const int GENERAL_INTENSITY = 0x5051; //一般强度
        public const int HIGH_INTENSITY = 0x5052; //高强度
        public const int NO_INTENSITY = 0x5053; //关闭增强


        /// <summary>
        /// 房间事件回调
        /// </summary>
        /// <param name="hroom"></param>
        /// <param name="iEvent">事件ID</param>
        /// <param name="pEventData">事件数据,Json格式</param>
        /// <param name="iDataSize"></param>
        /// <param name="pContext">回调上下文</param>
        /// <returns></returns>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int RoomEvent(IntPtr hroom, int iEvent, IntPtr pEventData, int iDataSize, IntPtr pContext);

        /// <summary>
        /// 数据回调
        /// </summary>
        /// <param name="clientId"></param>
        /// <param name="track"></param>
        /// <param name="canvas"></param>
        /// <param name="pic"></param>
        /// <param name="ctx"></param>
        /// <returns></returns>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int VCS_CBF_FrameEvent(int clientId, int track, int canvas, IntPtr pic, IntPtr ctx);

        /// <summary>
        /// 音频回调
        /// </summary>
        /// <param name="clientId"></param>
        /// <param name="cbData"></param>
        /// <param name="ctx"></param>
        /// <returns></returns>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int VCS_CBF_AudioEvent(int clientId, IntPtr cbData, IntPtr ctx);

        // 音频事件回调
        // iEvent:事件类型
        // ptr:字符串
        // ctx:上下文
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int VCS_CBF_AudioEventStatus(int iEvent, int wParam, int lParam, IntPtr ptr, IntPtr ctx);

        // display ctrl 透传(修复渲染问题)
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int DisplayCtrl(int wParam, IntPtr lParam, IntPtr ctx);



        public const string DllPath = "vcs.dll";
        /// <summary>
        /// SDK全局初始化
        /// </summary>
        /// <returns>0表示成功，&lt;0表示失败 使用SDK前必须初始化</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Init();

        /// <summary>
        /// SDK注销，自动清理所有内部资源,调用一次即可
        /// </summary>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_Cleanup();

        /// <summary>
        /// 创建输出(1.当outviewport!=viewport 时 push到服务器的流进行scale. 2.在这之间需要设置 服务器地址 房间号 AGC 等等)
        /// </summary>
        /// <param name="mylinkId">自己的房间id</param>
        /// <param name="hWnd">输出源绑定的窗口</param>
        /// <param name="iWidth">outviewport</param>
        /// <param name="iHeight">outviewport</param>
        /// <param name="viewWidth">viewport</param>
        /// <param name="viewHeight">viewport</param>
        /// <param name="iFps">输出帧率</param>
        /// <param name="iBitrate">输出码率</param>
        /// <param name="iSamplerate">音频采样率</param>
        /// <param name="pic">设置垫片 NULL 不设置</param>
        /// <returns>成功返回输出ID,ID&lt;0 失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateOutput(string mylinkId, IntPtr hWnd, int iWidth, int iHeight, int viewWidth, int viewHeight, int iFps, int iBitrate, int iSamplerate, string pic);

        /// <summary>
        /// 关闭输出
        /// </summary>
        /// <param name="hOutput">输出ID</param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_CloseOutput(int hOutput);

        /// <summary>
        /// 是否显示合屏
        /// </summary>
        /// <param name="hOutput">输出ID 参数无效</param>
        /// <param name="iShow">1-开始绘制; 0-停止绘制</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_ShowOutput(int hOutput, int iShow);

        /// <summary>
        /// 设置AGC 重置AGC 需要重新初始化音频采集
        /// </summary>
        /// <param name="hOutput">输出ID</param>
        /// <param name="iAgc">默认16000</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetOutputAgc(int hOutput, int iAgc);

        /// <summary>
        /// 设置AEC 重置AEC 需要重新初始化音频采集
        /// </summary>
        /// <param name="hOutput">输出ID</param>
        /// <param name="iAec">默认10</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetOutputAec(int hOutput, int iAec);

        /// <summary>
        /// 在输出源中叠加输入源，此方案可在运行时动态添加，并且线程安全(支持数量 4video+1audio，audio iWidth=1  iHeight=1  iLeft=0  iTop=0)
        /// </summary>
        /// <param name="hOutput">无效</param>
        /// <param name="hInput">源ID</param>
        /// <param name="iLeft">合屏位置（单位：像素）</param>
        /// <param name="iTop">合屏位置（单位：像素）</param>
        /// <param name="iWidth">目标宽（单位：像素）</param>
        /// <param name="iHeight">目标高（单位：像素）</param>
        /// <param name="iAudio">是否使用该输入源的audio(有声音源有效是 1-使用 0-不使用)</param>
        /// <param name="iVideo">是否使用该输入源的video(有声音源有效是 1-使用 0-不使用)</param>
        /// <param name="iDeep">缓存最少帧数目 这个是一个抖动源，
        /// 源音视频本身同步的很好，并且要求特别短延迟的源（例如摄像头采集），deep 设置为 1，也就画布针对该输入不再启用平滑缓存处理以减少延时；
        /// 对于一般的网络源，deep 设置为 0，由画布根据源的音视频同步情况自动调整，一般情况下，画布针对这种输入会启用平滑缓存（减少输入抖动），最少 8 帧左右，并且随着源异步情况会自动增加缓存；&#10;
        /// 对于屏幕采集这种没有音频的源, deep 推荐设置 3，也就缓存 3 帧。
        /// </param>
        /// <returns>0表示成功，0表示失败.</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_AddInput(int hOutput, int hInput, int iLeft, int iTop, int iWidth, int iHeight, int iAudio, int iVideo, int iDeep);

        /// <summary>
        /// 调整图像位置和尺寸
        /// </summary>
        /// <param name="w">画布宽</param>
        /// <param name="h">画面高</param>
        /// <param name="cx">图像宽</param>
        /// <param name="cy">图像高</param>
        /// <param name="iLeft"></param>
        /// <param name="iTop"></param>
        /// <param name="iWidth"></param>
        /// <param name="iHeight"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_AdjustPicture(int w, int h, int cx, int cy, out int iLeft, out int iTop, out int iWidth, out int iHeight);

        /// <summary>
        /// 修改输出源中叠加输入源
        /// </summary>
        /// <param name="hOutput">输出句柄</param>
        /// <param name="hInput">出入句柄</param>
        /// <param name="iLeft">在输出源中叠加的位置（单位：像素）</param>
        /// <param name="iTop">在输出源中叠加的位置（单位：像素）</param>
        /// <param name="iWidth">在输出源中叠加的宽度（单位：像素）</param>
        /// <param name="iHeight">在输出源中叠加的高度（单位：像素）</param>
        /// <param name="iAudio">是否合成音频 1-合成；0-不合成</param>
        /// <param name="iVideo">是否合成视频 1-合成；0-不合成</param>
        /// <param name="iDeep">缓存最少帧数目</param>
        /// <remarks>audio:iWidth=1 iHeight=1</remarks>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_UpdateInput(int hOutput, int hInput, int iLeft, int iTop, int iWidth, int iHeight, int iAudio, int iVideo, int iDeep);

        /// <summary>
        /// 在输出源中移除输入源 移除时对应的输入源会被关闭
        /// </summary>
        /// <param name="hOutput">输出句柄</param>
        /// <param name="hInput">出入句柄</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_RemoveInput(int hOutput, int hInput);

        /// <summary>
        /// 调整叠加合屏源Layout 只对视频源有效
        /// </summary>
        /// <param name="hOutput">输出句柄</param>
        /// <param name="szOrder">输入源ID列席，用逗号分开 【1,2,20....】包含单独的audio</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetViewLayoutInput(int hOutput, string szOrder);

        /// <summary>
        /// 更新输出 只有进行改更新时 最后推流到服务器的流才是更新后的out stream 在更新输入源是 必须调用该函数 使之生效
        /// </summary>
        /// <param name="hOutput">输出句柄</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_UpdateOutput(int hOutput);

        //[DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        //public static extern int VCS_UpdateOutput(int hOutput);

        /// <summary>
        /// 打开秒表 用来测试使用
        /// </summary>
        /// <param name="hOutput"></param>
        /// <param name="iOpen">1-打开；0-关闭</param>
        /// <returns>返回上次的状态，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_OpenWatch(int hOutput, int iOpen);

        /// <summary>
        /// 支持"自适应"延迟
        /// </summary>
        /// <param name="vcs_delay"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetXdelay(int vcs_delay);

        /// <summary>
        /// 用于云端选择所需的用户流转发给与会者
        /// </summary>
        /// <param name="hOutput"></param>
        /// <param name="mask">
        /// <remarks>
        /// 命令格式：
        /// LMIC.picker=mask:linkmicId
        /// mask = 1 音频
        /// mask = 2 视频
        /// mask = 3 音视频
        /// mask = 0 关闭转发
        /// client_id = 0 代表所有与会者
        /// </remarks>
        /// </param>
        /// <param name="client_id"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetPicker(int hOutput, int mask, int client_id);

        /// <summary>
        /// No Picking Audio 接口
        /// </summary>
        /// <param name="stat">stat:1 开启，无限制视频个数，由VCS_SetPicker来增加视频个数.stat:0 关闭，最多选择4方视频</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_NoPickAudio(int stat);

        /// <summary>
        /// 语音激励上报，用于服务端统计激励状态
        /// </summary>
        /// <param name="open">open:true 上报本地激励状态  open:false 不上报本地激励状态</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_OpenVoiceExci(bool open);

        /// <summary>
        /// 杨声器开关
        /// </summary>
        /// <param name="on">on:true 开启  on:false 关闭</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetSpeakerOn(bool on);

        /// <summary>
        /// 用于云端过滤特定用户的流不转发给与会者
        /// </summary>
        /// <remarks>
        /// 命令格式：
        /// LMIC.filter=mask:linkmicId
        /// mask = 1 音频,
        /// mask = 2 视频频,
        /// mask = 3 音视频,
        /// mask = 0 关闭过滤,
        /// mask = 0x2000 保持激活当前，其他人停止转发,
        /// client_id = 0 代表所有与会者,
        /// </remarks>
        /// <param name="hOutput"></param>
        /// <param name="mask"></param>
        /// <param name="client_id"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetFilter(int hOutput, int mask, int client_id);


        /// <summary>
        /// 用于云端选择特定用户的特定的子码率（轨道）转发给与会者
        /// </summary>
        /// <remarks>
        /// 命令格式：
        /// LMIC.track = mask:linkmicId
        /// mask：二进制选择掩码
        /// 1 1 1 1, 1 1 1 1
        ///               轨道 0
        ///             轨道 1
        ///           轨道 2
        /// 最多 7 个轨道
        /// 示例：
        /// mask = 1 选择转发视频轨 0  大流
        /// mask = 2 选择转发视频轨 1  小流
        /// mask = 5 选择转发视频轨 0 和 2
        /// client_id = 0 代表所有与会者
        /// </remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetTrack(int hOutput, int mask, int client_id);

        /// <summary>
        /// 设置音频采样率
        /// </summary>
        /// <param name="hOutput"></param>
        /// <param name="sample">采用率:22050/44100/48000</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetAudioSample(int hOutput, int sample);

        /// <summary>
        /// 设置音频通道数
        /// </summary>
        /// <param name="hOutput"></param>
        /// <param name="channels">1-单声道；2-双声道</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetAudioChannels(int hOutput, int channels);

        /// <summary>
        /// 枚举视频设备列表
        /// </summary>
        /// <param name="szDevices">        /// 返回的视频设备列表字符串，当szDevices传递NULL时，表示只需要获取一下所需的内存空间        /// </param>
        /// <param name="iSize">szDevices的内存字节数out IntPtr</param>
        /// <returns>返回szDevices的实际字节数</returns>
        /// <remarks>
        /// dvideo = "XiaoMi USB 2.0 Webcam; 640X480; 160X120; 320X240; 1280X720";
        /// dvideo = "XiaoMi USB 2.0 Webcam; 640X480; 160X120; 320X240; 1280X720||KPwebcam; 640X480; 160X120; 320X240; 1280X720";
        /// </remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int EnumVideoDevices(IntPtr szDevices, int iSize);

        /// <summary>
        /// 枚举音频设备列表
        /// </summary>
        /// <param name="szDevices">返回的音频设备列表字符串，当szDevices传递NULL时，表示只需要获取一下所需的内存空间</param>
        /// <param name="iSize">szDevices的内存字节数</param>
        /// <returns>返回szDevices的实际字节数</returns>
        /// <remarks>daudio = "麦克风(Realtek High Definition Audio)";daudio = "麦克风(Realtek High Definition Audio)||麦克风2(Realtek High Definition Audio)";</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int EnumAudioDevices(IntPtr szDevices, int iSize);

        /// <summary>
        /// 枚举扬声器设备列表
        /// </summary>
        /// <param name="szDevices"></param>
        /// <param name="iSize"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int EnumSpeakerDevices(IntPtr szDevices, int iSize);

        /// <summary>
        /// 设置扬声器
        /// </summary>
        /// <param name="szDevice"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetSpeakerDevice(string szDevice);

        /// <summary>
        /// 枚举当前所有的窗口句柄
        /// </summary>
        /// <param name="caps"></param>
        /// <returns>返回的caps字符串当不再需要时通过VCS_Freep释放</returns>
        /// <remarks>
        /// 枚举的结果中的capctx当不再需要时通过VCS_CloseWndCapture释放
        /// </remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int EnumWndCaptures(ref IntPtr caps);

        /// <summary>
        /// 绘制窗口缩略图
        /// </summary>
        /// <param name="capctx">通过EnumWndCaptures方法获取</param>
        /// <param name="hdc">通过EnumWndCaptures方法获取</param>
        /// <remarks>x、y、cx、cy: 要绘制到hdc上的位置及宽高</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_DrawSnapshot(IntPtr capctx, IntPtr hdc, int x, int y, int cx, int cy);

        /// <summary>
        /// 释放窗口句柄
        /// </summary>
        /// <param name="capctx">通过EnumWndCaptures方法获取的窗口句柄</param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_CloseWndCapture(IntPtr capctx);

        /// <summary>
        /// 是否显示源 在源初始化设置预览的时候设置有效 非DLL显示时无效
        /// </summary>
        /// <param name="input">创建输入源返回的ID</param>
        /// <param name="show"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetSrcStreamVisible(int input, bool show);

        /// <summary>
        /// camera 采集
        /// </summary>
        /// <param name="szDevice">视频设备名称</param>
        /// <param name="iWidth">设备输入分辨率 //必须在camera 支持的分辨率中</param>
        /// <param name="iHeight">视频输入分辨率//必须在camera 支持的分辨率中</param>
        /// <param name="iFps">视频输入帧率</param>
        /// <param name="hWnd">指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示</param>
        /// <returns>成功返回输入streamID，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputVideo(string szDevice, int iWidth, int iHeight, int iFps, IntPtr hWnd);

        /// <summary>
        /// 创建音频输入句柄
        /// </summary>
        /// <param name="szDevice">音频输入设备名称</param>
        /// <param name="iChannel">音频通道，1/2 channel=1;</param>
        /// <param name="iSampleRate">音频采样率  samplerate=48000</param>
        /// <returns>成功返回输入streamID，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputAudio(string szDevice, int iChannel, int iSampleRate);

        /// <summary>
        /// 创建屏幕输入句柄
        /// </summary>
        /// <param name="hWnd">指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示</param>
        /// <returns>成功返回输入句柄，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputScreen(IntPtr hWnd);

        /// <summary>
        /// 创建屏幕、软件截图句柄
        /// </summary>
        /// <param name="hWnd">指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示</param>
        /// <param name="hCapWnd">要截图的窗口句柄，NULL表示截取整个桌面</param>
        /// <param name="rect">窗口位置字符串 x,y,cx,cy  截取全屏下才有效</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputScreen2(IntPtr hWnd, IntPtr hCapWnd, string rect);

        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputScreen3(IntPtr hWnd, IntPtr hCapWnd, string rect,string ext);
        /// <summary>
        /// 创建网络流输入
        /// </summary>
        /// <param name="szUrl"> 网络流地址</param>
        /// <param name="hWnd">指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示</param>
        /// <returns>成功返回输入句柄，&lt;0表示失败</returns>
        /// <remarks>支持RTMP/HLS/RTSP等，支持: PC,Linux,iOS,Android</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputUrl(string szUrl, IntPtr hWnd);

        /// <summary>
        /// 创建本地文件输入 支持MP4 AVI
        /// </summary>
        /// <param name="szFilepath">文件绝对路径 [C:\\video\tv.mp4]</param>
        /// <param name="hWnd">指定预览句柄，当ptr=NULL 预览不显示 可以通过  VCS_SetSrcStreamVisible 来设置是否显示</param>
        /// <returns>成功返回输入句柄，&lt;0表示失败</returns>
        /// <remarks>支持: PC,Linux,iOS,Android</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputFile(string szFilepath, IntPtr hWnd);

        /// <summary>
        /// 关闭输入源句柄
        /// </summary>
        /// <param name="hInput">输入源句柄</param>
        /// <returns>成功返回-1 >0 未关闭 关闭对应的输入源</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CloseInput(int hInput);

        /// <summary>
        /// 获取错误码
        /// </summary>
        /// <returns>最近发生的错误码</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_GetLastError();

        // iError: 
        /// <summary>
        /// 设置错误码，支持TLS线程局部存储
        /// </summary>
        /// <param name="iError">错误码</param>
        /// <remarks>支持: PC,Linux,iOS,Android</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetLastError(int iError);

        /// <summary>
        /// 进入房间前调用
        /// </summary>
        /// <returns></returns>
        [DllImport(DllPath, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern int VCS_Room_Init();

        /// <summary>
        /// 退出房间后调用
        /// </summary>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_Room_Cleanup();

        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Stream_Multiple(int type);
        
        /// <summary>
        /// 创建房间句柄
        /// </summary>
        /// <returns>成功返回房间号，NULL表示失败</returns>
        /// <remarks>
        /// 支持: PC,Linux,iOS,Android
        /// szAddr: 会议服务器地址
        /// iPort: 会议服务器端口
        /// szRoomNo: 房间号
        /// szSessionId: 进入授权码【token】
        /// </remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern IntPtr VCS_CreateRoom();

        /// <summary>
        /// 设置房间信息
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="room"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetRoomInfo(IntPtr hRoom, string room);
        /// <summary>
        /// 获取房间信息
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="room"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_GetRoomInfo(IntPtr hRoom, out IntPtr room, out int size);

        /// <summary>
        /// 设置登录信息
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="account"></param>
        /// <param name="upload">upload=1,立即上传，upload=0 延迟上传</param>
        [DllImport(DllPath, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetAccountInfo(IntPtr hRoom, IntPtr account, int upload);
        /// <summary>
        /// 获取登录信息
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="account"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_GetAccountInfo(IntPtr hRoom, out string account, out int size);

        /// <summary>
        /// 设置认证信息
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="szSession"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetSession(IntPtr hRoom, string szSession);

        /// <summary>
        /// 设置服务器地址
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="szAddr"></param>
        /// <param name="iPort"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetRoomServer(IntPtr hRoom, string szAddr, int iPort);

        /// <summary>
        /// 设置流媒体地址
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="szAddr"></param>
        /// <param name="iPort"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetMediaServer(IntPtr hRoom, string szAddr, int iPort);

        /// <summary>
        /// 设置事件回调[可选设置]
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="cbfRoomEvent">事件回调,VCS_CBF_RoomEvent类型</param>
        /// <param name="pContext">回调上下文</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetRoomEvent(IntPtr hRoom, RoomEvent cbfRoomEvent, IntPtr pContext);

        /// <summary>
        /// 设置房间的输出句柄
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="hOutput">窗口</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetRoomOutput(IntPtr hRoom, int hOutput);

        /// <summary>
        /// 正式开始建立连接，进入房间
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <returns>成功返回>=0,&lt;0表示错误</returns>
        /// <remarks>myClientId: 设置自己在房间中的唯一标识</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_EnterRoom(IntPtr hRoom);

        /// <summary>
        /// 退出房间(支持: PC,Linux,iOS,Android)
        /// </summary>
        /// <param name="hRoom"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_ExitRoom(IntPtr hRoom);

        /// <summary>
        /// 退出房间（超时）
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="ms">超时毫秒数，小于0表示一直等待</param>
        /// <returns>0表示成功</returns>
        /// <remarks>支持: PC,Linux,iOS,Android</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_TimedExitRoom(IntPtr hRoom, int ms);

        /// <summary>
        /// 设置成员视频显示到窗口
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="iClientId"> 成员连接ID</param>
        /// <param name="iTrack">轨道ID</param>
        /// <param name="hWnd">窗口句柄，NULL则停止绘制</param>
        /// <returns> 1表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetClientWnd(IntPtr hRoom, int iClientId, int iTrack, IntPtr hWnd);

        /// <summary>
        /// 发送广播消息(支持: PC,Linux,iOS,Android)
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="iMyClientId">自己的连接ID</param>
        /// <param name="szMessage">文本消息</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SendMessage(IntPtr hRoom, int iMyClientId, string szMessage);

        /// <summary>
        /// 设置自己是否发送视频(支持: PC,Linux,iOS,Android)
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="iMyClientId">自己的连接ID</param>
        /// <param name="iEnabled">1-启用；0-关闭</param>
        /// <returns>0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_EnableSendVideo(IntPtr hRoom, int iMyClientId, int iEnabled);

        /// <summary>
        /// 设置自己是否发送音频(支持: PC,Linux,iOS,Android)
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="iMyClientId">自己的连接ID</param>
        /// <param name="iEnabled">1-启用；0-关闭</param>
        /// <returns>>=0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_EnableSendAudio(IntPtr hRoom, int iMyClientId, int iEnabled);

        /// <summary>
        /// 设置自己是否接收对方视频(支持: PC,Linux,iOS,Android)
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="iOtherClientId">对方的连接ID，0表示所有在同一房间内除了自己的所有人</param>
        /// <param name="iEnabled">1-启用；0-关闭</param>
        /// <returns>>=0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_EnableRecvVideo(IntPtr hRoom, int iOtherClientId, int iEnabled);

        /// <summary>
        /// 设置自己是否接收对方音频(支持: PC,Linux,iOS,Android)
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="iOtherClientId">对方的连接ID，00表示所有在同一房间内除了自己的所有人</param>
        /// <param name="iEnabled">1-启用；0-关闭</param>
        /// <returns>>=0表示成功，&lt;0表示失败</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_EnableRecvAudio(IntPtr hRoom, int iOtherClientId, int iEnabled);

        /// <summary>
        /// 系统时延设置网络抗抖动等级.(不允许动态设置)
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="iPlc">补偿级别：0，1，2， 默认为1</param>
        /// <returns>返回 实际的iPlc</returns>
        /// <remarks>
        /// 超短（0）单向延迟 120 ms 左右，这种模式下没有丢包补偿机制，并且编码关闭了 B 帧，一般不建议实际使用；
        /// 短  （1）单向延迟 200 ms 左右，单次丢包补偿，B 帧为 1，双向对讲环境下可以使用；
        /// 中  （2）单向延迟 350 ms 左右，两次丢包补偿，B 帧为 1，双向对讲环境下推荐使用；
        /// 长  （3）单向延迟 600 ms 左右，三次丢包补偿，B 帧为 3，这种模式仅用于单向收看，双向对讲环境下不建议使用；
        /// </remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetRoomPlc(IntPtr hRoom, int iPlc);

        /// <summary>
        /// 设置码率自适应 在收到接连成功VCS_CONNECTED 后设置有效 该函数可以进行多次设置(支持: PC,Linux,iOS,Android)
        /// </summary>
        /// <param name="hRoom">输出句柄</param>
        /// <param name="iSecond">0-关闭自适应；开启[>=3]</param>
        /// <returns>1 成功</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetRoomXBitrate(IntPtr hRoom, int iSecond);

        /// <summary>
        /// 获取上传的状态 speed delay Buffers Status Overflow
        /// </summary>
        /// <remarks>定时器 每一秒钟获取即可</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_GetUploadStatus();

        /// <summary>
        /// 获取接收流状态情况
        /// </summary>
        /// <remarks>定时器 每一秒钟获取即可</remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_GetRecvStatus();

        /// <summary>
        /// 主持人禁用音视频
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="szTargetId"></param>
        /// <param name="iAudioState"></param>
        /// <param name="iVideoState"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern unsafe int VCS_HostCtrl(IntPtr hRoom, string szTargetId, int* iAudioState, int* iVideoState);

        /// <summary>
        /// 主持人踢人
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="szTargetId"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_HostKickout(IntPtr hRoom, string szTargetId);

        /// <summary>
        /// 主持人打开/关闭电子白板
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="bOpen"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_HostWhiteBoard(IntPtr hRoom, int bOpen);

        /// <summary>
        /// 切换码流
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="strm"></param>
        /// <param name="o"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_StreamChange(IntPtr hRoom, string strm, int o);

        /// <summary>
        /// 主持人切换码流
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="target_id"></param>
        /// <param name="strm"></param>
        /// <param name="o"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_HostStreamChange(IntPtr hRoom, string target_id, string strm, int o);

        /// <summary>
        /// 透传
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="target_id"></param>
        /// <param name="msg"></param>
        /// <param name="msg_size"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Passthrough(IntPtr hRoom, string target_id, string msg, int msg_size);

        /// <summary>
        /// 聊天消息
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="target_id">接收者ID</param>
        /// <param name="type">消息类型</param>
        /// <param name="msg">消息内容</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Chat(IntPtr hRoom, string target_id, int type, string msg);

        /// <summary>
        /// 开启双流
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="multi">multi: 1-开启；0-关闭</param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetMultiTrack(IntPtr hRoom, int multi);

        /// <summary>
        /// 开启音频Opus编码
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="opus">opus:1-开启；0-关闭</param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetOpusCodec(IntPtr hRoom, int opus);

        /// <summary>
        /// 设置网络状态统计间隔，0-关闭 (单位:秒)
        /// </summary>
        /// <param name="hRoom"></param>
        /// <param name="interval"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetStatInterval(IntPtr hRoom, int interval);

        /// <summary>
        /// 释放内存
        /// </summary>
        /// <param name="p"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_Freep(ref IntPtr p);

        /// <summary>
        /// 创建注册服务器连接句柄
        /// </summary>
        /// <param name="account_id"></param>
        /// <param name="token"></param>
        /// <param name="address"></param>
        /// <param name="port"></param>
        /// <param name="cbfRoomEvent"></param>
        /// <param name="pContext"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern IntPtr VCS_CreateClient(string account_id, string token, string address, int port,
            RoomEvent cbfRoomEvent, IntPtr pContext);

        /// <summary>
        /// 开始连接注册服务器
        /// </summary>
        /// <param name="hclient"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Open(IntPtr hclient);

        /// <summary>
        /// 关闭服务器连接
        /// </summary>
        /// <param name="hclient"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_Close(IntPtr hclient);

        /// <summary>
        /// 发起邀请
        /// </summary>
        /// <param name="hclient"></param>
        /// <param name="tar_id"></param>
        /// <param name="room_no"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Invite(IntPtr hclient, string tar_id, string room_no);

        /// <summary>
        /// 邀请确认
        /// </summary>
        /// <param name="hclient"></param>
        /// <param name="id"></param>
        /// <param name="initiator_id"></param>
        /// <param name="room_no"></param>
        /// <param name="resp"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_InviteConfirm(IntPtr hclient, string id, string initiator_id, string room_no, int resp);

        /// <summary>
        /// 呼叫
        /// </summary>
        /// <param name="hclient"></param>
        /// <param name="room_no">房间号</param>
        /// <param name="restart">true(重新呼叫) false(追加呼叫)</param>
        /// <param name="accounts">呼叫对象的集合(json数组，类型为josn结构体)</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Call(IntPtr hclient, string room_no, bool restart, string accounts);

        /// <summary>
        /// 取消呼叫
        /// </summary>
        /// <param name="hclient"></param>
        /// <param name="room_no">房间号</param>
        /// <param name="target_id">目标id(json数组，类型为string)</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CallCancel(IntPtr hclient, string room_no, string target_id);

        /// <summary>
        /// 会议室等候
        /// </summary>
        /// <param name="hclient"></param>
        /// <param name="account">呼叫对象(josn 结构体)</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_WaitingRoom(IntPtr hclient, string account);

        /// <summary>
        /// 发送应用内推送
        /// </summary>
        /// <param name="hclient"></param>
        /// <param name="receivers">接收者用户ID集合(json数组，类型为string)</param>
        /// <param name="message">消息内容</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_PushRequest(IntPtr hclient, string receivers, string message);

        /// <summary>
        /// 设置加载的dll目录(当加载不到dll时调用)
        /// </summary>
        /// <param name="path"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetCurrentDir(string path);

        /// <summary>
        /// 设置视频原始数据回调
        /// </summary>
        /// <param name="hroom"></param>
        /// <param name="cbf"></param>
        /// <param name="ctx"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetFrameCallback(IntPtr hroom, VCS_CBF_FrameEvent cbf, IntPtr ctx);

        /// <summary>
        /// 设置音频原始数据回调
        /// </summary>
        /// <param name="hroom"></param>
        /// <param name="cbf"></param>
        /// <param name="ctx"></param>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetAudioCallback(IntPtr hroom, VCS_CBF_AudioEvent cbf, IntPtr ctx);

        /// <summary>
        /// 设置音频事件回调
        /// </summary>
        /// <param name="cbf"></param>
        /// <param name="ctx"></param>
        /*
        switch (opt)
        {
            case VCS_RPT_AUDIOINF:
            {
                // ptr 是返回的查询结果
                // {"audioInfo": [{"clientId": 20013157,"pow": 0,"db": -60}}
                break;
            }
            case VCS_EVENT_SPEECH_STAT:
            {
                if (ptr)
                {
                    // speech=1/0
                    // speech=1 为当前服务器允许你发言
                    // speech=0 为当前服务器禁止你发言
                    // {"speech" : {"status" : 1}}
                }
                break;
            }
        }
        */
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern void VCS_SetAudioEventStatusCallback(VCS_CBF_AudioEventStatus cbf, IntPtr ctx);

        //透传回调信息到SDK
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetCtrlDisplay(int wParam, IntPtr lParam);

        //透传回调信息回调设置
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetCtrlDisplayCallback(DisplayCtrl cb, IntPtr ctx);

        /// <summary>
        /// 开始分享屏幕
        /// </summary>
        /// <param name="hroom"></param>
        /// <param name="type">type:1-电子白板;2-图片;3-桌面窗口</param>
        /// <param name="pic_url">pic_url:分享图片时的图片地址</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_StartShare(IntPtr hroom, int type, string pic_url);

        /// <summary>
        /// 停止分享屏幕
        /// </summary>
        /// <param name="hroom"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_StopSharing(IntPtr hroom);

        /// <summary>
        /// 渲染事件
        /// </summary>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_DisplayFrame();


        /// <summary>
        /// 扩展参数接口，用于以后参数 和动作扩展，避免新功能还需要增加额外接口
        /// </summary>
        /// <param name="opt"></param>
        /// <param name="wParam"></param>
        /// <param name="lParam"></param>
        /// <param name="ptr"></param>
        /// <param name="ctx"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetOptParams(int opt, int wParam, int lParam, IntPtr ptr, IntPtr ctx);

        /// <summary>
        /// 心跳超时等异常退出会议，重新入会，
        /// </summary>
        /// <param name="hroom">房间句柄</param>
        /// <param name="host">重新入会后的服务器ip</param>
        /// <param name="port">重新入会后的服务器端口号</param>
        /// <param name="session">重新入会后的服务器session</param>
        /// <returns>0 成功  -1 失败。</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_ReStartMeeting(IntPtr hroom, string host, int port, string session);

        /// <summary>
        /// 房间水印开关
        /// </summary>
        /// <param name="hroom">房间句柄</param>
        /// <param name="open">是否开启水印</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_HostWaterMark(IntPtr hroom, int open);

        /// <summary>
        /// 窗口显示水印
        /// </summary>
        /// <param name="open">是否开启水印</param>
        /// <param name="wid">水印宽</param>
        /// <param name="hei">水印高</param>
        /// <param name="handle">窗口句柄</param>
        /// <param name="text1">水印文字内容</param>
        /// <param name="text2">水印文字内容</param>
        /// <returns></returns>  
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_WaterMark_Show(int open, int wid, int hei, IntPtr handle, string text1, string text2);

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
        [Obsolete]
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputVideoByUrl(string DeviceName, int iWidth, int iHeight, int iFps, IntPtr handle);

        //音频采集自定义插件
        //此方法类似于VCS_CreateInputAudio,只负责视麦克风始化 返回的采集句柄后需要VCS_AddInput 等一系列操作。
        //目前调用后悔调用plugin/mycap_receiver.dll 进行采集声音，并传输声音，此dll 只采集声音并不对声音进行任何其他操作。
        //DeviceName        摄像头设备名称，通过 EnumAudioDevices获取
        //audioChannel,     声道数，1
        //audioSample       采样频率，48000
        //返回              返回采集句柄,（小于0 异常）
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_CreateInputAudioByUrl(string DeviceName, int audioChannel, int audioSample);

        /// <summary>
        /// 主持人举手消息处理
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="target_id">目标用户id</param>
        /// <param name="type">处理的举手类型 //0 正常不举手 // 1 禁言举手</param>
        /// <param name="result">主持人处理举手结果 0 同意，其他拒绝</param>
        /// <returns>0 成功 -1房间句柄为空</returns>
        /// <remarks>
        /// 当主持人处理举手消息时调用,调用后指定目标成员将收到VCS_EVENT_HANDUP 事件消息，请在VCS_EVENT_HANDUP 做出相对于的同意拒绝处理
        /// </remarks>                      
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_Host_HandUp(IntPtr hRoom, string target_id, int type, int result);

        /// <summary>
        /// 成员发起举手
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="type">举手类型 //0 正常不举手 // 1 禁言举手</param>
        /// <returns>0 成功，-1房间句柄为空, -100设置信息异常，-101 更新状态异常</returns>                       
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_HandUp(IntPtr hRoom, int type);

        /// <summary>
        /// 主持人禁用音视频(支持多个用户)
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="szTargetId">需要控制的用户id，多个可以用;隔开</param>
        /// <param name="iAudioState">修改音频状态 NULL为不修改</param>
        /// <param name="iVideoState">修改视频状态 NULL为不修改</param>
        /// <returns>0 成功,-1房间句柄为空，-2用户id为空</returns>                   
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_HostCtrls(IntPtr hRoom, string szTargetId, out int iAudioState, out int iVideoState);

        /// <summary>
        /// 主持人房间禁用音视频开关
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="szTargetId">会议id</param>
        /// <param name="iAudioState">修改音频状态 NULL为不修改</param>
        /// <param name="iVideoState">修改视频状态 NULL为不修改</param>
        /// <returns>0 成功,-1房间句柄为空</returns>                        
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern unsafe int VCS_HostRoomCtrl(IntPtr hRoom, string szTargetId, int* iAudioState, int* iVideoState);

        /// <summary>
        /// 版本号
        /// </summary>
        /// <returns>版本号信息</returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern IntPtr VCS_Version();

        /// <summary>
        /// 房间移交主持人
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="szTargetId">移交主持人的id</param>
        /// <returns>0 成功,-1房间句柄为空</returns>
        /// <remarks>
        /// 设置后目标成员，与自己收到VCS_EVENT_NOTIFY_MYACCOUNT role角色变化。应用主动更新 VCS_SetAccountInfo role 信息
        /// </remarks>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_RoomMoveHost(IntPtr hRoom, string szTargetId);

        /// <summary>
        /// 设置联席主持人
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <param name="szTargetId">移交主持人的id</param>
        /// <param name="state">是否设置联席主持人</param>
        /// <returns>0 成功,-1房间句柄为空</returns>
        /// <remarks>
        /// 设置后目标成员，与自己收到VCS_EVENT_NOTIFY_MYACCOUNT role角色变化。应用主动更新 VCS_SetAccountInfo role 信息
        /// </remarks>                      
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_SetUnionHost(IntPtr hRoom, string szTargetId, int state);

        /// <summary>
        /// 恢复主持人
        /// </summary>
        /// <param name="hRoom">房间句柄</param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_RoomRecoveryHost(IntPtr hRoom);

        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
        public static extern int VCS_ChangeShareRect(IntPtr input, string url);


    }
}

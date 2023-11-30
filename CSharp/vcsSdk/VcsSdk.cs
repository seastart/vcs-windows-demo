using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using vcsSdk.Classes;
using vcsSdk.Enums;
using vcsSdk.Interface;
using vcsSdk.Models;
using vcsSdk.Sdk;

namespace vcsSdk
{
    /// <summary>
    /// 会议房间类
    /// </summary>
    public class VcsSdk
    {
        public RoomInfo Info { get;private set; }
        public RoomMyInfo MyInfo { get; private set; }
        public int SelfId { get; set; }
        private IntPtr roomHandle { get; set; }
        private IRoomMsgCallBack MsgCallBack;
        private Input input;
        private int output;
        private int audioSample { get; set; }
        private int audioChannel { get; set; }
        private bool myShare { get; set; }
        private WndCaptureItem ShareTarget { get; set; }
        private VcsNative.RoomEvent _roomEvent;
        private Dictionary<int, MemberData> MemberDataDic = new Dictionary<int, MemberData>();

        public Dictionary<int,MemberData> GetMemUser()
        {
            return MemberDataDic;
        }
        private int RoomEvent(IntPtr hroom, int iEvent, IntPtr pEventData, int iDataSize, IntPtr pContext)
        {
            //byte[] bts = new byte[iDataSize];
            //Marshal.Copy(pEventData, bts, 0, iDataSize);
            //string s = Encoding.UTF8.GetString(bts);
            //Console.WriteLine("---RoomEvent---:" + iEvent + ",---msg---:" + s);
            string s = "";
            if(iDataSize != 0)
            {
                byte[] bts = new byte[iDataSize];
                Marshal.Copy(pEventData, bts, 0, iDataSize);
                s = Encoding.UTF8.GetString(bts);
            }
            switch (iEvent)
            {
                case VcsNative.VCS_EVENT_ENTER:                 //进入会议
                    {
                        JObject json = JObject.Parse(s);
                        int res = int.Parse(json["result"].ToString());
                        MsgCallBack.RoomEnterFinish(res);
                        break;
                    }
                case VcsNative.VCS_EVENT_NOTIFY_ENTER:          //成员进入通知
                case VcsNative.VCS_EVENT_NOTIFY_ACCOUNT:        //成员信息更新
                    {
                        // 成员进入通知
                        StreamData data = JObject.Parse(s).ToObject<StreamData>();
                        if (data.StreamId == null)
                        {
                            break;
                        }
                        // 成员不存在，
                        if (!MemberDataDic.ContainsKey(data.StreamId.Value))
                        {
                            MemberData md = new MemberData();
                            md.data = data;
                            MemberDataDic.Add(data.StreamId.Value, md);
                            MsgCallBack.AddMemberData(data);
                        }
                        else
                        {
                            EnuUserChnage enu = CompaperData(MemberDataDic[data.StreamId.Value].data, data);
                            if (enu != EnuUserChnage.None)
                            {
                                MemberDataDic[data.StreamId.Value].data = data;
                                //更新成员状态
                                MsgCallBack.MemberDataChange(data, enu);
                            }
                        }
                        break;
                    }
                case VcsNative.VCS_EVENT_NOTIFY_EXIT:           //成员退出  
                    {
                        JObject j = JObject.Parse(s);
                        string stream_id = null;
                        stream_id = j["stream_id"].ToString();
                        if (stream_id != null)
                        {
                            MsgCallBack.RemoveMemberData(int.Parse(stream_id));
                        }
                        break;
                    }
                case VcsNative.VCS_EVENT_NOTIFY_ENDED:          //会议结束
                    {
                        CloseRoom();
                        MsgCallBack.MeetingEnd();
                        break;
                    }
                case VcsNative.VCS_EVENT_NOTIFY_KICKOUT:        //被主持人移出会议
                    {
                        CloseRoom();
                        MsgCallBack.MeetingKickOut();
                        
                        break;
                    }
                case VcsNative.VCS_EVENT_NOTIFY_MYACCOUNT:      //我的状态被修改
                    {
                        EnuUserChnage enu = EnuUserChnage.None;
                        JObject json = JObject.Parse(s);
                        bool roleChange = false;
                        JToken jv;
                        roleChange = json.TryGetValue("role", out jv);
                        if (roleChange)
                        {
                            int role = int.Parse(jv.ToString());
                            Info.Role = (EnuRole)role;
                            enu |= EnuUserChnage.Role;
                        }

                        bool audioChange = false;
                        audioChange = json.TryGetValue("astate", out jv);
                        if (audioChange)
                        {
                            int astate = int.Parse(jv.ToString());
                            MyInfo.Mic = (astate == 0);
                            enu |= EnuUserChnage.Audio;

                            if (MyInfo.Mic)
                            {
                                OpenMic();
                            }
                            else
                            {
                                CloseMic();
                            }
                        }
                        bool vstateChange = false;
                        vstateChange = json.TryGetValue("vstate", out jv);
                        if (vstateChange)
                        {
                            int vstate = int.Parse(jv.ToString());
                            MyInfo.Camera = (vstate == 0);
                            enu |= EnuUserChnage.Video;

                            if (MyInfo.Camera)
                            {
                                OpenCamera(MyInfo.Handle);
                            }
                            else
                            {
                                CloseCam();
                            }
                        }
                        MsgCallBack.MyDataChange(enu);
                        break;
                    }
                case VcsNative.VCS_EVENT_NOTIFY_ROOM:
                    {
                        JObject json = JObject.Parse(s);
                        NotifyRoom nr = json.ToObject<NotifyRoom>();
                        EnuRoomChange enu = CompaperRoomData(Info.roomData, nr);

                        if (enu != EnuRoomChange.None)
                        {
                            Info.roomData = nr;
                            MsgCallBack.RoomChange(enu);

                            if (Info.Role == 0)
                            {
                                if ((enu & EnuRoomChange.Audio) > 0)
                                {
                                    if (Info.roomData.Astate.Value > 0)  //房间静音的
                                    {
                                        CloseMic();
                                    }
                                }

                                if ((enu & EnuRoomChange.Video) > 0)
                                {
                                    if (Info.roomData.Vstate.Value > 0)  //房间禁用视频的
                                    {
                                        CloseCam();
                                    }
                                }
                            }

                            if ((enu & EnuRoomChange.SharingType) > 0)
                            {
                                //if(Info.roomData.SharingType == 0)
                                //{
                                //    break;
                                //}
                                //电子白板，上层应用处理
                                if (Info.roomData.SharingAccId == MyInfo.UserId)//我发起的共享
                                {
                                    switch (Info.roomData.SharingType)
                                    {
                                        case 0:
                                            {
                                                if (myShare)
                                                {
                                                    if (MyInfo.Camera)
                                                    {
                                                        DealCloseShareUpLoad();
                                                        OpenCamera(MyInfo.Handle);
                                                    }
                                                    else
                                                    {
                                                        DealCloseShare(false);
                                                    }

                                                    MsgCallBack.StopShare();
                                                }
                                                break;
                                            }
                                        case 1:
                                        case 2:
                                            {
                                               // MsgCallBack.ShareShowClose(Info.type, int.Parse(nr.SharingSdkno));
                                                break;
                                            }
                                        case 3:
                                            {
                                                myShare = true;
                                                if (MyInfo.Camera)
                                                {
                                                    CloseCamOutput();
                                                }

                                                IntPtr caps = IntPtr.Zero;
                                                VcsNative.EnumWndCaptures(ref caps);
                                                string js = Marshal.PtrToStringAnsi(caps);
                                                JArray jarr = JArray.Parse(js);
                                                List<WndCaptureItem> rs = new List<WndCaptureItem>();
                                                bool haveDesktop = false;
                                                foreach (JObject jpms in jarr)
                                                {
                                                    WndCaptureItem item = WndCaptureItem.Parse(jpms);
                                                    rs.Add(item);
                                                    if(item.Desktop > 0)
                                                    {
                                                        haveDesktop = true;
                                                        ShareTarget = item;
                                                        break;
                                                    }
                                                }
                                                VcsNative.VCS_Freep(ref caps);
                                                if(!haveDesktop)
                                                {
                                                    break;
                                                }
                                                //IntPtr i = Marshal.AllocHGlobal(bts.Length + 10);
                                                //Marshal.Copy(bts, 0, i, bts.Length);

                                                //VcsNative.VCS_SetAccountInfo(roomHandle, i, updata);
                                                //Marshal.FreeHGlobal(i);
                                                DealScreenShare();
                                                break;
                                            }
                                    }
                                }
                                else                                            //别人发起的共享
                                {
                                    int StreamIdType = 0;
                                    if (!int.TryParse(nr.SharingStreamId, out StreamIdType)) { break; }
                                    int SharingSdkno = 0;
                                    if (!int.TryParse(nr.SharingSdkno, out SharingSdkno)) { break; }
                                    MsgCallBack.ShareShowClose(Info.roomData.SharingType.Value, SharingSdkno, StreamIdType);
                                }
                            }
                        }
                        break;
                    }
                case VcsNative.VCS_EVENT_NET_STATE:
                    {
                        JObject json = JObject.Parse(s);
                        JToken jv;
                        int streamid = -1;
                        if (json.TryGetValue("client_id", out jv))
                        {
                            streamid = int.Parse(jv.ToString());
                        }
                        int state = -1;
                        if (json.TryGetValue("state", out jv))
                        {
                            state = int.Parse(jv.ToString());
                        }
                        if (streamid != -1 && state != -1)
                        {
                            if (streamid == SelfId)
                            {
                                MsgCallBack.MeNetStateChagne(state);
                            }
                            else
                            {
                                MsgCallBack.MemNetStateChagne(streamid, state);
                            }
                        }
                        break;
                    }
                case VcsNative.VCS_EVENT_SEND_STATUS:
                    {
                        int delay = 0;
                        int rate = 0;
                        double first_lost = 0;
                        double re_lost = 0;
                        int signal = 0;
                        JObject json = JObject.Parse(s);
                        JToken jv;
                        if (json.TryGetValue("delay", out jv))
                        {
                            delay = int.Parse(jv.ToString());
                        }
                        if (json.TryGetValue("rate", out jv))
                        {
                            rate = int.Parse(jv.ToString());
                        }
                        if (json.TryGetValue("first_lost", out jv))
                        {
                            first_lost = double.Parse(jv.ToString());
                        }
                        if (json.TryGetValue("re_lost", out jv))
                        {
                            re_lost = int.Parse(jv.ToString());
                        }
                        if (json.TryGetValue("signal", out jv))
                        {
                            signal = int.Parse(jv.ToString());
                        }
                        MsgCallBack.NetWorkUpData(delay, rate, first_lost, re_lost, signal);
                        SetAccountNetWork(delay, rate, first_lost, signal);
                        break;
                    }
                case VcsNative.VCS_EVENT_RECV_STATUS:
                    {
                        //QJsonArray ss = JsonUtil::getJsonArrayFromString(jsonString);
                        //for (QJsonArray::iterator it = ss.begin(); it != ss.end(); ++it)
                        //{
                        //    QJsonObject stream = (*it).toObject();
                        //    RecvNetWorkStatus s;
                        //    s.Load(stream);
                        //    setMemberNet(s.sdkno().toInt(), s);
                        //}
                        JArray jarr = JArray.Parse(s);
                        Dictionary<int, RecvNetWork> RecvNetWorkDic = new Dictionary<int, RecvNetWork>();
                        foreach (var j in jarr)
                        {
                            RecvNetWork rnw = j.ToObject<RecvNetWork>();
                            RecvNetWorkDic.Add(int.Parse(rnw.sdkno), rnw);
                        }
                        MsgCallBack.NetWorkRecvData(RecvNetWorkDic);
                        break;
                    }
                case VcsNative.VCS_EVENT_MEDIA_CONNECTED:
                    {
                        VcsNative.VCS_NoPickAudio(1);
                        VcsNative.VCS_SetPicker(output, 3, 0);
                        MsgCallBack.MediaConnect();
                        //foreach(var md in MemberDataDic)
                        //{
                        //    if(md.Value.data.VState == 0)
                        //    {
                        //        VcsNative.VCS_SetPicker(output, 3, md.Key);
                        //    }
                        //}
                        break;
                    }
                case VcsNative.VCS_EVENT_GRAPHICS_INVALID:
                    {
                        Info.noVideo = true;
                        MsgCallBack.DeviceFail();
                        break;
                    }
                case VcsNative.VCS_EVENT_CHAT:
                    {
                        JObject json = JObject.Parse(s);
                        ChatMsg cm = json.ToObject<ChatMsg>();
                        MsgCallBack.RecvChatMsg(cm);
                        break;
                    }
                case VcsNative.VCS_EVENT_DEV_CHANGED:
                    {
                        MsgCallBack.DeviceChange();
                        break;
                    }
                case VcsNative.VCS_EVENT_HANDUP:
                    {
                        JObject j = JObject.Parse(s);
                        HandUpNotify hp = j.ToObject<HandUpNotify>();
                        MsgCallBack.HostHandUpResult(hp.Hus, hp.Result);
                        if (hp.Result == 0)//同意了你的请求
                        {
                            OpenMic(MyInfo.MicIndex);
                        }
                        break;
                    }
                case VcsNative.VCS_EVENT_MEDIA_STREAM_RECV:
                    {
                        Console.WriteLine(s);
                    }
                    break;
                default:
                    break;
            }
            return 0;
        }



        public Tuple<bool,string> HostDealHandUp(int selectMemberId,int hus, bool v)
        {
            if (Info.Role != EnuRole.None)//除了普通成员其他人都可以处理
            {
                return new Tuple<bool, string>(false,"普通成员不能处理举手。");
            }
            int hres = v ? 0 : 1;
            VcsNative.VCS_Host_HandUp(roomHandle,MemberDataDic[selectMemberId].data.Id, hus, hres);
            return new Tuple<bool, string>(true, "");
        }

        public Tuple<bool, string> UnionHost(int selectMemberId)
        {
            if(Info.Role != EnuRole.Host)
            {
                return new Tuple<bool, string>(false, "只有主持人可以设置联席主持人。");
            }
            VcsNative.VCS_SetUnionHost(roomHandle, MemberDataDic[selectMemberId].data.Id, 1);
            return new Tuple<bool, string>(true, "");
        }

        public Tuple<bool, string> UnUnionHost(int selectMemberId)
        {
            if (Info.Role != EnuRole.Host)
            {
                return new Tuple<bool, string>(false, "只有主持人可以设置联席主持人。");
            }
            VcsNative.VCS_SetUnionHost(roomHandle, MemberDataDic[selectMemberId].data.Id, 0);
            return new Tuple<bool, string>(true, "");
        }

        public Tuple<bool, string> UnAudioFirst(int selectMemberId)
        {
            int isopen = 0;
            int ret = VcsNative.VCS_SetOptParams(VcsNative.VCS_OPT_AUDIOPRIO, isopen, selectMemberId, IntPtr.Zero, IntPtr.Zero);
            return new Tuple<bool, string>(ret == 0, "sdk :"+ret);
        }

        public Tuple<bool, string> AudioFirst(int selectMemberId)
        {
            int isopen = 1;
            int ret = VcsNative.VCS_SetOptParams(VcsNative.VCS_OPT_AUDIOPRIO, isopen, selectMemberId, IntPtr.Zero, IntPtr.Zero);
            return new Tuple<bool, string>(ret == 0, "sdk :" + ret);
        }

        public void StatInterval(int v)
        {
            VcsNative.VCS_SetStatInterval(roomHandle, v);
        }

        public Tuple<bool, string> RecoveryHost()
        {
            if(MyInfo.UserId != Info.RoomCreator)
            {
                return new Tuple<bool, string>(false, "只有会议创建者才能收回主持人。");
            }
            VcsNative.VCS_RoomRecoveryHost(roomHandle);
            return new Tuple<bool, string>(true, "");
        }

        public void SendChat(int v, string text)
        {
            string target = "";
            if(v != 0)
            {
                target = MemberDataDic[v].data.Id;
            }
            VcsNative.VCS_Chat(roomHandle, target,1, text);
        }

        public void HandUp(EnuHandUp v)
        {
            VcsNative.VCS_HandUp(roomHandle,(int)v);
        }

        public void CloseWaterMark(int selectId)
        {
            int o = 0;
            VcsNative.VCS_WaterMark_Show(o, 0, 0, MemberDataDic[selectId].handle, "", "");
        }

        public void OpenWaterMark(int selectMemberId,int w,int h)
        {
            int o = 1;
            VcsNative.VCS_WaterMark_Show(o, w, h, MemberDataDic[selectMemberId].handle,MyInfo.NickName, MyInfo.Mobile);
        }

        public int CloseShare()
        {
            return VcsNative.VCS_StopSharing(roomHandle);
        }

        public void StartShare(int index,string url = null)
        {
            VcsNative.VCS_StartShare(roomHandle, index, url);
        }

        public void HostMemberMute(int selectMemberId, bool v)
        {
            unsafe
            {
                int* av = null;
                int a = v ? 0 : 1;
                av = &a;
                VcsNative.VCS_HostCtrl(roomHandle, MemberDataDic[selectMemberId].data.Id, av,null);
            }
        }

        public void HostRoomMute(bool v)
        {
            unsafe
            {
                int* av = null;
                int a = v ? 0 : 1;
                av = &a;
                VcsNative.VCS_HostRoomCtrl(roomHandle, Info.roomId, av, null);
            }
        }

        public void HostWaterMark(bool open)
        {
            int o = open ? 1 : 0;
            VcsNative.VCS_HostWaterMark(roomHandle, o);
        }

        public void CloseSpeaker()
        {
            VcsNative.VCS_SetSpeakerOn(false);
            MyInfo.Speaker = false;
        }

        public void OpenSpeaker(int v = -1)
        {
            List<string> ls = EnumDevice.GetSpeaker();
            if(ls != null)
            {
                if(v == -1)
                {
                    v = MyInfo.SpeakerIndex;
                }
                if(MyInfo.SpeakerIndex >= ls.Count)
                {
                    MyInfo.SpeakerIndex = 0;
                }
                VcsNative.VCS_SetSpeakerDevice(ls[MyInfo.SpeakerIndex]);
                VcsNative.VCS_SetSpeakerOn(true);
            }
        }

        public void OpenMemView(IntPtr handle,int StreamId, int ViewType)
        {
            int key = StreamId;
            if(MemberDataDic[key].data.Streams.Count == 0)
            {
                return;
            }
            Stream streamModel = MemberDataDic[key].data.Streams[0];//默认选中第一个

            // 刷新大小码流
            foreach (Stream stream in MemberDataDic[key].data.Streams)
            {
                // 找到自己当前正在使用的码流配置
                if (ViewType == stream.Type)
                {
                    streamModel = stream;
                    break;
                }
            }
            UpdateVideoView(key, handle, streamModel.Id.Value);
        }
        
        private void UpdateVideoView(int key, IntPtr wind, int type)
        {
            VcsNative.VCS_SetPicker(output, 3, key);

            VcsNative.VCS_SetTrack(output, type, key);

            List<int> tracks = Utils.MaskToTrack(type);

            int track = tracks[0];

            VcsNative.VCS_SetClientWnd(roomHandle, key, track, wind);

            MemberDataDic[key].streamItemId = type;
        }

        public void CleanUp()
        {

            VcsNative.VCS_Cleanup();
        }

        public void CloseMemView(IntPtr hwnd,int StreamId)
        {
            //List<int> tracks = Utils.MaskToTrack(StreamId);

            int track = 1;

            VcsNative.VCS_SetClientWnd(hwnd, StreamId, track, IntPtr.Zero);

            VcsNative.VCS_SetPicker(output, 1, StreamId);
            MemberDataDic[StreamId].streamItemId = 0;
        }

        public void OpenShareView(IntPtr handle, int StreamId,int viewType)
        {
            //OpenMemView(handle, StreamId, viewType);

            UpdateVideoView(StreamId, handle, viewType);
        }

        public void CloseShareView(int StreamId)
        {
        }

        public bool ShareRectChange(int x,int y ,int width,int height)
        {
            int ret = input.ShareRectChange(x, y, width, height);
            return (ret == 0);
        }


        public int DealScreenShare2(WndCaptureItem st) 
        {
            ShareTarget = st;
            return DealScreenShare();
        }

        private int DealScreenShare()
        {
            VideoSize vs = new VideoSize();
            int ret = input.ScreenShare(ShareTarget,ref vs);
            if(ret < 0)
            {
                return ret;
            }
            // 调整图像位置和尺寸
            int left = 0, top = 0, width = 0, height = 0;

            VcsNative.VCS_AdjustPicture(
                vs.width,  // 编码画布宽
                vs.height, // 编码画布高
                1920, // 图像宽
                1080, // 图像高
                out left,
                out top,
                out width,
                out height);

            // 在输出源中叠加输入源(视频)
            VcsNative.VCS_AddInput(
                output,        // 输出句柄
                input.screenInput,  // 输入句柄
                left,          // 输入源在输出画面中叠加的位置
                top,           // 输入源在输出画面中叠加的位置
                width,         // 输入源在输出画面中叠加的宽度
                height,        // 输入源在输出画面中叠加的高度
                0,             // 是否使用该输入源的audio(有声音源有效是 1-使用 0-不使用)
                1,             // 是否使用该输入源的video(有声音源有效是 1-使用 0-不使用)
                1);            // 缓存最少帧数目 这个是一个抖动源

            // 更新输出
            VcsNative.VCS_UpdateOutput(output);

            JObject json = new JObject();
            json.Add("vstate", 0);

            JArray jArr = new JArray();

            JObject jStream = new JObject();

            jStream.Add("id", 2);
            jStream.Add("type", 0);
            jStream.Add("width", vs.width);
            jStream.Add("height", vs.height);
            jStream.Add("bitrate", vs.bitrate);
            jStream.Add("fps", vs.fps);
            jStream.Add("channel", audioChannel);
            jArr.Add(jStream);
            json.Add("streams", jArr);

            SetAccountInfo(json.ToString());
            VcsNative.VCS_EnableSendVideo(roomHandle, 0, 1);
            MsgCallBack.ShareStart();
            return 0;
        }

        private int DealCloseShareUpLoad()
        {
            int ret = input.CloseShare();
            if (ret != 0)
            {
                return ret;
            }

            // 移除输入源
            VcsNative.VCS_RemoveInput(output, input.screenInput);

            // 更新输出
            VcsNative.VCS_UpdateOutput(output);
            input.screenInput = -1;
            return 0;
        }

        public int DealCloseShare(bool v)
        {
            JObject j = new JObject();
            j.Add("vstate", v ? 0 : 1);
            JArray jArr = new JArray();
            j.Add("streams", jArr);
            SetAccountInfo(j.ToString());


            int ret = DealCloseShareUpLoad();
            if(ret != 0)
            {
                return ret;
            }

            VcsNative.VCS_EnableSendVideo(roomHandle, 0, v ? 0 : 1);

            return 0;
        }


        private EnuRoomChange CompaperRoomData(NotifyRoom data1, NotifyRoom data2)
        {
            EnuRoomChange enu = EnuRoomChange.None;
            if(data1 == null)
            {
                return enu = (EnuRoomChange)0xffff; 
            }

            if (data2.Locked != null)
            {
                if (data1.Locked != data2.Locked)
                {
                    enu |= EnuRoomChange.Lock;
                }
            }

            if (data2.Astate != null)
            {
                if (data1.Astate != data2.Astate)
                {
                    enu |= EnuRoomChange.Audio;
                }
            }

            if (data2.Vstate != null)
            {
                if (data1.Vstate != data2.Vstate)
                {
                    enu |= EnuRoomChange.Video;
                }
            }

            if (data2.SharingType != null)
            {
                if (data1.SharingType != data2.SharingType)
                {
                    enu |= EnuRoomChange.SharingType;
                }
            }

            if (data2.WaterMark != null)
            {
                if (data1.WaterMark != data2.WaterMark)
                {
                    enu |= EnuRoomChange.WaterMark;
                }
            }

            return enu;

        }

        private EnuUserChnage CompaperData(StreamData data1, StreamData data2)
        {
            EnuUserChnage enu = EnuUserChnage.None;
            if (data2.Hus != null)
            {
                if (data1.Hus != data2.Hus)
                {
                    enu |= EnuUserChnage.Hus;
                }
            }

            if (data2.AState != null)
            {
                if (data1.AState != data2.AState)
                {
                    enu |= EnuUserChnage.Audio;
                }
            }

            if (data2.VState != null)
            {
                if (data1.VState != data2.VState)
                {
                    enu |= EnuUserChnage.Video;
                }
            }

            if (data2.Role != null)
            {
                if (data1.Role != data2.Role)
                {
                    enu |= EnuUserChnage.Role;
                }
            }

            if (data2.NetLevel != null)
            {
                if (data1.NetLevel != data2.NetLevel)
                {
                    enu |= EnuUserChnage.NetLevel;
                }
            }
            return enu;
        }

        public VcsSdk()
        {
            _roomEvent = RoomEvent;
        }
        public void Init(IRoomMsgCallBack cb)
        {
            MsgCallBack = cb;
            VcsNative.VCS_Init();
            input = new Input();
        }

        ~VcsSdk()
        {
        }

        private bool isEnterRoom { get; set; }
        public bool IsEnterRoom() { return isEnterRoom; }
        private Timer timer = null;
        private int streamType = 1;

        public int EnterRoom(RoomInfo roomInfo, RoomMyInfo myInfo,int type = 1)
        {
            return EnterRoom(roomInfo, myInfo,type,new Dictionary<EnuInitValue, string>());
        }

        public int EnterRoom(RoomInfo roomInfo, RoomMyInfo myInfo,int type,Dictionary<EnuInitValue, string> initValue )
        {
            if (isEnterRoom)
            {
                return -100;
            }
            isEnterRoom = true;

            this.MyInfo = myInfo;
            this.Info = roomInfo;

            SelfId = myInfo.StreamId;
            int temp = VcsNative.VCS_Room_Init();
            //timer = new Timer(40);
            //timer.Elapsed += onTimer;
            //timer.Start();
            VcsNative.VCS_Stream_Multiple(type);
            streamType = type;
            // 编码画布的宽度/高度
            int outWidth = int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.OutPutSizeWidth,"1280"));
            int outHeight = int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.OutPutSizeHeight, "720"));
            audioSample = int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.AudioSample, "48000"));
            audioChannel = int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.AudioChannels, "1"));
            int fps = 25;
            int bitrate = 1500;
            output = VcsNative.VCS_CreateOutput(myInfo.StreamId.ToString(),IntPtr.Zero,
                outWidth,   // 输出画面宽度
                outHeight,  // 输出画面高度
                outWidth,   // 预览画面宽度
                outHeight,  // 预览画面高度
                fps,         // 输出帧率
                bitrate,       // 输出码率
                audioSample, // 输出音频采样率
                null);      // 设置垫片 NULL为不设置
            if (output < 0)
            {
                return -101;
            }
            const int VCS_USE_SOFTWARE_AEC = 0x4004;
            int i = 1;
            VcsNative.VCS_SetOutputAec(output, 6);
            VcsNative.VCS_SetOptParams(VCS_USE_SOFTWARE_AEC, i, 0, IntPtr.Zero, IntPtr.Zero);
            VcsNative.VCS_SetOpusCodec(roomHandle, 1);
            bool VoiceExci = "1".Equals(initValue.GetDictionaryValueOrDefault(EnuInitValue.VoiceExci, "1"));
            VcsNative.VCS_OpenVoiceExci(VoiceExci);

            VcsNative.VCS_SetXdelay(int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.Xdelay, "1")));

            VcsNative.VCS_SetOutputAgc(output, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.OutputAgc, "16000")));

            VcsNative.VCS_SetOutputAec(output, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.OutputAec, "10")));

            VcsNative.VCS_SetAudioSample(output, audioSample);

            VcsNative.VCS_SetAudioChannels(output, audioChannel);
            
            VcsNative.VCS_ShowOutput(output, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.ShowOutput, "1")));

            roomHandle = VcsNative.VCS_CreateRoom();

            VcsNative.VCS_SetMultiTrack(roomHandle, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.MultiTrack, "1")));

            VcsNative.VCS_SetRoomPlc(roomHandle, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.RoomPlc, "1")));
            
            VcsNative.VCS_SetRoomEvent(roomHandle, _roomEvent, IntPtr.Zero);

            StreamData acc = GetAccount(fps, bitrate, outWidth, outHeight);
            string json = acc.ToJson().ToString();
            SetAccountInfo(json);
            JObject j = new JObject();
            j.Add("id", roomInfo.roomId);
            j.Add("sdk_no", roomInfo.roomSdkNo);
            string j2 = j.ToString();
            VcsNative.VCS_SetRoomInfo(roomHandle, j2);

            VcsNative.VCS_SetSession(roomHandle, roomInfo.roomSession);

            VcsNative.VCS_SetRoomServer(roomHandle, roomInfo.meetingHost, roomInfo.meetingPort);

            VcsNative.VCS_SetMediaServer(roomHandle, roomInfo.streamHost, roomInfo.streamPort);

            VcsNative.VCS_SetRoomOutput(roomHandle, output);

            int ret = VcsNative.VCS_EnterRoom(roomHandle);
            
            if(ret < 0)
            {
                return -102;
            }

            VcsNative.VCS_EnableSendVideo(roomHandle, 0, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.SendVideo, "0")));

            VcsNative.VCS_EnableSendAudio(roomHandle, 0, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.SendAudio, "0")));

            VcsNative.VCS_SetRoomXBitrate(roomHandle, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.RoomXBitrate, "10")));

            VcsNative.VCS_SetStatInterval(roomHandle, int.Parse(initValue.GetDictionaryValueOrDefault(EnuInitValue.StatInterval, "10")));

            VcsNative.VCS_SetOptParams(VcsNative.VCS_RESET_SIZE, 1280, 720, IntPtr.Zero, IntPtr.Zero);
            return 0;
        }

        private string GetAccount2(int v1, int v2, int v3, int v4)
        {
            JObject obj = new JObject();
            obj.Add("id", MyInfo.UserId);
            obj.Add("name", MyInfo.Name);
            obj.Add("nickname", MyInfo.NickName);
            obj.Add("stream_id", Convert.ToInt32(MyInfo.StreamId));
            obj.Add("terminal_type", 1);
            obj.Add("role", 0);
            obj.Add("vstate", 1);
            obj.Add("astate", 1);
            JArray qj = new JArray();
            JObject stream1 = new JObject();
            //小码流
            stream1.Add("id", 1);
            stream1.Add("type", 1);
            stream1.Add("width", 320);
            stream1.Add("height", 240);
            stream1.Add("bitrate", 1500);
            stream1.Add("fps", 25);
            stream1.Add("channel", 1);
            qj.Add(stream1);
            // 大码流
            JObject stream2 = new JObject();
            stream2.Add("id", 2);
            stream2.Add("type", 0);
            stream2.Add("width", 1280);
            stream2.Add("height", 720);
            stream2.Add("bitrate", 1500);
            stream2.Add("fps", 25);
            stream2.Add("channel", 1);
            qj.Add(stream2);

            obj.Add("streams", qj);
            return obj.ToString();
        }

        public int OpenMic(int micIndex = -1)
        {
            if(micIndex == -1)
            {
                micIndex = MyInfo.MicIndex;
            }
            int ret = input.OpenMic(ref micIndex, audioSample, audioChannel);
            if(ret != 0)
            {
                return ret;
            }
            MyInfo.Mic = true;
            // 在输出源中叠加输入源(音频)
            VcsNative.VCS_AddInput(
                output,       // 输出句柄
                input.audioInput,   // 输入句柄
                0,          // 输入源在输出画面中叠加的位置
                0,           // 输入源在输出画面中叠加的位置
                1,         // 输入源在输出画面中叠加的宽度
                1,        // 输入源在输出画面中叠加的高度
                1,             // 是否使用该输入源的audio(有声音源有效是 1-使用 0-不使用)
                0,             // 是否使用该输入源的video(有声音源有效是 1-使用 0-不使用)
                1);            // 缓存最少帧数目 这个是一个抖动源

            // 更新输出
            VcsNative.VCS_UpdateOutput(output);

            // 开始发送音频
            VcsNative.VCS_EnableSendAudio(roomHandle, 0, 1);

            JObject j = new JObject();
            j.Add("astate", 0);
            SetAccountInfo(j.ToString());

            return 0;
        }

        public int CloseMic()
        {
            int ret = input.CloseMic();
            if (ret != 0)
            {
                return ret;
            }
            MyInfo.Mic = false;

            // 移除输入源
            VcsNative.VCS_RemoveInput(output, input.audioInput);

            // 更新输出
            VcsNative.VCS_UpdateOutput(output);
            input.audioInput = -1;

            // 停止发送音频
            VcsNative.VCS_EnableSendAudio(roomHandle, 0, 0);

            JObject j = new JObject();
            j.Add("astate", 1);
            SetAccountInfo(j.ToString());
            
            return 0;
        }

        
        public int OpenCamera(IntPtr hwnd,int CameraIndex = -1,int CameraExIndex = -1)
        {
            if(CameraIndex == -1)
            {
                CameraIndex = MyInfo.CameraIndex;
            }

            if (CameraExIndex == -1)
            {
                CameraExIndex = MyInfo.CameraResolution;
            }

            if (Info.noVideo)
            {
                return -1;
            }
            VideoSize vs = new VideoSize();
            int ret = input.OpenCamera(ref CameraIndex, ref CameraExIndex, hwnd,ref vs);
            if(ret != 0)
            {
                return ret;
            }
            MyInfo.Camera = true;
            // 调整图像位置和尺寸
            int left = 0;
            int top = 0;
            int width = vs.width;
            int height = vs.height;
            VcsNative.VCS_AdjustPicture(
                vs.width,    // 编码画布宽
                vs.height,   // 编码画布高
                vs.width,     // 图像宽
                vs.height,    // 图像高
                out left,
                out top,
                out width,
                out height);

            // 在输出源中叠加输入源(视频)
            VcsNative.VCS_AddInput(
                output,       // 输出句柄
                input.cameraInput,  // 输入句柄
                left,          // 输入源在输出画面中叠加的位置
                top,           // 输入源在输出画面中叠加的位置
                width,         // 输入源在输出画面中叠加的宽度
                height,        // 输入源在输出画面中叠加的高度
                0,             // 是否使用该输入源的audio(有声音源有效是 1-使用 0-不使用)
                1,             // 是否使用该输入源的video(有声音源有效是 1-使用 0-不使用)
                1);            // 缓存最少帧数目 这个是一个抖动源

            // 更新输出
            VcsNative.VCS_UpdateOutput(output);

            // 开始发送视频
            VcsNative.VCS_EnableSendVideo(roomHandle, 0, 1);

            // 设置自己的帐号信息
            StreamData acc = GetAccount(vs.fps, vs.bitrate, vs.width, vs.height);
            SetAccountInfo(acc.ToJson().ToString());
            return 0;
        }

        void SetAccountInfo(string json,int updata = 1)
        {
            //IntPtr i = Marshal.StringToHGlobalAuto(json);
            var bts=Encoding.UTF8.GetBytes(json);
            IntPtr i=Marshal.AllocHGlobal(bts.Length+10);
            Marshal.Copy(bts, 0, i, bts.Length);

            VcsNative.VCS_SetAccountInfo(roomHandle, i, updata);
            Marshal.FreeHGlobal(i);
        }

        void SetAccountNetWork(int delay,int rate,double uplose,int signal)
        {
            JObject j = new JObject();
            j.Add("delay", delay);
            j.Add("up_rate", rate);
            j.Add("up_lost", uplose);
            j.Add("net_level", signal);
            j.Add("nickname", MyInfo.NickName);
            SetAccountInfo(j.ToString(),0);
        }

        private int CloseCamOutput()
        {
            int ret = input.CloseCamera();
            if (ret != 0)
            {
                return ret;
            }
            // 移除输入源
            VcsNative.VCS_RemoveInput(output, input.cameraInput);

            // 更新输出
            VcsNative.VCS_UpdateOutput(output);
            input.cameraInput = -1;
            return 0;
        }

        public int CloseCam()
        {
            int ret = CloseCamOutput();
            if (ret != 0)
            {
                return ret + 100;
            }
            MyInfo.Camera = false;
            VcsNative.VCS_EnableSendVideo(roomHandle, 0, 0);
            JObject j = new JObject();
            j.Add("vstate", 1);

            SetAccountInfo(j.ToString());
            return 0;
        }



        public async Task<int> CloseRoom()
        {
            if (!isEnterRoom)
            {
                return -1;
            }
            isEnterRoom = false;

            MemberDataDic.Clear();
            if (timer!= null)
            {
                timer.Stop();
                timer.Dispose();
                timer = null;
            }

            VcsNative.VCS_SetCtrlDisplay(0x03, IntPtr.Zero);

            if(roomHandle != IntPtr.Zero)
            {
                VcsNative.VCS_ExitRoom(roomHandle);
                roomHandle = IntPtr.Zero;
            }

            VcsNative.VCS_Room_Cleanup();
            output = -1;
            return 0;
        }

        public string UTF8ToUnicode(string recvStr)
        {
            byte[] tempStr = Encoding.UTF8.GetBytes(recvStr);
            byte[] tempDef = Encoding.Convert(Encoding.UTF8, Encoding.Default, tempStr);
            string msgBody = Encoding.Default.GetString(tempDef);
            return msgBody;
        }
        public string UnicodeToUTF8(string sendStr)
        {
            byte[] tempStr = Encoding.UTF8.GetBytes(sendStr+"i");
            string msgBody = Encoding.Default.GetString(tempStr, 0, tempStr.Length - 1);
            return msgBody;
        }

        private StreamData GetAccount(int fps,int bitrate,int outWidth,int outHeight)
        {
            StreamData acc = new StreamData();

            acc.Id = MyInfo.UserId;
            acc.Name = MyInfo.Name;

            acc.NickName = MyInfo.NickName;
            acc.StreamId = MyInfo.StreamId;
            acc.TerminalType = 1;           //设备类型,1是pc
            acc.Role = 2;//(int)Info.Role;
            acc.VState = MyInfo.Camera ? 0 : 1;
            acc.AState = MyInfo.Mic ? 0 : 1;
            acc.Portrait = MyInfo.Portrait;

            acc.Streams = new List<Stream>();

            Stream s = new Stream();
            s.Id = 1;
            s.Type = 1;
            s.Width = 320;
            s.Height = 240;
            s.Bitrate = bitrate;
            s.Fps = fps;
            s.Channel = audioChannel;
            acc.Streams.Add(s);

            Stream s2 = new Stream();
            s2.Id = 2;
            s2.Type = 0;
            s2.Width = outWidth;
            s2.Height = outHeight;
            s2.Bitrate = bitrate;
            s2.Fps = fps;
            s2.Channel = audioChannel;
            acc.Streams.Add(s2);

            return acc;
        }

        private void onTimer(object sender, ElapsedEventArgs e)
        {
            VcsNative.VCS_DisplayFrame();
        }
    }
}

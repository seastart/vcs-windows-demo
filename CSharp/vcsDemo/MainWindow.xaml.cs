using apiSdk;
using apiSdk.Models;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using vcsDemo.Classes;
using vcsDemo.Model;
using vcsSdk;
using vcsSdk.Enums;
using vcsSdk.Models;

namespace vcsDemo
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            _mw = this;
        }
        string Token { get; set; }



        int selectMemberId { get; set; }
        string Appkey { get; set; }
        string Appid { get; set; }
        UserData userData { get; set; }
        RoomData roomData { get; set; }
        public VcsSdk sdk = new VcsSdk();
        ApiSdk api = null;
        private static MainWindow _mw;
        internal static MainWindow MW { get { return _mw; } }
        ObservableCollection<MemData> MemDataList = new ObservableCollection<MemData>();
        //MyView OtherScreen = new MyView();
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            Appid = "<# 替换成平台分配的AppID #>";
            Appkey = "<# 替换成平台分配的AppID #>";
            this.txtUrl.Text = "";
            this.txtAccount.Text = "";
            this.txtPass.Text = "";


            this.txtTitle.Text = "房间标题";
            this.txtRoomNo.Text = "";

            this.txtMic.Text = "0";
            this.txtCam.Text = "0";
            this.txtCamEx.Text = "0";

            sdk.Init(new RoomMsgCallBack());

            this.txtRoomNo.Text = "";
            lv.ItemsSource = MemDataList;
            lv.SelectionChanged += Lv_SelectionChanged;

            this.wrapJoin.IsEnabled = false;
            this.wrapMeeting.IsEnabled = false;


            IntPtr hwnd = ((HwndSource)PresentationSource.FromVisual(img)).Handle;

            IntPtr handle = new WindowInteropHelper(this).Handle;

        }

        internal void ReEnterRoom()
        {
            ThreadPool.QueueUserWorkItem(OnReEnterRoom);
        }

        private void OnReEnterRoom(object state)
        {

            this.Dispatcher.Invoke(new Action(() =>
            {
                Thread.Sleep(500);
                sdk.CloseRoom();
                MemDataList.Clear();
                MessageBoxResult ret = MessageBox.Show("是否重新入会 ?", "错误", MessageBoxButton.YesNo);
                if (ret == MessageBoxResult.Yes)
                {
                    AppendMsg("开始重新入会！");
                    JoinMeeting();
                }
            }));
        }

        private void Lv_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            MemData md = (MemData)lv.SelectedItem;
            if (md == null)
            {
                return;
            }
            this.lblSelectUser.Content = md.Name;
            selectMemberId = md.ID;
        }

        private void Button_Click_Login(object sender, RoutedEventArgs e)
        {
            api = new ApiSdk(this.txtUrl.Text, Appid, Appkey);

            UserData ud = null;
            Tuple<bool, string> res = api.Login(this.txtAccount.Text, this.txtPass.Text, ref ud);
            if (res.Item1)
            {

                userData = ud;
                this.wrapJoin.IsEnabled = true;
                this.wrapMeeting.IsEnabled = true;
            }
            AppendMsg("登录！~" + res.Item1 + " ,  " + res.Item2);

        }

        public void AppendMsg(string msg)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                this.txtMsg.Text += msg + "\r\n";
                Console.WriteLine(msg);
            }));
        }

        private void btnCreate_Click(object sender, RoutedEventArgs e)
        {
            string roomTitle = this.txtTitle.Text;
            Conference ud = null;
            Dictionary<string, string> map = new Dictionary<string, string>();
            map.Add("title", roomTitle);                                        //标题
            map.Add("content", "");                                             //内容
            map.Add("type", "1");                                               //会议类型1-即时会议；2-预约会议
            map.Add("begin_at", DateTime.Now.Ticks.ToString());                 //开始时间
            map.Add("duration", "3600");                                        //会议时长 单位秒 3600 = 半小时
            map.Add("corp_id", userData.Corp.Id);                               //成员
            map.Add("members", "[{\"id\":\"" + userData.Account.Id + "\",\"role\":1}]"); //成员信息
            Tuple<bool, string> res = api.ConferenceCreate(map, ref ud);    //
            AppendMsg("创建会议！~" + res.Item1 + " ,  " + res.Item2);
            this.txtRoomNo.Text = ud.Room.No;
            if (res.Item1)
            {
                JoinMeeting();
            }
        }



        private void btnJoin_Click(object sender, RoutedEventArgs e)
        {
            JoinMeeting();
        }


        private void btnJoin2_Click(object sender, RoutedEventArgs e)
        {
            JoinMeeting(2);
        }

        private void JoinMeeting(int streamtype = 1)
        {
            int ret = -1;
            string room_no = this.txtRoomNo.Text;
            RoomData ud = null;
            Tuple<bool, string> res = api.RoomEnter(room_no, ref ud);
            AppendMsg("用户：" + userData.Account.Nickname + "api 加入会议！~" + res.Item1 + " ,  " + res.Item2);
            if (res.Item1)
            {
                roomData = ud;
                RoomInfo roomInfo = new RoomInfo();
                roomInfo.Load(roomData);
                RoomMyInfo myInfo = new RoomMyInfo();
                myInfo.Load(userData, this.MeScreen.Handle);
                ret = sdk.EnterRoom(roomInfo, myInfo, streamtype);
                if (ret == 0)
                {
                    AppendMsg("sdk 加入房间成功！~");

                }
            }
        }

        private void btnQuit_Click(object sender, RoutedEventArgs e)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                sdk.CloseRoom();

                string room_no = this.txtRoomNo.Text;
                Tuple<bool, string> res = api.RoomExit(room_no);
                AppendMsg("用户：" + userData.Account.Nickname + "api 主动退出会议！~" + res.Item1 + " ,  " + res.Item2);
                MemDataList.Clear();
            }));
        }

        private void btnOpenMic_Click(object sender, RoutedEventArgs e)
        {
            int micIndex = int.Parse(this.txtMic.Text);
            int ret = sdk.OpenMic(micIndex);
            AppendMsg("打开摄像头：" + ret);
        }

        private void btnCloseMic_Click(object sender, RoutedEventArgs e)
        {
            int ret = sdk.CloseMic();
            AppendMsg("关闭摄像头：" + ret);
        }

        private void btnOpenCam_Click(object sender, RoutedEventArgs e)
        {
            int camIndex = int.Parse(this.txtCam.Text);
            int camExIndex = int.Parse(this.txtCamEx.Text);
            int ret = sdk.OpenCamera(this.MeScreen.Handle, camIndex, camExIndex);
            AppendMsg("打开摄像头：" + ret);
        }

        private void btnCloseCam_Click(object sender, RoutedEventArgs e)
        {
            int ret = sdk.CloseCam();
            AppendMsg("关闭摄像头：" + ret);
        }

        private void btnOpenSpeaker_Click(object sender, RoutedEventArgs e)
        {
            sdk.OpenSpeaker(0);
        }

        private void btnCloseSpeaker_Click(object sender, RoutedEventArgs e)
        {
            sdk.CloseSpeaker();
        }

        private void btnHostWaterMarkOpen_Click(object sender, RoutedEventArgs e)
        {
            sdk.HostWaterMark(true);
        }

        private void btnHostWaterMarkClose_Click(object sender, RoutedEventArgs e)
        {
            sdk.HostWaterMark(false);
        }

        private void btnHostRoomMute_Click(object sender, RoutedEventArgs e)
        {
            sdk.HostRoomMute(true);
        }

        private void btnHostRoomUnMute_Click(object sender, RoutedEventArgs e)
        {
            sdk.HostRoomMute(false);
        }
        private void btnHostMute_Click(object sender, RoutedEventArgs e)
        {
            sdk.HostMemberMute(selectMemberId, true);
        }

        private void btnHostUnMute_Click(object sender, RoutedEventArgs e)
        {
            sdk.HostMemberMute(selectMemberId, true);
        }

        private void btnShare_Click(object sender, RoutedEventArgs e)
        {
            //            <RadioButton x:Name="rbtnDesk" Content="桌面" IsChecked="True"></RadioButton>
            //<RadioButton x:Name="rbtnWhiteBoard" Content="白板"></RadioButton>
            //<RadioButton x:Name="rbtnImageBoard" Content="图片"></RadioButton>

            int index = 0;
            if (rbtnDesk.IsChecked ?? false)
            {
                index = 3;
            }
            else if (rbtnWhiteBoard.IsChecked ?? false)
            {
                index = 1;
            }
            else if (rbtnImageBoard.IsChecked ?? false)
            {
                index = 2;
            }
            sdk.StartShare(index);
        }

        private void btnShareClose_Click(object sender, RoutedEventArgs e)
        {
            sdk.CloseShare();
        }

        private void btnWaterMarkOpen_Click(object sender, RoutedEventArgs e)
        {
        }

        private void btnWaterMarkClose_Click(object sender, RoutedEventArgs e)
        {
            sdk.CloseWaterMark(selectMemberId);
        }

        private void btnHostLock_Click(object sender, RoutedEventArgs e)
        {

            Tuple<bool, string> res = api.LockMeeting(sdk.Info.roomId, true);
            AppendMsg("锁定会议！~" + res.Item1 + " ,  " + res.Item2);
        }

        private void btnHostUnLock_Click(object sender, RoutedEventArgs e)
        {
            Tuple<bool, string> res = api.LockMeeting(sdk.Info.roomId, false);
            AppendMsg("锁定会议！~" + res.Item1 + " ,  " + res.Item2);
        }

        private void btnHandUp_Click(object sender, RoutedEventArgs e)
        {
            sdk.HandUp(EnuHandUp.UnMute);
        }

        private void btnHandUpNo_Click(object sender, RoutedEventArgs e)
        {
            sdk.HandUp(EnuHandUp.None);
        }

        private void btnChatAll_Click(object sender, RoutedEventArgs e)
        {
            sdk.SendChat(0, this.txtChat.Text);
        }

        private void btnBackHost_Click(object sender, RoutedEventArgs e)
        {
            sdk.RecoveryHost();
        }

        private void rbtn1S_Click(object sender, RoutedEventArgs e)
        {
            sdk.StatInterval(1);
        }

        private void rbtn10S_Click(object sender, RoutedEventArgs e)
        {
            sdk.StatInterval(10);
        }

        private void btnAudioFirst_Click(object sender, RoutedEventArgs e)
        {
            sdk.AudioFirst(selectMemberId);
        }

        private void btnUnAudioFirst_Click(object sender, RoutedEventArgs e)
        {
            sdk.UnAudioFirst(selectMemberId);
        }

        private void btnChat_Click(object sender, RoutedEventArgs e)
        {
            sdk.SendChat(selectMemberId, this.txtChat.Text);
        }

        private void btnMoveHost_Click(object sender, RoutedEventArgs e)
        {
            sdk.UnionHost(selectMemberId);
        }

        private void btnUnionHost_Click(object sender, RoutedEventArgs e)
        {
            sdk.UnionHost(selectMemberId);
        }

        private void btnUnUnionHost_Click(object sender, RoutedEventArgs e)
        {
            sdk.UnUnionHost(selectMemberId);
        }

        private void btnMemberOpenCam_Click(object sender, RoutedEventArgs e)
        {
            sdk.OpenMemView(panel.Handle, selectMemberId, 1);//默认小流

        }
        private void btnMemberOpenCam2_Click(object sender, RoutedEventArgs e)
        {
            sdk.OpenMemView(panel.Handle, selectMemberId, 2);//默认小流
        }

        private void OtherScreen_MouseDoubleClick(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            ShowMaxWindow();
            WindowInteropHelper wndHelper = new WindowInteropHelper(maxWindow);
            IntPtr wpfHwnd = wndHelper.Handle;
            sdk.OpenMemView(wpfHwnd, selectMemberId, 0);//0 是大流
        }

        Window maxWindow = null;
        private void ShowMaxWindow()
        {
            if (maxWindow == null)
            {
                maxWindow = new Window();
                maxWindow.Closed += MaxWindow_Closed;
            }
            maxWindow.Show();
        }

        private void MaxWindow_Closed(object sender, EventArgs e)
        {
            maxWindow = null;
        }

        private void btnHostHandUpNo_Click(object sender, RoutedEventArgs e)
        {
            int hus = ((MemData)lv.SelectedItem).HandUp;
            sdk.HostDealHandUp(selectMemberId, hus, false);
        }

        private void btnHostHandUpOk_Click(object sender, RoutedEventArgs e)
        {

            int hus = ((MemData)lv.SelectedItem).HandUp;
            sdk.HostDealHandUp(selectMemberId, hus, true);
        }
        #region 房间成员
        internal void OpenShareView(int type, int sharingStreamId, int v)
        {
            switch (type)
            {
                case 0:
                    {
                        sdk.CloseShareView(sharingStreamId);
                        break;
                    }
                case 1:
                case 2:
                    {
                        //电子白板逻辑
                        MessageBox.Show("电子白板逻辑");
                        break;
                    }
                case 3:
                    {
                        this.Dispatcher.Invoke(new Action(() =>
                        {
                            Window w = new Window();
                            w.Loaded += (s, e) =>
                            {
                                IntPtr hwnd = ((HwndSource)PresentationSource.FromVisual(w)).Handle;
                                sdk.OpenShareView(hwnd, sharingStreamId, v);
                            };
                            w.Show();

                        }));

                        break;
                    }
            }
        }
        internal void addMemData(StreamData data)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                MemData md = new MemData();
                md.ID = data.StreamId.Value;
                md.Name = data.NickName;
                md.CamState = data.VState.Value;
                md.MicState = data.AState.Value;
                md.Network = data.NetLevel.Value;
                md.HandUp = data.Hus.Value;
                md.Role = data.Role.Value;
                MemDataList.Add(md);
                //if (md.CamState == 0)
                //{
                //    this.Dispatcher.BeginInvoke(new Action(() =>
                //    {
                //        AppendMsg("加载成员画面" + md.Name);
                //        System.Windows.Forms.Form w = new System.Windows.Forms.Form();
                //        w.Show();
                //        sdk.OpenMemView(w.Handle, md.ID, 1);//默认小流
                //    }));
                //}
            }));
        }

        public void SetMemData(EnuUserChnage enu, StreamData data)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                foreach (var md in MemDataList)
                {
                    if (md.ID == data.StreamId)
                    {
                        if ((enu & EnuUserChnage.Hus) > 0)       //修改了举手状态
                        {
                            md.HandUp = data.Hus.Value;
                            AppendMsg("成员：" + md.Name + "，举手状态改变：" + md.HandUp);
                        }
                        if ((enu & EnuUserChnage.Audio) > 0)    //修改了音频状态
                        {
                            md.MicState = data.AState.Value;
                            AppendMsg("成员：" + md.Name + "，音频状态改变：" + md.MicState);
                        }
                        if ((enu & EnuUserChnage.Video) > 0)    //修改了视频状态
                        {
                            md.CamState = data.VState.Value;
                            AppendMsg("成员：" + md.Name + "，视频状态改变：" + md.CamState);
                        }
                        if ((enu & EnuUserChnage.Role) > 0)     //修改了权限状态
                        {
                            md.Role = data.Role.Value;
                            AppendMsg("成员：" + md.Name + "，角色状态改变：" + md.Role);
                        }
                        if ((enu & EnuUserChnage.NetLevel) > 0)  //修改了网络状态
                        {
                            md.Network = data.NetLevel.Value;
                            AppendMsg("成员：" + md.Name + "，网络状态改变：" + md.Network);
                        }
                        break;
                    }
                }
            }));
        }

        internal void CloseMeeting()
        {

        }

        public void SetMemDataNetWork(Dictionary<int, RecvNetWork> RecvNetWorkDic)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                foreach (var md in MemDataList)
                {
                    if (RecvNetWorkDic.ContainsKey(md.ID))
                    {
                        md.AudioPack = RecvNetWorkDic[md.ID].Audio;
                        md.VideoPack = RecvNetWorkDic[md.ID].Video;
                        md.AllPack = RecvNetWorkDic[md.ID].Recv;
                        md.AllLosePack = RecvNetWorkDic[md.ID].Losf;
                        md.ReLoaePack = RecvNetWorkDic[md.ID].Comp;
                        md.ServerLose = RecvNetWorkDic[md.ID].Lr2;
                        md.ClientLose = RecvNetWorkDic[md.ID].Lr1;
                    }
                }
            }));
        }

        public void SetMemDataGear(int id, int gear)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                foreach (var md in MemDataList)
                {
                    if (md.ID == id)
                    {
                        md.Gaer = gear;
                        break;
                    }
                }
            }));
        }

        public void RemoveMemData(int id)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                foreach (var md in MemDataList)
                {
                    if (md.ID == id)
                    {
                        MemDataList.Remove(md);
                        break;
                    }
                }
            }));
        }

        public void SetDb()
        {

        }
        #endregion

        #region 我的状态
        public void HostSetMeData(EnuUserChnage enu)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                if ((enu & EnuUserChnage.Audio) > 0)    //修改了音频状态
                {
                    this.lblAudio.Content = sdk.MyInfo.Mic;
                    AppendMsg("您的音频状态改变：" + sdk.MyInfo.Mic);
                }
                if ((enu & EnuUserChnage.Video) > 0)    //修改了视频状态
                {
                    this.lblAudio.Content = sdk.MyInfo.Camera;
                    AppendMsg("您的视频状态改变：" + sdk.MyInfo.Camera);
                }
                if ((enu & EnuUserChnage.Role) > 0)     //修改了权限状态
                {
                    this.lblAudio.Content = sdk.Info.Role;
                    AppendMsg("您的角色状态改变：" + sdk.Info.Role);
                }
            }));
        }

        public void HostSetMeHus(int type, int res)
        {
            AppendMsg("主持人处理了你的举手类型：" + type + ",处理结果：" + res);
        }

        public void SetMeGear(int gear)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                this.lblGear.Content = gear.ToString();
            }));
        }

        public void SetMeNetWork(int Rate, int delay, double lose, double reLose, int netWork)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                this.lblRate.Content = Rate.ToString();
                this.lblDelay.Content = delay.ToString();
                this.lblLose.Content = lose.ToString();
                this.lblReLose.Content = reLose.ToString();
                this.lblNetwork.Content = netWork.ToString();
            }));
        }

        #endregion

        #region 房间状态
        public void SetRoomDate(EnuRoomChange enu)
        {
            this.Dispatcher.Invoke(new Action(() =>
            {
                if ((enu & EnuRoomChange.Lock) > 0)    //修改了房间锁定状态
                {
                    this.lblLock.Content = sdk.Info.roomData.Locked;
                    AppendMsg("房间锁定状态改变：" + sdk.Info.roomData.Locked);
                }
                if ((enu & EnuRoomChange.Audio) > 0)    //修改了房间音频状态
                {
                    this.lblRoomAudio.Content = sdk.Info.roomData.Astate;
                    AppendMsg("房间音频状态改变：" + sdk.Info.roomData.Astate);
                }
                if ((enu & EnuRoomChange.Video) > 0)    //修改了房间视频状态
                {
                    this.lblRoomVideo.Content = sdk.Info.roomData.Vstate;
                    AppendMsg("房间视频状态改变：" + sdk.Info.roomData.Vstate);
                }
                if ((enu & EnuRoomChange.SharingType) > 0)    //修改了房间类型状态
                {
                    this.lblShareType.Content = sdk.Info.roomData.SharingType;
                    AppendMsg("房间共享状态改变：" + sdk.Info.roomData.SharingType);
                }
                if ((enu & EnuRoomChange.WaterMark) > 0)    //修改了房间水印状态
                {
                    this.lblLock.Content = sdk.Info.roomData.WaterMark;
                    AppendMsg("房间水印状态改变：" + sdk.Info.roomData.WaterMark);
                }
            }));
        }
        #endregion

        private void Button_Click_Register(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_Register_Crop(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click_Crop_Add(object sender, RoutedEventArgs e)
        {

        }

        private void Window_Closed(object sender, EventArgs e)
        {
            sdk.CleanUp();
        }

        private void txtMsg_TextChanged(object sender, TextChangedEventArgs e)
        {
            txtMsg.ScrollToEnd();
        }

        private void btnShareRectChange_Click(object sender, RoutedEventArgs e)
        {
            sdk.ShareRectChange(0, 0, 500, 500);
        }

        private void btnTest_Click(object sender, RoutedEventArgs e)
        {
            //    public static (JObject jpms)
            //    {
            //        WndCaptureItem item = new WndCaptureItem();

            //item.Desktop = int.Parse(jpms["desktop"].ToString());
            //item.Ctx = new IntPtr((long) jpms["ctx"]);
            //item.Hwnd = new IntPtr((long) jpms["hwnd"]);
            //item.Title = (string) jpms["title"];
            //item.Rect = ((string) jpms["rect"]);
            //        item.ParseRect((string) jpms["rect"]);
            //        return item;
            //    }
            sdk.CloseCam();

            JObject json = new JObject();
            json.Add("rect", "0,0,200,300");
            json.Add("hwnd", 0);
            json.Add("desktop", 1);
            json.Add("ctx", 1);
            json.Add("title","123");
            sdk.DealScreenShare2(vcsSdk.Classes.WndCaptureItem.Parse(json));
        }

        private void btnTest2_Click(object sender, RoutedEventArgs e)
        {
            sdk.DealCloseShare(false);

            int camIndex = int.Parse(this.txtCam.Text);
            int camExIndex = int.Parse(this.txtCamEx.Text);
            int ret = sdk.OpenCamera(this.MeScreen.Handle, camIndex, camExIndex);
        }

        private void Button_Click_Menu(object sender, RoutedEventArgs e)
        {
            
        }


    }
}
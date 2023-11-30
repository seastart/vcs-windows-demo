using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using vcsSdk.Enums;
using vcsSdk.Interface;
using vcsSdk.Models;

namespace vcsDemo.Classes
{
    class RoomMsgCallBack : IRoomMsgCallBack
    {
        public void AddMemberData(StreamData data)
        {
            MainWindow.MW.addMemData(data);
        }

        public void DeviceChange()
        {
            MainWindow.MW.AppendMsg("系统系统发生了变化！~");
        }

        public void DeviceFail()
        {
            MainWindow.MW.AppendMsg("系统驱动异常无法加载视频！~");
        }

        public void HostHandUpResult(int hus, int result)
        {
            MainWindow.MW.AppendMsg("主持人"+ ((result == 0)?"同意":"拒绝") + "了你的举手类型:"+hus);
        }

        public void MediaConnect()
        {
            MainWindow.MW.AppendMsg("流媒体连接成功！~");
        }

        public void MeetingEnd()
        {
            MainWindow.MW.CloseMeeting();
            MainWindow.MW.AppendMsg("会议已结束");
        }

        public void MeetingKickOut()
        {
            MainWindow.MW.CloseMeeting();
            MainWindow.MW.AppendMsg("您被主持人请出了会议");
        }

        public void MemberDataChange(StreamData data, EnuUserChnage enu)
        {
            MainWindow.MW.SetMemData(enu,data);
        }

        public void MemNetStateChagne(int streamId, int state)
        {
            MainWindow.MW.AppendMsg(MainWindow.MW.sdk.GetMemUser()[streamId].data.NickName + "网络档位发生了变化："+ state);
        }

        public void MeNetStateChagne(int state)
        {
            MainWindow.MW.AppendMsg("您的网络档位发生了变化："+ state);
        }

        public void MyDataChange(EnuUserChnage enu)
        {
            MainWindow.MW.HostSetMeData(enu);
        }

        public void NetWorkRecvData(Dictionary<int, RecvNetWork> recvNetWorkDic)
        {
            MainWindow.MW.SetMemDataNetWork(recvNetWorkDic);
        }

        public void NetWorkUpData(int delay, int rate, double first_lost, double re_lost, int signal)
        {
            MainWindow.MW.SetMeNetWork(rate, delay, first_lost, re_lost, signal);
        }

        public void RecvChatMsg(ChatMsg cm)
        {
            MainWindow.MW.AppendMsg("收到"+((cm.TargetId == null) ? "全体" : cm.AccountName)+"聊天消息：" + cm.Message);
        }

        public void RemoveMemberData(int streamId)
        {
            MainWindow.MW.AppendMsg(MainWindow.MW.sdk.GetMemUser()[streamId].data.NickName + "离开了会议");
        }

        public void RoomChange(EnuRoomChange enu)
        {
            MainWindow.MW.SetRoomDate(enu);
        }

        /// <summary>
        /// 房间入会结果。
        /// </summary>
        /// <param name="res"></param>
        public void RoomEnterFinish(int res)
        {
            MainWindow.MW.AppendMsg("房间连接！~"+res);

            if(res != 0)
            {
                MainWindow.MW.ReEnterRoom();
            }
        }

        public void ShareShowClose(int type, int sharingStreamId,int v)
        {
            MainWindow.MW.OpenShareView(type, sharingStreamId,v);
        }

        public void ShareStart()
        {
            MainWindow.MW.AppendMsg("开始了桌面共享。~");
        }

        public void StopShare()
        {

            MainWindow.MW.AppendMsg("结束了桌面共享。~");
        }
    }
}

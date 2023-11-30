using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using vcsSdk.Enums;
using vcsSdk.Models;

namespace vcsSdk.Interface
{
    public interface IRoomMsgCallBack
    {
        void RoomEnterFinish(int res);
        void AddMemberData(StreamData data);
        void MemberDataChange(StreamData data, EnuUserChnage enu);
        void RemoveMemberData(int streamId);
        void MeetingEnd();
        void MeetingKickOut();
        void MyDataChange(EnuUserChnage enu);
        void NetWorkUpData(int delay, int rate, double first_lost, double re_lost, int signal);
        void NetWorkRecvData(Dictionary<int, RecvNetWork> recvNetWorkDic);
        void DeviceFail();
        void RecvChatMsg(ChatMsg cm);
        void DeviceChange();
        void HostHandUpResult(int hus, int result);
        void RoomChange(EnuRoomChange enu);
        void MeNetStateChagne(int state);
        void MemNetStateChagne(int streamid,int state);
        void ShareShowClose(int type, int sharingStreamId, int v = -1);
        void ShareStart();
        void StopShare();
        void MediaConnect();
    }
}

using apiSdk.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using vcsSdk.Enums;

namespace vcsSdk.Models
{
    public class RoomInfo
    {
        public RoomInfo()
        {
        }

        public void Load(RoomData rd)
        {
            this.roomId = rd.Room.Id;
            this.roomNo = rd.Room.No;
            this.roomSdkNo = rd.SdkNo;
            this.roomSession = rd.Session;
            this.meetingHost = rd.MeetingHost;
            this.meetingPort = rd.MeetingPort;
            this.streamHost = rd.StreamHost;
            this.streamPort = rd.streamPort;
            this.type = rd.Type;
            if (this.type == 2)
            {
                this.LowerId = rd.Conf.Id;
            }
            else
            {
                this.LowerId = rd.Account.Id;
            }
            this.Role = (EnuRole)rd.Role;
            this.RoomCreator = rd.Conf.AccountId;
        }

        public string RoomCreator { get; internal set; }
        /// <summary>
        /// 房间内你的角色
        /// </summary>
        public EnuRole Role { get; internal set; }

        /// <summary>
        /// 房间id
        /// </summary>
        public string roomId { get; private set; }

        /// <summary>
        /// 目标房间sdkno
        /// </summary>
        public string roomSdkNo { get; private set; }
        /// <summary>
        /// 房间号
        /// </summary>
        public string roomNo { get;private set; }

        /// <summary>
        /// 房间Session
        /// </summary>
        public string roomSession {get;private set;}

        /// <summary>
        /// 会按服务器
        /// </summary>
        public string meetingHost {get;private set;}

        /// <summary>
        /// 会按服务器端口号
        /// </summary>
        public int meetingPort {get;private set;}

        /// <summary>
        /// 流媒体服务器ip
        /// </summary>
        public string streamHost {get;private set;}
        /// <summary>
        /// 流媒体服务器端口号
        /// </summary>
        public int streamPort {get;private set;}

        /// <summary>
        /// 房间类型（1-用户房间 ，2-会议房间）
        /// </summary>
        public int type {get;private set;}

        /// <summary>
        /// 房间类型对应的id（1- 用户的id,2- 会议的id）
        /// </summary>
        public string LowerId {get;private set;}
        /// <summary>
        /// 无显卡，无视频
        /// </summary>
        public bool noVideo { get; internal set; }
        public NotifyRoom roomData { get; internal set; }

    }
}

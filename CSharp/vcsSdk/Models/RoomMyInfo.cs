using apiSdk.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Models
{
    public class RoomMyInfo
    {
        public RoomMyInfo()
        {

        }

        public void Load(UserData ud,IntPtr handle)
        {
            this.SpeakerIndex = 0;
            this.CameraIndex = 0;
            this.CameraResolution = 0;
            this.MicIndex = 0;
            this.Name = ud.Account.Name;
            this.NickName = ud.Account.Nickname;
            this.UserId = ud.Account.Id;
            this.StreamId = int.Parse(ud.Account.Room.SdkNo);
            this.Portrait = ud.Account.Portrait;
            this.Handle = handle;
            this.Mobile = ud.Account.Mobile;
            //this.Camera = true;
        }


        /// <summary>
        /// 显示图片的窗口句柄
        /// </summary>
        public IntPtr Handle { get; internal set; }

        /// <summary>
        /// 是否开户扬声器
        /// </summary>
        public bool Speaker { get; internal set; }

        /// <summary>
        /// 扬声器列表选择项
        /// </summary>
        public int SpeakerIndex { get; internal set; }

        /// <summary>
        /// 是否开启摄像头
        /// </summary>
        public bool Camera { get; internal set; }

        /// <summary>
        /// 摄像头列表选择项
        /// </summary>
        public int CameraIndex { get; internal set; }
        
        /// <summary>
        /// 摄像头设备分辨率选项（只保存了16:9）的
        /// </summary>
        public int CameraResolution { get; internal set; } 

        /// <summary>
        /// 是否开户麦克风
        /// </summary>
        public bool Mic { get; internal set; }

        /// <summary>
        /// 麦克风列表选择项
        /// </summary>
        public int MicIndex { get; internal set; }

        /// <summary>
        /// 名称
        /// </summary>
        public string Name { get; internal set; }

        /// <summary>
        /// 昵称
        /// </summary>
        public string NickName { get; internal set; }

        /// <summary>
        /// 手机号
        /// </summary>
        public string Mobile { get; internal set; }

        /// <summary>
        /// 用户id
        /// </summary>
        public string UserId { get; internal set; }

        /// <summary>
        /// sdk_no streamId
        /// </summary>
        public int StreamId { get; internal set; }

        /// <summary>
        /// 头像地址
        /// </summary>
        public string Portrait { get; internal set; }
        
    }
}

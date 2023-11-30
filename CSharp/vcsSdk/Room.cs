using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace vcsSdk.Models
{
    public class Room
    {
        [JsonProperty("id")]
        public string Id { get; set; }

        [JsonProperty("sdk_no")]
        public string SdkNo { get; set; }

        [JsonProperty("wb")]
        public bool? WhiteBoard { get; set; }
        /// <summary>
        /// 1-可以播放音视频；0-不可以播放音视频；
        /// </summary>
        [JsonProperty("state")]
        public int? State { get; set; }

        /// <summary>
        /// 1-帐号连线；2-会议连线；
        /// </summary>
        [JsonProperty("type")]
        public int? LinkType { get; set; }

        /// <summary>
        /// 当前分享者帐号ID
        /// </summary>
        [JsonProperty("sharing_acc_id")]
        public string SharingAccId { get; set; }

        /// <summary>
        /// 1-电子白板;2-图片;3-桌面
        /// </summary>
        [JsonProperty("sharing_type")]
        public int SharingType { get; set; }

        /// <summary>
        /// 分享图片时的图片地址
        /// </summary>
        [JsonProperty("sharing_pic_url")]
        public string SharingPicUrl { get; set; }

        public JObject ToJson()
        {
            return JObject.FromObject(this);
        }


    }
}

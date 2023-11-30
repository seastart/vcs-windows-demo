using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk.Models
{
    public class RoomData
    {
        [JsonProperty("stream_host")]
        public string StreamHost { get; set; }
        [JsonProperty("stream_port")]
        public int streamPort { get; set; }
        [JsonProperty("stream_ws_url")]
        public string StreamWSUrl { get; set; }
        [JsonProperty("wb_host")]
        public string WBHost { get; set; }
        [JsonProperty("meeting_host")]
        public string MeetingHost { get; set; }
        [JsonProperty("meeting_port")]
        public int MeetingPort { get; set; }
        [JsonProperty("meeting_ws_url")]
        public string MeetingWSUrl { get; set; }
        [JsonProperty("session")]
        public string Session { get; set; }
        [JsonProperty("sdk_no")]
        public string SdkNo { get; set; }
        [JsonProperty("role")]
        public int Role { get; set; }
        [JsonProperty("title")]
        public string Title { get; set; }
        [JsonProperty("room")]
        public Room Room { get; set; }
        [JsonProperty("type")]
        public int Type { get; set; }
        [JsonProperty("account")]
        public Account Account { get; set; }
        [JsonProperty("conf")]
        public Conference Conf { get; set; }
    }
}

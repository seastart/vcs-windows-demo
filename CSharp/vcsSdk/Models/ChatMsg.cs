using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Models
{
    public class ChatMsg
    {
        [JsonProperty("account_id")]
        public string AccountId { get; set; }
        [JsonProperty("room_id")]
        public string RoomId { get; set; }
        [JsonProperty("account_name")]
        public string AccountName { get; set; }
        [JsonProperty("account_portrait")]
        public string AccountPortrait { get; set; }
        [JsonProperty("target_id")]
        public string TargetId { get; set; }
        [JsonProperty("message")]
        public string Message { get; set; }
        [JsonProperty("type")]
        public int Type { get; set; }
    }
}

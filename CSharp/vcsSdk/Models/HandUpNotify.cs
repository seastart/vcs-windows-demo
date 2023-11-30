using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Models
{
    public class HandUpNotify
    {
        [JsonProperty("account_id")]
        public string AccountId { get; set; }
        [JsonProperty("account_ame")]
        public string AccountName { get; set; }
        [JsonProperty("hus")]
        public int Hus { get; set; }
        [JsonProperty("result")]
        public int Result { get; set; }
        [JsonProperty("room_id")]
        public string RoomId { get; set; }
    }
}

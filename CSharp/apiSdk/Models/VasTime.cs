using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk.Models
{
    public class VasTime
    {
        [JsonProperty("id")]
        public string Id { get; set; }

        [JsonProperty("account_id")]
        public string AccountId { get; set; }

        [JsonProperty("begin_time")]
        public ulong BeginTime { get; set; }

        [JsonProperty("end_time")]
        public ulong EndTime { get; set; }

        [JsonProperty("type")]
        public VasType VasType { get; set; }
    }
}

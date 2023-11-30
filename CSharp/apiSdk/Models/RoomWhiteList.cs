using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;

namespace apiSdk.Models
{
    public class RoomWhiteList
    {
        [JsonProperty("account")]
        public Account Account { get; set; }

        [JsonProperty("role")]
        public ConferenceRole Role { get; set; }
    }
}

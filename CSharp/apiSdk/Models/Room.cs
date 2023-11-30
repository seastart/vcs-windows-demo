using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;

namespace apiSdk.Models
{
    public class Room
    {
        [JsonProperty("id")]
        public string Id { get; set; }
        [JsonProperty("no")]
        public string No { get; set; }
        [JsonProperty("sdk_no")]
        public string SdkNo { get; set; }
        [JsonProperty("access_pwd")]
        public bool AccessPwd { get; set; }
        [JsonProperty("access_whitelist")]
        public bool AccessWhitelist { get; set; }
        [JsonProperty("password")]
        public string Password { get; set; }
        [JsonProperty("limited")]
        public int Limited { get; set; }
        [JsonProperty("samplerate")]
        public int SampleRate { get; set; }
        [JsonProperty("ol_count")]
        public int OlCount { get; set; }
    }
}

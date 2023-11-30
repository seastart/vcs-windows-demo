﻿using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace vcsSdk.Models
{
    public enum DeviceState
    {
        Active = 0,
        Closed = 1,
        Disabled = 2,
    }


    public class Account
    {
        [JsonProperty("id")]
        public string Id { get; set; }

        [JsonProperty("stream_id")]
        public int? StreamId { get; set; }

        [JsonProperty("name")]
        public string Name { get; set; }

        [JsonProperty("nickname")]
        public string NickName { get; set; }

        [JsonProperty("portrait")]
        public string Portrait { get; set; }

        [JsonProperty("role")]
        public int? Role { get; set; }

        [JsonProperty("vstate")]
        public int? VState { get; set; }

        [JsonProperty("astate")]
        public int? AState { get; set; }

        [JsonProperty("delay")]
        public int? Delay { get; set; }

        [JsonProperty("up_rate")]
        public int? UpRate { get; set; }

        [JsonProperty("down_rate")]
        public int? DownRate { get; set; }

        [JsonProperty("address")]
        public string Address { get; set; }

        [JsonProperty("port")]
        public int? Port { get; set; }

        [JsonProperty("shared_picture")]
        public string SharedPicture { get; set; }

        [JsonProperty("terminal_type")]
        public int? TerminalType { get; set; }

        [JsonProperty("net_level")]
        public int? NetLevel { get; set; }

        [JsonProperty("tag")]
        public string Tag { get; set; }

        [JsonProperty("streams",NullValueHandling =NullValueHandling.Ignore)]
        public List<Stream> Streams { get; set; }

        public Account()
        {
        }

        public JObject ToJson()
        {
            return JObject.FromObject(this);
        }
    }
}

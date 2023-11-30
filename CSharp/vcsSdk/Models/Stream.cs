using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace vcsSdk.Models
{
    public class Stream
    {
        [JsonProperty("id")]
        public int? Id { get; set; }

        [JsonProperty("width")]
        public int? Width { get; set; }

        [JsonProperty("height")]
        public int? Height { get; set; }

        [JsonProperty("bitrate")]
        public int? Bitrate { get; set; }

        [JsonProperty("fps")]
        public int? Fps { get; set; }

        [JsonProperty("type")]
        public int? Type { get; set; }

        [JsonProperty("channel")]
        public int? Channel { get; set; }

        public JObject ToJson()
        {
            return JObject.FromObject(this);
        }
    }
}

using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Models
{
    public class CapsData
    {
        [JsonProperty("ctx")]
        public string Ctx { get; set; }
        [JsonProperty("desktop")]
        public int Desktop { get; set; }
        [JsonProperty("hwnd")]
        public string Hwnd { get; set; }
        [JsonProperty("rect")]
        public string Rect { get; set; }
        [JsonProperty("title")]
        public string Title { get; set; }
    }
}

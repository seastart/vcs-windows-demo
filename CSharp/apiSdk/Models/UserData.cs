using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk.Models
{
    public class UserData
    {

        [JsonProperty("account")]
        public Account Account { get; set; }

        [JsonProperty("token")]
        public string Token { get; set; }

        [JsonProperty("corp")]
        public Corporation Corp { get; set; }

        [JsonProperty("corp_role")]
        public int Corpole{get;set;}

        [JsonProperty("reg")]
        public Reg Reg { get; set; }
    }
}

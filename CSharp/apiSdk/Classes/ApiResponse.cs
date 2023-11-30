using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk.Classes
{
    public class ApiResponse
    {
        [JsonProperty("code")]
        public int Code { get; private set; }

        [JsonProperty("msg")]
        public string Message { get; private set; }

        [JsonProperty("data")]
        public JToken Data { get; private set; }

        public bool IsSuccessed()
        {
            if (Code != 200)
                return false;

            return true;
        }

        public void CheckForThrow()
        {
            if (!IsSuccessed())
                throw new Exception(Message);
        }

    }
}

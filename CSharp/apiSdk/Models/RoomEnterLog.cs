using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using apiSdk.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk.Models
{
    public class RoomEnterLog
    {
        [JsonProperty("id")]
        public string Id { get; set; }
        [JsonProperty("account_id")]
        public string AccountId { get; set; }
        [JsonProperty("account")]
        public Account Account { get; set; }

        [JsonProperty("room_id")]
        public string RoomId { get; set; }
        [JsonProperty("room")]
        public Room Room { get; set; }

        [JsonProperty("created_at")]
        public ulong CreatedAt { get; set; }
        [JsonIgnore]
        public DateTime CreatedTime {
            get {
                return DateTimeUtil.FromUnixTime(CreatedAt);
            }
        }

        [JsonProperty("owner_id")]
        public string OwnerId { get; set; }
        [JsonProperty("owner_type")]
        public OwnerType OwnerType { get; set; }
        [JsonProperty("owner")]
        public object Owner { get; set; }

        public string GetOwnerName()
        {
            if(OwnerType==OwnerType.Account)
            {
                if (Owner != null)
                {
                    Account acc = JObject.FromObject(Owner).ToObject<Account>();
                    return acc.Nickname;
                }
            }
            else if (OwnerType == OwnerType.Conference)
            {
                Conference conf = JObject.FromObject(Owner).ToObject<Conference>();
                return conf.Title;
            }
            return "";
        }

        public string GetPortrait()
        {
            if (OwnerType == OwnerType.Account)
            {
                if (Owner != null)
                {
                    Account acc = JObject.FromObject(Owner).ToObject<Account>();
                    return acc.Portrait;
                }
            }
            else if (OwnerType == OwnerType.Conference)
            {
                //Conference conf = JObject.FromObject(Owner).ToObject<Conference>();
                return "";
            }
            return "";
        }
    }
}

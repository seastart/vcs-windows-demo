using Newtonsoft.Json;
using apiSdk.Utils;
using System;
using System.Collections.Generic;
using System.Text;

namespace apiSdk.Models
{
    

    public class Account
    {
        [JsonProperty("id")]
        public string Id { get; set; }
        [JsonProperty("name")]
        public string Name { get; set; }
        [JsonProperty("nickname")]
        public string Nickname { get; set; }
        [JsonProperty("type")]
        public AccountType Type { get; set; }
        [JsonProperty("portrait")]
        public string Portrait { get; set; }
        [JsonProperty("mobile")]
        public string Mobile { get; set; }

        [JsonProperty("created_at")]
        public ulong CreatedAt { get; set; }
        [JsonIgnore]
        public DateTime CreatedTime {
            get {
                return DateTimeUtil.FromUnixTime(CreatedAt);
            }
        }
        [JsonProperty("updated_at")]
        public ulong UpdatedAt { get; set; }
        [JsonIgnore]
        public DateTime UpdatedTime {
            get {
                return DateTimeUtil.FromUnixTime(UpdatedAt);
            }
        }
        [JsonProperty("state")]
        public AccountState State { get; set; }

        [JsonProperty("room_id")]
        public string RoomId { get; set; }

        [JsonProperty("room")]
        public Room Room { get; set; }

    }
}

using Newtonsoft.Json;
using apiSdk.Utils;
using System;
using System.Collections.Generic;
using System.Text;

namespace apiSdk.Models
{
    

    public class Conference
    {
        [JsonProperty("id")]
        public string Id { get; set; }

        [JsonProperty("title")]
        public string Title { get; set; }

        [JsonProperty("content")]
        public string Content { get; set; }

        [JsonProperty("type")]
        public ConferenceType Type { get; set; }

        [JsonProperty("begin_time")]
        public long BeginAt { get; set; }
        [JsonIgnore]
        public DateTimeOffset BeginTime {
            get {
                return DateTimeUtil.FromUnixTimeSeconds(BeginAt);
            }
        }

        [JsonProperty("end_time")]
        public long EndAt { get; set; }
        [JsonIgnore]
        public DateTimeOffset EndTime {
            get {
                return DateTimeUtil.FromUnixTimeSeconds(EndAt);
            }
        }

        [JsonProperty("duration")]
        public int Duration { get; set; }

        [JsonProperty("state")]
        public ConferenceState State { get; set; }

        [JsonProperty("account_id")]
        public string AccountId { get; set; }
        [JsonProperty("account")]
        public Account Account { get; set; }

        [JsonProperty("corp_id")]
        public string CorporationId { get; set; }

        [JsonProperty("room_id")]
        public string RoomId { get; set; }
        [JsonProperty("room")]
        public Room Room { get; set; }

        [JsonIgnore]
        public long DeletedAt { get; set; }
        [JsonIgnore]
        public DateTimeOffset DeletedTime {
            get {
                return DateTimeUtil.FromUnixTimeSeconds(DeletedAt);
            }
        }



    }
}

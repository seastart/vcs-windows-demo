using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk.Models
{
    public class Corporation
    {
		[JsonProperty("id")]
		public string Id { get; set; }
		[JsonProperty("name")]
		public string Name { get; set; }
		[JsonProperty("account_id")]
		public string Account_id { get; set; }
		[JsonProperty("created_at")]
		public int Created_at { get; set; }
		[JsonProperty("vas_time")]
		public bool Vas_time { get; set; }
		[JsonProperty("vas_conc")]
		public bool Vas_conc { get; set; }
		[JsonProperty("reg_from")]
		public int RegFrom { get; set; }
		[JsonProperty("app_id")]
		public string AppId { get; set; }
		[JsonProperty("account")]
		public Account Account { get; set; }
	}
}

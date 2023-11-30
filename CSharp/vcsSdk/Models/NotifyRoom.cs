using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Models
{
    public class NotifyRoom
	{
		[JsonProperty("astate")]
		public int? Astate { get; set; }
		[JsonProperty("id")]
		public string Id { get; set; }
		[JsonProperty("sdk_no")]
		public string SdkNo { get; set; }
		[JsonProperty("sharing_acc_id")]
		public string SharingAccId { get; set; }
		[JsonProperty("sharing_pic_url")]
		public string SharingPicUrl { get; set; }
		[JsonProperty("sharing_sdkno")]
		public string SharingSdkno { get; set; }
		[JsonProperty("sharing_type")]
		public int? SharingType { get; set; }
		[JsonProperty("state")]
		public int? State { get; set; }
		[JsonProperty("type")]
		public int? Type { get; set; }
		[JsonProperty("vstate")]
		public int? Vstate { get; set; }
		[JsonProperty("wb")]
		public bool? WB { get; set; }
		[JsonProperty("watermark")]
		public bool? WaterMark { get; set; }
		[JsonProperty("locked")]
		public bool? Locked { get; set; }
		[JsonProperty("sharing_stream_id")]
		public string SharingStreamId { get; set; }
	}
}

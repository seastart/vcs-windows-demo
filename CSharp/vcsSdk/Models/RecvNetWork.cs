using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Models
{
    public class RecvNetWork
    {
		[JsonProperty("audio")]
		public int Audio { get; set; }
		[JsonProperty("video")]
		public int Video { get; set; }
		[JsonProperty("comp")]
		public int Comp { get; set; }
		[JsonProperty("losf")]
		public int Losf { get; set; }
		[JsonProperty("lr1")]
		public double Lr1 { get; set; }
		[JsonProperty("lr2")]
		public double Lr2 { get; set; }
		[JsonProperty("recv")]
		public int Recv { get; set; }
		[JsonProperty("Sdkno")]
		public string sdkno { get; set; }
	}
}

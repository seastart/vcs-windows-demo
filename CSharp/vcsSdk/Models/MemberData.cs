using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Models
{
    public class MemberData
    {
        //成员数据
        public StreamData data { get;internal set; }

        //查看视频流的轨道号（释放用）
        public int streamItemId { get;internal set; }

        public IntPtr handle { get; internal set; }
    }
}

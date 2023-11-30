using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk.Classes
{
    public class WebClientEx:WebClient
    {
        protected override WebRequest GetWebRequest(Uri address)
        {
            HttpWebRequest request = (HttpWebRequest)base.GetWebRequest(address);
            request.Timeout = 30000;
            request.ReadWriteTimeout = 30000;
            return request;
        }
    }
}

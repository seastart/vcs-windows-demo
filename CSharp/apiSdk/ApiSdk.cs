using apiSdk.Classes;
using apiSdk.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace apiSdk
{
    public class ApiSdk
    {
        public ApiSdk(string host,string appid,string appkey)
        {
            this.AppId = appid;
            this.AppKey = appkey;
            this.Host = host;
        }
        public string AppId { get; set; }
        public string AppKey { get;set; }
        public string Host { get;set; }
        public string Token { get; set; }
        private ApiClient CreateApiClient()
        {
            return new ApiClient(AppId, AppKey, Host, Token);
        }

        public Tuple<bool,string> Login(string account,string pass,ref UserData ud)
        {
            bool ret = false;
            string msg = "";
            using (var client = CreateApiClient())
            {
                var rsp = client.Login(account, pass);
                ret = rsp.IsSuccessed();
                msg = rsp.Message;
                if (ret)
                {
                    var jdata = rsp.Data;
                    ud = jdata.ToObject<UserData>();
                    Token = jdata["token"].ToString();
                }
            }
            return new Tuple<bool, string>(ret, msg);
        }

        public Tuple<bool, string> RoomEnter(string room_no,ref RoomData rd)
        {
            bool ret = false;
            string msg = "";
            using (var client = CreateApiClient())
            {
                var rsp = client.RoomEnter(room_no,Token);
                ret = rsp.IsSuccessed();
                msg = rsp.Message;
                if (ret)
                {
                    var jdata = rsp.Data;
                    rd = jdata.ToObject<RoomData>();
                }
            }
            return new Tuple<bool, string>(ret, msg);
        }

        public Tuple<bool, string> ConferenceCreate(Dictionary<string,string> dic, ref Conference rd)
        {
            bool ret = false;
            string msg = "";
            using (var client = CreateApiClient())
            {
                var rsp = client.ConferenceCreate(dic);
                ret = rsp.IsSuccessed();
                msg = rsp.Message;
                if (ret)
                {
                    var jdata = rsp.Data;
                    rd = jdata.ToObject<Conference>();
                }
            }
            return new Tuple<bool, string>(ret, msg);
        }

        public Tuple<bool, string> RoomExit(string room_no)
        {
            bool ret = false;
            string msg = "";
            using (var client = CreateApiClient())
            {
                var rsp = client.RoomExit(room_no);
                ret = rsp.IsSuccessed();
                msg = rsp.Message;
            }
            return new Tuple<bool, string>(ret, msg);
        }

        public Tuple<bool, string> LockMeeting(string room_id,bool v)
        {
            bool ret = false;
            string msg = "";
            using (var client = CreateApiClient())
            {
                var rsp = client.RoomLock(room_id, v);
                ret = rsp.IsSuccessed();
                msg = rsp.Message;
            }
            return new Tuple<bool, string>(ret, msg);
        }
    }
}

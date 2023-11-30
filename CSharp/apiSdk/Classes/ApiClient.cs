using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using apiSdk.Models;
using apiSdk.Utils;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;

namespace apiSdk.Classes
{
    public class ApiClient:IDisposable
    {
        public string AppId { get; private set; }
        public string AppKey { get; private set; }
        public string Host { get; private set; }
        public string Token { get; private set; }

        private WebClientEx Client;

        public ApiClient(string app_id,string app_key,string host,string token)
        {
            AppId = app_id;
            AppKey = app_key;
            Host = host;
            Token = token;

            Client = new WebClientEx();
        }



        public void Dispose()
        {
            if (Client != null)
            {
                Client.Dispose();
                Client = null;
            }
        }

        private void SetHeaders(NameValueCollection pms)
        {
            Client.Headers.Set("vcs-appid", AppId);
            string sig = Signature(pms);
            Client.Headers.Set("vcs-signature",sig );
            if (Token != null)
            {
                Client.Headers.Set("vcs-token", Token);
            }
        }

        private string Signature(NameValueCollection pms)
        {
            List<KeyValuePair<string, string>> pms2 = new List<KeyValuePair<string, string>>();
            foreach (var pkey in pms.AllKeys)
                pms2.Add(new KeyValuePair<string, string>(pkey, pms.Get(pkey)));
            pms2.Add(new KeyValuePair<string, string>("appid", this.AppId));
            pms2 = pms2.OrderBy(e => e.Key).ToList();

            //FormUrlEncodedContent c = new FormUrlEncodedContent(pms2);
            //string s=c.ReadAsStringAsync().Result;
            StringBuilder str = new StringBuilder();
            for (int i = 0; i < pms2.Count; i++)
            {
                str.Append(pms2[i].Key + "=" + pms2[i].Value + "&");
            }
            string s = str.ToString().Substring(0, str.Length - 1);
            byte[] key = Encoding.UTF8.GetBytes(this.AppKey);
            byte[] data = Encoding.UTF8.GetBytes(s); 
            
            return SecurityUtil.HMacSha1String(key, data, 0, data.Length);
        }

        private string Password(string user,string pwd)
        {
            var key = Encoding.UTF8.GetBytes("0a6430bcb7084269817813a06e905979");//Encoding.UTF8.GetBytes(AppKey);// Encoding.UTF8.GetBytes("0a6430bcb7084269817813a06e905979");
            var data = Encoding.UTF8.GetBytes(user + pwd);
            return SecurityUtil.HMacSha1String(key,data,0,data.Length);
        }

        private string ConcatUrl(string url)
        {
            string all = Host;
            if (all.EndsWith("/"))  
                all += url;
            else
                all += ("/" + url);
            return all;
        }

        public ApiResponse Request(string url, NameValueCollection pms)
        {
            if (pms == null)
                pms = new NameValueCollection();
            this.SetHeaders(pms);
            var rsp = Client.UploadValues(ConcatUrl(url), pms);
            string json = Encoding.UTF8.GetString(rsp);
            return JsonConvert.DeserializeObject<ApiResponse>(json);
            
        }

        internal ApiResponse RoomLock(string room_id, bool Locked)
        {
            var pms = new NameValueCollection();
            pms.Add("room_id", room_id);
            pms.Add("lock", Locked.ToString()) ;

            return Request("account/register", pms);
        }

        //注册
        public ApiResponse Register(string mobile, string pwd,string vcode)
        {
            var pms = new NameValueCollection();
            pms.Add("name", mobile);
            byte[] pwd_bytes = Encoding.UTF7.GetBytes(pwd);
            pms.Add("password", Password(mobile,pwd));
            pms.Add("nickname", mobile);
            pms.Add("type", ((int)AccountType.Account).ToString());
            pms.Add("mobile", mobile);
            pms.Add("vcode", vcode);

            return Request("account/register", pms);
        }

        //登录
        public ApiResponse Login(string name, string pwd)
        {
            var pms = new NameValueCollection();
            pms.Add("loginname", name);
            pms.Add("dev_type", "1");
            string p = Password(name, pwd);
            pms.Add("password", p);

            return Request("account/login", pms);
        }

        public ApiResponse RoomEnter(string room,string token)
        {
            var pms = new NameValueCollection();
            pms.Add("room_no", room);
            pms.Add("device_id", SecurityUtil.Md5Hex(token));

            return Request("room/enter", pms);
        }

        public ApiResponse ConferenceCreate(Dictionary<string,string> map)
        {
            var pms = new NameValueCollection();
            foreach(var p in map)
            {
                pms.Add(p.Key, p.Value);
            }
            return Request("conference/create", pms);
        }

        public ApiResponse RoomExit(string room)
        {
            var pms = new NameValueCollection();
            pms.Add("room_no", room);

            return Request("room/exit", pms);
        }

        public ApiResponse Logout()
        {
            return Request("account/logout", null);
        }

        //修改用户信息
        public ApiResponse UpdateAccount(string nickname,bool? accessPwd,bool? accessWl,string roomPwd,int? limited,int? samplerate)
        {
            var pms = new NameValueCollection();
            if (nickname != null)
                pms.Add("nickname", nickname);
            if (accessPwd != null)
                pms.Add("access_pwd", accessPwd.Value.ToString());
            if(accessWl!=null)
                pms.Add("access_wl", accessWl.Value.ToString());
            if (roomPwd != null)
                pms.Add("room_password", roomPwd);
            if (limited != null)
                pms.Add("limited", limited.Value.ToString());
            if (samplerate != null)
                pms.Add("samplerate", samplerate.Value.ToString());

            return Request("account/update", pms);
        }

        //修改密码
        public ApiResponse UpdatePassword(string name,string old_password,string new_password)
        {
            string oldPwd = this.Password(name, old_password);
            string newPwd = this.Password(name, new_password);

            var pms = new NameValueCollection();
            pms.Add("old_password", oldPwd);
            pms.Add("new_password", newPwd);

            return Request("account/update-password", pms);

        }

        //重置密码
        public ApiResponse ResetPassword(string name,string vcode,string new_password)
        {
            string pwd = this.Password(name, new_password);
            var pms = new NameValueCollection();
            pms.Add("name", name);
            pms.Add("vcode", vcode);
            pms.Add("new_password", pwd);
            return Request("account/reset-password", pms);
        }

        public ApiResponse VCode(VCodeUsedFor used_for,string mobile,string account_name)
        {
            var pms = new NameValueCollection();
            pms.Add("used_for", ((int)used_for).ToString());
            if(mobile!=null)
                pms.Add("mobile", mobile);
            if (account_name != null)
                pms.Add("account_name", account_name);
            return Request("account/vcode", pms);
        }



        public ApiResponse GetWhiteList()
        {
            return Request("account/get-whitelist", null);
        }


        public ApiResponse AddWhiteList(string name, ConferenceRole role)
        {
            var pms = new NameValueCollection();
            pms.Add("name", name);
            pms.Add("role", ((int)role).ToString());

            return Request("account/add-whitelist", pms);

        }


        public ApiResponse DeleteWhiteList(params string[] names)
        {
            var pms = new NameValueCollection();
            pms.Add("names", string.Join(",", names));
            return Request("account/del-whitelist", pms);
        }


        public ApiResponse Enter(string room_no,string password)
        {
            var pms = new NameValueCollection();
            pms.Add("room_no", room_no);
            if (password != null)
            {
                pms.Add("password", password);
            }

            return Request("room/enter", pms);
        }

        public ApiResponse Exit(string room_no)
        {
            var pms = new NameValueCollection();
            pms.Add("room_no", room_no);
            return Request("room/exit", pms);
        }

        public ApiResponse GetEnterLogs(int offset,int limit)
        {
            var pms = new NameValueCollection();
            pms.Add("offset", offset.ToString());
            pms.Add("limit", limit.ToString());
            return Request("account/enter-logs", pms);
        }

        public ApiResponse GetVasTime(VasType? type,int offset,int limit)
        {
            var pms = new NameValueCollection();
            if (type != null)
                pms.Add("type", ((int)type.Value).ToString());
            pms.Add("offset", offset.ToString());
            pms.Add("limit", limit.ToString());
            return Request("capacity/vas-time", pms);
        }

    }
}


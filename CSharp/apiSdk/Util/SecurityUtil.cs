using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace apiSdk.Utils
{
    public static class SecurityUtil
    {
        public static byte[] Md5(byte[] data, int offsert, int count)
        {
            MD5 md5 = new MD5CryptoServiceProvider();
            return md5.ComputeHash(data, offsert, count);
        }

        public static string Md5Hex(string str)
        {
            MD5CryptoServiceProvider md5 = new MD5CryptoServiceProvider();
            byte[] bytValue, bytHash;
            bytValue = System.Text.Encoding.UTF8.GetBytes(str);
            bytHash = md5.ComputeHash(bytValue);
            md5.Clear();
            string sTemp = "";
            for (int i = 0; i < bytHash.Length; i++)
            {
                sTemp += bytHash[i].ToString("X").PadLeft(2, '0');
            }
            return sTemp.ToLower();
        }

        public static string Md5String(byte[] data, int offset, int count)
        {
            byte[] md5 = Md5(data, offset, count);
            return BitConverter.ToString(md5).Replace("-", "").ToLower();
        }

        public static string Md5String(string data)
        {
            var bytes=Encoding.UTF8.GetBytes(data);
            byte[] md5 = Md5(bytes, 0, bytes.Length);
            return BitConverter.ToString(md5).Replace("-", "").ToLower();
        }

        public static byte[] Sha1(byte[] data, int offset, int count)
        {
            SHA1 sha1 = new SHA1CryptoServiceProvider();
            return sha1.ComputeHash(data, offset, count);
        }

        public static string Sha1String(byte[] data, int offset, int count)
        {
            byte[] sha1 = Sha1(data, offset, count);
            return BitConverter.ToString(sha1).Replace("-", "").ToLower();
        }

        public static byte[] Sha256(byte[] data,int offset,int count)
        {
            SHA256 sha256 = new SHA256CryptoServiceProvider();
            return sha256.ComputeHash(data, offset, count);
        }

        public static string Sha256String(byte[] data, int offset, int count)
        {
            byte[] sha256 = Sha256(data, offset, count);
            return BitConverter.ToString(sha256).Replace("-", "").ToLower();
        }

        public static byte[] HMacSha256(byte[] key,byte[] data, int offset, int count)
        {
            var hmac = new HMACSHA256(key);
            return hmac.ComputeHash(data, offset, count);
        }

        public static string HMacSha256String(byte[] key,byte[] data, int offset, int count)
        {
            byte[] hmac = HMacSha256(key,data, offset, count);
            return BitConverter.ToString(hmac).Replace("-", "").ToLower();
        }

        public static byte[] HMacSha1(byte[] key, byte[] data, int offset, int count)
        {
            var hmac = new HMACSHA1(key);
            return hmac.ComputeHash(data, offset, count);
        }

        public static string HMacSha1String(byte[] key, byte[] data, int offset, int count)
        {
            byte[] hmac = HMacSha1(key, data, offset, count);
            return BitConverter.ToString(hmac).Replace("-", "").ToLower();
        }

        public static string Password(string pwd)
        {
            var bts = Encoding.UTF8.GetBytes(pwd);
            return Sha256String(bts, 0, bts.Length);
        }

        public static string Password(string user,string pwd,string key=null)
        {
            string s = user + pwd;
            if (key != null)
                s += key;
            return Password(s);
        }
    }
}

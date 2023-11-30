using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Classes
{
    public class WndCaptureItem
    {
        public IntPtr Ctx { get; set; }
        public IntPtr Hwnd { get; set; }
        public string Title { get; set; }
        public string Rect { get; set; }
        public int X { get; set; }
        public int Y { get; set; }
        public int CX { get; set; }
        public int CY { get; set; }
        public int Desktop { get; set; }

        public static WndCaptureItem Parse(JObject jpms)
        {
            WndCaptureItem item = new WndCaptureItem();

            item.Desktop = int.Parse(jpms["desktop"].ToString());
            item.Ctx = new IntPtr((long)jpms["ctx"]);
            item.Hwnd = new IntPtr((long)jpms["hwnd"]);
            item.Title = (string)jpms["title"];
            item.Rect = ((string)jpms["rect"]);
            item.ParseRect((string)jpms["rect"]);
            return item;
        }

        private void ParseRect(string rc)
        {
            string[] ss = rc.Split(',');
            if (ss.Length < 4)
                throw new Exception("Rect 字符串格式不正确:" + rc);
            X = int.Parse(ss[0]);
            Y = int.Parse(ss[1]);
            CX = int.Parse(ss[2]);
            CY = int.Parse(ss[3]);
        }

    }
}

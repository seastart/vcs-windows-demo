using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using vcsSdk.Sdk;

namespace vcsSdk.Classes
{
    public class EnumDevice
    {
        public static List<VideoDevice> GetVideo()
        {
            List<VideoDevice> lvd = null;

            IntPtr m = Marshal.AllocHGlobal(1024);
            VcsNative.EnumVideoDevices(m, 1024);
            string v = Marshal.PtrToStringAnsi(m);

            string[] vl = v.Split(new char[] { '|' });
            foreach (string s in vl)
            {
                if (string.IsNullOrEmpty(s))
                {
                    continue;
                }
                if (lvd == null)
                {
                    lvd = new List<VideoDevice>();
                }
                VideoDevice vd = VideoDevice.Parse(s);
                if (vd != null)
                {
                    lvd.Add(vd);
                }
            }
            return lvd;
        }

        internal static List<string> GetAudio()
        {
            List<string> lvd = null;

            IntPtr m = Marshal.AllocHGlobal(1024);
            VcsNative.EnumAudioDevices(m, 1024);
            string v = Marshal.PtrToStringAnsi(m);

            string[] vl = v.Split(new char[] { '|' });
            foreach (string s in vl)
            {
                if (string.IsNullOrEmpty(s))
                {
                    continue;
                }
                if (lvd == null)
                {
                    lvd = new List<string>();
                }
                lvd.Add(s);
            }
            return lvd;
        }

        internal static List<string> GetSpeaker()
        {
            List<string> lvd = null;

            IntPtr m = Marshal.AllocHGlobal(1024);
            VcsNative.EnumSpeakerDevices(m, 1024);
            string v = Marshal.PtrToStringAnsi(m);

            string[] vl = v.Split(new char[] { '|' });
            foreach (string s in vl)
            {
                if (string.IsNullOrEmpty(s))
                {
                    continue;
                }
                if (lvd == null)
                {
                    lvd = new List<string>();
                }
                lvd.Add(s);
            }
            return lvd;
        }
    }

    public class VideoDevice
    {
        public string Name { get; private set; }
        public List<Resolution> Resolutions { get; private set; }

        public VideoDevice()
        {
            Resolutions = new List<Resolution>();
        }

        public static VideoDevice Parse(string s)
        {
            string[] ss = s.Split(';');
            if (ss.Length < 2)
            {
                return null;
            }

            VideoDevice vd = new VideoDevice();
            vd.Name = ss[0];
            for (int i = 1; i < ss.Length; i++)
            {
                Resolution r = Resolution.Parse(ss[i]);
                vd.Resolutions.Add(r);
            }
            vd.Resolutions = vd.Resolutions.OrderBy(e => e.Height * e.Width).ToList();
            return vd;
        }

        public Resolution GetResolution(ref int index)
        {
            if(index > Resolutions.Count)
            {
                index = 0;
            }
            return Resolutions[1];
        }

        public Resolution FindAFittingOne(int x, int y)
        {
            int val = x * y;

            foreach (var res in Resolutions)
            {
                if (res.Width * res.Height >= val)
                {
                    return res;
                }
            }
            return Resolutions.LastOrDefault();
        }
    }

    public class Resolution
    {
        public int Width { get; set; }
        public int Height { get; set; }

        public string Text
        {
            get { return this.ToString(); }
        }

        public static Resolution Parse(string s)
        {
            string[] ss = s.Split(',', 'X');
            if (ss.Length < 2)
                throw new FormatException("分辨率格式无法解析:" + s);

            Resolution r = new Resolution();
            r.Width = int.Parse(ss[0]);
            r.Height = int.Parse(ss[1]);
            return r;
        }

        public static bool TryParse(string s, out Resolution res)
        {
            res = null;
            string[] ss = s.Split(',', 'X');
            if (ss.Length < 2)
                return false;

            res = new Resolution();
            int w, h;
            if (!int.TryParse(ss[0], out w))
                return false;
            if (!int.TryParse(ss[1], out h))
                return false;
            res.Width = w;
            res.Height = h;
            return true;
        }

        public override string ToString()
        {
            return string.Format("{0}X{1}", Width, Height);
        }
    }

    public class VideoSize
    {
        public int width { get; set; }
        public int height { get; set; }
        public int fps { get; set; }
        public int bitrate { get; set; }
    }
}

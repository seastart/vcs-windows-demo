using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace vcsSdk
{
    public static class VcsWinNative
    {
        public const string ModuleName = "WindSDK";


        [StructLayout(LayoutKind.Sequential,CharSet=CharSet.Ansi)]
        public struct VcsRoomInfo
        {
            public string HttpHost;     //Http服务器地址
            public string AppId;        //程序AppId
            public string UserJson;
            public string RoomNo;
            public string Password;
        }

        [DllImport(ModuleName,CharSet =CharSet.Ansi,CallingConvention = CallingConvention.StdCall)]
        public static extern void WIND_RoomShow(ref VcsRoomInfo roomInfo);

        [DllImport(ModuleName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern IntPtr WIND_OpenDrawing(int number);
    }
}

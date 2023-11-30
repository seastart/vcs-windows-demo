using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Enums
{
    public enum EnuUserChnage
    {
        None        = 0,
        Hus         = 0x1,
        Audio       = 0x2,
        Video       = 0x4,
        Role        = 0x8,
        NetLevel    = 0x10,
        //Gear        = 0x20, 
        //DB          = 0x40,
    }

    public enum EnuRoomChange
    {
        None        = 0,
        Lock        = 0x1,
        Audio       = 0x2,
        Video       = 0x4,
        SharingType = 0x8,
        WaterMark   = 0x10,
    }
}

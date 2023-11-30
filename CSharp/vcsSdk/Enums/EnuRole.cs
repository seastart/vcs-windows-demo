using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vcsSdk.Enums
{
    public enum EnuRole
    {
        /// <summary>
        /// 普通成员
        /// </summary>
        None            = 0,
        /// <summary>
        /// 创建者
        /// </summary>
        Creator         = 1,
        /// <summary>
        /// 主持人
        /// </summary>
        Host            = 2,
        /// <summary>
        /// 联席主持人
        /// </summary>
        UnionHost       = 4,
    }
}

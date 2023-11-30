using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace apiSdk.Models
{
    /// <summary>
    /// 帐号类型
    /// </summary>
    public enum AccountType
    {
        [Description("帐号")]
        Account=1,
        [Description("终端")]
        Terminal =2,
    }

    /// <summary>
    /// 帐号状态
    /// </summary>
    public enum AccountState
    {
        [Description("正常")]
        Active=0,
        [Description("停用")]
        Disabled =1,
    }


    /// <summary>
    /// 验证码用途
    /// </summary>
    public enum VCodeUsedFor
    {
        Register=1,
        Reset=2,
    }



    public enum VasType
    {
        [Description("充值")]
        Recharge = 0,

        [Description("赠送")]
        Gift = 1,

        [Description("转移")]
        Transfer = 2,
    }


    /// <summary>
    /// 会议类型
    /// </summary>
    public enum ConferenceType
    {
        [Description("即时会议")]
        Immediate = 1,

        [Description("预约会议")]
        Scheduled = 2,
    }

    /// <summary>
    /// 会议角色
    /// </summary>
    public enum ConferenceRole
    {
        [Description("参会人")]
        Member = 0,

        [Description("创建者")]
        Creator = 1,

        [Description("主持人")]
        Host = 2,
    }

    /// <summary>
    /// 所有者类型
    /// </summary>
    public enum OwnerType
    {
        [Description("帐号")]
        Account = 1,

        [Description("会议")]
        Conference = 2,

        [Description("企业")]
        Corporation = 3,
    }


    /// <summary>
    /// 会议状态
    /// </summary>
    public enum ConferenceState
    {

        [Description("会议中")]
        InProgress = 1,

        [Description("待开始")]
        Preparing = 2,

        [Description("已结束")]
        Closed = 3,
    }
}

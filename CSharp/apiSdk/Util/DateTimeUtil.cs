using System;
using System.Collections.Generic;
using System.Text;

namespace apiSdk.Utils
{
    public static class DateTimeUtil
    {
        private static DateTime UnixBaseTime = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);

        /// <summary>
        /// 将DateTime转换成Unix时间戳
        /// </summary>
        /// <param name="dt"></param>
        /// <returns></returns>
        public static ulong ToUnixTime(this DateTime dt)
        {
            if(dt.Kind==DateTimeKind.Unspecified)
            {
                throw new InvalidTimeZoneException("DateTime 未指定的时区类型");
            }
            else if (dt.Kind == DateTimeKind.Local)
            {
                dt = dt.ToUniversalTime();
            }

            TimeSpan ts = dt - UnixBaseTime;
            return (ulong)ts.TotalSeconds;
        }

        /// <summary>
        /// 将Unix时间戳转换成DateTime本地时间
        /// </summary>
        /// <param name="unix"></param>
        /// <returns></returns>
        public static DateTime FromUnixTime(ulong unix)
        {
            DateTime dt=UnixBaseTime.AddSeconds(unix);
            return dt.ToLocalTime();
        }


        public static DateTimeOffset FromUnixTimeSeconds(long seconds)
        {
            if (seconds < -62135596800L || seconds > 253402300799L)
            {
                throw new Exception("错误");
            }
            long ticks = seconds * 10000000L + 621355968000000000L;
            return new DateTimeOffset(ticks, TimeSpan.Zero);
        }
    }
}

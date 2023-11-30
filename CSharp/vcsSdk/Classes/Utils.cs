using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using vcsSdk.Enums;

namespace vcsSdk.Classes
{
    public static class Utils
    {
        public static string GetDictionaryValueOrDefault(this Dictionary<EnuInitValue,string> v, EnuInitValue key, string t2)
        {
            if (v.Keys.Contains(key))
            {
                return v[key];
            }
            return t2;
        }

        public static List<int> MaskToTrack(int mask)
        {
            int track = (int)Math.Log(mask,2);
            List<int> result = new List<int>();
            // 通道数可能是多个
            if (BinaryCount(mask) == 1)
            {
                result.Add(track);
            }
            else
            {
                int number = 1;

                for (int i = 0; i <= track; i++)
                {
                    if ((mask & number) > 0)
                    {
                        result.Add(i);
                    }
                    number = number << 1;
                }
            }
            return result;
        }

        private static int BinaryCount(int i)
        {
            int j = 0;

            while (i != 0)
            {
                j++;

                // 把最右边的1变成0
                int a = i - 1;

                // 把最右边变化的位全部置0
                i = i & a;
            }
            return j;
        }
    }
}

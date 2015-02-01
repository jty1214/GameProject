using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDL.Helper
{
    public static class EncodingHelper
    {
        static Dictionary<String, String> dic = null;

        public static String GetEncodingType(String key)
        {
            if (dic == null)
            {
                dic = new Dictionary<string, string>();
                dic.InitEncodingList();
            }

            String sKey = key.ToLower();

            if( dic.ContainsKey(sKey) == false)
            {
                return null;
            }
            else
            {
                return dic[sKey];
            }
        }

        public static String[] GetSupportEncodingList()
        {
            Dictionary<String,String>.ValueCollection it = dic.Values;
            String[] sList = it.Distinct<String>().ToArray<String>();
            return sList;
        }

        static void InitEncodingList(this Dictionary<String, String> dic)
        {
            { // UTF-7 Style
                String UTF_7 = "utf-7";
                dic["utf7"] = UTF_7;
                dic["utf-7"] = UTF_7;
                dic["utf_7"] = UTF_7;
                dic["utf-seven"] = UTF_7;
                dic["utf_seven"] = UTF_7;

                // UTF-7 = ASCII
                dic["ascii"] = UTF_7;
                dic["asciicode"] = UTF_7;
            }
            { // UTF-8 Style
                String UTF_8 = "utf-8";
                dic["utf8"] = UTF_8;
                dic["utf-8"] = UTF_8;
                dic["utf_8"] = UTF_8;
                dic["utf-eight"] = UTF_8;
                dic["utf_eight"] = UTF_8;
            }
            { // UTF-16 Style
                String UTF_16 = "utf-16";
                dic["utf16"] = UTF_16;
                dic["utf-16"] = UTF_16;
                dic["utf_16"] = UTF_16;
                dic["utf-hex"] = UTF_16;
                dic["utf_hex"] = UTF_16;
            }
            { // UTF-32 Style
                String UTF_32 = "utf-32";
                dic["utf32"] = UTF_32;
                dic["utf-32"] = UTF_32;
                dic["utf_32"] = UTF_32;
            }
            { // EUC-JP Style
                String EUC_JP = "EUC-JP";
                dic["eucjp"] = EUC_JP;
                dic["euc-jp"] = EUC_JP;
                dic["euc_jp"] = EUC_JP;
                dic["japanese"] = EUC_JP;
            }
            { // EUC-CN
                String EUC_CN = "EUC-CN";
                dic["euccn"] = EUC_CN;
                dic["euc-cn"] = EUC_CN;
                dic["euc_cn"] = EUC_CN;
                dic["chinese"] = EUC_CN;
            }
            { // euc-kr
                String EUC_KR = "euc-kr";
                dic["euckr"] = EUC_KR;
                dic["euc-kr"] = EUC_KR;
                dic["euc_kr"] = EUC_KR;
                dic["korean"] = EUC_KR;
                dic["한국어"] = EUC_KR;
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace PDL.Helper
{
    public class Log
    {
        static StreamWriter log = null;
        public static void Initialize(String LogFilePath)
        {
            FileStream ErrorLog;
            try
            {
                ErrorLog = new FileStream(LogFilePath + "\\" + TimeZone.CurrentTimeZone.ToLocalTime(DateTime.Now).ToShortDateString() + ".log", FileMode.Append, FileAccess.Write);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return;
            }
            log = new StreamWriter(ErrorLog, Encoding.UTF8);

            log.WriteLine("========================");
            Write("Log Trace Start : ");
            log.WriteLine("========================");
        }
        public static void Write(Object msg)
        {
            log.Write(msg);
            WriteTime();
            
        }

        public static void Close()
        {
            log.WriteLine("========================");
            Write("Log Trace End : ");
            log.Close();
        }

        public static void WriteTime()
        {
            log.WriteLine(" (" + TimeZone.CurrentTimeZone.ToLocalTime(DateTime.Now).ToString() + ")");
        }
    }
}

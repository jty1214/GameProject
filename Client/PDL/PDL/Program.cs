using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;

using PDL.Helper;
using PDL.Factory.Interface;

namespace PDL
{
    class Program
    {
        private static String PDLFileName = "PDL.xml";
        static void Main(string[] args)
        {
            String DirectoryPath = Directory.GetCurrentDirectory();
            if (args.Length >= 1) DirectoryPath = args[0];

            String GeneratePath = Directory.GetCurrentDirectory();
            if (args.Length >= 2) GeneratePath = args[1];

            FileStream ErrorLog;
            try
            {
                ErrorLog = new FileStream(GeneratePath + "\\" + TimeZone.CurrentTimeZone.ToLocalTime(DateTime.Now).ToShortDateString() + ".log", FileMode.Append, FileAccess.Write);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return;
            }
            StreamWriter Log = new StreamWriter(ErrorLog, Encoding.UTF8);

            String PDLPath = DirectoryPath + "\\" + PDLFileName;
            XmlTextReader Reader = new XmlTextReader(PDLPath);

            Log.WriteLine("========================");
            Log.Write("Log Trace Start : ");
            Log.WriteTime();
            Log.WriteLine("========================");

            Log.Write(PDLPath+" Read OK");
            Log.WriteTime();

            String Parser = "";
            // 파싱에 실패한 경우
            if ( XMLReadHelper.XMLParsing(ref Parser, Reader, Log) == false)
            {
                Log.Write(PDLPath + " Parsing Error");
                Log.WriteTime();
                Log.Close();

                return;
            }

            Log.Write(PDLPath + " Parsing OK");
            Log.WriteTime();

            NodeInterface RootNode = Parser.GetDataCenter(Log);

            if( RootNode == null )
            {
                Log.Write("Fail to make DataCenter");
                Log.WriteTime();
                Log.Close();
                return;
            }

            Log.Write("Making DataCenter is OK");
            Log.WriteTime();
            Log.Close();
        }
    }
}
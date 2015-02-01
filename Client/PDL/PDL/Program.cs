using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;
using System.Runtime.InteropServices;

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

            String LogFilePath = Directory.GetCurrentDirectory();
            if (args.Length >= 3) LogFilePath = args[2];

            String ProgramLanguage = "C#";
            if (args.Length >= 4) ProgramLanguage = args[3];

            String InputEncodingStyle = "EUC-FR";
            if (args.Length >= 5) InputEncodingStyle = args[4];
            
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
            StreamWriter Log = new StreamWriter(ErrorLog, Encoding.UTF8);

            String PDLPath = DirectoryPath + "\\" + PDLFileName;
            XmlTextReader Reader = new XmlTextReader(PDLPath);

            Log.WriteLine("========================");
            Log.Write("Log Trace Start : ");
            Log.WriteTime();
            Log.WriteLine("========================");

            String EncodingStyle = EncodingHelper.GetEncodingType(InputEncodingStyle);
            if (EncodingStyle == null)
            {
                Log.WriteLine(InputEncodingStyle + " check valid");
                String[] sList = EncodingHelper.GetSupportEncodingList();

                Log.WriteLine("Support Encoding Style ----");
                
                for (int i = 0; i < sList.Length;i++)
                {
                    Log.WriteLine(sList[i]);
                }
                Log.WriteLine("--------------------------");
                Log.WriteTime();
                Log.Close();
                return;
            }

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

            String MakeFileName;
            switch(ProgramLanguage)
            {
                case "C#":
                    {
                        MakeFileName = "gPDL.cs";
                        FileStream GeneratedFile;
                        try
                        {
                            GeneratedFile = new FileStream(GeneratePath + "\\" + MakeFileName, FileMode.Create, FileAccess.Write);
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine(e);
                            return;
                        }

                        StreamWriter Generator = new StreamWriter(GeneratedFile, Encoding.UTF8);

                        if (RootNode.exec_CSharp(Generator, Log, EncodingStyle) == true)
                        {
                            Generator.Close();
                            Log.Write("Making \"" + MakeFileName + "\" is OK");
                            Log.WriteTime();
                        }
                        else
                        {
                            Log.Write("Fail to Make \"" + MakeFileName + "\"");
                            Log.WriteTime();
                            Log.Close();
                            return;
                        }
                        break;
                    }
                default :
                    {
                        Log.Write("Invalid Program Language : " + ProgramLanguage);
                        Log.WriteTime();
                        Log.Close();
                        return;
                    }
            }

            Log.WriteLine("========================");
            Log.Write("Log Trace End : ");
            Log.WriteTime();
            Log.Close();
        }
    }
}
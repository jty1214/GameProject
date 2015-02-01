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

            String InputEncodingStyle = "EUC-KR";
            if (args.Length >= 5) InputEncodingStyle = args[4];

            Log.Initialize(LogFilePath);
            String PDLPath = DirectoryPath + "\\" + PDLFileName;
            XmlTextReader Reader = new XmlTextReader(PDLPath);

            
            String EncodingStyle = EncodingHelper.GetEncodingType(InputEncodingStyle);
            if (EncodingStyle == null)
            {
                Log.Write(InputEncodingStyle + " check valid");
                String[] sList = EncodingHelper.GetSupportEncodingList();

                String SupportEncodingStyle = "";
                SupportEncodingStyle += "Support Encoding Style ----\n";
                Log.Write("Support Encoding Style ----");
                
                for (int i = 0; i < sList.Length;i++)
                {
                    SupportEncodingStyle += sList[i] + "\n";
                }
                SupportEncodingStyle+= "--------------------------\n";
                Log.Write(SupportEncodingStyle);
                Log.Close();
                return;
            }

            Log.Write(PDLPath+" Read OK");

            String Parser = "";
            // 파싱에 실패한 경우
            if ( XMLReadHelper.XMLParsing(ref Parser, Reader) == false)
            {
                Log.Write(PDLPath + " Parsing Error");
                Log.Close();

                return;
            }

            Log.Write(PDLPath + " Parsing OK");

            NodeInterface RootNode = Parser.GetDataCenter();

            if( RootNode == null )
            {
                Log.Write("Fail to make DataCenter");
                Log.Close();
                return;
            }

            Log.Write("Making DataCenter is OK");

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

                        if (RootNode.exec_CSharp(Generator, EncodingStyle) == true)
                        {
                            Generator.Close();
                            Log.Write("Making \"" + MakeFileName + "\" is OK");
                        }
                        else
                        {
                            Log.Write("Fail to Make \"" + MakeFileName + "\"");
                            Log.Close();
                            return;
                        }
                        break;
                    }
                default :
                    {
                        Log.Write("Invalid Program Language : " + ProgramLanguage);
                        Log.Close();
                        return;
                    }
            }

            Log.Close();
        }
    }
}
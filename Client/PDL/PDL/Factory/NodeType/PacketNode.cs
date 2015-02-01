using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;
using PDL.Factory.CommandFactory;
using PDL.Helper;
using System.IO;

namespace PDL.Factory.NodeType
{
    class PacketNode : ChildInterface
    {
        public override String GetName() { return "Packet"; }
        public override void Constructor_CSharp(StreamWriter Generator, String EncodingStyle)
        {
            //놀아 놀아
        }
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log, String EncodingStyle)
        {
            try
            {
                if (Attributes["from"].ToLower() == "client")
                {
                    Generator.WriteLine(this.space() + "public class " + Attributes["class"] + "_WRITE");
                }
                else if (Attributes["from"].ToLower() == "server")
                {
                    Generator.WriteLine(this.space() + "public class " + Attributes["class"] + "_READ");
                }
                else if (Attributes["from"].ToLower() == "both")
                {
                    Generator.WriteLine(this.space() + "public class " + Attributes["class"] + "_BOTH");
                }
                else
                {
                    return false;
                }
                Generator.WriteLine(this.space() + "{");
                
                for (int i = 0; i < ChildNodeList.Count; i++)
                {
                    if (ChildNodeList[i].exec_CSharp(Generator, Log, EncodingStyle) == false)
                    {
                        return false;
                    }
                }

                if (Attributes["from"].ToLower() == "client")
                {
                    Generator.WriteLine(this.space(1) + "public " + Attributes["class"] + "_WRITE()");
                }
                else if (Attributes["from"].ToLower() == "server")
                {
                    Generator.WriteLine(this.space(1) + "public " + Attributes["class"] + "_READ()");
                }
                else if (Attributes["from"].ToLower() == "both")
                {
                    Generator.WriteLine(this.space(1) + "public " + Attributes["class"] + "_BOTH()");
                }
                else
                {
                    return false;
                }
                
                Generator.WriteLine(this.space(1) + "{");

                for (int i = 0; i < ChildNodeList.Count; i++)
                {
                    ChildNodeList[i].Constructor_CSharp(Generator, EncodingStyle);
                }

                Generator.WriteLine(this.space(1) + "}");

                if (Attributes["from"].ToLower() == "both") // "_BOTH"
                {
                    this.GetStreamLength_CSharp(Generator, EncodingStyle);
                    this.Serialize_CSharp(Generator, EncodingStyle);
                    this.Parsing_CSharp(Generator, EncodingStyle);
                }
                else if (Attributes["from"].ToLower() == "client") // "_WRITE"
                {
                    this.GetStreamLength_CSharp(Generator, EncodingStyle);
                    this.Serialize_CSharp(Generator, EncodingStyle);
                }
                else if (Attributes["from"].ToLower() == "server") // "_READ"
                {
                    this.Parsing_CSharp(Generator, EncodingStyle);
                }
                Generator.WriteLine(this.space() + "}");

                return true;
            }
            catch (KeyNotFoundException e)
            {
                Log.WriteLine(e);
                Log.WriteTime();
                return false;
            }
        }
        public override void GetStreamLength_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "")
        {
            Generator.WriteLine(this.space(1) + "public Int32 GetStreamLength()");
            Generator.WriteLine(this.space(1) + "{");
            Generator.WriteLine(this.space(2) + "Int32 size = 0;");

            for (int i = 0; i < ChildNodeList.Count; i++)
            {
                ChildNodeList[i].GetStreamLength_CSharp(Generator, EncodingStyle);
            }

            Generator.WriteLine(this.space(2) + "return size;");
            Generator.WriteLine(this.space(1) + "}");
        }
        public override void Serialize_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "")
        {
            Generator.WriteLine(this.space(1) + "public void Serialize(byte[] stream)");
            Generator.WriteLine(this.space(1) + "{");
            if (ChildNodeList.Count > 0)
            {
                Generator.WriteLine(this.space(2) + "Int32 index = 0;");
            }

            for (int i = 0; i < ChildNodeList.Count; i++)
            {
                ChildNodeList[i].Serialize_CSharp(Generator, EncodingStyle);
            }

            Generator.WriteLine(this.space(1) + "}");
        }
        public override void Parsing_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "", String Type = "")
        {
            Generator.WriteLine(this.space(1) + "public void Parsing(byte[] stream)");
            Generator.WriteLine(this.space(1) + "{");
            if (ChildNodeList.Count > 0)
            {
                Generator.WriteLine(this.space(2) + "Int32 index = 0;");
            }

            for (int i = 0; i < ChildNodeList.Count; i++)
            {
                ChildNodeList[i].Parsing_CSharp(Generator, EncodingStyle);
            }

            Generator.WriteLine(this.space(1) + "}");
        }
    }
}

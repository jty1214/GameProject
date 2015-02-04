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
        public override bool exec_CSharp(StreamWriter Generator, String EncodingStyle)
        {
            try
            {
                String PostType;
                if (Attributes["from"].ToLower() == "both")
                {
                    PostType = "_BOTH";
                }
                else if (Attributes["from"].ToLower() == "client")
                {
                    if( UserPosition.GetUser() == "client" )
                    {
                        PostType = "_WRITE";
                    }
                    else if( UserPosition.GetUser() == "server" )
                    {
                        PostType = "_READ";
                    }
                    else
                    {
                        return false;
                    }
                }
                else if(Attributes["from"].ToLower() == "server")
                {
                    if( UserPosition.GetUser() == "client" )
                    {
                        PostType = "_READ";
                    }
                    else if( UserPosition.GetUser() == "server" )
                    {
                        PostType = "_WRITE";
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }

                Generator.WriteLine(this.space() + "public class " + Attributes["class"] + PostType);

                Generator.WriteLine(this.space() + "{");
                
                for (int i = 0; i < ChildNodeList.Count; i++)
                {
                    if (ChildNodeList[i].exec_CSharp(Generator, EncodingStyle) == false)
                    {
                        return false;
                    }
                }

                Generator.WriteLine(this.space(1) + "public " + Attributes["class"] + PostType + "()");
                
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
                else if (PostType == "_WRITE")
                {
                    this.GetStreamLength_CSharp(Generator, EncodingStyle);
                    this.Serialize_CSharp(Generator, EncodingStyle);
                }
                else if (PostType == "_READ")
                {
                    this.Parsing_CSharp(Generator, EncodingStyle);
                }
                else
                {
                    return false;
                }

                Generator.WriteLine(this.space() + "}");

                return true;
            }
            catch (KeyNotFoundException e)
            {
                Log.Write(e);
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

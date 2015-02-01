using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

using PDL.Factory.Interface;
using PDL.Factory.CommandFactory;
using PDL.Helper;

namespace PDL.Factory.NodeType
{
    class BoolNode : ChildInterface
    {
        public override String GetName() { return "Bool"; }
        public override void Constructor_CSharp(StreamWriter Generator, String EncodingStyle)
        {
            Generator.WriteLine(this.space(1) + Attributes["name"] + "= new Boolean();");
        }
        public override bool exec_CSharp(StreamWriter Generator, String EncodingStyle)
        {
            try
            {
                Generator.WriteLine(this.space() + "public Boolean " + Attributes["name"] + ";");
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
            Generator.WriteLine(this.space(1) + "size += sizeof(Boolean);");  // 타입 더해주고~
            //놀자
        }
        public override void Serialize_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "")
        {
            Generator.WriteLine(this.space(1) + "BitConverter.GetBytes(" + Parent + Attributes["name"] + ").CopyTo(stream, index);");
            Generator.WriteLine(this.space(1) + "index += sizeof(Boolean);");
            //놀자!!
        }
        public override void Parsing_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "", String Type = "")
        {
            Generator.WriteLine(this.space(1) + Parent + Attributes["name"] + " = BitConverter.ToBoolean(stream, index);");
            Generator.WriteLine(this.space(1) + "index += sizeof(Boolean);");
        }
    }
}

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
    class LongNode : ChildInterface
    {
        public override String GetName() { return "Long"; }
        public override void Constructor_CSharp(StreamWriter Generator)
        {
            Generator.WriteLine(this.space(1) + Attributes["name"] + "= new Int64();");
        }
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log)
        {
            try
            {
                Generator.WriteLine(this.space() + "public Int64 " + Attributes["name"] + ";");
                return true;
            }
            catch (KeyNotFoundException e)
            {
                Log.WriteLine(e);
                Log.WriteTime();
                return false;
            }
        }
        public override void GetStreamLength_CSharp(StreamWriter Generator, String Parent="")
        {
            Generator.WriteLine(this.space(1) + "size += sizeof(Int64);");  // 타입 더해주고~
            //놀자
        }
        public override void Serialize_CSharp(StreamWriter Generator, String Parent="")
        {
            Generator.WriteLine(this.space(1) + "foreach(byte " + Attributes["name"] + "i in BitConverter.GetBytes(" + Parent + Attributes["name"] + ").Reverse() )");
            Generator.WriteLine(this.space(1) + "{");
            Generator.WriteLine(this.space(2) + "stream[index++] = " + Attributes["name"] + "i;");
            Generator.WriteLine(this.space(1) + "}");
            //놀자!!
        }
    }
}

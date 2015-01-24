using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;
using PDL.Helper;
using System.IO;

namespace PDL.Factory.NodeType
{
    class PacketNode : ChildInterface
    {
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log)
        {
            try
            {
                Generator.WriteLine("public class "+Attributes["name"]+"_"+( (Attributes["from"].ToLower()=="client") ? "WRITE" : "READ") );
                Generator.WriteLine("{");
                
                for (int i = 0; i < ChildNodeList.Count; i++)
                {
                    if (ChildNodeList[i].exec_CSharp(Generator, Log) == false)
                    {
                        return false;
                    }
                }

                this.GetStreamLength_CSharp(Generator);
                this.Serialize_CSharp(Generator);
                
                Generator.WriteLine("}");

                return true;
            }
            catch (KeyNotFoundException e)
            {
                Log.WriteLine(e);
                Log.WriteTime();
                return false;
            }
        }
        public override void GetStreamLength_CSharp(StreamWriter Generator)
        {
            Generator.WriteLine("public Int32 GetStreamLength()");
            Generator.WriteLine("{");
            Generator.WriteLine("Int32 size = 0;");

            for (int i = 0; i < ChildNodeList.Count; i++)
            {
                ChildNodeList[i].GetStreamLength_CSharp(Generator);
            }

            Generator.WriteLine("return size;");
            Generator.WriteLine("}");
        }
        public override void Serialize_CSharp(StreamWriter Generator)
        {
            
        }
    }
}

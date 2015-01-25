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
    class PDLNode : NodeInterface
    {
        public override String GetName() { return "PDL"; }
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log)
        {
            try
            {
                Generator.WriteLine("using System;");
                Generator.WriteLine("using System.Collections.Generic;");
                Generator.WriteLine("using System.Linq;");
                Generator.WriteLine("using System.Text;");
                Generator.WriteLine("using System.Threading.Tasks;");
                Generator.WriteLine("");
                Generator.WriteLine("namespace PDL");
                Generator.WriteLine("{");
                Generator.WriteLine(this.space(1)+"//Version:"+Attributes["Version"]);

                for(int i=0;i<ChildNodeList.Count;i++)
                {
                    if( ChildNodeList[i].exec_CSharp(Generator, Log) == false )
                    {
                        return false;
                    }
                    Generator.WriteLine("");
                }

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
        public override void Constructor_CSharp(StreamWriter Generator)
        {
            //노올자
        }
        public override void GetStreamLength_CSharp(StreamWriter Generator, String Parent)
        {
            //놀자
        }
        public override void Serialize_CSharp(StreamWriter Generator, String Parent)
        {
            //놀자!!
        }
    }
}

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
    class ListNode : ChildInterface
    {
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log)
        {
            try
            {
                Generator.WriteLine("public class " + Attributes["class"]);
                Generator.WriteLine("{");

                for (int i = 0; i < ChildNodeList.Count; i++)
                {
                    if (ChildNodeList[i].exec_CSharp(Generator, Log) == false)
                    {
                        return false;
                    }
                }
                Generator.WriteLine("}");

                Generator.WriteLine("public List<" + Attributes["class"] + "> " + Attributes["name"] + ";");

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
            Generator.WriteLine("size += sizeof(Int32);");  // 리스트의 수를 먼저 한번 보내주고~
            
            for(int i=0;i<ChildNodeList.Count;i++)
            {
                ChildNodeList[i].GetStreamLength_CSharp(Generator);
            }
        }
        public override void Serialize_CSharp(StreamWriter Generator)
        {

        }
    }
}

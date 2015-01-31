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
    class ListNode : ChildInterface
    {
        public override String GetName() { return "List"; }
        public override void Constructor_CSharp(StreamWriter Generator)
        {
            Generator.WriteLine(this.space(1) + Attributes["name"] + "= new List<" + Attributes["class"] + ">();");
        }
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log)
        {
            try
            {
                Generator.WriteLine(this.space() + "public class " + Attributes["class"]);
                Generator.WriteLine(this.space() + "{");

                for (int i = 0; i < ChildNodeList.Count; i++)
                {
                    if (ChildNodeList[i].exec_CSharp(Generator, Log) == false)
                    {
                        return false;
                    }
                }
                Generator.WriteLine("");
                Generator.WriteLine(this.space(1) + "public " + Attributes["class"] + "()");
                Generator.WriteLine(this.space(1) + "{");
                for (int i = 0; i < ChildNodeList.Count; i++)
                {
                    ChildNodeList[i].Constructor_CSharp(Generator);
                }
                Generator.WriteLine(this.space(1) + "}");

                Generator.WriteLine(this.space() + "}");

                Generator.WriteLine(this.space() + "public List<" + Attributes["class"] + "> " + Attributes["name"] + ";");

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
            Generator.WriteLine(this.space(1) + "size += sizeof(Int32);");  // 리스트의 수를 먼저 한번 보내주고~

            //루프 돌면서 객체들 크기 재고 사이즈 채워주는걸 작성해줘야지 ㅎㅎ
            Generator.WriteLine(this.space(1)
                + "for(int " + Attributes["name"] + "i" + Depth + "=0;"
                + Attributes["name"] + "i" + Depth + " < " + Parent + Attributes["name"] + ".Count;"
                + Attributes["name"] + "i" + Depth + "++)");
            Generator.WriteLine(this.space(1) + "{");
            for(int i=0;i<ChildNodeList.Count;i++)
            {
                ChildNodeList[i].GetStreamLength_CSharp(Generator, Parent + Attributes["name"] + "[" + Attributes["name"] + "i" + Depth + "].");
            }
            Generator.WriteLine(this.space(1) + "}");
        }
        public override void Serialize_CSharp(StreamWriter Generator, String Parent="")
        {
            Generator.WriteLine(this.space(1) + "BitConverter.GetBytes(" + Parent + Attributes["name"] + ".Count).CopyTo(stream, index);");
            Generator.WriteLine(this.space(1) + "index += sizeof(Int32);");

            Generator.WriteLine(this.space(1)
                + "for(int " + Attributes["name"] + "i" + Depth + "=0;"
                + Attributes["name"] + "i" + Depth + " < " + Parent + Attributes["name"] + ".Count;"
                + Attributes["name"] + "i" + Depth + "++)");
            Generator.WriteLine(this.space(1) + "{");
            for (int i = 0; i < ChildNodeList.Count; i++)
            {
                ChildNodeList[i].Serialize_CSharp(Generator, Parent + Attributes["name"] + "[" + Attributes["name"] + "i" + Depth + "].");
            }
            Generator.WriteLine(this.space(1) + "}");
        }
        public override void Parsing_CSharp(StreamWriter Generator, String Parent = "", String Type = "")
        {
            Generator.WriteLine(this.space(1) + "Int32 " + Attributes["name"] + "Length" + Depth + " = BitConverter.ToInt32(stream, index);");
            Generator.WriteLine(this.space(1) + "index += sizeof(Int32);");

            Generator.WriteLine(this.space(1)
                + "for(int " + Attributes["name"] + "i" + Depth + "=0;"
                + Attributes["name"] + "i" + Depth + " < " + Attributes["name"] + "Length" + Depth + ";"
                + Attributes["name"] + "i" + Depth + "++)");
            Generator.WriteLine(this.space(1) + "{");
            Generator.WriteLine(this.space(2) + Type + Attributes["class"] + " " + Attributes["name"] + "it" + Depth + " = " + "new " + Type + Attributes["class"] + "();");

            for (int i = 0; i < ChildNodeList.Count; i++)
            {
                ChildNodeList[i].Parsing_CSharp(Generator, Attributes["name"] + "it" + Depth + ".", Type + Attributes["class"] + ".");
            }
            Generator.WriteLine(this.space(2) + Parent + Attributes["name"] + ".Add(" + Attributes["name"] + "it" + Depth + ");");
            Generator.WriteLine(this.space(1) + "}");
        }
    }
}

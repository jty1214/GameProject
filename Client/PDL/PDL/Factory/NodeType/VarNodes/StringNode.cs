﻿using System;
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
    class StringNode : ChildInterface
    {
        public override String GetName() { return "String"; }
        public override void Constructor_CSharp(StreamWriter Generator)
        {
            Generator.WriteLine(this.space(1) + Attributes["name"] + "= \"\";");
        }
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log)
        {
            try
            {
                Generator.WriteLine(this.space() + "public String " + Attributes["name"] + ";");
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
            Generator.WriteLine(this.space(1) + "size += sizeof(Int32);");  // 갯수 먼저 보내주고~
            Generator.WriteLine(this.space(1) + "size += Encoding.Default.GetBytes(" + Parent + Attributes["name"] + ").Length;");   // 진짜 개수만큼 더해주고~
            // 여기서부터 작업 해야됨, BitConverter로 전부 돌려놓자.
        }
        public override void Serialize_CSharp(StreamWriter Generator, String Parent="")
        {
            Generator.WriteLine(this.space(1) + "foreach(byte " + Attributes["name"] + "i" + Depth + " in BitConverter.GetBytes(Encoding.Default.GetBytes(" + Parent + Attributes["name"] + ").Length) )");
            Generator.WriteLine(this.space(1) + "{");
            Generator.WriteLine(this.space(2) + "stream[index++] = " + Attributes["name"] + "i" + Depth + ";");
            Generator.WriteLine(this.space(1) + "}");
            // 개수 바이트로 먼저 쏘고
            Generator.WriteLine(this.space(1) + "foreach(byte " + Attributes["name"] + "i" + Depth + " in Encoding.Default.GetBytes(" + Parent + Attributes["name"] + ") )");
            Generator.WriteLine(this.space(1) + "{");
            Generator.WriteLine(this.space(2) + "stream[index++] = " + Attributes["name"] + "i" + Depth + ";");
            Generator.WriteLine(this.space(1) + "}");
            // 실제 바이트 정보들 하나하나 옮기고
        }
        public override void Parsing_CSharp(StreamWriter Generator, String Parent = "", String Type = "")
        {
            Generator.WriteLine(this.space(1) + "Int32 " + Attributes["name"] + "Length" + Depth + " = BitConverter.ToInt32(stream, index);");
            Generator.WriteLine(this.space(1) + "index += sizeof(Int32);");

            Generator.WriteLine(this.space(1) + Parent + Attributes["name"] + " = Encoding.Default.GetString(stream, index, " + Attributes["name"] + "Length" + Depth + ");");
            Generator.WriteLine(this.space(1) + "index += " + Attributes["name"] + "Length" + Depth + ";");
        }
    }
}

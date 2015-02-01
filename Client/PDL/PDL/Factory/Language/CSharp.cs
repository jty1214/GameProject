using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace PDL.Factory.Language
{
    interface CSharp
    {
        bool exec_CSharp(StreamWriter Generator, String EncodingStyle);
        void Constructor_CSharp(StreamWriter Generator, String EncodingStyle);
        void GetStreamLength_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "");
        void Serialize_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "");
        void Parsing_CSharp(StreamWriter Generator, String EncodingStyle, String Parent = "", String Type = "");
    }
}

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
        bool exec_CSharp(StreamWriter Generator, StreamWriter Log);
        void Constructor_CSharp(StreamWriter Generator);
        void GetStreamLength_CSharp(StreamWriter Generator, String Parent="");
        void Serialize_CSharp(StreamWriter Generator, String Parent = "");
        void Parsing_CSharp(StreamWriter Generator, String Parent = "", String Type="");
    }
}

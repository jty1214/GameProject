using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

namespace PDL.Factory.Language
{
    public abstract class CSharp
    {
        abstract public bool exec_CSharp(StreamWriter Generator, StreamWriter Log);
        abstract public void Constructor_CSharp(StreamWriter Generator);
        abstract public void GetStreamLength_CSharp(StreamWriter Generator, String Parent="");
        abstract public void Serialize_CSharp(StreamWriter Generator, String Parent="");
    }
}

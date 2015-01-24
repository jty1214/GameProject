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
    class VarNode : ChildInterface
    {
        public override bool exec_CSharp(StreamWriter Generator, StreamWriter Log)
        {
            return true;
        }
        public override void GetStreamLength_CSharp(StreamWriter Generator)
        {

        }
        public override void Serialize_CSharp(StreamWriter Generator)
        {

        }
    }
}

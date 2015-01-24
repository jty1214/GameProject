using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory;
using System.IO;

namespace PDL.Factory.Interface
{
    public abstract class NodeInterface
    {
        public List<ChildInterface> ChildNodeList;
        public Dictionary<String, String> Attributes;
        public int Depth;

        public NodeInterface()
        {
            ChildNodeList = new List<ChildInterface>();
            Attributes = new Dictionary<String,String>();
            Depth = -1;
        }
        public void add(ChildInterface node)
        {
            ChildNodeList.Add(node);
        }
        public void add(Attribute attr)
        {
            Attributes.Add(attr.Key, attr.Value);
        }
        abstract public bool exec_CSharp(StreamWriter Generator, StreamWriter Log);
        abstract public void GetStreamLength_CSharp(StreamWriter Generator);
        abstract public void Serialize_CSharp(StreamWriter Generator);
    }
}

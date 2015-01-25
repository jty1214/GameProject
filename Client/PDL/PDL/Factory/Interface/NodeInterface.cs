using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory;
using System.IO;

using PDL.Factory.CommandFactory;
using PDL.Factory.Language;

namespace PDL.Factory.Interface
{
    public abstract class NodeInterface
        : CSharp
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
        abstract public String GetName();
    }
}

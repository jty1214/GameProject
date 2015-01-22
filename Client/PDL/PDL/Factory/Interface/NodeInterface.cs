using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory;

namespace PDL.Factory.Interface
{
    public abstract class NodeInterface
    {
        public List<ChildInterface> ChildNodeList;
        public List<Attribute> AttributeList;
        public int Depth;

        public NodeInterface()
        {
            ChildNodeList = new List<ChildInterface>();
            AttributeList = new List<Attribute>();
            Depth = -1;
        }
        public void add(ChildInterface node)
        {
            ChildNodeList.Add(node);
        }
        public void add(Attribute attr)
        {
            AttributeList.Add(attr);
        }
        abstract public void exec();
    }
}

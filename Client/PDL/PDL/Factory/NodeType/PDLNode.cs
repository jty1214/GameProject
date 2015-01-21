using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;

namespace PDL.Factory.NodeType
{
    class PDLNode : NodeInterface
    {
        public List<ChildInterface> childList;

        public bool add(ChildInterface node)
        {
            childList.Add(node);
            return true;
        }

        public void exec()
        {

        }
    }
}

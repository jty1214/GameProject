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

        public PDLNode ()
        {
            childList = new List<ChildInterface>();
        }

        public bool add(NodeInterface node)
        {
            if (node is ChildInterface)
            {
                childList.Add(node as ChildInterface);
                return true;
            }
            else
            {
                Console.WriteLine("자식 타입이어야 합니다.");
                return false;
            }
        }

        public void exec()
        {

        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;

namespace PDL.Factory.NodeType
{
    class ListNode : ChildInterface
    {
        public List<NodeInterface> childList;

        public ListNode()
        {
            childList = new List<NodeInterface>();
        }

        public bool add(NodeInterface node)
        {
            if (node is ChildInterface)
            {
                childList.Add(node as ChildInterface);
                return true;
            }
            if (node is NodeInterface)
            {
                childList.Add(node as NodeInterface);
                return true;
            }
            else
            {
                Console.WriteLine("ListNode에는 Attribute가 입력될 수 없습니다.");
                return false;
            }
        }
        public void exec()
        {

        }
    }
}

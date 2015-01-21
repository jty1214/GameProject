using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;

namespace PDL.Factory.NodeType
{
    class VarNode : NodeInterface
    {
        public List<AttributeInterface> childList;

        public VarNode()
        {
            childList = new List<AttributeInterface>();
        }

        public bool add(ChildInterface node)
        {
            if( node is AttributeInterface )
            {
                childList.Add(node as AttributeInterface);
                return true;
            }
            else
            {
                Console.WriteLine("VarNode에는 Attribute만 입력 가능합니다.");
                return false;
            }
        }
        public void exec()
        {

        }
    }
}

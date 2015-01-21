using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDL.Factory.NodeType
{
    class VarNode : NodeInterface
    {
        public List<AttributeInterface> childList;

        public VarNode()
        {
            childList = new List<AttributeInterface>();
        }

        public void add(NodeInterface node)
        {
            if( node is AttributeInterface )
            {
                childList.Add(node as AttributeInterface);
            }
            else
            {
                Console.WriteLine("VarNode에는 Attribute만 입력 가능합니다.");
            }
        }
        public void exec()
        {

        }
    }
}

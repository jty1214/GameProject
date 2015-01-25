using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;
using PDL.Factory.NodeType;

namespace PDL.Factory.CommandFactory
{
    public static class NodeHelper
    {
        public static Dictionary<String, NodeInterface> nMap;
        public static void RegistClass(this NodeInterface UniqueNode)
        {
            if (nMap == null) nMap = new Dictionary<String, NodeInterface>();

            String NodeName = UniqueNode.GetName().ToLower();
            if( nMap.ContainsKey(NodeName) == false)
            {
                nMap[NodeName] = (NodeInterface)Activator.CreateInstance(UniqueNode.GetType());
            }
        }

        public static NodeInterface NodeMaker(String NodeName)
        {
            if (nMap == null) nMap = new Dictionary<String, NodeInterface>();

            if (nMap.ContainsKey(NodeName) == true)
            {
                return (NodeInterface)Activator.CreateInstance(nMap[NodeName.ToLower()].GetType());
            }
            return null;
        }

        public static void RegistNodeList()
        {
            new PDLNode().RegistClass();
            new ListNode().RegistClass();
            new PacketNode().RegistClass();

            new BoolNode().RegistClass();
            new IntNode().RegistClass();
            new LongNode().RegistClass();
            new StringNode().RegistClass();
            
        }

        public static String space(this NodeInterface node, int inc = 0)
        {
            String space = "";
            for (int i = 0; i < node.Depth + inc; i++) { space += "  "; }
            return space;
        }
    }
}

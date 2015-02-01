using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using PDL.Helper;

using PDL.Factory.Interface;
using PDL.Factory.NodeType;
using PDL.Factory.CommandFactory;

namespace PDL.Helper
{
    public static class BuildDataCenter
    {
        public static NodeInterface GetDataCenter(this String Parser)
        {
            // 유효한 노드들을 미리 등록해놓는다.
            NodeHelper.RegistNodeList();

            String[] ElementList = Parser.Split(';');
            Log.Write("Split Elements OK");

            Stack<NodeInterface> NodeStack = new Stack<NodeInterface>();
            NodeInterface RootNode = null;
            foreach(var Element in ElementList)
            {
                if( Element == "" )
                {
                    // 비어있는 내용물이 있는 경우 패스한다.
                    continue;
                }

                String[] NodeInfo = Element.Split(':');

                String NodeType = NodeInfo[0].ToLower();

                switch(NodeType)
                {
                    case "node":
                        {
                            String NodeName = NodeInfo[1].ToLower();
                            int NodeDepth = int.Parse(NodeInfo[2]);
                            NodeInterface Node = NodeHelper.NodeMaker(NodeName);
                            if( Node == null )
                            {
                                Log.Write("NodeName ["+NodeName+"] need Check");
                                return null;
                            }
                            Node.Depth = NodeDepth;

                            if (NodeStack.Count == 0)
                            {
                                // 루트 노드의 경우
                                RootNode = Node;
                            }
                            else
                            {
                                // 자식 노드들의 경우
                                if( Node is ChildInterface)
                                {
                                    while( NodeStack.Count > 0 && NodeStack.Peek().Depth >= Node.Depth )
                                    {
                                        NodeStack.Pop();
                                    }
                                    if( NodeStack.Count == 0 )
                                    {
                                        Log.Write(Node + "need Check");
                                        return null;
                                    }

                                    NodeStack.Peek().add(Node as ChildInterface);
                                }
                                else
                                {
                                    Log.Write(NodeName+" is not childInterface");
                                    return null;
                                }
                            }

                            NodeStack.Push(Node);
                        }
                        break;
                    case "attribute" :
                        {
                            String Key = NodeInfo[1];
                            String Value = NodeInfo[2];

                            NodeStack.Peek().add(new PDL.Factory.Attribute(Key, Value));
                        }
                        break;
                    case "endnode":
                        {
                            if( NodeStack.Count == 0 )
                            {
                                Log.Write("Error : Empty Stack");
                                return null;
                            }
                            String NodeName = NodeInfo[1].ToLower();
                            int NodeDepth = int.Parse(NodeInfo[2]);

                            Type eType = NodeHelper.NodeMaker(NodeName).GetType();
                            if( eType == null)
                            {
                                Log.Write(NodeName + "need to write into dictionary");
                                return null;
                            }

                            while (NodeStack.Count > 0 && NodeStack.Peek().Depth > NodeDepth)
                            {
                                NodeStack.Pop();
                            }
                            if (NodeStack.Count == 0)
                            {
                                Log.Write(NodeName + "need Check");
                                return null;
                            }

                            if(  NodeStack.Peek().GetType() == eType )
                            {
                                NodeStack.Pop();
                            }
                            else
                            {
                                Log.Write("Error : Node pair is not Matched");
                                return null;
                            }
                        }
                        break;
                    default :
                        {
                            Log.Write(NodeType + " is What?");
                            return null;
                        }
                }
            }
            return RootNode;
        }
    }
}

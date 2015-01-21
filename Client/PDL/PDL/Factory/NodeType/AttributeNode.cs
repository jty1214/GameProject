﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;

namespace PDL.Factory.NodeType
{
    class AttributeNode<T> : AttributeInterface
    {
        public String Key;
        public T Value;

        public AttributeNode(String Key, T Value)
        {
            this.Key = Key;
            this.Value = Value;
        }

        public bool add(NodeInterface node)
        {
            Console.WriteLine("Attribute에는 자식이 있을 수 없습니다.");
            return false;
        }
        public void exec()
        {

        }
    }
}

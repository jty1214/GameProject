using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDL.Factory.Interface
{
    public interface NodeInterface
    {
        bool add(NodeInterface node);
        void exec();
    }
}

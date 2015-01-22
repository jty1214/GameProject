using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDL.Factory
{
    public class Attribute
    {
        public String Key;
        public String Value;

        public Attribute(String Key, String Value)
        {
            this.Key = Key;
            this.Value = Value;
        }
    }
}

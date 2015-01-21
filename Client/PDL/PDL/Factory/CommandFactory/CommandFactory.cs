using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using PDL.Factory.Interface;

namespace PDL.Factory.CommandFactory
{
    public class CommandFactory
    {
        private readonly IDictionary<string, Func<NodeInterface>> _commands;

        public CommandFactory()
        {
            _commands = new Dictionary<string, Func<NodeInterface>>
                        {
      //                      {"A", () => new CommandA()},
       //                     {"B", () => new CommandB()},
        //                    {"C", () => new CommandC()}
                        };
        }

        public NodeInterface GetCommand(string jobKey)
        {
            Func<NodeInterface> command;
            _commands.TryGetValue(jobKey.ToUpper(), out command);
            return command();
        }
    }    
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PDL
{
    public class CommandFactory
    {
        private readonly IDictionary<string, Func<ICommand>> _commands;

        public CommandFactory()
        {
            _commands = new Dictionary<string, Func<ICommand>>
                        {
      //                      {"A", () => new CommandA()},
       //                     {"B", () => new CommandB()},
        //                    {"C", () => new CommandC()}
                        };
        }

        public ICommand GetCommand(string jobKey)
        {
            Func<ICommand> command;
            _commands.TryGetValue(jobKey.ToUpper(), out command);
            return command();
        }
    }    
}

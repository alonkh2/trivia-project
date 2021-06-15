using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_GUI
{
    public class Question
    {
        public string name { get; set; }

        public Dictionary<int, string> answers { get; set; }

        public int answer { get; set; }
        
    }
}

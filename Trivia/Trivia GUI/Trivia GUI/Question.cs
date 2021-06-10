using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_GUI
{
    class Question
    {
        public string name { get; set; }

        public string ans1 { get; set; }
        public string ans2 { get; set; }
        public string ans3 { get; set; }
        public string ans4 { get; set; }

        public int correctAns { get; set; }
        
    }
}

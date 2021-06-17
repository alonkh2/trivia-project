using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_GUI
{
    public class Results
    {
        public string username { get; set; }

        public int currentQuestion { get; set; }

        public int correctAnswers { get; set; }

        public int wrongAnswers { get; set; }

        public double averageTime { get; set; }

        public int score { get; set; }

       
    }
}

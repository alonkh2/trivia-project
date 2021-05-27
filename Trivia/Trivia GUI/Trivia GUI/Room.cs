using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Trivia_GUI
{
    class Room
    {
        public string roomID{ get; set; }

        public string name { get; set; }

        public double timeout { get; set; }

        public int max { get; set; }
        
        public int count { get; set; }
    }
}

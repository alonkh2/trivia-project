using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace Trivia_GUI
{
    class Communicator
    {
        private Socket socket;


        public Communicator()
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Connect("127.0.0.1", 2410); //Synchronous blocking
        }

        public static void sendMessage(string msg)
        {
            
        }
    }
}

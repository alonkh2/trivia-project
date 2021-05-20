using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using Newtonsoft.Json;
using System;

namespace Trivia_GUI
{
    public class Communicator
    {
        private Socket socket;


        public Communicator()
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Connect("127.0.0.1", 2410); //Synchronous blocking
        }

        ~Communicator()
        {
            socket.Close();
        }

        public int signup(string email, string name, string pass)
        {
            User user = new User
            {
                password = pass,
                mail = email,
                username =  name
            };

            string json = JsonConvert.SerializeObject(user);

            string data = String.Empty;

            try
            {
                data = data + sendAndReceive(json, 'f');
            }
            catch (Exception)
            {
                return 1;
            }

            dynamic reply = JsonConvert.DeserializeObject(data);

            if (reply.status != null && reply.status == "1")
            {
                return 2; // success 
            }
            return 1; // Login/Signup excpetion
        }

        public int signin(string name, string pass)
        {
            User user = new User
            {
                username = name,
                password = pass
            };


            string json = JsonConvert.SerializeObject(user);

            string data = String.Empty;

            try
            {
                data = data + sendAndReceive(json, 'e');
            }
            catch (Exception)
            {
                return 0;
            }

            dynamic reply = JsonConvert.DeserializeObject(data);

            if (reply.status != null && reply.status == "1")
            {
                return 2; // success 
            }
            return 1; // Login/Signup excpetionstring byteLength = getByteLength(json);

        }

        private string getByteLength(string json)
        {
            byte[] bytes = BitConverter.GetBytes(json.Length);

            string byteLength = System.Text.Encoding.Default.GetString(bytes);

            return byteLength;
        }

        private Byte[] receive(int length)
        {
            Byte[] arr = new Byte[length];
            int received = socket.Receive(arr, arr.Length, 0);
            if (received == 0)
            {
                throw new Exception("Client disconnected");
            }


            return arr;
        }

        private string sendAndReceive(string json, char initCode)
        {
            string byteLength = getByteLength(json);

            string dataSent = initCode + byteLength + json;


            Byte[] bytesSent = Encoding.ASCII.GetBytes(dataSent);
            socket.Send(bytesSent);

            Byte[] code = new Byte[1];
            Byte[] len = new Byte[4];

            code = receive(code.Length);

            char charicCode = Convert.ToChar(code[0]);
            

            len = receive(len.Length);

            int numericalLength = BitConverter.ToInt32(len, 0);

            Byte[] bytesReceived = new Byte[numericalLength];

            bytesReceived = receive(numericalLength);

            if (charicCode != initCode && charicCode != 'g')
            {
                throw new Exception("Irrelevant request");
            }

            return System.Text.Encoding.Default.GetString(bytesReceived);
        }
    }
}

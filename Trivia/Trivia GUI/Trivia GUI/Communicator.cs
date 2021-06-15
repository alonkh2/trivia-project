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
            if (socket.Connected)
                logout();
        }

        /// <summary>
        /// Signs a user up.
        /// </summary>
        /// <param name="email">The user's email</param>
        /// <param name="name">The user's username</param>
        /// <param name="pass">Ther user's password</param>
        /// <returns>The signup status</returns>
        public int signup(string email, string name, string pass)
        {
            User user = new User
            {
                password = pass,
                mail = email,
                username = name
            };

            string json = JsonConvert.SerializeObject(user);

            dynamic reply = getJson(json, 'f');

            if (reply == null)
            {
                return 0;
            }

            if (reply.status != null && reply.status == "1")
            {
                
                return 2; // success 
            }
            return 1; // Login/Signup excpetion
        }

        /// <summary>
        /// Signs a user in.
        /// </summary>
        /// <param name="name">The user's username</param>
        /// <param name="pass">The user's password</param>
        /// <returns>The login status</returns>
        public int signin(string name, string pass)
        {
            User user = new User
            {
                username = name,
                password = pass
            };

            string json = JsonConvert.SerializeObject(user);

            dynamic reply = getJson(json, 'e');

            if (reply == null)
            {
                return 0;
            }

            if (reply.status != null && reply.status == "1")
            {
                return 2; // success 
            }
            return 1; // Login/Signup excpetionstring byteLength = getByteLength(json);
        }

        /// <summary>
        /// Gets the personal stats of a user.
        /// </summary>
        /// <param name="name">The user's name</param>
        /// <returns>The stats</returns>
        public string[] getPersonalStats(string name)
        {
            User user = new User()
            {
                username = name
            };

            string json = JsonConvert.SerializeObject(user);

            dynamic data = getJson(json, 'k');

            if (data != null && data.statistics != null)
            {
                string stat = data.statistics;
                string[] stats = stat.Split(',');
                return stats;
            }
            return null;
        }

        /// <summary>
        /// Logs the user out.
        /// </summary>
        /// <returns>The logout status</returns>
        public int logout()
        {
            User user = new User { };
            string json = JsonConvert.SerializeObject(user);


            dynamic reply = getJson(json, 'h');

            if (reply == null)
            {
                return 0;
            }

            if (reply.status != null && reply.status == "1")
            {
                if (socket.Connected)
                {
                    socket.Close();
                }
                return 2; // success 
            }
            return 1; // Login/Signup excpetionstring byteLength = getByteLength(json);
        }

        /// <summary>
        /// Gets high scores.
        /// </summary>
        /// <returns>The high scores</returns>
        public string[] getHighScores()
        {
            string json = JsonConvert.SerializeObject("{}");
            string data = string.Empty;

            dynamic reply = getJson(json, 'l');

            if (reply == null || reply.statistics == null)
            {
                return null;
            }
            string stat = reply.statistics;
            string[] stats = stat.Split(',');

            return stats;
        }


        public List<Room> getRooms()
        {
            string json = JsonConvert.SerializeObject("{}");
            string data = string.Empty;
            List<Room> roooms = new List<Room>();

            dynamic reply = getJson(json, 'i');

            if (reply != null && reply.rooms != null)
            {
                string rooms = reply.rooms;

                string[] meta = rooms.Split('$');

                string[][] metadata = new string[meta.Length - 1][];
                for (int i = 0; i < meta.Length - 1; i++)
                {
                    metadata[i] = meta[i].Split(',');

                    roooms.Add(new Room
                    {
                        roomID = metadata[i][0],
                        name = metadata[i][1],
                        max = int.Parse(metadata[i][2]),
                        count = int.Parse(metadata[i][3]),
                        timeout = double.Parse(metadata[i][4]),
                        isActive = int.Parse(metadata[i][5])
                    });
                }
            }

            return roooms;
        }

        public bool joinRoom(Room room)
        {
            string json = JsonConvert.SerializeObject(room);
            string data = string.Empty;
            dynamic reply = getJson(json, 'm');

            if (reply == null || reply.status == null || reply.status != "1")
            {
                return false;
            }
            return true;
        }

        public int createRoom(Room room)
        {
            
            string json = JsonConvert.SerializeObject(room);

            dynamic reply = getJson(json, 'n');

            if (reply == null || reply.status == null || reply.status != "1" || reply.id == null)
            {
                return 0;
            }
            return reply.id;

        }

        public List<User> getPlayersInRoom(Room room)
        {
            string json = JsonConvert.SerializeObject(room);
            dynamic reply = getJson(json, 'j');

            if (reply == null || reply.players == null)
            {
                return null;
            }
            List<User> users = new List<User>();
            string players = reply.players;

            string[] usernames = players.Split(',');
            for (int i = 0; i < usernames.Length - 1; i++)
            {
                users.Add(new User { username = usernames[i] });
            }
            return users;
        }

        public Room getRoomState(Room room)
        {
            string json = JsonConvert.SerializeObject("{}");
            dynamic reply = getJson(json, 'p');

            if (reply == null || reply.players == null || reply.status == null || reply.state == null || reply.count == null || reply.timeout == null || reply.status != "1")
            {
                return null;
            }

            try
            {
                List<User> users = new List<User>();
                string players = reply.players;

                string[] usernames = players.Split(',');
                for (int i = 0; i < usernames.Length - 1; i++)
                {
                    users.Add(new User { username = usernames[i] });
                }

                room.users = users;
                room.isActive = reply.state;
                room.count = reply.count;
                room.timeout = reply.timeout;

                return room;
            }
            catch (Exception)
            {

                return null;
            }
        }

        public bool leaveRoom()
        {
            string json = JsonConvert.SerializeObject("{}");
            dynamic reply = getJson(json, 'r');

            if (reply == null || reply.status == null || reply.status != "1")
            {
                return false;
            }
            return true;
        }

        public bool closeRoom()
        {
            string json = JsonConvert.SerializeObject("{}");
            dynamic reply = getJson(json, 'o');

            if (reply == null || reply.status == null || reply.status != "1")
            {
                return false;
            }
            return true;
        }

        public bool startGame()
        {
            string json = JsonConvert.SerializeObject("{}");
            dynamic reply = getJson(json, 'q');

            if (reply == null || reply.status == null || reply.status != "1")
            {
                return false;
            }
            return true;
        }

        public Question getQuestion()
        {
            string json = JsonConvert.SerializeObject("{}");
            dynamic reply = getJson(json, 't');
            Dictionary<int, string> ans = new Dictionary<int, string>();

            if (reply == null || reply.status == null || reply.status != "1" || reply.question == null || reply.answers == null)
            {
                return null;
            }
            string question = reply.question;
            string[] answers = ((string)(reply.answers)).Split('$');
            foreach (string item in answers)
            {
                ans.Add(int.Parse(item.Split(',')[0]), item.Split(',')[1]);
            }
            Question q = new Question
            {
                answers = ans,
                name = question
            };
            return q;
            
        }

        public int submitAnswer(int ans)
        {
            Question question = new Question
            {
                answer = ans
            };
            string json = JsonConvert.SerializeObject(question);
            dynamic reply = getJson(json, 'u');

            if (reply == null || reply.status == null || reply.status != "1" || reply.correct == null)
            {
                return -1;
            }

            return (int)reply.correct;

        }

        public bool leaveGame()
        {
            string json = JsonConvert.SerializeObject("{}");
            dynamic reply = getJson(json, 's');

            return !(reply == null || reply.status == null || reply.status != "1");
            
        }

        public List<Results> getGameResults()
        {
            string json = JsonConvert.SerializeObject("{}");
            dynamic reply = getJson(json, 'v');

            if (reply == null || reply.status == null || reply.results == null || reply.status != "1")
            {
                return null;
            }

            string[] players = ((string)(reply.results)).Split('$');
            List<Results> results = new List<Results>();

            for (int i = 0; i < players.Length; i++)
            {
                string[] stats = players[i].Split(',');
                results.Add(new Results
                {
                    username = stats[0],
                    correctAnswers = int.Parse(stats[1]),
                    wrongAnswers = int.Parse(stats[2]),
                    averageTime = double.Parse(stats[3]),
                    score = int.Parse(stats[4])
                });
            }

            results.Sort(delegate (Results one, Results two)
            {
                if (one.score > two.score)
                {
                    return -1;
                }
                return 1;
            });
            return results;
        }

        /// <summary>
        /// Takes in the json request and the request code and generates the result json.
        /// </summary>
        /// <param name="json">The request</param>
        /// <param name="code">The request code</param>
        /// <returns>The request's result</returns>
        private Object getJson(string json, char code)
        {
            string data = string.Empty;
            try
            {
                data = data + sendAndReceive(json, code);
                dynamic reply = JsonConvert.DeserializeObject(data);

                return reply;
            }
            catch (Exception)
            {
                return null;
            }
        }

        /// <summary>
        /// Calculates the length of a string and returns a string representation of a byte representation of the length.
        /// </summary>
        /// <param name="json">A string</param>
        /// <returns>The string's length</returns>
        private string getByteLength(string json)
        {
            byte[] bytes = BitConverter.GetBytes(json.Length);

            string byteLength = System.Text.Encoding.Default.GetString(bytes);

            return byteLength;
        }

        /// <summary>
        /// Receives a given amount of bytes.
        /// </summary>
        /// <param name="length">The amount of bytes to receive</param>
        /// <returns>The received bytes</returns>
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

        /// <summary>
        /// Sends a string and receives a reply.
        /// </summary>
        /// <param name="json">The string to send</param>
        /// <param name="initCode">The request's code</param>
        /// <returns>The reply</returns>
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

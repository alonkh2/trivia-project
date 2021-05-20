using Newtonsoft.Json;
using System;
using System.Buffers.Binary;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;



namespace Trivia_GUI
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {


        Socket client = null;
        Task taskOfReceiveData;

        public SignupWindow()
        {
            InitializeComponent();

        }

        /// <summary>
        /// This function exits the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }


        /// <summary>
        /// This function checks if an email is valid
        /// </summary>
        /// <param name="source"></param>
        /// <returns></returns>
        private bool IsValidEmail(string source)
        {
            return new EmailAddressAttribute().IsValid(source);
        }

        private string ToBytes(byte[] bytes)
        {
            string byteLength = String.Empty;

            for(int i = 0; i < 4; i++)
            {

                if(bytes[i] != 0)
                {
                    byteLength += Encoding.ASCII.GetString(new byte[] { bytes[i] });

                }

                else
                {
                    byteLength += "x00";
                }

                byteLength += "\\";
            }
            byteLength = byteLength.Remove(byteLength.Length - 1);

            return byteLength;
        }

        /// <summary>
        /// This function check wether the Input Boxes are empty or invalid, and if not continues to the MainWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 
        private void BtnLogin_Click(object sender, RoutedEventArgs e)
        {
            if (!IsValidEmail(txtEmail.Text))
            {
                MessageBox.Show("Invalid email address");
            }

            else if (String.IsNullOrEmpty(txtPassword.Password) && String.IsNullOrEmpty(txtEmail.Text) && String.IsNullOrEmpty(txtUsername.Text))
            {
                MessageBox.Show("Missing or invalid paramaters");
            }

            else
            {
                client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                client.Connect("127.0.0.1", 2410); //Synchronous blocking

                if (client.Connected)
                {
                    User user = new User
                    {
                        password = txtPassword.Password,
                        mail = txtEmail.Text,
                        username = txtUsername.Text
                    };

                    string json = JsonConvert.SerializeObject(user, Formatting.Indented);
                    byte[] bytes = BitConverter.GetBytes(json.Length);


                    string byteLength = ToBytes(bytes);
                    MessageBox.Show(byteLength);

                    string dataSent = "f" + byteLength + json;


                    MessageBox.Show(dataSent);
                    Console.WriteLine(dataSent);
                    Byte[] bytesSent = Encoding.ASCII.GetBytes(dataSent);
                    client.Send(bytesSent);




                    //string dataReceive = string.Empty;
                    //Byte[] bytesReceived = new Byte[2400];
                    //int numOfBytes = 0;

                   // numOfBytes = client.Receive(bytesReceived, bytesReceived.Length, 0); //Get data continuously until get all data
                   //dataReceive = dataReceive + Encoding.ASCII.GetString(bytesReceived, 0, numOfBytes);

                    //MessageBox.Show(dataReceive);


                }






                //sender

                //User user = new User {
                //    password = txtPassword.Password,
                //    email = txtEmail.Text,
                //    username = txtUsername.Text
                //    };

                //string json = JsonConvert.SerializeObject(user, Formatting.Indented);
                //int len = json.Length;
                //byte[] bytes = BitConverter.GetBytes(len);

                //string parsedMessage
                //Console.Write(json.Length);
                //PrintByteArray(bytes);
                //MessageBox.Show(json.Length.ToString());
                //MessageBox.Show(Convert.ToByte(json.Length).ToString());



                MainWindow mainWin = new MainWindow();
                mainWin.Show();
                this.Close();
            }


        }

        public void PrintByteArray(byte[] bytes)
        {
            var sb = new StringBuilder("new byte[] { ");
            foreach (var b in bytes)
            {
                sb.Append(b + ", ");
            }
            sb.Append("}");
            MessageBox.Show(sb.ToString());
        }
    }
}

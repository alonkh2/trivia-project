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
using Newtonsoft.Json;



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

                
                byteLength += Encoding.ASCII.GetString(new byte[] { bytes[i] });


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

                    string json = JsonConvert.SerializeObject(user);
                    byte[] bytes = BitConverter.GetBytes(json.Length);

                    string byteLength = System.Text.Encoding.Default.GetString(bytes);

                    string dataSent = "f" + byteLength + json;


                    Byte[] bytesSent = Encoding.ASCII.GetBytes(dataSent);
                    client.Send(bytesSent);

                    string dataReceive = string.Empty;
                    Byte[] code = new Byte[1];
                    Byte[] len = new Byte[4];

                    code = receive(code.Length);

                    char charicCode = Convert.ToChar(code[0]);
                    if (charicCode != 'f')
                    {
                        MessageBox.Show("SERVER ERROR");
                    }

                    len = receive(len.Length);

                    int numericalLength = BitConverter.ToInt32(len, 0);

                    if (numericalLength == 0)
                    {
                        MessageBox.Show("SERVER ERROR");
                    }

                    Byte[] bytesReceived = new Byte[numericalLength];

                    bytesReceived = receive(numericalLength);

                    string data = System.Text.Encoding.Default.GetString(bytesReceived);

                    dynamic reply = JsonConvert.DeserializeObject(data);

                    if (reply.status == "1")
                    {
                        MainWindow mainWin = new MainWindow(client);
                        mainWin.Show();
                        this.Close();
                    }
                    else
                    {
                        MessageBox.Show("SIGNUP ERROR");
                    }
                }

                
            }
        }

        private Byte[] receive(int length)
        {
            Byte[] arr = new Byte[length];
            int received = client.Receive(arr, arr.Length, 0);
            if (received == 0)
            {
                MessageBox.Show("SERVER ERROR");
            }


            return arr;
        }
    }
}

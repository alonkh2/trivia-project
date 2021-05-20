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


        Communicator communicator;
        Task taskOfReceiveData;

        public SignupWindow(Communicator communicator_)
        {
            InitializeComponent();

            communicator = communicator_;
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
            else if (String.IsNullOrEmpty(txtPassword.Password) || String.IsNullOrEmpty(txtEmail.Text) || String.IsNullOrEmpty(txtUsername.Text))
            {
                MessageBox.Show("Missing or invalid paramaters");
            }
            else
            { 
                int result = communicator.signup(txtEmail.Text, txtUsername.Text, txtPassword.Password);

                switch (result)
                {
                    case 0:
                        MessageBox.Show("Server error");
                        break;
                    case 1:
                        MessageBox.Show("Login error");
                        break;
                    case 2:
                        MainWindow main = new MainWindow(communicator);
                        main.Show();
                        this.Close();
                        break;
                    default:
                        break;
                }
            }
        }

    }
}

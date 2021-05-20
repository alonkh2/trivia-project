using System;
using System.Collections.Generic;
using System.Linq;
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
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        Communicator communicator;
        public LoginWindow(Communicator communicator_)
        {
            InitializeComponent();

            communicator = communicator_;
        }

        /// <summary>
        /// This function exits the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        /// <summary>
        /// This function check wether the text boxes are empty, and if not continues to the MainWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnLogin_Click(object sender, RoutedEventArgs e)
        {
            if(String.IsNullOrEmpty(txtPassword.Password) || String.IsNullOrEmpty(txtUsername.Text))
            {
                MessageBox.Show("Missing or invalid paramaters");
            }
            else
            {
                int result = communicator.signin(txtUsername.Text, txtPassword.Password);

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

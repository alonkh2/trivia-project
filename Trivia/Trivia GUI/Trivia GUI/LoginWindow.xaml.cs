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

        /// <summary>
        /// Constructor of the LoginWindow
        /// </summary>
        /// <param name="communicator_">The Communicator of the user</param>
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
        /// This functin returns the user back to the WelcomeWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            WelcomeWindow welcomeWin = new WelcomeWindow();
            welcomeWin.Show();
            this.Close();
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

                switch (result) // Checking the different error codes
                {
                    case 0:
                        MessageBox.Show("Server error");
                        break;

                    case 1:
                        MessageBox.Show("Login error");
                        break;

                    case 2:
                        MainWindow main = new MainWindow(communicator, txtUsername.Text);
                        main.Show();
                        this.Close();
                        break;

                    default:
                        break;
                }
            }
        }

        /// <summary>
        /// This function allows the window to be dragged across the screen
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Window_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Left)
            {
                this.DragMove();
            }
        }
    }
}

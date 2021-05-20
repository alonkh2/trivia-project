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
    /// Interaction logic for WelcomeWindow.xaml
    /// </summary>
    public partial class WelcomeWindow : Window
    {
        Communicator communicator;

        public WelcomeWindow()
        {
            InitializeComponent();

            communicator = new Communicator();
        }

        /// <summary>
        /// This fuction stops the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        /// <summary>
        /// This function sends a user to the LoginWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow loginWin = new LoginWindow(communicator);
            loginWin.Show();
            this.Close();
        }

        /// <summary>
        /// This function directs a user to the SignupWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void SignupButton_Click(object sender, RoutedEventArgs e)
        {
            SignupWindow signupWin = new SignupWindow(communicator);
            signupWin.Show();
            this.Close();
        }
    }
}

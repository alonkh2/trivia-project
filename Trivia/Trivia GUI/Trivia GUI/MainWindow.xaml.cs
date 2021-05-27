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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;

namespace Trivia_GUI
{
    public partial class MainWindow : Window
    {
        Communicator communicator;
        string currUser;
        ///Initializes the MainWindow
        public MainWindow(Communicator communicator_, string username)
        {
            InitializeComponent();

            communicator = communicator_;
            currUser = username;
        }

        /// <summary>
        /// This function exits the application when the 'Exit' radio button is toggled
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            communicator.logout();
            System.Windows.Application.Current.Shutdown();
        }

        public void LogOut_Click(object sender, RoutedEventArgs e)
        {
            int result = communicator.logout();

            switch (result)
            {
                case 0:
                    MessageBox.Show("Error while logging out");
                    break;
                case 1:
                    MessageBox.Show("Error while logging out");
                    break;
                case 2:
                    WelcomeWindow welcomeWin = new WelcomeWindow();
                    welcomeWin.Show();
                    this.Close();
                    break;
                default:
                    break;
            }
        }

        private void High_Click(object sender, RoutedEventArgs e)
        {
            
            HighScoresWindow highWin = new HighScoresWindow(communicator, currUser);
            highWin.Show();
            this.Close();
        }

        private void Stats_Click(object sender, RoutedEventArgs e)
        {

            StatsWindow statWin = new StatsWindow(communicator, currUser);
            statWin.Show();
            this.Close();
        }
    }
}

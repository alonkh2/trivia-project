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
        
        /// <summary>
        /// This fuction constructs the MainWindow
        /// </summary>
        /// <param name="communicator_">The communicator</param>
        /// <param name="username">The username of the current user</param>
        public MainWindow(Communicator communicator_, string username)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

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

        /// <summary>
        /// This function logs the user out of the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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

        /// <summary>
        /// This function sends the user to the HighScoresWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void High_Click(object sender, RoutedEventArgs e)
        {
            
            HighScoresWindow highWin = new HighScoresWindow(communicator, currUser);
            highWin.Show();
            this.Close();
        }

        /// <summary>
        /// This function send the user to the CreateRoomWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Create_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow createWin = new CreateRoomWindow(communicator, currUser);
            createWin.Show();
            this.Close();
        }

        /// <summary>
        /// This function send the user to the StatsWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Stats_Click(object sender, RoutedEventArgs e)
        {
            //StatsWindow statWin = new StatsWindow(communicator, currUser);
            //statWin.Show();
            //this.Close();

            QuestionWindow questWin = new QuestionWindow(communicator, currUser);
            questWin.Show();
            this.Close();
        }

        /// <summary>
        /// This function send the user to the JoinRoomWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Join_Click(object sender, RoutedEventArgs e)
        {

            JoinRoomWindow joinWin = new JoinRoomWindow(communicator, currUser);
            joinWin.Show();
            this.Close();
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

            App.Current.Properties["verticalDis"] = this.Top;
            App.Current.Properties["horizontalDis"] = this.Left;
        }
    }
}

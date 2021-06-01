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
    /// Interaction logic for StatsWindow.xaml
    /// </summary>
    public partial class StatsWindow : Window
    {

        Communicator communicator;
        string currUser;

        /// <summary>
        /// This function constructs the StatsWindow
        /// </summary>
        /// <param name="communicator_">The communicator</param>
        /// <param name="username">The username of the current user</param>
        public StatsWindow(Communicator communicator_, string username)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator = communicator_;
            currUser = username;

            string[] stats = communicator.getPersonalStats(currUser);


            if (stats.Length < 5) // If there is no data on the user
            {
                totalGames.Text = "No data";
                correctAnswers.Text = "No data";
                totalAnswers.Text = "No data";
                avgTime.Text = "No data";
                totalPoints.Text = "No data";
            }

            else 
            {
                totalAnswers.Text = stats[0];
                correctAnswers.Text = stats[1];
                totalGames.Text = stats[2];
                avgTime.Text = stats[3];
                totalPoints.Text = stats[4];
            }
        }

        /// <summary>
        /// This function returns the user to the MainWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator, currUser);
            mainWin.Show();
            this.Close();
        }

        /// <summary>
        /// This function exits the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            communicator.logout();
            System.Windows.Application.Current.Shutdown();
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

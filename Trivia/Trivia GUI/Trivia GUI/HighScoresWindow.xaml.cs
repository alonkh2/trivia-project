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
    /// Interaction logic for HighScoresWindow.xaml
    /// </summary>
    public partial class HighScoresWindow : Window
    {
        Communicator communicator;
        string currUser;

        /// <summary>
        /// This function initalizes the HighScoresWindow
        /// </summary>
        /// <param name="communicator_">The communicator</param>
        /// <param name="username">The username of the current user</param>
        public HighScoresWindow(Communicator communicator_, string username)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator = communicator_;
            currUser = username;

            try
            {
                string[] stats = communicator.getHighScores();

                // Checking if there are enough players to fill the entire window, and if not, fill it up to a certain point
                if (stats == null)
                {
                    MessageBox.Show("Error");
                }
                else
                {
                    if (stats.Length > 1 && !string.IsNullOrEmpty(stats[0]) && !string.IsNullOrEmpty(stats[1]))
                    {
                        firstUser.Text = stats[0];
                        firstPoints.Text = stats[1];
                    }

                    if (stats.Length > 3 && !string.IsNullOrEmpty(stats[2]) && !string.IsNullOrEmpty(stats[3]))
                    {
                        secondUser.Text = stats[2];
                        secondPoints.Text = stats[3];
                    }


                    if (stats.Length > 5 && !string.IsNullOrEmpty(stats[4]) && !string.IsNullOrEmpty(stats[5]))
                    {
                        thirdUser.Text = stats[4];
                        thirdPoints.Text = stats[5];
                    }

                    if (stats.Length > 7 && !string.IsNullOrEmpty(stats[6]) && !string.IsNullOrEmpty(stats[7]))
                    {
                        fourthUser.Text = stats[6];
                        fourthPoints.Text = stats[7];
                    }

                    if (stats.Length > 9 && !string.IsNullOrEmpty(stats[8]) && !string.IsNullOrEmpty(stats[9]))
                    {
                        fifthUser.Text = stats[8];
                        fifthPoints.Text = stats[9];
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                if (ex.Message == "An existing connection was forcibly closed by the remote host")
                {
                    this.Close();
                }
            }
        }

        /// <summary>
        /// This fuction returns the user to the main window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator, currUser);
            mainWin.Show();
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

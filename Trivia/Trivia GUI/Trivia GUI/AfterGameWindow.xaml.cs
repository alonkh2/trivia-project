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
using System.Threading;

namespace Trivia_GUI
{
    /// <summary>
    /// Interaction logic for AfterGameWindow.xaml
    /// </summary>
    public partial class AfterGameWindow : Window
    {

        Communicator communicator;
        string username;
        Thread t_;

        public AfterGameWindow(Communicator communicator_, string username_)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator = communicator_;
            username = username_;

            t_ = new Thread(getResults);
            t_.Start();
        }


        public void getResults()
        {
            while (true)
            {
                this.Dispatcher.BeginInvoke(new Action(delegate ()
                {
                    List<Results> results = communicator.getGameResults();

                    firstPlaces.Text = results.ElementAt(0).username;

                    if (results.Count >= 2)
                        secondPlace.Text = results.ElementAt(1).username;
                    if (results.Count >= 3)
                        thirdPlace.Text = results.ElementAt(2).username;

                    int pos = results.FindIndex(x => x.username == username);
                    position.Text = (pos + 1).ToString();
                    avgTime.Text = results[pos].averageTime.ToString();
                    totalPoints.Text = results[pos].score.ToString();
                }));
                Thread.Sleep(200);
            }
        }


        /// <summary>
        /// This function exits the application when the 'Exit' button is toggled
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            t_.Abort();
            try
            {
                communicator.leaveGame();
                communicator.logout();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            System.Windows.Application.Current.Shutdown();
        }

        /// <summary>
        /// This fuction returns the user to the MainWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            t_.Abort();
            try
            {
                communicator.leaveGame();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            MainWindow mainWin = new MainWindow(communicator, username); ;
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

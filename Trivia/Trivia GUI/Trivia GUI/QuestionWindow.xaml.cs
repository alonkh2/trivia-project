using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Trivia_GUI
{
    /// <summary>
    /// Interaction logic for QuestionWindow.xaml
    /// </summary>
    /// 


    public partial class QuestionWindow : Window
    {
        DispatcherTimer _timer;
        TimeSpan _time;
        Communicator communicator_;
        string username_;
        bool admin_;
        public QuestionWindow(Communicator communicator, string username, bool admin)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator_ = communicator;
            username_ = username;
            admin_ = admin;
            

            //idk what this does, looks important tho

            _time = TimeSpan.FromSeconds(100);

            _timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            {
                timer.Text = _time.ToString(@"mm\:ss");

                if (_time == TimeSpan.Zero)
                {
                    _timer.Stop();
                }

                _time = _time.Add(TimeSpan.FromSeconds(-1));
            }, Application.Current.Dispatcher);

            _timer.Start();
        }

        private void Ans_Click(object sender, RoutedEventArgs e)
        {
            if(sender == ans1)
            {
                // do stuff
            }

            else if(sender == ans2)
            {
                // do more stuff
            }
        }




        /// <summary>
        /// This function returns the user to his previous window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            _timer.Stop();
            if (admin_)
            {
                communicator_.closeRoom();
            }
            else
            {
                communicator_.leaveRoom();
            }
            MainWindow mainWin = new MainWindow(communicator_, username_);
            mainWin.Show();
            this.Close();
        }


        /// <summary>
        /// This function exits the application when the 'Exit' radio button is toggled
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            if (admin_)
            {
                communicator_.closeRoom();
            }
            else
            {
                communicator_.leaveRoom();
            }
            _timer.Stop();
            communicator_.logout();
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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Threading;
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
    /// Interaction logic for JoinRoomWindow.xaml
    /// </summary>
    public partial class JoinRoomWindow : Window
    {

        public List<Room> RoomList { get; set; }
        Communicator communicator_;
        string username_;

        Thread t;

        /// <summary>
        /// JoinRoom constructor
        /// </summary>
        /// <param name="communicator"></param>
        /// <param name="username"></param>
        public JoinRoomWindow(Communicator communicator, string username)
        {
            InitializeComponent();
            communicator_ = communicator;
            username_ = username;

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            t = new Thread(updateRooms);
            t.Start();
        }

        /// <summary>
        /// This function updates the room list
        /// </summary>
        public void updateRooms()
        {
            while (true)
            {
                this.Dispatcher.BeginInvoke(new Action(delegate ()
                {
                    RoomList = communicator_.getRooms();

                    lv.ItemsSource = RoomList;
                    DataContext = this;

                }));
                Thread.Sleep(3000);
            }
            
        }

        /// <summary>
        /// This function joins a room, and send the user to RoomView
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void JoinRoom(object sender, MouseButtonEventArgs e)
        {
            Room room = (Room)lv.SelectedItems[0];
            if (communicator_.joinRoom(room))
            {
                t.Abort();
                RoomWindow rw = new RoomWindow(communicator_, username_, false, room);
                rw.Show();
                this.Close();
            }
            else
            {
                MessageBox.Show("Error!");
            }

        }

        /// <summary>
        /// This function returns the user back to the main window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator_, username_);
            mainWin.Show();
            t.Abort();
            this.Close();
        }

        /// <summary>
        /// This function leaves the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            t.Abort();
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

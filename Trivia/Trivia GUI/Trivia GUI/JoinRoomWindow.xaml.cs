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
        public JoinRoomWindow(Communicator communicator, string username)
        {
            InitializeComponent();
            communicator_ = communicator;
            username_ = username;

            /*RoomList = communicator_.getRooms();

            DataContext = this;*/

            t = new Thread(updateRooms);
            t.Start();
        }


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

        private void JoinRoom(object sender, MouseButtonEventArgs e)
        {
            Room room = (Room)lv.SelectedItems[0]; // Should return the details of the row (room) which got double clicked
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

        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator_, username_);
            mainWin.Show();
            t.Abort();
            this.Close();
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            t.Abort();
            communicator_.logout();
            System.Windows.Application.Current.Shutdown();
        }
    }
}

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
    }
}

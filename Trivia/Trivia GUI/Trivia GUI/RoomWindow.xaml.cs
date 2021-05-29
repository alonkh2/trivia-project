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
    /// Interaction logic for RoomWindow.xaml
    /// </summary>
    public partial class RoomWindow : Window
    {
        List<User> UserList { get; set; }
        string username_;
        Communicator communicator_;
        Room room_;
        Thread t_;
        bool admin_;
        public RoomWindow(Communicator communicator, string username, bool admin, Room room)
        {
            InitializeComponent();

            communicator_ = communicator;
            username_ = username;
            room_ = room;
            admin_ = admin;

            roomName.Text = room_.name;


            if (admin_) // If the current user is the admin, add a start game button
            {
                adminName.Text = username;
                var adminButton = new Button();
                var bc = new BrushConverter();

                Style style = this.FindResource("MaterialDesignRaisedButton") as Style;
                adminButton.Style = style;

                adminButton.Margin = new Thickness(725, 479, 95, 80);
                adminButton.Width = 100;
                adminButton.Height = 40;
                adminButton.BorderThickness = new Thickness(0);
                adminButton.BorderBrush = Brushes.Transparent;
                adminButton.Background = (Brush)bc.ConvertFrom("#4c0121");
                adminButton.Foreground = Brushes.White;
                adminButton.Click += new RoutedEventHandler(Start_Click);
                adminButton.Content = "Start";
                adminButton.HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
                adminButton.UseLayoutRounding = true;
                grid.Children.Add(adminButton);
            }

            t_ = new Thread(updateList);
            t_.Start();
        }


        private void Start_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("nice");
        }

        /// <summary>
        /// This function exits the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            t_.Abort();
            communicator_.logout();
            System.Windows.Application.Current.Shutdown();
        }

        /// <summary>
        /// This function returns the user to his previous window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            t_.Abort();

            if (admin_) // If admin go back to CreateRoom
            {
                CreateRoomWindow createWin = new CreateRoomWindow(communicator_, username_);
                createWin.Show();
                this.Close();
            }

            else // If player go back to JoinRoom
            {
                JoinRoomWindow joinRoom = new JoinRoomWindow(communicator_, username_);
                joinRoom.Show();
                this.Close();
            }
        }

        
        private void updateList()
        {
            while (true)
            {
                this.Dispatcher.BeginInvoke(new Action(delegate ()
                {
                    UserList = communicator_.getPlayersInRoom(room_);
                    adminName.Text = UserList.First().username;
                    UserList.RemoveAt(0);
                    playerList.ItemsSource = UserList;
                    
                    DataContext = this;
                }));

                Thread.Sleep(3000);
            }
        }
    }
}

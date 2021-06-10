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

        /// <summary>
        /// This function constructs a RoomWindow
        /// </summary>
        /// <param name="communicator">The communicator</param>
        /// <param name="username">The username of the current user</param>
        /// <param name="admin">Wether the current user is the admin of the room</param>
        /// <param name="room">The current room</param>
        public RoomWindow(Communicator communicator, string username, bool admin, Room room)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

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

                Style style = this.FindResource("MaterialDesignFlatButton") as Style;
                adminButton.Style = style;

                MaterialDesignThemes.Wpf.ButtonAssist.SetCornerRadius(adminButton, new CornerRadius(10));

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
            communicator_.startGame();
            QuestionWindow questionWindow = new QuestionWindow(communicator_, username_, admin_);
            t_.Abort();
            questionWindow.Show();
            this.Close();
            // MessageBox.Show("nice");
        }

        /// <summary>
        /// This function exits the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            t_.Abort();
            if (admin_)
            {
                communicator_.closeRoom();
            }
            else
            {
                communicator_.leaveRoom();
            }
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

            if (admin_) // If the current user is the admin go back to CreateRoom
            {
                communicator_.closeRoom();
                CreateRoomWindow createWin = new CreateRoomWindow(communicator_, username_);
                createWin.Show();
                this.Close();
            }

            else // If the current user is a regular player go back to JoinRoom
            {
                communicator_.leaveRoom();
                JoinRoomWindow joinRoom = new JoinRoomWindow(communicator_, username_);
                joinRoom.Show();
                this.Close();
            }
        }

        
        /// <summary>
        /// This function updates the user list every three seconds
        /// </summary>
        private void updateList()
        {
            while (true)
            {
                this.Dispatcher.BeginInvoke(new Action(delegate ()
                {
                    room_ = communicator_.getRoomState(room_);

                    UserList = room_.users;
                    adminName.Text = room_.users.First().username;
                    UserList.RemoveAt(0);
                    playerList.ItemsSource = UserList;

                    DataContext = this;

                    if (room_.isActive == 2)
                    {
                        t_.Abort();
                        QuestionWindow questionWindow = new QuestionWindow(communicator_, username_, admin_);
                        questionWindow.Show();
                        this.Close();
                    }
                    else if (room_.isActive == 0)
                    {
                        t_.Abort();
                        communicator_.leaveRoom();
                        JoinRoomWindow joinRoom = new JoinRoomWindow(communicator_, username_);
                        joinRoom.Show();
                        this.Close();
                    }
                }));

                Thread.Sleep(200); // 3 seconds is way too much
            }
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

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
        public RoomWindow(Communicator communicator, string username, bool admin, Room room)
        {
            InitializeComponent();

            communicator_ = communicator;
            username_ = username;
            room_ = room;

            roomName.Text = room_.name;
            /*
             * If admin then this
             */

            if (admin)
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

        private void updateList()
        {
            while (true)
            {
                this.Dispatcher.BeginInvoke(new Action(delegate ()
                {
                    UserList = communicator_.getPlayersInRoom(room_);
                    adminName.Text = UserList.First().username;
                    playerList.ItemsSource = UserList;
                    
                    DataContext = this;
                }));

                Thread.Sleep(3000);
            }
        }
    }
}

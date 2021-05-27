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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {

        Communicator communicator_;
        string username_;
        public CreateRoomWindow(Communicator communicator, string username)
        {
            InitializeComponent();
            communicator_ = communicator;
            username_ = username;
        }

        private void Sub_Click(object sender, RoutedEventArgs e) // This function needs to check that all the field are valid and then creates a room
        {
            string name = nameOfRoom.Text;
            string time = timePerQuestion.Text;
            string users = numOfPlayers.Text;
            string questions = numOfQuestions.Text;


            double timeout;
            int max, count;

            if (!double.TryParse(time, out timeout) || !int.TryParse(users, out max) || !int.TryParse(questions, out count) || string.IsNullOrEmpty(name))
            {
                MessageBox.Show("Invalid parameters! Please try again");
                return;
            }

            if (communicator_.createRoom(name, timeout, max, count))
            {
                MessageBox.Show("Success");
            }
            else
            {
                MessageBox.Show("Not success");
            }
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator_, username_); ;
            mainWin.Show();
            this.Close();
        }
    }
}

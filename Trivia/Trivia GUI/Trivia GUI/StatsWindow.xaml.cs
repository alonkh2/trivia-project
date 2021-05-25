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
    /// Interaction logic for StatsWindow.xaml
    /// </summary>
    public partial class StatsWindow : Window
    {

        Communicator communicator;
        string currUser;
        public StatsWindow(Communicator communicator_, string username)
        {
            InitializeComponent();

            communicator = communicator_;
            currUser = username;

            string[] stats = communicator.getPersonalStats(currUser);
        }


        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator, currUser);
            mainWin.Show();
            this.Close();
        }
    }
}

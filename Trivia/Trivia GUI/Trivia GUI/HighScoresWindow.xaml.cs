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
    /// Interaction logic for HighScoresWindow.xaml
    /// </summary>
    public partial class HighScoresWindow : Window
    {
        Communicator communicator;

        public HighScoresWindow(Communicator communicator_)
        {
            InitializeComponent();

            communicator = communicator_;

            string[] stats = communicator.getHighScores();

            if(stats.Length > 1 && String.IsNullOrEmpty(stats[0]) && string.IsNullOrEmpty(stats[1]))
            {
                firstUser.Text = stats[0];
                firstPoints.Text = stats[1];
            }

            if (stats.Length > 3 && String.IsNullOrEmpty(stats[2]) && string.IsNullOrEmpty(stats[3]))
            {
                secondUser.Text = stats[2];
                secondPoints.Text = stats[3];
            }


            if (stats.Length > 5 && String.IsNullOrEmpty(stats[4]) && string.IsNullOrEmpty(stats[5]))
            {
                thirdUser.Text = stats[4];
                thirdPoints.Text = stats[5];
            }

            if (stats.Length > 7 && String.IsNullOrEmpty(stats[6]) && string.IsNullOrEmpty(stats[7]))
            {
                fourthUser.Text = stats[6];
                fourthPoints.Text = stats[7];
            }

            if (stats.Length > 9 && String.IsNullOrEmpty(stats[8]) && string.IsNullOrEmpty(stats[9]))
            {
                fifthUser.Text = stats[8];
                fifthPoints.Text = stats[9];
            }

        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator);
            mainWin.Show();
            this.Close();
        }
    }
}

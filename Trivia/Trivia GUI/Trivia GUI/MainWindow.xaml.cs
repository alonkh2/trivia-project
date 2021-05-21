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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Net.Sockets;

namespace Trivia_GUI
{
    public partial class MainWindow : Window
    {
        Socket socket;
        ///Initializes the MainWindow
        public MainWindow(Socket s)
        {
            InitializeComponent();

            this.socket = s;
        }

        /// <summary>
        /// This function exits the application when the 'Exit' radio button is toggled
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        public void LogOut_Click(object sender, RoutedEventArgs e)
        {
            WelcomeWindow welcomeWin = new WelcomeWindow();
            welcomeWin.Show();
            this.Close();
        }

        private void High_Click(object sender, RoutedEventArgs e)
        {
            HighScoresWindow highWin = new HighScoresWindow();
            highWin.Show();
            this.Close();
        }
    }
}

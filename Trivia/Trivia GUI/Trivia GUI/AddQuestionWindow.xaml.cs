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
    /// Interaction logic for AddQuestionWindow.xaml
    /// </summary>
    public partial class AddQuestionWindow : Window
    {
        Communicator communicator;
        string username;

        public AddQuestionWindow(Communicator communicator_, string username_)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator = communicator_;
            username = username_;
        }



        private void Sub_Click(object sender, RoutedEventArgs e)
        {
            if(string.IsNullOrEmpty(QuestionBox.Text) || string.IsNullOrEmpty(Correct.Text) || string.IsNullOrEmpty(Incorrect1.Text) || string.IsNullOrEmpty(Incorrect2.Text) || string.IsNullOrEmpty(Incorrect3.Text))
            {
                MessageBox.Show("Invalid parameters");
                
            }

            else
            {
                // communicator stuff
                Back_Click(sender, e);

            }
        }


        /// <summary>
        /// This function exits the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }

        /// <summary>
        /// This function returns the user to WelcomeWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator, username);
            mainWin.Show();
            this.Close();
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

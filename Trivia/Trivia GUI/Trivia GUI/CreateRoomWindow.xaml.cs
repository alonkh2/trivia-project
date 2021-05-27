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
        public CreateRoomWindow(Communicator communicator)
        {
            InitializeComponent();
        }

        private void Sub_Click(object sender, RoutedEventArgs e) // This function needs to check that all the field are valid and then creates a room
        {

        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}

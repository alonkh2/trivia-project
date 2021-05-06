using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
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
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {


        public SignupWindow()
        {
            InitializeComponent();
        }

        /// <summary>
        /// This function exits the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 
        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Application.Current.Shutdown();
        }


        /// <summary>
        /// This function checks if an email is valid
        /// </summary>
        /// <param name="source"></param>
        /// <returns></returns>
        private bool IsValidEmail(string source)
        {
            return new EmailAddressAttribute().IsValid(source);
        }

        /// <summary>
        /// This function check wether the Input Boxes are empty or invalid, and if not continues to the MainWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// 
        private void BtnLogin_Click(object sender, RoutedEventArgs e)
        {
            if (!IsValidEmail(txtEmail.Text))
            {
                MessageBox.Show("Invalid email address");
            }

            else if (!String.IsNullOrEmpty(txtPassword.Password) && !String.IsNullOrEmpty(txtEmail.Text) && !String.IsNullOrEmpty(txtUsername.Text))
            {
                MainWindow mainWin = new MainWindow();
                mainWin.Show();
                this.Close();
            }

            else
            {
                MessageBox.Show("Invalid or missing parameters");
            }
        }
    }
}

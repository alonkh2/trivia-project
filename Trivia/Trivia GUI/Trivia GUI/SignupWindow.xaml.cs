﻿using System;
using System.ComponentModel.DataAnnotations;
using System.Windows;
using System.Windows.Input;


namespace Trivia_GUI
{
    /// <summary>
    /// Interaction logic for SignupWindow.xaml
    /// </summary>
    public partial class SignupWindow : Window
    {


        Communicator communicator;

        /// <summary>
        /// This function constructs a SignupWindow
        /// </summary>
        /// <param name="communicator_"></param>
        public SignupWindow(Communicator communicator_)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator = communicator_;
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
        /// This function returns the user to WelcomeWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            WelcomeWindow welcomeWin = new WelcomeWindow();
            welcomeWin.Show();
            this.Close();
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
            else if (String.IsNullOrEmpty(txtPassword.Password) || String.IsNullOrEmpty(txtEmail.Text) || String.IsNullOrEmpty(txtUsername.Text))
            {
                MessageBox.Show("Missing or invalid paramaters");
            }
            else
            {
                try
                {
                    int result = communicator.signup(txtEmail.Text, txtUsername.Text, txtPassword.Password);

                    switch (result)
                    {
                        case 0:
                            MessageBox.Show("Server error");
                            break;

                        case 1:
                            MessageBox.Show("Login error");
                            break;

                        case 2:
                            MainWindow main = new MainWindow(communicator, txtUsername.Text);
                            main.Show();
                            this.Close();
                            break;

                        default:
                            break;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                

                
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

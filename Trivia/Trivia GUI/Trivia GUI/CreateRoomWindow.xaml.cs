﻿using System;
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

        /// <summary>
        /// Create room constructor
        /// </summary>
        /// <param name="communicator">The communicator</param>
        /// <param name="username">The username of the current user</param>
        public CreateRoomWindow(Communicator communicator, string username)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator_ = communicator;
            username_ = username;
        }

        /// <summary>
        /// This fuction tries to create the room, and if successful moves the user to RoomView as an admin
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Sub_Click(object sender, RoutedEventArgs e) // This function needs to check that all the field are valid and then creates a room
        {
            string name = nameOfRoom.Text;
            string time = timePerQuestion.Text;
            string users = numOfPlayers.Text;
            string questions = numOfQuestions.Text;


            double timeout;
            int max, count;

            // Checking that the paramaters are valid
            if (!double.TryParse(time, out timeout) || !int.TryParse(users, out max) || !int.TryParse(questions, out count) || string.IsNullOrEmpty(name))
            {
                MessageBox.Show("Invalid parameters! Please try again");
                return;
            }

            Room room = new Room
            {
                name = name,
                timeout = timeout,
                max = max,
                count = count
            };

            try
            {
                int id = communicator_.createRoom(room);
                room.roomID = id.ToString();
                RoomWindow rw = new RoomWindow(communicator_, username_, true, room);
                rw.Show();
                this.Close();
            }
            catch (Exception ex)
            {
                if (ex.Message == "An existing connection was forcibly closed by the remote host")
                {
                    this.Close();
                }
                MessageBox.Show(ex.Message);
            }
        }

        /// <summary>
        /// This fuction returns the user to the MainWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator_, username_); ;
            mainWin.Show();
            this.Close();
        }

        /// <summary>
        /// This function leaves the program
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                communicator_.logout();
            }
            catch (Exception ex)
            {
                if (ex.Message == "An existing connection was forcibly closed by the remote host")
                {
                    this.Close();
                }
                MessageBox.Show(ex.Message);
            }
            System.Windows.Application.Current.Shutdown();
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

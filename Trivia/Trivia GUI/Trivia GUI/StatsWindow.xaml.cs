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

            string[] stats = communicator.getPersonalStats(currUser); // This does not work alon (stats.length = 1)


            if (stats.Length < 5)
            {
                totalGames.Text = "No data";
                correctAnswers.Text = "No data";
                totalAnswers.Text = "No data";
                avgTime.Text = "No data";
                totalPoints.Text = "No data";
            }

            else 
            {
                totalAnswers.Text = stats[0];
                correctAnswers.Text = stats[1];
                totalGames.Text = stats[2];
                avgTime.Text = stats[3];
                totalPoints.Text = stats[4];
            }
        }


        private void Back_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(communicator, currUser);
            mainWin.Show();
            this.Close();
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            communicator.logout();
            System.Windows.Application.Current.Shutdown();
        }
    }
}

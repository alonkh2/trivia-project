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
    /// Interaction logic for HighScoresWindow.xaml
    /// </summary>
    public partial class HighScoresWindow : Window
    {
        public HighScoresWindow()
        {
            InitializeComponent();
        }

        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWin = new MainWindow(null);
            mainWin.Show();
            this.Close();
        }
    }
}

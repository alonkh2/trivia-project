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
using Xceed.Wpf.AvalonDock.Layout;

namespace Trivia_GUI
{
    /// <summary>
    /// Interaction logic for RoomWindow.xaml
    /// </summary>
    public partial class RoomWindow : Window
    {
        List<User> UserList { get; set; }
        string username;
        Communicator communicator;
        public RoomWindow(Communicator communicator_, string username_)
        {
            InitializeComponent();

            communicator = communicator_;
            username = username_;


            /*
             * If admin then this
             */
            var adminButton = new Button();
            var bc = new BrushConverter();

            Style style = this.FindResource("MaterialDesignRaisedButton") as Style;
            adminButton.Style = style;

            adminButton.Margin = new Thickness(725, 479, 95, 80); 
            adminButton.Width = 100;
            adminButton.Height = 40;
            adminButton.BorderThickness = new Thickness(0);
            adminButton.BorderBrush = Brushes.Transparent;
            adminButton.Background = (Brush)bc.ConvertFrom("#4c0121");
            adminButton.Foreground = Brushes.White;
            adminButton.Click += new RoutedEventHandler(Start_Click);
            adminButton.Content = "Start";
            adminButton.HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
            adminButton.UseLayoutRounding = true;
            grid.Children.Add(adminButton);
            
        }


        private void Start_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("nice");
        }
    }
}

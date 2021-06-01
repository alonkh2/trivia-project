using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Trivia_GUI
{
    /// <summary>
    /// Interaction logic for QuestionWindow.xaml
    /// </summary>
    /// 


    public partial class QuestionWindow : Window
    {
        DispatcherTimer _timer;
        TimeSpan _time;

        public QuestionWindow()
        {
            InitializeComponent();


            //idk what this does, looks important tho

            //_time = TimeSpan.FromSeconds(10);

            //_timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            //{
            //    timer.Text = _time.ToString("c");

            //    if (_time == TimeSpan.Zero)
            //    {
            //        _timer.Stop();
            //    }

            //    _time = _time.Add(TimeSpan.FromSeconds(-1));
            //}, Application.Current.Dispatcher);

            //_timer.Start();
        }

        private void Ans_Click(object sender, RoutedEventArgs e)
        {
            if(sender == ans1)
            {
                // do stuff
            }
        }
    }

}

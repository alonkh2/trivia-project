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
        DispatcherTimer timer_;
        TimeSpan time_;
        Communicator communicator_;
        string username_;
        bool admin_;
        Question question_;
        int count_;
        double timeout_;
        int current_;
        public QuestionWindow(Communicator communicator, string username, bool admin, int count, double timeout, int current)
        {
            InitializeComponent();

            this.Top = (double)App.Current.Properties["verticalDis"];
            this.Left = (double)App.Current.Properties["horizontalDis"];

            communicator_ = communicator;
            username_ = username;
            admin_ = admin;
            count_ = count;
            timeout_ = timeout;
            current_ = current;

            questionNum.Text = current_.ToString() + "/" + count_.ToString();

            try
            {
                question_ = communicator_.getQuestion();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                if (ex.Message == "An existing connection was forcibly closed by the remote host")
                {
                    timer_.Stop();
                    this.Close();
                }
            }

            time_ = TimeSpan.FromSeconds(timeout);

            timer_ = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            {
                timer.Text = time_.ToString(@"mm\:ss");

                if (time_ == TimeSpan.Zero)
                {
                    timer_.Stop();
                    try
                    {
                        communicator.submitAnswer(5);
                    }
                    catch (Exception ex)
                    {
                        if (ex.Message == "An existing connection was forcibly closed by the remote host")
                        {
                            this.Close();
                        }
                        MessageBox.Show(ex.Message);
                    }

                    MessageBox.Show("Wrong");


                    if (current_ == count_)
                    {
                        AfterGameWindow afterGameWindow = new AfterGameWindow(communicator_, username_);
                        afterGameWindow.Show();
                        this.Close();
                    }
                    else
                    {
                        QuestionWindow questionWindow = new QuestionWindow(communicator_, username_, admin_, count_, timeout_, current_ + 1);
                        questionWindow.Show();
                        this.Close();
                    }
                }

                time_ = time_.Add(TimeSpan.FromSeconds(-1));
            }, Application.Current.Dispatcher);


            question.Text = question_.name;
            ans1Txt.Text = question_.answers[0];
            ans2Txt.Text = question_.answers[1];
            ans3Txt.Text = question_.answers[2];
            ans4Txt.Text = question_.answers[3];
            timer_.Start();

        }

        private void Ans_Click(object sender, RoutedEventArgs e)
        {
            int ans = -1;
            int correct = -2;
            if (sender == ans1)
            {
                ans = 1;
            }
            else if (sender == ans2)
            {
                ans = 2;
            }
            else if (sender == ans3)
            {
                ans = 3;
            }
            else if (sender == ans4)
            {
                ans = 4;
            }

            timer_.Stop();

            try
            {
                correct = communicator_.submitAnswer(ans);
            }
            catch (Exception ex)
            {
                if (ex.Message == "An existing connection was forcibly closed by the remote host")
                {
                    timer_.Stop();
                    this.Close();
                }
                MessageBox.Show(ex.Message);
                
            }

            if (correct == ans)
            {
                MessageBox.Show("Correct");
            }
            else
            {
                MessageBox.Show("Wrong");
            }

            if (current_ == count_)
            {
                AfterGameWindow afterGameWindow = new AfterGameWindow(communicator_, username_);
                afterGameWindow.Show();
                this.Close();
            }
            else
            {
                QuestionWindow questionWindow = new QuestionWindow(communicator_, username_, admin_, count_, timeout_, current_ + 1);
                questionWindow.Show();
                this.Close();
            }

        }


        /// <summary>
        /// This function returns the user to his previous window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Back_Click(object sender, RoutedEventArgs e)
        {
            timer_.Stop();
            try
            {
                communicator_.leaveGame();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                if (ex.Message == "An existing connection was forcibly closed by the remote host")
                {
                    this.Close();
                }
            }
            MainWindow mainWin = new MainWindow(communicator_, username_);
            mainWin.Show();
            this.Close();
        }


        /// <summary>
        /// This function exits the application when the 'Exit' radio button is toggled
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Leave_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                communicator_.leaveGame();
                timer_.Stop();
                communicator_.logout();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                if (ex.Message == "An existing connection was forcibly closed by the remote host")
                {
                    timer_.Stop();
                    this.Close();
                }
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

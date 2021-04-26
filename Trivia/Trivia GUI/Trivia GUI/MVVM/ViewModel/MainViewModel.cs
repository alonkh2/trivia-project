using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Trivia_GUI.Core;
using Trivia_GUI.MVVM.ViewModel;

namespace Trivia_GUI.MVVM
{
    /// <summary>
    ///  MainViewModel class, defining the current screen on display (Home, stats, etc.)
    /// </summary>
    class MainViewModel : ObservableObject
    {

        // RelayCommand referncing the HomeView
        public RelayCommand HomeViewCommand { get; set; }

        public HomeViewModel HomeVM { get; set; }

        private object _currentView;

        /// <summary>
        /// Creating class CurrentView
        /// </summary>
        public object CurrentView
        {
            get { return _currentView; }
            set
            {
                _currentView = value;
                onPropertyChanged();
            }
        }

        /// <summary>
        /// This function changes the view according to the relay commands 
        /// </summary>
        public MainViewModel()
        {
            HomeVM = new HomeViewModel();
            CurrentView = HomeVM;

            HomeViewCommand = new RelayCommand(o =>
            {
                CurrentView = HomeVM;
            });
        }
    }
}

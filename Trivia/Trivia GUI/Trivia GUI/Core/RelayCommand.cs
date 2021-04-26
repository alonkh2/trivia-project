using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Trivia_GUI.Core
{
    class RelayCommand : ICommand
    {
        private Action<object> _execute;
        private Func<object, bool> _canExecute;

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        /// <summary>
        /// This function constructs a RelayCommand
        /// </summary>
        /// <param name="execute"></param>
        /// <param name="canExecute"></param>
        public RelayCommand(Action<Object> execute, Func<object, bool> canExecute = null)
        {
            _execute = execute;
            _canExecute = canExecute;
        }

        /// <summary>
        /// This function checks if param can be executed
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        public bool CanExecute(object param)
        {
            return _canExecute == null || _canExecute(param);
        }

        /// <summary>
        /// This function executes param
        /// </summary>
        /// <param name="param"></param>
        public void Execute(object param)
        {
            _execute(param);
        }
    }
}

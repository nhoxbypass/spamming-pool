using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace QLD
{
    static class Program
    {
        /// <summary>
        /// Open the login form, to sign in or sign up
        /// If succeed, open the main form to manipulate
        /// Popup form undertake add and edit profile of Student
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new LoginForm());
            
        }
    }
}

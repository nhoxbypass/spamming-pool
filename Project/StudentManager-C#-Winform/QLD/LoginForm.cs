using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;




namespace QLD
{
    public partial class LoginForm : Form
    {
        public LoginForm()
        {
            InitializeComponent();
        }

        

        private void login_Click(object sender, EventArgs e)
        {
            if ((!signup.Checked) && (!signin.Checked))
            {
                MessageBox.Show("Bạn phải chọn sign in hoặc sign up.", "Thông báo");
            }
            else
            {
                //Get user name and password from text box, normalize it
                string UserName = username.Text;
                UserName = UserName.Trim();
                string Password = password.Text;

                //Connect database
                Login login = new Login();
                login.connectAcount();

                if (cfrm_password.Enabled == false)
                {
                    login.signIn(UserName, Password);
                }
                else
                {
                    login.signUp(UserName, Password, cfrm_password.Text, txtName.Text, txtSub.Text);
                }

                login.closeConnect();
            }
        }


        private void LoginForm_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
            {
                MainForm mainForm = new MainForm();
                mainForm.Activate();
                mainForm.Show();
            }
        }

            
        private void bt_exit_Click(object sender, EventArgs e)
        {
            Login login = new Login();
            login.exitProgram();
        }

        

        private void signup_CheckedChanged(object sender, EventArgs e)
        {
            cfrm_password.Enabled = true;
            txtName.Enabled = true;
            txtSub.Enabled = true;
            this.username.ResetText();
            this.password.ResetText();
            this.cfrm_password.ResetText();
            this.txtName.ResetText();
            this.txtSub.ResetText();
            login.Text = "Sign up";
        }


        private void signin_CheckedChanged_1(object sender, EventArgs e)
        {
            cfrm_password.Enabled = false;
            txtName.Enabled = false;
            txtSub.Enabled = false;
            this.username.ResetText();
            this.password.ResetText();
            this.cfrm_password.ResetText();
            this.txtName.ResetText();
            this.txtSub.ResetText();
            login.Text = "Sign in";
        }

        

      



        
    }


    
}

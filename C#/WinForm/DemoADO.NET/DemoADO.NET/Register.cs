using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DemoADO.NET
{
    public partial class Register : Form
    {
        SqlConnection sqlConnection;
        public Register()
        {
            InitializeComponent();
        }

        private void btnRegister_Click(object sender, EventArgs e)
        {
            string username = txtUsername.Text;
            string password = txtPassword.Text;

            if(username != "" && password != "")
            {
                //hop le
                sqlConnection = new SqlConnection(Form1.connectionString);
                sqlConnection.Open();

                SqlCommand command = new SqlCommand("INSERT INTO Account(username,password) VALUES ('" + username +  "','" + password + "')", sqlConnection);
                int res = command.ExecuteNonQuery();

                if(res > 0)
                {
                    MessageBox.Show("Đăng ký thành công","Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    command = sqlConnection.CreateCommand();
                    command.CommandText = "CREATE TABLE " + username + " (id int IDENTITY(1,1) PRIMARY KEY, title nvarchar(50), text ntext, date date)";
                    command.ExecuteNonQuery();
                    sqlConnection.Close();                    
                    this.Close();
                }
                else
                {
                    MessageBox.Show("Đăng ký thất bại", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    sqlConnection.Close();            
                }

                
            }
        }

        private void txtUsername_Leave(object sender, EventArgs e)
        {
            if (txtUsername.Text.Length == 0)
            {
                txtUsername.Text = "Enter username...";
                txtUsername.ForeColor = SystemColors.GrayText;
            }
        }

        private void txtPassword_Leave(object sender, EventArgs e)
        {
            if (txtPassword.Text.Length == 0)
            {
                txtPassword.Text = "Enter password...";
                txtPassword.ForeColor = SystemColors.GrayText;
            }
        }

        private void txtUsername_Enter(object sender, EventArgs e)
        {
            if (txtUsername.Text == "Enter username...")
            {
                txtUsername.Text = "";
                txtUsername.ForeColor = SystemColors.WindowText;
            }
        }

        private void txtPassword_Enter(object sender, EventArgs e)
        {
            if (txtPassword.Text == "Enter password...")
            {
                txtPassword.Text = "";
                txtPassword.ForeColor = SystemColors.WindowText;
            }
        }
    }
}

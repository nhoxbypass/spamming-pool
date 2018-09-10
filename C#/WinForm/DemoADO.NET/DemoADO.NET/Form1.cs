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
using System.Configuration;


namespace DemoADO.NET
{
    public partial class Form1 : Form
    {
        //Default SQL connection String, another is in App.config. Must specify server name (Data Source)
        //Data Source=.\SQLEXPRESS
        //or
        //Data Source=(local)
        string defaultConnectionString = @"Data Source=localhost\SQLExpress; Integrated Security=True";
        //Declare variables
        string userID = "admin";
        string databaseName = "DIARY"; 
        public static string connectionString;
        SqlConnection sqlConnection;
        List<Item> listItem;

        public Form1()
        {
            InitializeComponent();
            connectionString = defaultConnectionString;
            listItem = new List<Item>();
            createOrOpenDatabase();
    
            
        }

        public void createOrOpenDatabase() //Open or create main db if not exists
        {
            if (checkDatabaseExists(connectionString, databaseName))
            {
                //If db exist
                connectionString = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

                sqlConnection = new SqlConnection(connectionString);
            }
            else
            {
                //Db does not exist
                //Create db
                connectionString = defaultConnectionString + "; database=master";
                sqlConnection = new SqlConnection(connectionString);

                sqlConnection.Open();
                var command = sqlConnection.CreateCommand();
                command.CommandText = "CREATE DATABASE " + databaseName;
                command.ExecuteNonQuery();
                sqlConnection.Close();

                connectionString = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
                sqlConnection = new SqlConnection(connectionString);

                sqlConnection.Open();

                command = sqlConnection.CreateCommand();
                command.CommandText = "CREATE TABLE Account (username varchar(255) PRIMARY KEY, password varchar(255))";
                command.ExecuteNonQuery();

                sqlConnection.Close();  
            }
        }

        public static bool checkDatabaseExists(string connectionString, string databaseName)
        {
            using (var connection = new SqlConnection(connectionString))
            {
                using (var command = new SqlCommand(string.Format(
                       "SELECT db_id('{0}')", databaseName), connection))
                {
                    connection.Open();
                    return (command.ExecuteScalar() != DBNull.Value);
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string text = rtbInputField.Text;

            sqlConnection.Open();
            
            //SqlCommand command = new SqlCommand("SELECT id from " + userID + " WHERE id=(SELECT MAX(id) FROM " + userID + ")");
            //int id = (int)command.ExecuteScalar();

            SqlCommand command = new SqlCommand(@"INSERT INTO [" + userID + "] (title, text) VALUES (N'" + txtTitle.Text + "', N'" + text + "')", sqlConnection);
            int res = command.ExecuteNonQuery();

            if(res <= 0)
            {
                MessageBox.Show("Thêm thất bại","Thông báo",MessageBoxButtons.OK,MessageBoxIcon.Error);
                sqlConnection.Close();
            }
            else
            {
                MessageBox.Show("Thành công", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Information);
                sqlConnection.Close();
                loadItemsToListview();
                rtbInputField.Clear();
                txtTitle.Clear();
            }

            
        }

        private void loadItemsToListview()
        {
            if (sqlConnection.State == ConnectionState.Closed)
            {
                sqlConnection.Open();
            }

            SqlCommand command = new SqlCommand("SELECT * FROM [" + userID + "]",sqlConnection);
            SqlDataReader reader = command.ExecuteReader();

            if(reader.HasRows == true)
            {
                lvItem.Items.Clear();
                listItem.Clear();

                while (reader.Read())
                {
                    Item item = new Item(reader["title"].ToString(), reader["text"].ToString());
                    listItem.Add(item);
                    lvItem.Items.Add(reader["title"].ToString());
                }
            }

            sqlConnection.Close();
        }

        private void lvItem_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (lvItem.SelectedIndices.Count > 0 && listItem.Count > 0)
            {
                int selectedIndex = lvItem.SelectedIndices[0];
                rtbInputField.Text = listItem[selectedIndex].mText;
                txtTitle.Text = listItem[selectedIndex].mTitle;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string username = txtID.Text;
            string password = txtPass.Text;
            if (username != "" && password != "")
            {
                sqlConnection.Open();
                SqlCommand command = new SqlCommand("SELECT * FROM Account WHERE username = '" + username + "' AND password = '" + password + "'", sqlConnection);
                SqlDataReader reader = command.ExecuteReader();

                if(reader.HasRows)
                {
                    //Dang nhap thanh cong
                    reader.Read();
                    userID = reader["username"].ToString();
                    reader.Close();
                    loadItemsToListview();

                    //
                    txtID.Enabled = false;
                    txtPass.Enabled = false;
                    btnLogin.Enabled = false;

                    txtTitle.Enabled = true;
                    rtbInputField.Enabled = true;
                    btnSave.Enabled = true;

                    txtTitle.Text = "Enter note title...";
                    txtTitle.ForeColor = SystemColors.GrayText;
                }
                else
                {
                    //Dang nhap that bai
                    MessageBox.Show("Sai tài khoản hoặc mật khẩu!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                sqlConnection.Close();
            }
            else
            {
                MessageBox.Show("Tài khoản và mật khẩu không được trống!", "Thông báo", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }


        }

        private void đăngKýToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Register regForm = new Register();
            regForm.ShowDialog();
        }

        private void thoátToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new About().Show();
        }

        private void txtID_Leave(object sender, EventArgs e)
        {
            if (txtID.Text.Length == 0)
            {
                txtID.Text = "Username...";
                txtID.ForeColor = SystemColors.GrayText;
            }
        }

        private void txtPass_Leave(object sender, EventArgs e)
        {
            if (txtPass.Text.Length == 0)
            {
                txtPass.Text = "Password...";
                txtPass.ForeColor = SystemColors.GrayText;
            }
        }

        private void txtID_Enter(object sender, EventArgs e)
        {
            if (txtID.Text == "Username...")
            {
                txtID.Text = "";
                txtID.ForeColor = SystemColors.WindowText;
            }
        }

        private void txtPass_Enter(object sender, EventArgs e)
        {
            if (txtPass.Text == "Password...")
            {
                txtPass.Text = "";
                txtPass.ForeColor = SystemColors.WindowText;
            }
        }

        private void txtTitle_Leave(object sender, EventArgs e)
        {
            if (txtTitle.Text.Length == 0)
            {
                txtTitle.Text = "Enter note title...";
                txtTitle.ForeColor = SystemColors.GrayText;
            }
        }

        private void txtTitle_Enter(object sender, EventArgs e)
        {
            if (txtTitle.Text == "Enter note title...")
            {
                txtTitle.Text = "";
                txtTitle.ForeColor = SystemColors.WindowText;
            }
        }
    }

    class Item
    {
        public string mTitle;
        public string mText;
        
        public Item(string title, string text)
        {
            mTitle = title;
            mText = text;
        }
    }
}

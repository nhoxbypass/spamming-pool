using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Data;
using System.Configuration;

namespace QLD
{
    //DataAdapter la cau noi giua database va dataset
    public class Login
    {
        //Declare variables
        public SqlConnection accConnect;
        public static int teacherID = 0; //Locate the id of teacher to show in MainForm
        

        
        //Functions
        public bool connectAcount()
        {
            string connectString = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
           

            //connectString = @"Data Source=.\SQLEXPRESS;AttachDbFilename=StudentData.mdf;database=StudentData;Integrated Security=True;Connect Timeout=30;User Instance=True";
            accConnect = new SqlConnection(connectString);

            try
            {
                
                accConnect.Open();
                return true;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return false;
            }

        }

        public void signIn(string UserName, string Password)
        {
            if (isBlank(UserName,Password) == false)
            {
                SqlCommand myCommand; //sqlcommand <doi tuong> = new sqlcommand(<cau lenh sql>, <doi tuong connection>)
                SqlDataAdapter da;
                string cmdString = "SELECT * FROM Account WHERE username = '" + UserName + "' AND password = '" + Password + "'";

                myCommand = new SqlCommand(cmdString, accConnect);
                

                try
                {
                    da = new SqlDataAdapter(myCommand);
                    DataSet ds = new DataSet();
                    DataTable dt = new DataTable();
                    da.Fill(dt);

                    //Save the value of teacherID to use later
                    teacherID = Convert.ToInt32(dt.Rows[0][0]);


                    //Open main form
                    MainForm mainForm = new MainForm();
                    mainForm.Activate();
                    mainForm.Show();

                }
                catch (Exception ex)
                {
                    MessageBox.Show("Sai tài khoản hoặc mật khẩu. ");
                }
            }
        }

        public void signUp(string UserName, string Password, string CfrmPassWord, string Name, string Subject)
        {
            if (isBlank(UserName, Password) == false)
            {
                if (Password == CfrmPassWord)
                {
                    int result = 0;
                    
                    //Add new account to DB
                    string cmdString = "insert into Account (username, password, name, subject) values ('" + UserName + "','" + Password + "', N'" + Name + "', N'" + Subject + "')";
                    result = addAccount(cmdString);

                    if(result > 0)
                    {
                        MessageBox.Show("Đăng ký thành công!", "Thông báo");
                    }
                    else{
                        MessageBox.Show("Đăng ký thất bại!", "Thông báo");
                    }
                    
                }
                else
                {
                    MessageBox.Show("Mật khẩu không trùng khớp! ", "Thông báo");
                }
            }
        }


        public void closeConnect()
        {
            if (accConnect.State == ConnectionState.Open)
            { accConnect.Close(); }
        }


        public void exitProgram()
        {
            //Take a DialogResult to collect result of the Mbox, if 'Yes' exit program
            DialogResult thongbao;
            thongbao = (MessageBox.Show("Bạn có muốn thoát?", "Chú ý", MessageBoxButtons.YesNo, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1));

            if (thongbao == DialogResult.Yes)
            {
                Application.Exit();
            }
        }


        public void showTeacherInfo(int _teacherId)
        {
            connectAcount();

            SqlDataAdapter da;
            string cmdString = "SELECT * FROM Account WHERE id = " + _teacherId.ToString();

            try
            {

                //Sql cmd, to fill data in to DataTable
                da = new SqlDataAdapter(cmdString,accConnect);
                DataSet ds = new DataSet();
                DataTable dt = new DataTable();
                da.Fill(dt);

                string info = "Tài khoản: " + dt.Rows[0]["username"].ToString() + "\nHọ tên: " + dt.Rows[0]["name"].ToString() + "\nMôn giảng dạy: " + dt.Rows[0]["subject"].ToString();
                MessageBox.Show(info, "Thông tin giáo viên");

            }
            catch (Exception ex)
            {
                MessageBox.Show("Sai tài khoản hoặc mật khẩu. ");
            }

            closeConnect();
        }


        //Additional function
        public bool isBlank(string UserName, string Password)
        {
            if (UserName == "")
            {
                MessageBox.Show("Username can not be blank!");
                return true;
            }
            else if(Password == "")
            {
                MessageBox.Show("Password can not be blank!");
                return true;
            }
            else
                return false;
        }


        public int addAccount(string cmdString)
        {
            int result = 0;
            try
            {
               connectAcount();
               SqlCommand cmd = new SqlCommand(cmdString, accConnect);
               result = cmd.ExecuteNonQuery();
           
            }
            catch (Exception ex)
            {
                MessageBox.Show("Tài khoản đã tồn tại", "Thông báo");
                result = 0;
            }
            finally
            {
                closeConnect();
            }
                return result;
        }
    }

    }


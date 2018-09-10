using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Configuration;

namespace QLD
{
    class Main
    {
        public SqlConnection dataConnect;
        public DataTable dataTable = new DataTable();
        //0: Show, 1: Add, 2: Edit, 3: Delete, 4: Search MSSV, 5: Search name
        public static int SelectedBtIndex;
        public static string SelectedStudentId = "0";

        public bool connectData()
        {
            string connectString = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

            dataConnect = new SqlConnection(connectString);

            try
            {
                dataConnect.Open();
                return true;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return false;
            }
        }


        public DataTable GetDataTable(string cmdString)
        {
            try
            {
                connectData();
                SqlDataAdapter da = new SqlDataAdapter(cmdString, dataConnect);
                DataSet ds = new DataSet();

                da.Fill(dataTable);
            }
            catch (System.Exception)
            {
                dataTable = null;
            }
            finally
            {
                closeConnect();
            }

            return dataTable;
        }


        public void ShowSearchForm(MainForm mainfrm)
        {
            //Take a instance of MainForm as argument, don't make a new instance form, so when call this func in MainForm, we call ShowSearchForm(this)
            PopupForm search = new PopupForm(mainfrm);

            search.label.Text = "TÌM KIẾM HỌC SINH";

            search.groupBoxAdd.Visible = false;
            search.groupBoxEdit.Visible = false;
            search.groupBoxSearch.Visible = true;
            search.groupBoxSearch.BringToFront();
            SelectedBtIndex = 4;

            search.Show();
        }


        public void ShowAddForm(MainForm mainfrm)
        {
            PopupForm add = new PopupForm(mainfrm);

            add.label.Text = "THÊM HỌC SINH";

            add.groupBoxAdd.Visible = true;
            add.groupBoxAdd.BringToFront();
            add.groupBoxEdit.Visible = false;
            add.groupBoxSearch.Visible = false;
            SelectedBtIndex = 1;

            add.Show();
        }

        public bool addStudent(string cmdStr)
        {
            //cmdStr like "insert into Data(name, studentID, birthday, gender,faculty,class,address) values (N'" + txtAddName.Text + "'," + 'txtAddMSSV.Text' + ",'" + dateTPAdd.Text + "',N'" + cbAddGender.Text + "', N'" + cbAddFalcuty.Text + "', '" + cbAddClass.Text + "', '" + txtAddAddress.Text + "')"
            int result = 0;
           
            result = dataProcessing(cmdStr);

            if (result > 0)
            {
                MessageBox.Show("Thêm thành công.", "Thông báo");
                return true;
            }
            else
            {
                MessageBox.Show("Không thành công, vui lòng thử lại.", "Thông báo");
                return false;
            }
                
        }


        public void ShowEditForm(MainForm mainfrm)
        {
            if(SelectedStudentId != "0")
            {
                PopupForm edit = new PopupForm(mainfrm);

                edit.label.Text = "SỬA HỌC SINH";

                edit.groupBoxAdd.Visible = false;
                edit.groupBoxEdit.Visible = true;
                edit.groupBoxEdit.BringToFront();
                edit.groupBoxSearch.Visible = false;
                SelectedBtIndex = 2;

                edit.Show();
            }
            else
                MessageBox.Show("Chọn sinh viên cần sửa!", "Thông báo");
                 
        }


        public bool editStudent(string cmdStr)
        {
            //CmdString like "update Data set name=N'"+ txtEditName.Text +"', studentID='"+ txtEditMSSV.Text +"', birthday='" + dateTPEdit.Text + "', gender=N'"+ cbEditGender.Text +"',faculty=N'"+ cbEditFalcuty.Text +"',class='"+ cbEditClass.Text +"',address=N'"+ txtEditAddress.Text +"' where studentID='"+ txtEditMSSV.Text +"'"
            int result = 0;
            MessageBox.Show(cmdStr);
            result = dataProcessing(cmdStr);

            if (result > 0)
            {
                MessageBox.Show("Sửa thành công.", "Thông báo");
                return true;
                
            }
            else
            {
                MessageBox.Show("Không thành công, vui lòng thử lại.", "Thông báo");
                return false;
            }

        }


        public void DeleteStudent(string StudentIndex)
        {
            connectData();
            if(StudentIndex == "0")
            {
                MessageBox.Show("Bạn phải chọn sinh viên cần xóa");
                return;
            }

            
            int result = dataProcessing("delete from Data WHERE studentID = '" + StudentIndex +"'");
            if (result > 0)
            {
                MessageBox.Show("Đã xóa!");
            }
            else
            {
                MessageBox.Show("Error!");
            }
        }



        public void closeConnect()
        {
            if (dataConnect.State == ConnectionState.Open)
            { dataConnect.Close(); }
        }


        public int dataProcessing(string cmdString) //Do something as cmdString and return result > 0 if succeed
        {
            int result = 0;
            try
            {
                connectData();
                SqlCommand cmd = new SqlCommand(cmdString, dataConnect);
                result = cmd.ExecuteNonQuery();

            }
            catch (Exception ex)
            {
                //Thông báo lỗi ra!
                MessageBox.Show(ex.ToString());
                /*MessageBox.Show("MSSV đã tồn tại");*/
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

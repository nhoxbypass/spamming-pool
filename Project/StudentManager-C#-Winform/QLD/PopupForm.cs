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
    public partial class PopupForm : Form
    {
        private MainForm mainfrm;
        public PopupForm(MainForm form)
        {
            InitializeComponent();
            mainfrm = form;
        }



        private void PopupForm_Load(object sender, EventArgs e)
        {
            AddFalcuty();
            if (Main.SelectedBtIndex == 2) //Edit Form
            {
                
                    loadDataToEdit();
                
            }
        }

        private void btCancle_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        
        private void btDone_Click(object sender, EventArgs e)
        {
            if(Main.SelectedBtIndex == 1)   //Add Form
            {
                if (isAddBlank() == false)
                {
                    Main main = new Main();
                    bool result = false;

                    result = main.addStudent("insert into Data(name, studentID, birthday, gender,faculty,class,address) values (N'" + txtAddName.Text + "','" + txtAddMSSV.Text + "','" + dateTPAdd.Text + "',N'" + cbAddGender.Text + "', N'" + cbAddFalcuty.Text + "', '" + cbAddClass.Text + "', N'" + txtAddAddress.Text + "')");

                    if(result == true)
                    {
                        //Close the form when succeed
                        this.Close();
                        mainfrm.getData("select * from Data");
                        

                    }
                }
            }
            else if (Main.SelectedBtIndex == 2) //Edit Form
            {
                if (isEditBlank() == false)
                {
                    Main main = new Main();
                    bool result = false;

                    result = main.editStudent("update Data set name=N'"+ txtEditName.Text +"', studentID='"+ txtEditMSSV.Text +"', birthday='" + dateTPEdit.Text + "', gender=N'"+ cbEditGender.Text +"',faculty=N'"+ cbEditFalcuty.Text +"',class='"+ cbEditClass.Text +"',address=N'"+ txtEditAddress.Text +"' where studentID='"+ txtEditMSSV.Text +"'");

                    if (result == true)
                    {
                        this.Close();
                        mainfrm.getData("select * from Data");
                    }
                }
            }
            else if(Main.SelectedBtIndex == 4) //Search MSSV form
            {
                if(txtSearchMSSV.Text != "")
                {
                    Main main = new Main();
                    DataTable dt = main.GetDataTable("select * from Data where studentID like '%" + txtSearchMSSV.Text + "%'");
                    
                    try
                    {
                        if(dt.Rows[0]["studentID"] != null)
                        {
                            mainfrm.getData("select * from Data where studentID like '%" + txtSearchMSSV.Text + "%'");
                            this.Close();
                        }

                    }
                    catch(Exception ex)
                    {
                        MessageBox.Show("Không tìm thấy!");
                    }
                    
                }
                else
                {
                    MessageBox.Show("MSSV không được để trống");
                }

            }
            else if (Main.SelectedBtIndex == 5) //Search Name Form
            {
                if (txtSearchName.Text != "")
                {
                    Main main = new Main();
                    DataTable dt = main.GetDataTable("select * from Data where name like N'%" + txtSearchName.Text + "%'");
                    
                    try
                    {
                        if (dt.Rows[0]["name"] != null)
                        {
                            mainfrm.getData("select * from Data where name like N'%" + txtSearchName.Text + "%'");
                            this.Close();
                        }

                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("Không tìm thấy!");
                    }


                }
                else
                {
                    MessageBox.Show("Tên không được để trống");
                }
            }
            
        }

        private void radioBtMSSV_CheckedChanged(object sender, EventArgs e)
        {
            Main.SelectedBtIndex = 4;
            txtSearchMSSV.ResetText();
            txtSearchName.ResetText();
            txtSearchMSSV.Enabled = true;
            txtSearchName.Enabled = false;

        }

        private void radioBtName_CheckedChanged(object sender, EventArgs e)
        {
            Main.SelectedBtIndex = 5;
            txtSearchMSSV.ResetText();
            txtSearchName.ResetText();
            txtSearchMSSV.Enabled = false;
            txtSearchName.Enabled = true;
        }


        //Additional Functions
        private void AddFalcuty()
        {
            cbAddFalcuty.Items.Add("Công nghệ thông tin");
            cbAddFalcuty.Items.Add("Hóa học");
            cbEditFalcuty.Items.Add("Công nghệ thông tin");
            cbEditFalcuty.Items.Add("Hóa học");
        }

        private void cbAddFalcuty_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Refresh the AddClass ComboBox
            cbAddClass.SelectedIndex = -1;
            cbAddClass.Items.Clear();
            
            //Add new item to this CB
            if(cbAddFalcuty.SelectedIndex == 0)
            {
                cbAddClass.Items.Add("14CTT3");
                cbAddClass.Items.Add("14CTT2");
                cbAddClass.Items.Add("14CTT1");
            }
            else if (cbAddFalcuty.SelectedIndex == 1)
            {
                cbAddClass.Items.Add("14HOH2");
                cbAddClass.Items.Add("14HOH1");
            }

        }

        private void cbEditFalcuty_SelectedIndexChanged(object sender, EventArgs e)
        {
            //Refresh the AddClass ComboBox
            cbEditClass.SelectedIndex = -1;
            cbEditClass.Items.Clear();

            //Add new item to this CB
            if (cbEditFalcuty.SelectedIndex == 0)
            {
                cbEditClass.Items.Add("14CTT3");
                cbEditClass.Items.Add("14CTT2");
                cbEditClass.Items.Add("14CTT1");
            }
            else if (cbEditFalcuty.SelectedIndex == 1)
            {
                cbEditClass.Items.Add("14HOH2");
                cbEditClass.Items.Add("14HOH1");
            }
        }

        private bool isAddBlank()
        {
            if (txtAddMSSV.Text == "") 
            {
                errorProvider1.SetError(txtAddMSSV, "Mã số SV không được để trống");
                return true;
            } 
            if (txtAddName.Text == "") 
            {
                errorProvider1.SetError(txtAddName, "Tên SV không được để trống");
                return true;
            }
            if (cbAddGender.Text == "") 
            {
                errorProvider1.SetError(cbAddGender, "Giới tính không được để trống");
                return true;
            }
            
            return false;

        }

        private bool isEditBlank()
        {
            if (txtEditMSSV.Text == "")
            {
                errorProvider1.SetError(txtEditMSSV, "Mã số SV không được để trống");
                return true;
            }
            if (txtEditName.Text == "")
            {
                errorProvider1.SetError(txtEditName, "Tên SV không được để trống");
                return true;
            }
            if (cbEditGender.Text == "")
            {
                errorProvider1.SetError(cbEditGender, "Giới tính không được để trống");
                return true;
            }

            return false;

        }

        private void txtAddMSSV_TextChanged(object sender, EventArgs e)
        {
            errorProvider1.SetError(txtAddMSSV, "");
        }

        private void txtAddName_TextChanged(object sender, EventArgs e)
        {
            errorProvider1.SetError(txtAddName, "");
        }

        private void cbAddGender_SelectedIndexChanged(object sender, EventArgs e)
        {
            errorProvider1.SetError(cbAddGender, "");
        }

        private void cbEditGender_SelectedIndexChanged(object sender, EventArgs e)
        {
            errorProvider1.SetError(cbEditGender, "");
        }

        private void txtEditName_TextChanged(object sender, EventArgs e)
        {
            errorProvider1.SetError(txtEditName, "");
        }

        private void txtEditMSSV_TextChanged(object sender, EventArgs e)
        {
            errorProvider1.SetError(txtEditMSSV, "");
        }

        
        private void loadDataToEdit() //Load data to txtBox of the edit form
        {
            Main main = new Main();
            DataTable dt = main.GetDataTable("select * from Data where studentID = '" + Main.SelectedStudentId + "'");
                
                try
                {
                    txtEditName.Text = dt.Rows[0][1].ToString();
                    txtEditMSSV.Text = dt.Rows[0][2].ToString();
                    dateTPEdit.Value = DateTime.Parse(dt.Rows[0][3].ToString());
                    cbEditGender.Text = dt.Rows[0][4].ToString();
                    cbEditFalcuty.Text = dt.Rows[0][5].ToString();
                    cbEditClass.Text = dt.Rows[0][6].ToString();
                    txtEditAddress.Text = dt.Rows[0][7].ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }    
        }

       
    }
}

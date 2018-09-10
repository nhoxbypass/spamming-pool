using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace QLD
{
    public partial class MainForm : Form
    {
        

        public MainForm()
        {
            InitializeComponent();
        }


        

        private void MainForm_Load(object sender, EventArgs e)
        {
            getData("select * from Data");
        }


        private void btSearch_Click(object sender, EventArgs e)
        {
            Main main = new Main();
            main.ShowSearchForm(this);
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            Main main = new Main();
            main.ShowAddForm(this);
        }



        private void EditButton_Click(object sender, EventArgs e)
        {
            Main main = new Main();
            main.ShowEditForm(this);
        }

        

        private void TeacherInfo_ToolStripMenu_Click(object sender, EventArgs e)
        {
            Login teacher = new Login();
            teacher.showTeacherInfo(Login.teacherID);
        }


        private void ExitToolStripMenu_Click(object sender, EventArgs e)
        {
            Login program = new Login();
            program.exitProgram();
        }


        private void dataGWMain_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            //Check if user click on the Cell and take the studentID in that Row which has that Cell and locate in 'SelectedStudentId'
            DataGridViewRow row = new DataGridViewRow();
            if (e.RowIndex != -1)
            {
                row = this.dataGWMain.Rows[e.RowIndex];
                Main.SelectedStudentId = row.Cells["studentID"].Value.ToString();
                /*MessageBox.Show( Main.SelectedStudentId);*/
            }

        }
 


        //Additional Functions
        private DataTable AutoNumberedTable(DataTable SourceTable)
        {

            DataTable ResultTable = new DataTable();

            DataColumn AutoNumberColumn = new DataColumn();

            AutoNumberColumn.ColumnName = "S.No.";

            AutoNumberColumn.DataType = typeof(int);

            AutoNumberColumn.AutoIncrement = true;

            AutoNumberColumn.AutoIncrementSeed = 1;

            AutoNumberColumn.AutoIncrementStep = 1;

            ResultTable.Columns.Add(AutoNumberColumn);

            ResultTable.Merge(SourceTable);

            return ResultTable;

        }


        public void getData(string cmdString)
        {
            //Get data table
            Main main = new Main();
            main.connectData();
            DataTable dt = main.GetDataTable(cmdString);

            //dt = AutoNumberedTable(dt);

            this.dataGWMain.DataSource = dt;
            dataGWMain.Update();

            //Rename the columns
            dataGWMain.Columns[0].Visible = false;
            dataGWMain.Columns[1].HeaderText = "Tên Sinh viên";
            dataGWMain.Columns[2].HeaderText = "MSSV";
            dataGWMain.Columns[3].HeaderText = "Ngày sinh";
            dataGWMain.Columns[4].HeaderText = "Giới tính";
            dataGWMain.Columns[5].HeaderText = "Khoa";
            dataGWMain.Columns[6].HeaderText = "Lớp";
            dataGWMain.Columns[7].HeaderText = "Địa chỉ";

        }

        private void btDelete_Click(object sender, EventArgs e)
        {
            Main main = new Main();
            main.DeleteStudent(Main.SelectedStudentId);
            getData("select * from Data");
        }

        

        private void btShow_Click(object sender, EventArgs e)
        {
            getData("select * from Data");
            MessageBox.Show("Đã cập nhật dữ liệu!");
        }

        

        
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SortCompare
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btInsert_Click(object sender, EventArgs e)
        {
            Sort sort = new Sort();
            int[] A = sort.CreateArr();

            txtInsert_Time.Text = sort.InsertionSort(A).ToString();

            txtInsert_Res.Text = sort.ShowArr(A);
        }

      

        private void btMerge_Click(object sender, EventArgs e)
        {
            Sort sort = new Sort();
            int[] A = sort.CreateArr();

            sort.MergeSort(A, 0, A.Length -1);

            txtMerge_Res.Text = sort.ShowArr(A);
        }

        private void btNormal_Click(object sender, EventArgs e)
        {
            Sort sort = new Sort();
            int[] A = sort.CreateArr();

            txtNormal_Time.Text = sort.NormalSort(A).ToString();

            txtNormal_Res.Text = sort.ShowArr(A);
        }

        private void btSelection_Click(object sender, EventArgs e)
        {
            Sort sort = new Sort();
            int[] A = sort.CreateArr();

            txtSelection_Time.Text = sort.SelectionSort(A).ToString();

            txtSelection_Res.Text = sort.ShowArr(A);
        }

        
    }
}

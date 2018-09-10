namespace QLD
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button1 = new System.Windows.Forms.Button();
            this.AddButton = new System.Windows.Forms.Button();
            this.EditButton = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.hệThốngToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.càiĐặtToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ExitToolStripMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.giáoViênToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.TeacherInfo_ToolStripMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.SignOut_ToolStripMenu = new System.Windows.Forms.ToolStripMenuItem();
            this.khácToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dataGWMain = new System.Windows.Forms.DataGridView();
            this.MainFrm = new System.Windows.Forms.Label();
            this.btSearch = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGWMain)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(544, 46);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(83, 43);
            this.button1.TabIndex = 0;
            this.button1.Text = "CẬP NHẬT";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btShow_Click);
            // 
            // AddButton
            // 
            this.AddButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AddButton.Location = new System.Drawing.Point(633, 47);
            this.AddButton.Name = "AddButton";
            this.AddButton.Size = new System.Drawing.Size(85, 41);
            this.AddButton.TabIndex = 0;
            this.AddButton.Text = "THÊM";
            this.AddButton.UseVisualStyleBackColor = true;
            this.AddButton.Click += new System.EventHandler(this.AddButton_Click);
            // 
            // EditButton
            // 
            this.EditButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EditButton.Location = new System.Drawing.Point(724, 48);
            this.EditButton.Name = "EditButton";
            this.EditButton.Size = new System.Drawing.Size(77, 41);
            this.EditButton.TabIndex = 0;
            this.EditButton.Text = "SỬA";
            this.EditButton.UseVisualStyleBackColor = true;
            this.EditButton.Click += new System.EventHandler(this.EditButton_Click);
            // 
            // button4
            // 
            this.button4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button4.Location = new System.Drawing.Point(807, 48);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(86, 43);
            this.button4.TabIndex = 0;
            this.button4.Text = "XÓA";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.btDelete_Click);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.hệThốngToolStripMenuItem,
            this.giáoViênToolStripMenuItem,
            this.khácToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(926, 24);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // hệThốngToolStripMenuItem
            // 
            this.hệThốngToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.càiĐặtToolStripMenuItem,
            this.ExitToolStripMenu});
            this.hệThốngToolStripMenuItem.Name = "hệThốngToolStripMenuItem";
            this.hệThốngToolStripMenuItem.Size = new System.Drawing.Size(69, 20);
            this.hệThốngToolStripMenuItem.Text = "Hệ thống";
            // 
            // càiĐặtToolStripMenuItem
            // 
            this.càiĐặtToolStripMenuItem.Name = "càiĐặtToolStripMenuItem";
            this.càiĐặtToolStripMenuItem.Size = new System.Drawing.Size(111, 22);
            this.càiĐặtToolStripMenuItem.Text = "Cài đặt";
            // 
            // ExitToolStripMenu
            // 
            this.ExitToolStripMenu.Name = "ExitToolStripMenu";
            this.ExitToolStripMenu.Size = new System.Drawing.Size(111, 22);
            this.ExitToolStripMenu.Text = "Thoát";
            this.ExitToolStripMenu.Click += new System.EventHandler(this.ExitToolStripMenu_Click);
            // 
            // giáoViênToolStripMenuItem
            // 
            this.giáoViênToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.TeacherInfo_ToolStripMenu,
            this.SignOut_ToolStripMenu});
            this.giáoViênToolStripMenuItem.Name = "giáoViênToolStripMenuItem";
            this.giáoViênToolStripMenuItem.Size = new System.Drawing.Size(68, 20);
            this.giáoViênToolStripMenuItem.Text = "Giáo viên";
            // 
            // TeacherInfo_ToolStripMenu
            // 
            this.TeacherInfo_ToolStripMenu.Name = "TeacherInfo_ToolStripMenu";
            this.TeacherInfo_ToolStripMenu.Size = new System.Drawing.Size(127, 22);
            this.TeacherInfo_ToolStripMenu.Text = "Thông tin";
            this.TeacherInfo_ToolStripMenu.Click += new System.EventHandler(this.TeacherInfo_ToolStripMenu_Click);
            // 
            // SignOut_ToolStripMenu
            // 
            this.SignOut_ToolStripMenu.Name = "SignOut_ToolStripMenu";
            this.SignOut_ToolStripMenu.Size = new System.Drawing.Size(127, 22);
            this.SignOut_ToolStripMenu.Text = "Đăng xuất";
            // 
            // khácToolStripMenuItem
            // 
            this.khácToolStripMenuItem.Name = "khácToolStripMenuItem";
            this.khácToolStripMenuItem.Size = new System.Drawing.Size(45, 20);
            this.khácToolStripMenuItem.Text = "Khác";
            // 
            // dataGWMain
            // 
            this.dataGWMain.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGWMain.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGWMain.Location = new System.Drawing.Point(24, 127);
            this.dataGWMain.Name = "dataGWMain";
            this.dataGWMain.Size = new System.Drawing.Size(869, 316);
            this.dataGWMain.TabIndex = 4;
            this.dataGWMain.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGWMain_CellClick);
            // 
            // MainFrm
            // 
            this.MainFrm.AutoSize = true;
            this.MainFrm.Font = new System.Drawing.Font("Georgia", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MainFrm.ForeColor = System.Drawing.Color.Blue;
            this.MainFrm.Location = new System.Drawing.Point(27, 46);
            this.MainFrm.Name = "MainFrm";
            this.MainFrm.Size = new System.Drawing.Size(403, 41);
            this.MainFrm.TabIndex = 5;
            this.MainFrm.Text = "QUẢN LÝ SINH VIÊN";
            // 
            // btSearch
            // 
            this.btSearch.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btSearch.Location = new System.Drawing.Point(455, 46);
            this.btSearch.Name = "btSearch";
            this.btSearch.Size = new System.Drawing.Size(83, 43);
            this.btSearch.TabIndex = 6;
            this.btSearch.Text = "TÌM KIẾM";
            this.btSearch.UseVisualStyleBackColor = true;
            this.btSearch.Click += new System.EventHandler(this.btSearch_Click);
            // 
            // MainForm
            // 
            this.ClientSize = new System.Drawing.Size(926, 497);
            this.Controls.Add(this.btSearch);
            this.Controls.Add(this.MainFrm);
            this.Controls.Add(this.dataGWMain);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.EditButton);
            this.Controls.Add(this.AddButton);
            this.Controls.Add(this.button1);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGWMain)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button AddButton;
        private System.Windows.Forms.Button EditButton;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem hệThốngToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem giáoViênToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem TeacherInfo_ToolStripMenu;
        private System.Windows.Forms.ToolStripMenuItem khácToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SignOut_ToolStripMenu;
        private System.Windows.Forms.ToolStripMenuItem càiĐặtToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ExitToolStripMenu;
        private System.Windows.Forms.Label MainFrm;
        public System.Windows.Forms.DataGridView dataGWMain;
        private System.Windows.Forms.Button btSearch;
    }
}
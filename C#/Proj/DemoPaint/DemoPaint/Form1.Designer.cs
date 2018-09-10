namespace DemoPaint
{
    partial class Form1
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
            this.btDrawLine = new System.Windows.Forms.Button();
            this.btDrawRect = new System.Windows.Forms.Button();
            this.btDrawEllipse = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.propertiesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.undoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.redoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btFillEllipse = new System.Windows.Forms.Button();
            this.btFillRect = new System.Windows.Forms.Button();
            this.btChooseColor = new System.Windows.Forms.Button();
            this.btRightColor = new System.Windows.Forms.Button();
            this.btLeftColor = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cbSize = new System.Windows.Forms.ComboBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.lbCoor = new System.Windows.Forms.Label();
            this.resizeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btDrawLine
            // 
            this.btDrawLine.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.btDrawLine.FlatAppearance.BorderSize = 2;
            this.btDrawLine.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btDrawLine.Location = new System.Drawing.Point(3, 3);
            this.btDrawLine.Name = "btDrawLine";
            this.btDrawLine.Size = new System.Drawing.Size(98, 61);
            this.btDrawLine.TabIndex = 1;
            this.btDrawLine.Text = "Vẽ đoạn thẳng";
            this.btDrawLine.UseVisualStyleBackColor = true;
            this.btDrawLine.Click += new System.EventHandler(this.btDrawLine_Click);
            // 
            // btDrawRect
            // 
            this.btDrawRect.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.btDrawRect.FlatAppearance.BorderSize = 2;
            this.btDrawRect.Location = new System.Drawing.Point(107, 3);
            this.btDrawRect.Name = "btDrawRect";
            this.btDrawRect.Size = new System.Drawing.Size(98, 61);
            this.btDrawRect.TabIndex = 2;
            this.btDrawRect.Text = "Vẽ hình chữ nhật";
            this.btDrawRect.UseVisualStyleBackColor = true;
            this.btDrawRect.Click += new System.EventHandler(this.btDrawRect_Click);
            // 
            // btDrawEllipse
            // 
            this.btDrawEllipse.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.btDrawEllipse.FlatAppearance.BorderSize = 2;
            this.btDrawEllipse.Location = new System.Drawing.Point(211, 3);
            this.btDrawEllipse.Name = "btDrawEllipse";
            this.btDrawEllipse.Size = new System.Drawing.Size(98, 61);
            this.btDrawEllipse.TabIndex = 3;
            this.btDrawEllipse.Text = "Vẽ hình tròn";
            this.btDrawEllipse.UseVisualStyleBackColor = true;
            this.btDrawEllipse.Click += new System.EventHandler(this.btDrawEllipse_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.viewToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(915, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.propertiesToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // propertiesToolStripMenuItem
            // 
            this.propertiesToolStripMenuItem.Name = "propertiesToolStripMenuItem";
            this.propertiesToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.propertiesToolStripMenuItem.Text = "Prop&erties";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.exitToolStripMenuItem.Text = "E&xit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.undoToolStripMenuItem,
            this.redoToolStripMenuItem,
            this.resizeToolStripMenuItem});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "E&dit";
            // 
            // undoToolStripMenuItem
            // 
            this.undoToolStripMenuItem.Name = "undoToolStripMenuItem";
            this.undoToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.undoToolStripMenuItem.Text = "&Undo";
            // 
            // redoToolStripMenuItem
            // 
            this.redoToolStripMenuItem.Name = "redoToolStripMenuItem";
            this.redoToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.redoToolStripMenuItem.Text = "&Redo";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.viewToolStripMenuItem.Text = "&View";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Silver;
            this.panel1.Controls.Add(this.btFillEllipse);
            this.panel1.Controls.Add(this.btFillRect);
            this.panel1.Controls.Add(this.btChooseColor);
            this.panel1.Controls.Add(this.btRightColor);
            this.panel1.Controls.Add(this.btLeftColor);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.cbSize);
            this.panel1.Controls.Add(this.btDrawLine);
            this.panel1.Controls.Add(this.btDrawEllipse);
            this.panel1.Controls.Add(this.btDrawRect);
            this.panel1.Location = new System.Drawing.Point(0, 27);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(915, 67);
            this.panel1.TabIndex = 5;
            // 
            // btFillEllipse
            // 
            this.btFillEllipse.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.btFillEllipse.FlatAppearance.BorderSize = 2;
            this.btFillEllipse.Location = new System.Drawing.Point(419, 3);
            this.btFillEllipse.Name = "btFillEllipse";
            this.btFillEllipse.Size = new System.Drawing.Size(98, 61);
            this.btFillEllipse.TabIndex = 10;
            this.btFillEllipse.Text = "Tô hình tròn";
            this.btFillEllipse.UseVisualStyleBackColor = true;
            this.btFillEllipse.Click += new System.EventHandler(this.btFillEllipse_Click);
            // 
            // btFillRect
            // 
            this.btFillRect.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.btFillRect.FlatAppearance.BorderSize = 2;
            this.btFillRect.Location = new System.Drawing.Point(315, 3);
            this.btFillRect.Name = "btFillRect";
            this.btFillRect.Size = new System.Drawing.Size(98, 61);
            this.btFillRect.TabIndex = 9;
            this.btFillRect.Text = "Tô hình chữ nhật";
            this.btFillRect.UseVisualStyleBackColor = true;
            this.btFillRect.Click += new System.EventHandler(this.btFillRect_Click);
            // 
            // btChooseColor
            // 
            this.btChooseColor.Location = new System.Drawing.Point(798, 0);
            this.btChooseColor.Name = "btChooseColor";
            this.btChooseColor.Size = new System.Drawing.Size(89, 61);
            this.btChooseColor.TabIndex = 8;
            this.btChooseColor.Text = "Chọn màu";
            this.btChooseColor.UseVisualStyleBackColor = true;
            this.btChooseColor.Click += new System.EventHandler(this.btChooseColor_Click);
            // 
            // btRightColor
            // 
            this.btRightColor.BackColor = System.Drawing.Color.White;
            this.btRightColor.Cursor = System.Windows.Forms.Cursors.Default;
            this.btRightColor.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.btRightColor.FlatAppearance.BorderSize = 2;
            this.btRightColor.Location = new System.Drawing.Point(745, 0);
            this.btRightColor.Name = "btRightColor";
            this.btRightColor.Size = new System.Drawing.Size(47, 61);
            this.btRightColor.TabIndex = 7;
            this.btRightColor.UseVisualStyleBackColor = false;
            this.btRightColor.Click += new System.EventHandler(this.btRightColor_Click);
            // 
            // btLeftColor
            // 
            this.btLeftColor.BackColor = System.Drawing.Color.Black;
            this.btLeftColor.FlatAppearance.BorderColor = System.Drawing.Color.CornflowerBlue;
            this.btLeftColor.FlatAppearance.BorderSize = 2;
            this.btLeftColor.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btLeftColor.Location = new System.Drawing.Point(692, 0);
            this.btLeftColor.Name = "btLeftColor";
            this.btLeftColor.Size = new System.Drawing.Size(47, 61);
            this.btLeftColor.TabIndex = 6;
            this.btLeftColor.UseVisualStyleBackColor = false;
            this.btLeftColor.Click += new System.EventHandler(this.btLeftColor_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(523, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Size";
            // 
            // cbSize
            // 
            this.cbSize.FormattingEnabled = true;
            this.cbSize.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "7",
            "10",
            "15",
            "20",
            "30"});
            this.cbSize.Location = new System.Drawing.Point(556, 24);
            this.cbSize.Name = "cbSize";
            this.cbSize.Size = new System.Drawing.Size(121, 21);
            this.cbSize.TabIndex = 4;
            this.cbSize.SelectedIndexChanged += new System.EventHandler(this.cbSize_SelectedIndexChanged);
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.LightGray;
            this.panel2.Controls.Add(this.lbCoor);
            this.panel2.Location = new System.Drawing.Point(0, 537);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(923, 21);
            this.panel2.TabIndex = 6;
            // 
            // lbCoor
            // 
            this.lbCoor.AutoSize = true;
            this.lbCoor.Location = new System.Drawing.Point(13, 5);
            this.lbCoor.Name = "lbCoor";
            this.lbCoor.Size = new System.Drawing.Size(0, 13);
            this.lbCoor.TabIndex = 0;
            // 
            // resizeToolStripMenuItem
            // 
            this.resizeToolStripMenuItem.Name = "resizeToolStripMenuItem";
            this.resizeToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.resizeToolStripMenuItem.Text = "Res&ize";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(915, 557);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "United - My Paint";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btDrawLine;
        private System.Windows.Forms.Button btDrawRect;
        private System.Windows.Forms.Button btDrawEllipse;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem propertiesToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem undoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem redoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbSize;
        private System.Windows.Forms.Button btRightColor;
        private System.Windows.Forms.Button btChooseColor;
        private System.Windows.Forms.Button btLeftColor;
        private System.Windows.Forms.Button btFillEllipse;
        private System.Windows.Forms.Button btFillRect;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label lbCoor;
        private System.Windows.Forms.ToolStripMenuItem resizeToolStripMenuItem;
    }
}


namespace SortCompare
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
            this.btInsert = new System.Windows.Forms.Button();
            this.txtInsert_Res = new System.Windows.Forms.TextBox();
            this.txtInsert_Time = new System.Windows.Forms.TextBox();
            this.txtMerge_Res = new System.Windows.Forms.TextBox();
            this.txtMerge_Time = new System.Windows.Forms.TextBox();
            this.txtNormal_Time = new System.Windows.Forms.TextBox();
            this.txtNormal_Res = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtSelection_Time = new System.Windows.Forms.TextBox();
            this.txtSelection_Res = new System.Windows.Forms.TextBox();
            this.btSelection = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btInsert
            // 
            this.btInsert.Location = new System.Drawing.Point(151, 65);
            this.btInsert.Name = "btInsert";
            this.btInsert.Size = new System.Drawing.Size(75, 23);
            this.btInsert.TabIndex = 0;
            this.btInsert.Text = "Insert Sort";
            this.btInsert.UseVisualStyleBackColor = true;
            this.btInsert.Click += new System.EventHandler(this.btInsert_Click);
            // 
            // txtInsert_Res
            // 
            this.txtInsert_Res.Enabled = false;
            this.txtInsert_Res.Location = new System.Drawing.Point(151, 110);
            this.txtInsert_Res.Name = "txtInsert_Res";
            this.txtInsert_Res.Size = new System.Drawing.Size(180, 20);
            this.txtInsert_Res.TabIndex = 1;
            // 
            // txtInsert_Time
            // 
            this.txtInsert_Time.Enabled = false;
            this.txtInsert_Time.Location = new System.Drawing.Point(151, 136);
            this.txtInsert_Time.Name = "txtInsert_Time";
            this.txtInsert_Time.Size = new System.Drawing.Size(180, 20);
            this.txtInsert_Time.TabIndex = 1;
            // 
            // txtMerge_Res
            // 
            this.txtMerge_Res.Enabled = false;
            this.txtMerge_Res.Location = new System.Drawing.Point(406, 110);
            this.txtMerge_Res.Name = "txtMerge_Res";
            this.txtMerge_Res.Size = new System.Drawing.Size(180, 20);
            this.txtMerge_Res.TabIndex = 1;
            // 
            // txtMerge_Time
            // 
            this.txtMerge_Time.Enabled = false;
            this.txtMerge_Time.Location = new System.Drawing.Point(406, 136);
            this.txtMerge_Time.Name = "txtMerge_Time";
            this.txtMerge_Time.Size = new System.Drawing.Size(180, 20);
            this.txtMerge_Time.TabIndex = 1;
            // 
            // txtNormal_Time
            // 
            this.txtNormal_Time.Enabled = false;
            this.txtNormal_Time.Location = new System.Drawing.Point(653, 136);
            this.txtNormal_Time.Name = "txtNormal_Time";
            this.txtNormal_Time.Size = new System.Drawing.Size(180, 20);
            this.txtNormal_Time.TabIndex = 1;
            // 
            // txtNormal_Res
            // 
            this.txtNormal_Res.Enabled = false;
            this.txtNormal_Res.Location = new System.Drawing.Point(653, 110);
            this.txtNormal_Res.Name = "txtNormal_Res";
            this.txtNormal_Res.Size = new System.Drawing.Size(180, 20);
            this.txtNormal_Res.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(406, 65);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Merge Sort";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btMerge_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(653, 65);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 4;
            this.button2.Text = "Normal Sort";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.btNormal_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(31, 113);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Result";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(31, 139);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Time";
            // 
            // txtSelection_Time
            // 
            this.txtSelection_Time.Enabled = false;
            this.txtSelection_Time.Location = new System.Drawing.Point(151, 296);
            this.txtSelection_Time.Name = "txtSelection_Time";
            this.txtSelection_Time.Size = new System.Drawing.Size(180, 20);
            this.txtSelection_Time.TabIndex = 8;
            // 
            // txtSelection_Res
            // 
            this.txtSelection_Res.Enabled = false;
            this.txtSelection_Res.Location = new System.Drawing.Point(151, 270);
            this.txtSelection_Res.Name = "txtSelection_Res";
            this.txtSelection_Res.Size = new System.Drawing.Size(180, 20);
            this.txtSelection_Res.TabIndex = 7;
            // 
            // btSelection
            // 
            this.btSelection.Location = new System.Drawing.Point(151, 225);
            this.btSelection.Name = "btSelection";
            this.btSelection.Size = new System.Drawing.Size(75, 23);
            this.btSelection.TabIndex = 6;
            this.btSelection.Text = "Selection Sort";
            this.btSelection.UseVisualStyleBackColor = true;
            this.btSelection.Click += new System.EventHandler(this.btSelection_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(863, 439);
            this.Controls.Add(this.txtSelection_Time);
            this.Controls.Add(this.txtSelection_Res);
            this.Controls.Add(this.btSelection);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txtNormal_Res);
            this.Controls.Add(this.txtMerge_Time);
            this.Controls.Add(this.txtNormal_Time);
            this.Controls.Add(this.txtInsert_Time);
            this.Controls.Add(this.txtMerge_Res);
            this.Controls.Add(this.txtInsert_Res);
            this.Controls.Add(this.btInsert);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btInsert;
        private System.Windows.Forms.TextBox txtInsert_Res;
        private System.Windows.Forms.TextBox txtInsert_Time;
        private System.Windows.Forms.TextBox txtMerge_Res;
        private System.Windows.Forms.TextBox txtMerge_Time;
        private System.Windows.Forms.TextBox txtNormal_Time;
        private System.Windows.Forms.TextBox txtNormal_Res;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtSelection_Time;
        private System.Windows.Forms.TextBox txtSelection_Res;
        private System.Windows.Forms.Button btSelection;
    }
}


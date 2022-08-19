namespace MJ
{
    partial class MainWindow
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.mainLayout = new System.Windows.Forms.TableLayoutPanel();
            this.groupBoxTop = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.button_unpack_run = new System.Windows.Forms.Button();
            this.button_unpack_dst = new System.Windows.Forms.Button();
            this.button_unpack_src = new System.Windows.Forms.Button();
            this.textBox_unpack_dst = new System.Windows.Forms.TextBox();
            this.textBox_unpack_src = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBoxExtract = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.checkBox_report = new System.Windows.Forms.CheckBox();
            this.checkBox_extract = new System.Windows.Forms.CheckBox();
            this.button_extract_run = new System.Windows.Forms.Button();
            this.button_extract_out = new System.Windows.Forms.Button();
            this.button_extract_update = new System.Windows.Forms.Button();
            this.button_extract_pre = new System.Windows.Forms.Button();
            this.textBox_extract_update = new System.Windows.Forms.TextBox();
            this.textBox_extract_out = new System.Windows.Forms.TextBox();
            this.textBox_extract_pre = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.mainLayout.SuspendLayout();
            this.groupBoxTop.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.groupBoxExtract.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainLayout
            // 
            this.mainLayout.ColumnCount = 1;
            this.mainLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.mainLayout.Controls.Add(this.groupBoxTop, 0, 0);
            this.mainLayout.Controls.Add(this.groupBoxExtract, 0, 1);
            this.mainLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainLayout.Location = new System.Drawing.Point(0, 0);
            this.mainLayout.Name = "mainLayout";
            this.mainLayout.RowCount = 2;
            this.mainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 37.5F));
            this.mainLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 62.5F));
            this.mainLayout.Size = new System.Drawing.Size(433, 333);
            this.mainLayout.TabIndex = 0;
            // 
            // groupBoxTop
            // 
            this.groupBoxTop.AutoSize = true;
            this.groupBoxTop.Controls.Add(this.tableLayoutPanel2);
            this.groupBoxTop.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBoxTop.Location = new System.Drawing.Point(3, 3);
            this.groupBoxTop.Name = "groupBoxTop";
            this.groupBoxTop.Size = new System.Drawing.Size(427, 117);
            this.groupBoxTop.TabIndex = 4;
            this.groupBoxTop.TabStop = false;
            this.groupBoxTop.Text = "Unpack Folder";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.AutoSize = true;
            this.tableLayoutPanel2.ColumnCount = 3;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 22.84264F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 61.04061F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.11675F));
            this.tableLayoutPanel2.Controls.Add(this.button_unpack_run, 2, 2);
            this.tableLayoutPanel2.Controls.Add(this.button_unpack_dst, 2, 1);
            this.tableLayoutPanel2.Controls.Add(this.button_unpack_src, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.textBox_unpack_dst, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.textBox_unpack_src, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.label2, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 21);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 3;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(421, 93);
            this.tableLayoutPanel2.TabIndex = 2;
            // 
            // button_unpack_run
            // 
            this.button_unpack_run.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button_unpack_run.Location = new System.Drawing.Point(355, 65);
            this.button_unpack_run.Name = "button_unpack_run";
            this.button_unpack_run.Size = new System.Drawing.Size(63, 25);
            this.button_unpack_run.TabIndex = 7;
            this.button_unpack_run.Text = "Run";
            this.button_unpack_run.UseVisualStyleBackColor = true;
            this.button_unpack_run.Click += new System.EventHandler(this.button_unpack_run_Click);
            // 
            // button_unpack_dst
            // 
            this.button_unpack_dst.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button_unpack_dst.Location = new System.Drawing.Point(355, 34);
            this.button_unpack_dst.Name = "button_unpack_dst";
            this.button_unpack_dst.Size = new System.Drawing.Size(63, 25);
            this.button_unpack_dst.TabIndex = 6;
            this.button_unpack_dst.Text = "Open";
            this.button_unpack_dst.UseVisualStyleBackColor = true;
            this.button_unpack_dst.Click += new System.EventHandler(this.button_unpack_dst_Click);
            // 
            // button_unpack_src
            // 
            this.button_unpack_src.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button_unpack_src.Location = new System.Drawing.Point(355, 3);
            this.button_unpack_src.Name = "button_unpack_src";
            this.button_unpack_src.Size = new System.Drawing.Size(63, 25);
            this.button_unpack_src.TabIndex = 5;
            this.button_unpack_src.Text = "Open";
            this.button_unpack_src.UseVisualStyleBackColor = true;
            this.button_unpack_src.Click += new System.EventHandler(this.button_unpack_src_Click);
            // 
            // textBox_unpack_dst
            // 
            this.textBox_unpack_dst.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox_unpack_dst.Location = new System.Drawing.Point(99, 34);
            this.textBox_unpack_dst.Name = "textBox_unpack_dst";
            this.textBox_unpack_dst.Size = new System.Drawing.Size(250, 25);
            this.textBox_unpack_dst.TabIndex = 4;
            // 
            // textBox_unpack_src
            // 
            this.textBox_unpack_src.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox_unpack_src.Location = new System.Drawing.Point(99, 3);
            this.textBox_unpack_src.Name = "textBox_unpack_src";
            this.textBox_unpack_src.Size = new System.Drawing.Size(250, 25);
            this.textBox_unpack_src.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(3, 34);
            this.label2.Margin = new System.Windows.Forms.Padding(3);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(90, 25);
            this.label2.TabIndex = 2;
            this.label2.Text = "Destination";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Location = new System.Drawing.Point(3, 3);
            this.label1.Margin = new System.Windows.Forms.Padding(3);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 25);
            this.label1.TabIndex = 1;
            this.label1.Text = "Source Folder";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // groupBoxExtract
            // 
            this.groupBoxExtract.AutoSize = true;
            this.groupBoxExtract.Controls.Add(this.tableLayoutPanel1);
            this.groupBoxExtract.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBoxExtract.Location = new System.Drawing.Point(3, 127);
            this.groupBoxExtract.Name = "groupBoxExtract";
            this.groupBoxExtract.Size = new System.Drawing.Size(427, 194);
            this.groupBoxExtract.TabIndex = 3;
            this.groupBoxExtract.TabStop = false;
            this.groupBoxExtract.Text = "Extract";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.ColumnCount = 3;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 22.84264F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 61.04061F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 16.11675F));
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel4, 1, 7);
            this.tableLayoutPanel1.Controls.Add(this.button_extract_run, 2, 7);
            this.tableLayoutPanel1.Controls.Add(this.button_extract_out, 2, 5);
            this.tableLayoutPanel1.Controls.Add(this.button_extract_update, 2, 3);
            this.tableLayoutPanel1.Controls.Add(this.button_extract_pre, 2, 2);
            this.tableLayoutPanel1.Controls.Add(this.textBox_extract_update, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.textBox_extract_out, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.textBox_extract_pre, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.label6, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.label5, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.label4, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.label3, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 21);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 8;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 5F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(421, 170);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.AutoSize = true;
            this.tableLayoutPanel4.ColumnCount = 2;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Controls.Add(this.checkBox_report, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.checkBox_extract, 1, 0);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Right;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(170, 142);
            this.tableLayoutPanel4.Margin = new System.Windows.Forms.Padding(3, 3, 10, 3);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 1;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(172, 25);
            this.tableLayoutPanel4.TabIndex = 14;
            // 
            // checkBox_report
            // 
            this.checkBox_report.AutoSize = true;
            this.checkBox_report.Location = new System.Drawing.Point(6, 3);
            this.checkBox_report.Margin = new System.Windows.Forms.Padding(6, 3, 6, 3);
            this.checkBox_report.Name = "checkBox_report";
            this.checkBox_report.Size = new System.Drawing.Size(66, 19);
            this.checkBox_report.TabIndex = 0;
            this.checkBox_report.Text = "report";
            this.checkBox_report.UseVisualStyleBackColor = true;
            // 
            // checkBox_extract
            // 
            this.checkBox_extract.AutoSize = true;
            this.checkBox_extract.Location = new System.Drawing.Point(92, 3);
            this.checkBox_extract.Margin = new System.Windows.Forms.Padding(6, 3, 6, 3);
            this.checkBox_extract.Name = "checkBox_extract";
            this.checkBox_extract.Size = new System.Drawing.Size(74, 19);
            this.checkBox_extract.TabIndex = 1;
            this.checkBox_extract.Text = "extract";
            this.checkBox_extract.UseVisualStyleBackColor = true;
            // 
            // button_extract_run
            // 
            this.button_extract_run.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button_extract_run.Location = new System.Drawing.Point(355, 142);
            this.button_extract_run.Name = "button_extract_run";
            this.button_extract_run.Size = new System.Drawing.Size(63, 25);
            this.button_extract_run.TabIndex = 13;
            this.button_extract_run.Text = "Run";
            this.button_extract_run.UseVisualStyleBackColor = true;
            this.button_extract_run.Click += new System.EventHandler(this.button_extract_run_Click);
            // 
            // button_extract_out
            // 
            this.button_extract_out.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button_extract_out.Location = new System.Drawing.Point(355, 106);
            this.button_extract_out.Name = "button_extract_out";
            this.button_extract_out.Size = new System.Drawing.Size(63, 25);
            this.button_extract_out.TabIndex = 12;
            this.button_extract_out.Text = "Open";
            this.button_extract_out.UseVisualStyleBackColor = true;
            this.button_extract_out.Click += new System.EventHandler(this.button_extract_out_Click);
            // 
            // button_extract_update
            // 
            this.button_extract_update.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button_extract_update.Location = new System.Drawing.Point(355, 70);
            this.button_extract_update.Name = "button_extract_update";
            this.button_extract_update.Size = new System.Drawing.Size(63, 25);
            this.button_extract_update.TabIndex = 11;
            this.button_extract_update.Text = "Open";
            this.button_extract_update.UseVisualStyleBackColor = true;
            this.button_extract_update.Click += new System.EventHandler(this.button_extract_update_Click);
            // 
            // button_extract_pre
            // 
            this.button_extract_pre.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button_extract_pre.Location = new System.Drawing.Point(355, 39);
            this.button_extract_pre.Name = "button_extract_pre";
            this.button_extract_pre.Size = new System.Drawing.Size(63, 25);
            this.button_extract_pre.TabIndex = 10;
            this.button_extract_pre.Text = "Open";
            this.button_extract_pre.UseVisualStyleBackColor = true;
            this.button_extract_pre.Click += new System.EventHandler(this.button_extract_pre_Click);
            // 
            // textBox_extract_update
            // 
            this.textBox_extract_update.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox_extract_update.Location = new System.Drawing.Point(99, 70);
            this.textBox_extract_update.Name = "textBox_extract_update";
            this.textBox_extract_update.Size = new System.Drawing.Size(250, 25);
            this.textBox_extract_update.TabIndex = 8;
            // 
            // textBox_extract_out
            // 
            this.textBox_extract_out.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox_extract_out.Location = new System.Drawing.Point(99, 106);
            this.textBox_extract_out.Name = "textBox_extract_out";
            this.textBox_extract_out.Size = new System.Drawing.Size(250, 25);
            this.textBox_extract_out.TabIndex = 7;
            // 
            // textBox_extract_pre
            // 
            this.textBox_extract_pre.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textBox_extract_pre.Location = new System.Drawing.Point(99, 39);
            this.textBox_extract_pre.Name = "textBox_extract_pre";
            this.textBox_extract_pre.Size = new System.Drawing.Size(250, 25);
            this.textBox_extract_pre.TabIndex = 6;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label6.Location = new System.Drawing.Point(3, 70);
            this.label6.Margin = new System.Windows.Forms.Padding(3);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(90, 25);
            this.label6.TabIndex = 5;
            this.label6.Text = "update data";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label5.Location = new System.Drawing.Point(3, 106);
            this.label5.Margin = new System.Windows.Forms.Padding(3);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(90, 25);
            this.label5.TabIndex = 4;
            this.label5.Text = "outputs";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label4.Location = new System.Drawing.Point(3, 39);
            this.label4.Margin = new System.Windows.Forms.Padding(3);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(90, 25);
            this.label4.TabIndex = 3;
            this.label4.Text = "pre data";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label3.Location = new System.Drawing.Point(3, 3);
            this.label3.Margin = new System.Windows.Forms.Padding(3);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(90, 25);
            this.label3.TabIndex = 2;
            this.label3.Text = "data type";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.AutoSize = true;
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.comboBox2, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.comboBox1, 0, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Left;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(96, 0);
            this.tableLayoutPanel3.Margin = new System.Windows.Forms.Padding(0);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(254, 31);
            this.tableLayoutPanel3.TabIndex = 9;
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Location = new System.Drawing.Point(130, 3);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 23);
            this.comboBox2.TabIndex = 1;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(3, 3);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 23);
            this.comboBox1.TabIndex = 0;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.WorkerReportsProgress = true;
            this.backgroundWorker1.WorkerSupportsCancellation = true;
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            this.backgroundWorker1.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker1_ProgressChanged);
            this.backgroundWorker1.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorker1_RunWorkerCompleted);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(433, 333);
            this.Controls.Add(this.mainLayout);
            this.MinimumSize = new System.Drawing.Size(450, 47);
            this.Name = "MainWindow";
            this.Text = "Window";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.mainLayout.ResumeLayout(false);
            this.mainLayout.PerformLayout();
            this.groupBoxTop.ResumeLayout(false);
            this.groupBoxTop.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.groupBoxExtract.ResumeLayout(false);
            this.groupBoxExtract.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel mainLayout;
        private System.Windows.Forms.GroupBox groupBoxTop;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button button_unpack_run;
        private System.Windows.Forms.Button button_unpack_dst;
        private System.Windows.Forms.Button button_unpack_src;
        private System.Windows.Forms.TextBox textBox_unpack_dst;
        private System.Windows.Forms.TextBox textBox_unpack_src;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBoxExtract;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.CheckBox checkBox_report;
        private System.Windows.Forms.CheckBox checkBox_extract;
        private System.Windows.Forms.Button button_extract_run;
        private System.Windows.Forms.Button button_extract_out;
        private System.Windows.Forms.Button button_extract_update;
        private System.Windows.Forms.Button button_extract_pre;
        private System.Windows.Forms.TextBox textBox_extract_update;
        private System.Windows.Forms.TextBox textBox_extract_out;
        private System.Windows.Forms.TextBox textBox_extract_pre;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}


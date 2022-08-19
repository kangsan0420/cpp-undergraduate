namespace InputShaperCoder
{
	partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.buttonExcute = new System.Windows.Forms.Button();
            this.textZeta = new System.Windows.Forms.TextBox();
            this.textWn = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textM = new System.Windows.Forms.TextBox();
            this.textC = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textK = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.radioStandard = new System.Windows.Forms.RadioButton();
            this.radioMCK = new System.Windows.Forms.RadioButton();
            this.textTd = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.textXtotal = new System.Windows.Forms.TextBox();
            this.textVmax = new System.Windows.Forms.TextBox();
            this.textTA = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.textSysM = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.textSysC = new System.Windows.Forms.TextBox();
            this.textSysK = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.radioZVDD = new System.Windows.Forms.RadioButton();
            this.radioZVD = new System.Windows.Forms.RadioButton();
            this.radioZV = new System.Windows.Forms.RadioButton();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.buttonSave = new System.Windows.Forms.Button();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.textDwell = new System.Windows.Forms.TextBox();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.label20 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.groupBox2.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonExcute
            // 
            this.buttonExcute.Location = new System.Drawing.Point(5, 50);
            this.buttonExcute.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonExcute.Name = "buttonExcute";
            this.buttonExcute.Size = new System.Drawing.Size(203, 29);
            this.buttonExcute.TabIndex = 1;
            this.buttonExcute.Text = "Copy to Clipboard";
            this.buttonExcute.UseVisualStyleBackColor = true;
            this.buttonExcute.Click += new System.EventHandler(this.buttonExcute_Click);
            // 
            // textZeta
            // 
            this.textZeta.Location = new System.Drawing.Point(49, 39);
            this.textZeta.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textZeta.MaxLength = 9;
            this.textZeta.Name = "textZeta";
            this.textZeta.Size = new System.Drawing.Size(80, 25);
            this.textZeta.TabIndex = 2;
            this.textZeta.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textWn
            // 
            this.textWn.Location = new System.Drawing.Point(49, 66);
            this.textWn.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textWn.MaxLength = 9;
            this.textWn.Name = "textWn";
            this.textWn.Size = new System.Drawing.Size(80, 25);
            this.textWn.TabIndex = 2;
            this.textWn.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textWn.Enter += new System.EventHandler(this.textWn_Enter);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.SystemColors.ButtonFace;
            this.label1.Location = new System.Drawing.Point(27, 43);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 15);
            this.label1.TabIndex = 3;
            this.label1.Text = "ξ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(21, 69);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(26, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "ωn";
            // 
            // textM
            // 
            this.textM.Location = new System.Drawing.Point(33, 28);
            this.textM.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textM.Name = "textM";
            this.textM.Size = new System.Drawing.Size(80, 25);
            this.textM.TabIndex = 2;
            // 
            // textC
            // 
            this.textC.Location = new System.Drawing.Point(33, 57);
            this.textC.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textC.Name = "textC";
            this.textC.Size = new System.Drawing.Size(80, 25);
            this.textC.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(18, 15);
            this.label3.TabIndex = 3;
            this.label3.Text = "m";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(15, 15);
            this.label4.TabIndex = 3;
            this.label4.Text = "c";
            // 
            // textK
            // 
            this.textK.Location = new System.Drawing.Point(33, 84);
            this.textK.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textK.Name = "textK";
            this.textK.Size = new System.Drawing.Size(80, 25);
            this.textK.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 87);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(14, 15);
            this.label5.TabIndex = 3;
            this.label5.Text = "k";
            // 
            // radioStandard
            // 
            this.radioStandard.AutoSize = true;
            this.radioStandard.Location = new System.Drawing.Point(27, 14);
            this.radioStandard.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radioStandard.Name = "radioStandard";
            this.radioStandard.Size = new System.Drawing.Size(86, 19);
            this.radioStandard.TabIndex = 0;
            this.radioStandard.Text = "Standard";
            this.radioStandard.UseVisualStyleBackColor = true;
            // 
            // radioMCK
            // 
            this.radioMCK.AutoSize = true;
            this.radioMCK.Location = new System.Drawing.Point(27, 136);
            this.radioMCK.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radioMCK.Name = "radioMCK";
            this.radioMCK.Size = new System.Drawing.Size(54, 19);
            this.radioMCK.TabIndex = 0;
            this.radioMCK.Text = "mck";
            this.radioMCK.UseVisualStyleBackColor = true;
            // 
            // textTd
            // 
            this.textTd.Location = new System.Drawing.Point(49, 95);
            this.textTd.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textTd.MaxLength = 9;
            this.textTd.Name = "textTd";
            this.textTd.Size = new System.Drawing.Size(80, 25);
            this.textTd.TabIndex = 2;
            this.textTd.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.textTd.Enter += new System.EventHandler(this.textTd_Enter);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(21, 98);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(23, 15);
            this.label6.TabIndex = 3;
            this.label6.Text = "Td";
            // 
            // textXtotal
            // 
            this.textXtotal.Location = new System.Drawing.Point(67, 39);
            this.textXtotal.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textXtotal.MaxLength = 9;
            this.textXtotal.Name = "textXtotal";
            this.textXtotal.Size = new System.Drawing.Size(80, 25);
            this.textXtotal.TabIndex = 2;
            this.textXtotal.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textVmax
            // 
            this.textVmax.Location = new System.Drawing.Point(67, 66);
            this.textVmax.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textVmax.MaxLength = 9;
            this.textVmax.Name = "textVmax";
            this.textVmax.Size = new System.Drawing.Size(80, 25);
            this.textVmax.TabIndex = 2;
            this.textVmax.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textTA
            // 
            this.textTA.Location = new System.Drawing.Point(67, 95);
            this.textTA.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textTA.MaxLength = 9;
            this.textTA.Name = "textTA";
            this.textTA.Size = new System.Drawing.Size(80, 25);
            this.textTA.TabIndex = 2;
            this.textTA.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(19, 42);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 15);
            this.label7.TabIndex = 3;
            this.label7.Text = "Xtotal";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(19, 69);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(43, 15);
            this.label8.TabIndex = 3;
            this.label8.Text = "Vmax";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(31, 98);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(24, 15);
            this.label9.TabIndex = 3;
            this.label9.Text = "TA";
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(16, 12);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Size = new System.Drawing.Size(124, 118);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.groupBox5);
            this.groupBox2.Controls.Add(this.textM);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.textC);
            this.groupBox2.Controls.Add(this.textK);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new System.Drawing.Point(16, 134);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Size = new System.Drawing.Size(124, 118);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.textSysM);
            this.groupBox5.Controls.Add(this.label13);
            this.groupBox5.Controls.Add(this.textSysC);
            this.groupBox5.Controls.Add(this.textSysK);
            this.groupBox5.Controls.Add(this.label14);
            this.groupBox5.Controls.Add(this.label15);
            this.groupBox5.Location = new System.Drawing.Point(0, 0);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox5.Size = new System.Drawing.Size(124, 119);
            this.groupBox5.TabIndex = 4;
            this.groupBox5.TabStop = false;
            // 
            // textSysM
            // 
            this.textSysM.Location = new System.Drawing.Point(33, 28);
            this.textSysM.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textSysM.MaxLength = 9;
            this.textSysM.Name = "textSysM";
            this.textSysM.Size = new System.Drawing.Size(80, 25);
            this.textSysM.TabIndex = 2;
            this.textSysM.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(12, 87);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(14, 15);
            this.label13.TabIndex = 3;
            this.label13.Text = "k";
            // 
            // textSysC
            // 
            this.textSysC.Location = new System.Drawing.Point(33, 57);
            this.textSysC.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textSysC.MaxLength = 9;
            this.textSysC.Name = "textSysC";
            this.textSysC.Size = new System.Drawing.Size(80, 25);
            this.textSysC.TabIndex = 2;
            this.textSysC.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textSysK
            // 
            this.textSysK.Location = new System.Drawing.Point(33, 84);
            this.textSysK.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textSysK.MaxLength = 9;
            this.textSysK.Name = "textSysK";
            this.textSysK.Size = new System.Drawing.Size(80, 25);
            this.textSysK.TabIndex = 2;
            this.textSysK.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(12, 59);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(15, 15);
            this.label14.TabIndex = 3;
            this.label14.Text = "c";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(11, 30);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(18, 15);
            this.label15.TabIndex = 3;
            this.label15.Text = "m";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox4);
            this.groupBox3.Location = new System.Drawing.Point(11, 0);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Size = new System.Drawing.Size(137, 272);
            this.groupBox3.TabIndex = 4;
            this.groupBox3.TabStop = false;
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBox1);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.textBox2);
            this.groupBox4.Controls.Add(this.textBox3);
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.label12);
            this.groupBox4.Location = new System.Drawing.Point(5, 134);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Size = new System.Drawing.Size(124, 118);
            this.groupBox4.TabIndex = 4;
            this.groupBox4.TabStop = false;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(33, 28);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(80, 25);
            this.textBox1.TabIndex = 2;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 87);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(14, 15);
            this.label10.TabIndex = 3;
            this.label10.Text = "k";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(33, 57);
            this.textBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(80, 25);
            this.textBox2.TabIndex = 2;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(33, 84);
            this.textBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(80, 25);
            this.textBox3.TabIndex = 2;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(12, 59);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(15, 15);
            this.label11.TabIndex = 3;
            this.label11.Text = "c";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(11, 30);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(18, 15);
            this.label12.TabIndex = 3;
            this.label12.Text = "m";
            // 
            // radioZVDD
            // 
            this.radioZVDD.AutoSize = true;
            this.radioZVDD.Location = new System.Drawing.Point(135, 20);
            this.radioZVDD.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radioZVDD.Name = "radioZVDD";
            this.radioZVDD.Size = new System.Drawing.Size(65, 19);
            this.radioZVDD.TabIndex = 0;
            this.radioZVDD.TabStop = true;
            this.radioZVDD.Text = "ZVDD";
            this.radioZVDD.UseVisualStyleBackColor = true;
            // 
            // radioZVD
            // 
            this.radioZVD.AutoSize = true;
            this.radioZVD.Location = new System.Drawing.Point(67, 20);
            this.radioZVD.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radioZVD.Name = "radioZVD";
            this.radioZVD.Size = new System.Drawing.Size(55, 19);
            this.radioZVD.TabIndex = 0;
            this.radioZVD.TabStop = true;
            this.radioZVD.Text = "ZVD";
            this.radioZVD.UseVisualStyleBackColor = true;
            // 
            // radioZV
            // 
            this.radioZV.AutoSize = true;
            this.radioZV.Location = new System.Drawing.Point(5, 20);
            this.radioZV.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.radioZV.Name = "radioZV";
            this.radioZV.Size = new System.Drawing.Size(45, 19);
            this.radioZV.TabIndex = 0;
            this.radioZV.TabStop = true;
            this.radioZV.Text = "ZV";
            this.radioZV.UseVisualStyleBackColor = true;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.radioZVDD);
            this.groupBox6.Controls.Add(this.radioZVD);
            this.groupBox6.Controls.Add(this.radioZV);
            this.groupBox6.Controls.Add(this.buttonSave);
            this.groupBox6.Controls.Add(this.buttonExcute);
            this.groupBox6.Location = new System.Drawing.Point(161, 153);
            this.groupBox6.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox6.Size = new System.Drawing.Size(213, 119);
            this.groupBox6.TabIndex = 5;
            this.groupBox6.TabStop = false;
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(5, 82);
            this.buttonSave.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(203, 29);
            this.buttonSave.TabIndex = 1;
            this.buttonSave.Text = "Save As .txt";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label18);
            this.groupBox7.Controls.Add(this.label9);
            this.groupBox7.Controls.Add(this.label8);
            this.groupBox7.Controls.Add(this.label16);
            this.groupBox7.Controls.Add(this.label7);
            this.groupBox7.Controls.Add(this.textDwell);
            this.groupBox7.Controls.Add(this.textTA);
            this.groupBox7.Controls.Add(this.textVmax);
            this.groupBox7.Controls.Add(this.textXtotal);
            this.groupBox7.Location = new System.Drawing.Point(213, 0);
            this.groupBox7.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Padding = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.groupBox7.Size = new System.Drawing.Size(161, 156);
            this.groupBox7.TabIndex = 6;
            this.groupBox7.TabStop = false;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(15, 126);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(41, 15);
            this.label18.TabIndex = 3;
            this.label18.Text = "Dwell";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(15, 14);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(78, 15);
            this.label16.TabIndex = 3;
            this.label16.Text = "parameters";
            // 
            // textDwell
            // 
            this.textDwell.Location = new System.Drawing.Point(67, 122);
            this.textDwell.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textDwell.MaxLength = 9;
            this.textDwell.Name = "textDwell";
            this.textDwell.Size = new System.Drawing.Size(80, 25);
            this.textDwell.TabIndex = 2;
            this.textDwell.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileName = "pvtShaper.txt";
            this.saveFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            this.saveFileDialog1.InitialDirectory = "\"C://\"";
            this.saveFileDialog1.RestoreDirectory = true;
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(156, 91);
            this.label20.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(58, 15);
            this.label20.TabIndex = 7;
            this.label20.Text = "in msec";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(155, 75);
            this.label19.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(41, 15);
            this.label19.TabIndex = 8;
            this.label19.Text = "Dwell";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(155, 58);
            this.label17.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(55, 15);
            this.label17.TabIndex = 9;
            this.label17.Text = "Td, TA,";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(389, 279);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textTd);
            this.Controls.Add(this.textWn);
            this.Controls.Add(this.textZeta);
            this.Controls.Add(this.radioMCK);
            this.Controls.Add(this.radioStandard);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox3);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "InputShaper";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.Button buttonExcute;
		private System.Windows.Forms.TextBox textZeta;
		private System.Windows.Forms.TextBox textWn;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textM;
		private System.Windows.Forms.TextBox textC;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox textK;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.RadioButton radioStandard;
		private System.Windows.Forms.RadioButton radioMCK;
		private System.Windows.Forms.TextBox textTd;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox textXtotal;
		private System.Windows.Forms.TextBox textVmax;
		private System.Windows.Forms.TextBox textTA;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.RadioButton radioZVDD;
		private System.Windows.Forms.RadioButton radioZVD;
		private System.Windows.Forms.RadioButton radioZV;
		private System.Windows.Forms.GroupBox groupBox5;
		private System.Windows.Forms.TextBox textSysM;
		private System.Windows.Forms.Label label13;
		private System.Windows.Forms.TextBox textSysC;
		private System.Windows.Forms.TextBox textSysK;
		private System.Windows.Forms.Label label14;
		private System.Windows.Forms.Label label15;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.TextBox textBox2;
		private System.Windows.Forms.TextBox textBox3;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.GroupBox groupBox6;
		private System.Windows.Forms.GroupBox groupBox7;
		private System.Windows.Forms.Label label16;
		private System.Windows.Forms.Button buttonSave;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
		private System.Windows.Forms.Label label18;
		private System.Windows.Forms.TextBox textDwell;
		private System.Windows.Forms.Label label20;
		private System.Windows.Forms.Label label19;
		private System.Windows.Forms.Label label17;
	}
}

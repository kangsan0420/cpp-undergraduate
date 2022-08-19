using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InputShaperCoder
{
	public partial class Form1 : Form
	{
		double Xtot, sumX, Vmax, K;
		double zeta, Wn;
		int TA, Td, Zid, Ttot, dwell;

		public Form1()
		{
			InitializeComponent();
		}

		private void textTd_Enter(object sender, EventArgs e)
		{
			textWn.Clear();
		}

		private void textWn_Enter(object sender, EventArgs e)
		{
			textTd.Clear();
		}

		private void buttonSave_Click(object sender, EventArgs e)
		{
			string s = "";

			//======================================================================================================================================================
			double sysM, sysC, sysK;

			textXtotal.Text = textXtotal.Text.Replace(" ", "");
			textVmax.Text = textVmax.Text.Replace(" ", "");
			textTA.Text = textTA.Text.Replace(" ", "");
			textDwell.Text = textDwell.Text.Replace(" ", "");
			if (textXtotal.Text.Length == 0 || textVmax.Text.Length == 0 || textTA.Text.Length ==0 || textDwell.Text.Length == 0)
			{
				MessageBox.Show("parameters : 공란이 있습니다");
				return;
			}
			try
			{
				Xtot = double.Parse(textXtotal.Text);
				Vmax = double.Parse(textVmax.Text);
				TA = int.Parse(textTA.Text);
				dwell = int.Parse(textDwell.Text);
			}
			catch
			{
				MessageBox.Show("parameters : 숫자만 입력하세요");
				return;
			}

			if (radioStandard.Checked)
			{
				textZeta.Text = textZeta.Text.Replace(" ", "");
				textWn.Text = textWn.Text.Replace(" ", "");
				textTd.Text = textTd.Text.Replace(" ", "");
				if ((textZeta.Text.Length == 0) || ((textWn.Text.Length == 0) && (textTd.Text.Length == 0)))
				{
					MessageBox.Show("Standard : 공란이 있습니다");
					return;
				}
				try
				{
					zeta = double.Parse(textZeta.Text);
					if (textWn.TextLength > 0)
					{
						Wn = double.Parse(textWn.Text);
						Td = (int)(1000 * 2 * Math.PI / Wn * Math.Sqrt(1 - zeta * zeta));

					}
					else Td = int.Parse(textTd.Text);
				}
				catch
				{
					MessageBox.Show("Standard : 숫자만 입력하세요");
					return;
				}
			}
			else
			{
				textSysM.Text = textSysM.Text.Replace(" ", "");
				textSysC.Text = textSysC.Text.Replace(" ", "");
				textSysK.Text = textSysK.Text.Replace(" ", "");
				if ((textSysM.Text.Length == 0) || (textSysC.Text.Length == 0) || (textSysK.Text.Length == 0))
				{
					MessageBox.Show("mck : 공란이 있습니다");
					return;
				}
				try
				{
					sysM = double.Parse(textSysM.Text);
					sysC = double.Parse(textSysC.Text);
					sysK = double.Parse(textSysK.Text);

					Wn = Math.Sqrt(sysK / sysM);
					zeta = sysC / (2 * sysM * Wn);
					Td = (int)(1000 * 2 * Math.PI / Wn * Math.Sqrt(1 - zeta * zeta));
				}
				catch
				{
					MessageBox.Show("mck : 숫자만 입력하세요");
					return;
				}
			}

			K = Math.Exp(-zeta * Math.PI / Math.Sqrt(1 - zeta * zeta));

			if (radioZV.Checked) Zid = 1;
			else if (radioZVD.Checked) Zid = 2;
			else Zid = 3;

			//======================================================================================================================================================
			double Vtot = 0;

			Ttot = 0;
			sumX = 0;

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, 0, Vtot);

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								Vtot,
								Vtot);
				s += PVTcoder(TA,
								Vtot,
								Vtot + Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			if (Xtot <= 0.001 * Ttot * Vmax)
			{
				MessageBox.Show("입력성형에 필요한 이동거리가 전체 이동거리를 초과합니다.");
				return;
			}

			s += PVTcoder((int)((1000 * Xtot - Ttot * Vmax) / Vmax), Vmax, Vmax); // center

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, Vmax, Vmax - Vtot);

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								Vmax - Vtot,
								Vmax - Vtot);

				s += PVTcoder(TA,
								Vmax - Vtot,
								Vmax - Vtot - Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			s += "\ndwell " + dwell.ToString() + "\n";
			Ttot = 0;
			sumX = 0;

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, 0, -Vtot);

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								-Vtot,
								-Vtot);
				s += PVTcoder(TA,
								-Vtot,
								-(Vtot + Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid)));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			s += PVTcoder((int)((1000 * Xtot - Ttot * Vmax) / Vmax), -Vmax, -Vmax); // center

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, -Vmax, -(Vmax - Vtot));

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								-(Vmax - Vtot),
								-(Vmax - Vtot));

				s += PVTcoder(TA,
								-(Vmax - Vtot),
								-(Vmax - Vtot - Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid)));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			//======================================================================================================================================================
			if (saveFileDialog1.ShowDialog() == DialogResult.OK)
			{
				System.IO.File.WriteAllText(saveFileDialog1.FileName, s, Encoding.Default);
			}
		}

		private void buttonExcute_Click(object sender, EventArgs e)
		{
			string s = "";
			//======================================================================================================================================================
			double sysM, sysC, sysK;

			textXtotal.Text = textXtotal.Text.Replace(" ", "");
			textVmax.Text = textVmax.Text.Replace(" ", "");
			textTA.Text = textTA.Text.Replace(" ", "");
			textDwell.Text = textDwell.Text.Replace(" ", "");
			if (textXtotal.Text.Length == 0 || textVmax.Text.Length == 0 || textTA.Text.Length == 0 || textDwell.Text.Length == 0)
			{
				MessageBox.Show("parameters : 공란이 있습니다");
				return;
			}
			try
			{
				Xtot = double.Parse(textXtotal.Text);
				Vmax = double.Parse(textVmax.Text);
				TA = int.Parse(textTA.Text);
				dwell = int.Parse(textDwell.Text);
			}
			catch
			{
				MessageBox.Show("parameters : 숫자만 입력하세요");
				return;
			}

			if (radioStandard.Checked)
			{
				textZeta.Text = textZeta.Text.Replace(" ", "");
				textWn.Text = textWn.Text.Replace(" ", "");
				textTd.Text = textTd.Text.Replace(" ", "");
				if ((textZeta.Text.Length == 0) || ((textWn.Text.Length == 0) && (textTd.Text.Length == 0)))
				{
					MessageBox.Show("Standard : 공란이 있습니다");
					return;
				}
				try
				{
					zeta = double.Parse(textZeta.Text);
					if (textWn.TextLength > 0)
					{
						Wn = double.Parse(textWn.Text);
						Td = (int)(1000 * 2 * Math.PI / Wn * Math.Sqrt(1 - zeta * zeta));

					}
					else Td = int.Parse(textTd.Text);
				}
				catch
				{
					MessageBox.Show("Standard : 숫자만 입력하세요");
					return;
				}
			}
			else
			{
				textSysM.Text = textSysM.Text.Replace(" ", "");
				textSysC.Text = textSysC.Text.Replace(" ", "");
				textSysK.Text = textSysK.Text.Replace(" ", "");
				if ((textSysM.Text.Length == 0) || (textSysC.Text.Length == 0) || (textSysK.Text.Length == 0))
				{
					MessageBox.Show("mck : 공란이 있습니다");
					return;
				}
				try
				{
					sysM = double.Parse(textSysM.Text);
					sysC = double.Parse(textSysC.Text);
					sysK = double.Parse(textSysK.Text);

					Wn = Math.Sqrt(sysK / sysM);
					zeta = sysC / (2 * sysM * Wn);
					Td = (int)(1000 * 2 * Math.PI / Wn * Math.Sqrt(1 - zeta * zeta));
				}
				catch
				{
					MessageBox.Show("mck : 숫자만 입력하세요");
					return;
				}
			}

			K = Math.Exp(-zeta * Math.PI / Math.Sqrt(1 - zeta * zeta));

			if (radioZV.Checked) Zid = 1;
			else if (radioZVD.Checked) Zid = 2;
			else Zid = 3;

			//======================================================================================================================================================
			double Vtot = 0;

			Ttot = 0;
			sumX = 0;

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, 0, Vtot);

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								Vtot,
								Vtot);
				s += PVTcoder(TA,
								Vtot,
								Vtot + Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			if (Xtot <= 0.001 * Ttot * Vmax)
			{
				MessageBox.Show("입력성형에 필요한 이동거리가 전체 이동거리를 초과합니다.");
				return;
			}

			s += PVTcoder((int)((1000 * Xtot - Ttot * Vmax) / Vmax), Vmax, Vmax); // center

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, Vmax, Vmax - Vtot);

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								Vmax - Vtot,
								Vmax - Vtot);

				s += PVTcoder(TA,
								Vmax - Vtot,
								Vmax - Vtot - Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			s += "\ndwell " + dwell.ToString() + "\n";
			Ttot = 0;
			sumX = 0;

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, 0, -Vtot);

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								-Vtot,
								-Vtot);
				s += PVTcoder(TA,
								-Vtot,
								-(Vtot + Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid)));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			s += PVTcoder((int)((1000 * Xtot - Ttot * Vmax) / Vmax), -Vmax, -Vmax); // center

			Vtot = Vmax / Math.Pow(1 + K, Zid);
			s += PVTcoder(TA, -Vmax, -(Vmax - Vtot));

			for (int i = 0; i < Zid; i++)
			{
				s += PVTcoder((int)(Td * 0.5 - TA),
								-(Vmax - Vtot),
								-(Vmax - Vtot));

				s += PVTcoder(TA,
								-(Vmax - Vtot),
								-(Vmax - Vtot - Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid)));
				Vtot += Vmax * combination(Zid, i + 1) * Math.Pow(K, i + 1) / Math.Pow((1 + K), Zid);
			}

			//======================================================================================================================================================
			Clipboard.SetText(s);
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			radioStandard.Select();
			radioZV.Select();
		}

		int factorial(int n)
		{
			if (n <= 1) return 1;
			else return n * factorial(n - 1);
		}

		double combination(int n, int r)
		{
			return factorial(n) / (double)(factorial(n - r) * factorial(r));
		}


		string PVTcoder(int msec, double Fi, double Fe)
		{
			string code = "";
			double x;
			x = 0.5 * (Fi + Fe) * msec * 0.001;
			sumX += x;
			Ttot += msec;
			code += "pvt " + msec + "\n";
			code += "x " + x.ToString("F3") + " : " + Fe.ToString("F3") + "\n";
			return code;
		}

	}
}
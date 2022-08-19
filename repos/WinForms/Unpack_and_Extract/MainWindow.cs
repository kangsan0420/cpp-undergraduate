using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Windows.Forms;
using System.ComponentModel;

namespace MJ
{
    public partial class MainWindow : Form
    {
        Progressbar prog_window;

        static string solution_path = Path.GetFullPath(@"../..");
        Dictionary<string, string> default_path = new Dictionary<string, string>()
        {
            {"unpack_src", null},
            {"unpack_dst", null},
            {"extract_pre", null},
            {"extract_update", null},
            {"extract_out", null}
        };
        Dictionary<string, string[]> extract_struct = new Dictionary<string, string[]>()
        {
            {"normal", new string[] { }},
            {"Tomtom", new string[] {"All", "JCT", "3DLandMark"}},
            {"Here", new string[] {"All", "JCT", "3DLandMark"}},
            {"Zenlin", new string[] {"All", "JCT", "3DLandMark"}},
        };
        Dictionary<string, dynamic> default_values = new Dictionary<string, dynamic>()
        {   
            {"textBox_extract_pre", Path.Combine(solution_path, "DATA", "src")},
            {"textBox_extract_update", Path.Combine(solution_path, "DATA", "dst")},
            {"textBox_extract_out", Path.Combine(solution_path, "DATA", "out")},
            {"checkBox_report", true},
            {"checkBox_extract", true},
        };

        public MainWindow()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Initialize textBox
            textBox_extract_pre.Text = default_values["textBox_extract_pre"];
            textBox_extract_update.Text = default_values["textBox_extract_update"];
            textBox_extract_out.Text = default_values["textBox_extract_out"];

            // Initialize checkBox
            checkBox_report.Checked = default_values["checkBox_report"];
            checkBox_extract.Checked = default_values["checkBox_extract"];

            // Initialize ComboBox1
            comboBox1.Items.AddRange(extract_struct.Keys.ToArray<string>());
            comboBox1.SelectedIndex = 0;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            // set Values to ComboBox2
            string[] items = extract_struct[comboBox1.Text];
            comboBox2.Items.Clear();
            comboBox2.Items.AddRange(items);
            comboBox2.SelectedIndex = 0 - Convert.ToInt32(items.Length == 0);
        }

        private void button_unpack_src_Click(object sender, EventArgs e)
        {
            FileIO.SetTextFolderDialog(textBox_unpack_src, default_path["unpack_src"]);
        }

        private void button_unpack_dst_Click(object sender, EventArgs e)
        {
            FileIO.SetTextFolderDialog(textBox_unpack_dst, default_path["unpack_dst"]);
        }

        private void button_unpack_run_Click(object sender, EventArgs e)
        {
            string save_path = textBox_unpack_dst.Text;
            bool result = FileIO.CreateFolder(save_path);
            if (result)
            {
                Func<string, bool> skip_cond = fname => fname.Contains(@"\here\") && !fname.Contains("_S.");
                FileIO.CopyFolder(textBox_unpack_src.Text, textBox_unpack_dst.Text, skip_cond);
                MessageBox.Show("폴더 취합이 완료되었습니다.");
            }
        }

        private void button_extract_pre_Click(object sender, EventArgs e)
        {
            FileIO.SetTextFolderDialog(textBox_extract_pre, default_path["extract_pre"]);
        }

        private void button_extract_update_Click(object sender, EventArgs e)
        {
            FileIO.SetTextFolderDialog(textBox_extract_update, default_path["extract_update"]);
        }

        private void button_extract_out_Click(object sender, EventArgs e)
        {
            FileIO.SetTextFolderDialog(textBox_extract_out, default_path["extract_out"]);
        }

        private void button_extract_run_Click(object sender, EventArgs e)
        {
            prog_window = new Progressbar(backgroundWorker1);
            prog_window.Show();
            backgroundWorker1.RunWorkerAsync();
        }
        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            string[] data_type = new string[2] { comboBox1.Text, comboBox2.Text };
            Dictionary<string, bool> options = new Dictionary<string, bool>() {
                { "report", checkBox_report.Checked },
                { "extract", checkBox_extract.Checked }
            };
            FileIO.ExtractFiles_async(textBox_extract_pre.Text, textBox_extract_update.Text,
                textBox_extract_out.Text, data_type, options, e, backgroundWorker1);
            MessageBox.Show("파일 변경점 추출이 완료되었습니다.");
        }
        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            prog_window.updateValue(e.ProgressPercentage);
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                MessageBox.Show("You have Cancelled");
            }
            else
            {
                MessageBox.Show("Work completed successfully");
            }
            prog_window.Close();
        }
    }
}
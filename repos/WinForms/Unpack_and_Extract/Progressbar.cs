using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace MJ
{
    public partial class Progressbar : Form
    {
        BackgroundWorker backgroundWorker1;

        public Progressbar(BackgroundWorker worker)
        {
            InitializeComponent();
            this.backgroundWorker1 = worker;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            backgroundWorker1.CancelAsync();
        }
        public void updateValue(int percent)
        {
            progressBar1.Value = percent;
            label1.Text = $"{percent.ToString()}%";
        }
    }
}

using System;
using System.Windows.Forms;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.ComponentModel;
using System.Threading;

namespace MJ
{
    internal class Utils
    {
        public static bool IsSameDict(Dictionary<string, string> a, Dictionary<string, string> b)
        {
            bool is_same = true;

            if (a.Count != b.Count)
                is_same = false;
            else
                foreach (KeyValuePair<string, string> dict in a)
                    if (!(b.ContainsKey(dict.Key) && b[dict.Key] == dict.Value))
                    {
                        is_same = false;
                        break;
                    }
            return is_same;
        }
        public static string getMD5Hash(string folder, string fname)
        {
            byte[] byte_hash = MD5.Create().ComputeHash(File.ReadAllBytes(Path.Combine(folder, fname)));
            return BitConverter.ToString(byte_hash).Replace("-", "").ToLower();
        }
        public static string format(string folder, string fname)
        {
            return String.Format("{0} | {1}", fname, getMD5Hash(folder, fname));
        }
        public static string formatter(string folder, string[] files, string divider)
        {
            return String.Join(divider, files.Select(x => format(folder, x)));
        }
        public static string formatter(string src_folder, string[] files, string dst_folder, string divider)
        {
            
            return String.Join(divider, files.Select(x => format(src_folder, x) + " -> " + format(dst_folder, x)));
        }
    }
    internal class FileIO
    {
        static public void SetTextFolderDialog(TextBox tb, object default_path)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if (default_path != null)
            {
                dialog.SelectedPath = (string)default_path;
            }
            DialogResult result = dialog.ShowDialog();
            
            if (result == DialogResult.OK)
            {
                tb.Text = dialog.SelectedPath;
            }
        }
        public static bool CreateFolder(string path)
        {
            if (Directory.Exists(path))
            {
                string message = "폴더가 이미 존재합니다. 지우고 진행하시겠습니까?";
                if (MessageBox.Show(message, "Warning", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    Directory.Delete(path, recursive: true);
                }
                else
                {
                    return false;
                }
            }
            Directory.CreateDirectory(path);
            return true;
        }
        public static void CopyFolder(string src_folder, string dst_folder, Func<string, bool> skip_cond)
        {
            string[] src_paths = Directory.GetFiles(src_folder, "*.*", SearchOption.AllDirectories);
            string[] dst_paths = (from src_path in src_paths select Path.Combine(dst_folder, Path.GetFileName(src_path))).ToArray();
            
            CopyFiles(src_paths, dst_paths, skip_cond);
        }

        public static void CopyFiles(string[] src_paths, string[] dst_paths, Func<string, bool> skip_cond)
        {
            if (src_paths.Length != dst_paths.Length)
                throw new ArgumentException("The length of src_paths and dst_paths must be same.");

            for (int i=0 ; i<src_paths.Length ; i++)
            {
                if (skip_cond(src_paths[i]))
                    continue;
                Directory.CreateDirectory(Path.GetDirectoryName(dst_paths[i]));
                File.Copy(src_paths[i], dst_paths[i], overwrite:true);
            }
        }

        static BaseFile ParseFile(string folder, string fname, string[] data_type)
        {
            BaseFile parsed_file;

            // Rules Here
            if (data_type[1] == "3DLandMark")
                parsed_file = new LandMarkFile(folder, fname);
            else
                parsed_file = new NormalFile(folder, fname);
            return parsed_file;
        }

        public static void ExtractFiles(string pre_folder, string update_folder, string output_folder, string[] data_type, Dictionary<string, bool> options)
        {
            DateTime ptime = DateTime.Now;
            string[] src_paths = Directory.GetFiles(pre_folder, "*.*", SearchOption.AllDirectories);
            string[] dst_paths = Directory.GetFiles(update_folder, "*.*", SearchOption.AllDirectories);

            string[] src_files = (from src_path in src_paths select src_path.Replace(pre_folder + "\\", "")).ToArray();
            string[] dst_files = (from dst_path in dst_paths select dst_path.Replace(update_folder + "\\", "")).ToArray();

            string[] added_files = dst_files.Except(src_files).ToArray();
            string[] removed_files = src_files.Except(dst_files).ToArray();
            string[] unchanged_files = src_files.Intersect(dst_files).ToArray();

            Dictionary<string, string> modified_paths = new Dictionary<string, string>();
            foreach (string fname in unchanged_files)
            {
                string src_path = Path.Combine(pre_folder, fname);
                string dst_path = Path.Combine(update_folder, fname);

                BaseFile src_file = ParseFile(pre_folder, fname, data_type);
                BaseFile dst_file = ParseFile(update_folder, fname, data_type);

                Console.WriteLine($"src - {src_file} = {String.Join(", ", src_file.ID.Keys)}: {String.Join(", ", src_file.ID.Values)}");
                Console.WriteLine($"dst - {dst_file} = {String.Join(", ", dst_file.ID.Keys)}: {String.Join(", ", dst_file.ID.Values)}");
                Console.WriteLine();
                if (!Utils.IsSameDict(src_file.ID, dst_file.ID))
                {
                    modified_paths.Add(src_path, dst_path);
                }
            }
            Func<string, bool> skip_cond = fname => false; // no skipping

            // Copy Added Files
            string[] add_src = added_files.Select(x => Path.Combine(update_folder, x)).ToArray();
            string[] add_out = added_files.Select(x => Path.Combine(output_folder, x)).ToArray();

            // Copy Modified Files
            string[] mod_src = modified_paths.Keys.ToArray();
            string[] mod_dst = modified_paths.Values.ToArray();
            string[] mod_out = mod_dst.Select(x => x.Replace(update_folder, output_folder)).ToArray();

            if (options["extract"])
            {
                CopyFiles(add_src, add_out, skip_cond);
                CopyFiles(mod_src, mod_out, skip_cond);
            }
            if (options["report"])
            {
                string divider = "\n";

                string message = $@"
[{ptime} - {DateTime.Now}]

{src_paths.Length} files found in pre folder: ""{ pre_folder}""
{Utils.formatter(pre_folder, src_files, divider)}

{dst_paths.Length} files found in update folder: ""{update_folder}""
{Utils.formatter(update_folder, dst_files, divider)}

{added_files.Length} new files found:
{Utils.formatter(update_folder, added_files, divider)}

{removed_files.Length} removed files found:
{Utils.formatter(pre_folder, removed_files, divider)}

{unchanged_files.Length} files are found on both folders:
{Utils.formatter(pre_folder, unchanged_files, divider)}

{mod_src.Length} files are determined to be changed(by MD5 hash):
{Utils.formatter(pre_folder, mod_src.Select(x => x.Replace(pre_folder + "\\", "")).ToArray(), update_folder, divider)}
";

                StreamWriter sFile;
                sFile = File.CreateText(Path.Combine(output_folder, "report.log"));
                sFile.Write(message);
                sFile.Close();
            }
        }

        public static void ExtractFiles_async(string pre_folder, string update_folder, string output_folder, string[] data_type, Dictionary<string, bool> options, DoWorkEventArgs e, BackgroundWorker backgroundWorker1)
        {
            DateTime ptime = DateTime.Now;
            string[] src_paths = Directory.GetFiles(pre_folder, "*.*", SearchOption.AllDirectories);
            string[] dst_paths = Directory.GetFiles(update_folder, "*.*", SearchOption.AllDirectories);

            string[] src_files = (from src_path in src_paths select src_path.Replace(pre_folder + "\\", "")).ToArray();
            string[] dst_files = (from dst_path in dst_paths select dst_path.Replace(update_folder + "\\", "")).ToArray();

            string[] added_files = dst_files.Except(src_files).ToArray();
            string[] removed_files = src_files.Except(dst_files).ToArray();
            string[] unchanged_files = src_files.Intersect(dst_files).ToArray();

            Dictionary<string, string> modified_paths = new Dictionary<string, string>();
            for (int i=0; i<unchanged_files.Length; i++)
            {
                string fname = unchanged_files[i];
                int percent = (int)(100 * (i + 1) / unchanged_files.Length);
                if (backgroundWorker1.CancellationPending)
                {
                    //CANCEL
                    e.Cancel = true;
                }
                else
                {
                    string src_path = Path.Combine(pre_folder, fname);
                    string dst_path = Path.Combine(update_folder, fname);

                    BaseFile src_file = ParseFile(pre_folder, fname, data_type);
                    BaseFile dst_file = ParseFile(update_folder, fname, data_type);

                    Console.WriteLine($"src - {src_file} = {String.Join(", ", src_file.ID.Keys)}: {String.Join(", ", src_file.ID.Values)}");
                    Console.WriteLine($"dst - {dst_file} = {String.Join(", ", dst_file.ID.Keys)}: {String.Join(", ", dst_file.ID.Values)}");
                    Console.WriteLine();
                    if (!Utils.IsSameDict(src_file.ID, dst_file.ID))
                    {
                        modified_paths.Add(src_path, dst_path);
                    }
                    backgroundWorker1.ReportProgress(percent);
                }
                Thread.Sleep(1000);
            }
            Func<string, bool> skip_cond = fname => false; // no skipping

            // Copy Added Files
            string[] add_src = added_files.Select(x => Path.Combine(update_folder, x)).ToArray();
            string[] add_out = added_files.Select(x => Path.Combine(output_folder, x)).ToArray();

            // Copy Modified Files
            string[] mod_src = modified_paths.Keys.ToArray();
            string[] mod_dst = modified_paths.Values.ToArray();
            string[] mod_out = mod_dst.Select(x => x.Replace(update_folder, output_folder)).ToArray();

            if (options["extract"])
            {
                CopyFiles(add_src, add_out, skip_cond);
                CopyFiles(mod_src, mod_out, skip_cond);
            }
            if (options["report"])
            {
                string divider = "\n";

                string message = $@"
[{ptime} - {DateTime.Now}]

{src_paths.Length} files found in pre folder: ""{ pre_folder}""
{Utils.formatter(pre_folder, src_files, divider)}

{dst_paths.Length} files found in update folder: ""{update_folder}""
{Utils.formatter(update_folder, dst_files, divider)}

{added_files.Length} new files found:
{Utils.formatter(update_folder, added_files, divider)}

{removed_files.Length} removed files found:
{Utils.formatter(pre_folder, removed_files, divider)}

{unchanged_files.Length} files are found on both folders:
{Utils.formatter(pre_folder, unchanged_files, divider)}

{mod_src.Length} files are determined to be changed(by MD5 hash):
{Utils.formatter(pre_folder, mod_src.Select(x => x.Replace(pre_folder + "\\", "")).ToArray(), update_folder, divider)}
";

                StreamWriter sFile;
                sFile = File.CreateText(Path.Combine(output_folder, "report.log"));
                sFile.Write(message);
                sFile.Close();
            }
        }
    }
}
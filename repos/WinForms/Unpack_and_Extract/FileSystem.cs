using System;
using System.Collections.Generic;
using System.IO;

namespace MJ
{
    using Identifier = Dictionary<string, string>; // path: hash

    internal class BaseFile
    {
        internal Identifier ID { get; set; } = new Identifier() { };
        
        
        public bool IsSameFile(BaseFile other)
        {
            return Utils.IsSameDict(this.ID, other.ID);
        }
    }
    internal class NormalFile : BaseFile
    {

        public NormalFile(string folder, string fname)
        {
            this.ID.Add(fname, Utils.getMD5Hash(folder, fname));
        }
    }

    internal class LandMarkFile : NormalFile
    {
        public string[] extensions = new string [] { ".MTL", ".OBJ", ".PNG" };
        public Dictionary<string, bool> IsLoaded { get; set; } = new Dictionary<string, bool>();

        public LandMarkFile(string folder, string fname) : base(folder, fname)
        {
            addGroupID(folder, fname);
        }
        public void addGroupID(string folder, string fname)
        {
            foreach (string ext in this.extensions)
            {
                if (fname.Contains(ext)) { continue; }
                string new_name = fname.Replace(Path.GetExtension(fname), ext);
                if (File.Exists(Path.Combine(folder, new_name)))
                {
                    this.IsLoaded[ext] = true;
                    this.ID.Add(new_name, Utils.getMD5Hash(folder, new_name));
                }
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OOProj.WindowsAplikacija
{
    public partial class FormStudent : Form
    {
        Student _student = null;

        public Student VratiStudenta
        {
            get 
            { 
                if(_student == null)
                    _student = new Student();

                return _student; 
            }
        }

        public FormStudent()
        {
            InitializeComponent();
        }

        private void btnOdustani_Click(object sender, EventArgs e)
        {
            //DialogResult dlg = MessageBox.Show("Da li stvarno zelite da odustanete?",
            //                "Obavestenje",
            //                MessageBoxButtons.YesNo,
            //                MessageBoxIcon.Question);

            //if (dlg == DialogResult.Yes)
            //{
            //    this.Close();
            //    this.DialogResult = DialogResult.Cancel;

               
            //}

            this.Close();
        }

        private void btnProsledi_Click(object sender, EventArgs e)
        {
            _student = new Student();

            _student.Ime = txtIme.Text;
            _student.Prezime = txtPrezime.Text;

            int i = 0;
            if (int.TryParse(txtIndex.Text, out i))
            {
                _student.Index = i;
            }
            else
            {
                _student.Index = -1;
            }

            this.Close();
            this.DialogResult = DialogResult.OK;
        
        }

        private void FormStudent_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult dlg = MessageBox.Show("Da li stvarno zelite da odustanete?",
                      "Obavestenje",
                      MessageBoxButtons.YesNo,
                      MessageBoxIcon.Question);

            if (dlg == DialogResult.No)
            {
                e.Cancel = true;
            }

            this.DialogResult = DialogResult.Cancel;
        }
    }
}

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
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();

        }

        private void btnHelloWorld_Click(object sender, EventArgs e)
        {
            DialogResult dlg = MessageBox.Show("Prvi duge :)",
                                            "Obavestenje",
                                            MessageBoxButtons.YesNo,
                                            MessageBoxIcon.Question);

            if (dlg == DialogResult.Yes)
            {
                MessageBox.Show("Kliknuli smo na dugme Yes");
            }
            else
            {
                MessageBox.Show("Kliknuli smo na dugme No");
            }
        }

        private void btnTacnoVreme_Click(object sender, EventArgs e)
        {
            String str = DateTime.Now.ToString("dd.MM.yyyy. HH:mm ss");

            MessageBox.Show(str, "Tacno vreme",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information);

            lblDatum.Text = "Vreme: " + str;

        }

        private void btnKreirajStudenta_Click(object sender, EventArgs e)
        {
            Student s = new Student();

            s.Ime = "Pera";
            s.Prezime = "Peric";
            s.Index = 123213;
        }

        private void btnUnesiNovogStudenta_Click(object sender, EventArgs e)
        {
            FormStudent frm = new FormStudent();
            DialogResult dlg = frm.ShowDialog();

            if (dlg == DialogResult.Cancel)
            {
                MessageBox.Show("Korisnik je odustao sa unosm studenta!");
            }
            else
            {
                Student std = frm.VratiStudenta;
                MessageBox.Show(std.PrikaziPodatke());
            }
        }
    }
}

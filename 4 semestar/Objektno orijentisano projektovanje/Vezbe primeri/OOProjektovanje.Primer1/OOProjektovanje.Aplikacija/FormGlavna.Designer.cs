﻿namespace OOProjektovanje1
{
    partial class FormGlavna
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
            this.btnDodaj = new System.Windows.Forms.Button();
            this.lblIme = new System.Windows.Forms.Label();
            this.lblPrezime = new System.Windows.Forms.Label();
            this.lblJmbg = new System.Windows.Forms.Label();
            this.txtIme = new System.Windows.Forms.TextBox();
            this.txtPrezime = new System.Windows.Forms.TextBox();
            this.txtJMBG = new System.Windows.Forms.TextBox();
            this.lbxStudent = new System.Windows.Forms.ListBox();
            this.btnObrisi = new System.Windows.Forms.Button();
            this.btnTacnoVreme = new System.Windows.Forms.Button();
            this.lblTacnoVreme = new System.Windows.Forms.Label();
            this.btnZatvori = new System.Windows.Forms.Button();
            this.btnSort = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnDodaj
            // 
            this.btnDodaj.Location = new System.Drawing.Point(20, 95);
            this.btnDodaj.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnDodaj.Name = "btnDodaj";
            this.btnDodaj.Size = new System.Drawing.Size(100, 28);
            this.btnDodaj.TabIndex = 6;
            this.btnDodaj.Text = "Dodaj";
            this.btnDodaj.UseVisualStyleBackColor = true;
            this.btnDodaj.Click += new System.EventHandler(this.btnDodaj_Click);
            // 
            // lblIme
            // 
            this.lblIme.AutoSize = true;
            this.lblIme.Location = new System.Drawing.Point(16, 30);
            this.lblIme.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblIme.Name = "lblIme";
            this.lblIme.Size = new System.Drawing.Size(32, 16);
            this.lblIme.TabIndex = 0;
            this.lblIme.Text = "Ime:";
            // 
            // lblPrezime
            // 
            this.lblPrezime.AutoSize = true;
            this.lblPrezime.Location = new System.Drawing.Point(229, 30);
            this.lblPrezime.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblPrezime.Name = "lblPrezime";
            this.lblPrezime.Size = new System.Drawing.Size(59, 16);
            this.lblPrezime.TabIndex = 2;
            this.lblPrezime.Text = "Prezime:";
            // 
            // lblJmbg
            // 
            this.lblJmbg.AutoSize = true;
            this.lblJmbg.Location = new System.Drawing.Point(16, 66);
            this.lblJmbg.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblJmbg.Name = "lblJmbg";
            this.lblJmbg.Size = new System.Drawing.Size(47, 16);
            this.lblJmbg.TabIndex = 4;
            this.lblJmbg.Text = "JMBG:";
            // 
            // txtIme
            // 
            this.txtIme.Location = new System.Drawing.Point(60, 26);
            this.txtIme.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtIme.MaxLength = 20;
            this.txtIme.Name = "txtIme";
            this.txtIme.Size = new System.Drawing.Size(132, 22);
            this.txtIme.TabIndex = 1;
            this.txtIme.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtIme_KeyPress);
            // 
            // txtPrezime
            // 
            this.txtPrezime.Location = new System.Drawing.Point(303, 26);
            this.txtPrezime.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtPrezime.MaxLength = 20;
            this.txtPrezime.Name = "txtPrezime";
            this.txtPrezime.Size = new System.Drawing.Size(132, 22);
            this.txtPrezime.TabIndex = 3;
            this.txtPrezime.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtPrezime_KeyPress);
            // 
            // txtJMBG
            // 
            this.txtJMBG.Location = new System.Drawing.Point(73, 63);
            this.txtJMBG.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtJMBG.MaxLength = 13;
            this.txtJMBG.Name = "txtJMBG";
            this.txtJMBG.Size = new System.Drawing.Size(359, 22);
            this.txtJMBG.TabIndex = 5;
            this.txtJMBG.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtJMBG_KeyPress);
            // 
            // lbxStudent
            // 
            this.lbxStudent.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lbxStudent.FormattingEnabled = true;
            this.lbxStudent.HorizontalScrollbar = true;
            this.lbxStudent.ItemHeight = 16;
            this.lbxStudent.Location = new System.Drawing.Point(20, 154);
            this.lbxStudent.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.lbxStudent.Name = "lbxStudent";
            this.lbxStudent.ScrollAlwaysVisible = true;
            this.lbxStudent.Size = new System.Drawing.Size(415, 148);
            this.lbxStudent.TabIndex = 8;
            this.lbxStudent.DoubleClick += new System.EventHandler(this.lbxStudent_DoubleClick);
            // 
            // btnObrisi
            // 
            this.btnObrisi.Location = new System.Drawing.Point(192, 95);
            this.btnObrisi.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnObrisi.Name = "btnObrisi";
            this.btnObrisi.Size = new System.Drawing.Size(100, 28);
            this.btnObrisi.TabIndex = 7;
            this.btnObrisi.Text = "Obrisi";
            this.btnObrisi.UseVisualStyleBackColor = true;
            this.btnObrisi.Click += new System.EventHandler(this.bntObrisi_Click);
            // 
            // btnTacnoVreme
            // 
            this.btnTacnoVreme.Location = new System.Drawing.Point(17, 310);
            this.btnTacnoVreme.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnTacnoVreme.Name = "btnTacnoVreme";
            this.btnTacnoVreme.Size = new System.Drawing.Size(127, 28);
            this.btnTacnoVreme.TabIndex = 9;
            this.btnTacnoVreme.Text = "Tacno vreme";
            this.btnTacnoVreme.UseVisualStyleBackColor = true;
            this.btnTacnoVreme.Click += new System.EventHandler(this.btnTacnoVreme_Click);
            // 
            // lblTacnoVreme
            // 
            this.lblTacnoVreme.AutoSize = true;
            this.lblTacnoVreme.Location = new System.Drawing.Point(152, 316);
            this.lblTacnoVreme.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTacnoVreme.Name = "lblTacnoVreme";
            this.lblTacnoVreme.Size = new System.Drawing.Size(81, 16);
            this.lblTacnoVreme.TabIndex = 10;
            this.lblTacnoVreme.Text = "tacno vreme";
            // 
            // btnZatvori
            // 
            this.btnZatvori.Location = new System.Drawing.Point(309, 310);
            this.btnZatvori.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnZatvori.Name = "btnZatvori";
            this.btnZatvori.Size = new System.Drawing.Size(127, 28);
            this.btnZatvori.TabIndex = 11;
            this.btnZatvori.Text = "Zatvori";
            this.btnZatvori.UseVisualStyleBackColor = true;
            this.btnZatvori.Click += new System.EventHandler(this.btnZatvori_Click);
            // 
            // btnSort
            // 
            this.btnSort.Location = new System.Drawing.Point(336, 95);
            this.btnSort.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnSort.Name = "btnSort";
            this.btnSort.Size = new System.Drawing.Size(100, 28);
            this.btnSort.TabIndex = 12;
            this.btnSort.Text = "Sortiraj";
            this.btnSort.UseVisualStyleBackColor = true;
            this.btnSort.Click += new System.EventHandler(this.btnSort_Click);
            // 
            // FormGlavna
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(449, 341);
            this.Controls.Add(this.btnSort);
            this.Controls.Add(this.btnZatvori);
            this.Controls.Add(this.lblTacnoVreme);
            this.Controls.Add(this.btnTacnoVreme);
            this.Controls.Add(this.btnObrisi);
            this.Controls.Add(this.lbxStudent);
            this.Controls.Add(this.txtJMBG);
            this.Controls.Add(this.txtPrezime);
            this.Controls.Add(this.txtIme);
            this.Controls.Add(this.lblJmbg);
            this.Controls.Add(this.lblPrezime);
            this.Controls.Add(this.lblIme);
            this.Controls.Add(this.btnDodaj);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(467, 388);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(467, 388);
            this.Name = "FormGlavna";
            this.Opacity = 0.95D;
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "OOProjektovanje :)";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormGlavna_FormClosing);
            this.Load += new System.EventHandler(this.FormGlavna_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnDodaj;
        private System.Windows.Forms.Label lblIme;
        private System.Windows.Forms.Label lblPrezime;
        private System.Windows.Forms.Label lblJmbg;
        private System.Windows.Forms.TextBox txtIme;
        private System.Windows.Forms.TextBox txtPrezime;
        private System.Windows.Forms.TextBox txtJMBG;
        private System.Windows.Forms.ListBox lbxStudent;
        private System.Windows.Forms.Button btnObrisi;
        private System.Windows.Forms.Button btnTacnoVreme;
        private System.Windows.Forms.Label lblTacnoVreme;
        private System.Windows.Forms.Button btnZatvori;
        private System.Windows.Forms.Button btnSort;
    }
}


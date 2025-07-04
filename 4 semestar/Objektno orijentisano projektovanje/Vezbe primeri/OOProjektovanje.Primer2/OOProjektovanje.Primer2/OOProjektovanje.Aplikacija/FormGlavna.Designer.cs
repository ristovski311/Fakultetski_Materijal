﻿namespace OOProjektovanje.Aplikacija
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
            this.components = new System.ComponentModel.Container();
            this.dgvListaStudenata = new System.Windows.Forms.DataGridView();
            this.btnZatvori = new System.Windows.Forms.Button();
            this.lblTacnoVreme = new System.Windows.Forms.Label();
            this.tmrTacnoVReme = new System.Windows.Forms.Timer(this.components);
            this.btnPrikaziSvojstvaZaDataGridVies = new System.Windows.Forms.Button();
            this.btnObrisi = new System.Windows.Forms.Button();
            this.btnIzmeni = new System.Windows.Forms.Button();
            this.btnDodaj = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvListaStudenata)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvListaStudenata
            // 
            this.dgvListaStudenata.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dgvListaStudenata.BackgroundColor = System.Drawing.Color.White;
            this.dgvListaStudenata.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvListaStudenata.Location = new System.Drawing.Point(1, 82);
            this.dgvListaStudenata.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.dgvListaStudenata.Name = "dgvListaStudenata";
            this.dgvListaStudenata.RowHeadersWidth = 51;
            this.dgvListaStudenata.Size = new System.Drawing.Size(704, 346);
            this.dgvListaStudenata.TabIndex = 0;
            this.dgvListaStudenata.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvListaStudenata_CellContentClick);
            // 
            // btnZatvori
            // 
            this.btnZatvori.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnZatvori.Location = new System.Drawing.Point(609, 443);
            this.btnZatvori.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnZatvori.Name = "btnZatvori";
            this.btnZatvori.Size = new System.Drawing.Size(88, 28);
            this.btnZatvori.TabIndex = 4;
            this.btnZatvori.Text = "Zatvori";
            this.btnZatvori.UseVisualStyleBackColor = true;
            this.btnZatvori.Click += new System.EventHandler(this.btnZatvori_Click);
            // 
            // lblTacnoVreme
            // 
            this.lblTacnoVreme.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.lblTacnoVreme.AutoSize = true;
            this.lblTacnoVreme.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblTacnoVreme.Location = new System.Drawing.Point(-4, 442);
            this.lblTacnoVreme.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTacnoVreme.Name = "lblTacnoVreme";
            this.lblTacnoVreme.Size = new System.Drawing.Size(272, 28);
            this.lblTacnoVreme.TabIndex = 5;
            this.lblTacnoVreme.Text = "HH:mm:ss dd.MM.yyyy.";
            // 
            // tmrTacnoVReme
            // 
            this.tmrTacnoVReme.Interval = 1000;
            this.tmrTacnoVReme.Tick += new System.EventHandler(this.tmrTacnoVReme_Tick);
            // 
            // btnPrikaziSvojstvaZaDataGridVies
            // 
            this.btnPrikaziSvojstvaZaDataGridVies.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnPrikaziSvojstvaZaDataGridVies.Location = new System.Drawing.Point(557, 15);
            this.btnPrikaziSvojstvaZaDataGridVies.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnPrikaziSvojstvaZaDataGridVies.Name = "btnPrikaziSvojstvaZaDataGridVies";
            this.btnPrikaziSvojstvaZaDataGridVies.Size = new System.Drawing.Size(140, 60);
            this.btnPrikaziSvojstvaZaDataGridVies.TabIndex = 6;
            this.btnPrikaziSvojstvaZaDataGridVies.Text = "Prikazi svojstva za  spisak studenata";
            this.btnPrikaziSvojstvaZaDataGridVies.UseVisualStyleBackColor = true;
            this.btnPrikaziSvojstvaZaDataGridVies.Click += new System.EventHandler(this.btnPrikaziSvojstvaZaDataGridVies_Click);
            // 
            // btnObrisi
            // 
            this.btnObrisi.Image = global::OOProjektovanje.Aplikacija.Properties.Resources.cleanAll;
            this.btnObrisi.Location = new System.Drawing.Point(287, 15);
            this.btnObrisi.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnObrisi.Name = "btnObrisi";
            this.btnObrisi.Size = new System.Drawing.Size(100, 60);
            this.btnObrisi.TabIndex = 3;
            this.btnObrisi.Text = "Obrisi";
            this.btnObrisi.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.btnObrisi.UseVisualStyleBackColor = true;
            this.btnObrisi.Click += new System.EventHandler(this.btnObrisi_Click);
            // 
            // btnIzmeni
            // 
            this.btnIzmeni.Image = global::OOProjektovanje.Aplikacija.Properties.Resources.edit;
            this.btnIzmeni.Location = new System.Drawing.Point(149, 15);
            this.btnIzmeni.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnIzmeni.Name = "btnIzmeni";
            this.btnIzmeni.Size = new System.Drawing.Size(100, 60);
            this.btnIzmeni.TabIndex = 2;
            this.btnIzmeni.Text = "Izmeni";
            this.btnIzmeni.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.btnIzmeni.UseVisualStyleBackColor = true;
            this.btnIzmeni.Click += new System.EventHandler(this.btnIzmeni_Click);
            // 
            // btnDodaj
            // 
            this.btnDodaj.Image = global::OOProjektovanje.Aplikacija.Properties.Resources.add;
            this.btnDodaj.Location = new System.Drawing.Point(16, 15);
            this.btnDodaj.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnDodaj.Name = "btnDodaj";
            this.btnDodaj.Size = new System.Drawing.Size(100, 60);
            this.btnDodaj.TabIndex = 1;
            this.btnDodaj.Text = "Dodaj";
            this.btnDodaj.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.btnDodaj.UseVisualStyleBackColor = true;
            this.btnDodaj.Click += new System.EventHandler(this.btnDodaj_Click);
            // 
            // FormGlavna
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(705, 479);
            this.Controls.Add(this.btnPrikaziSvojstvaZaDataGridVies);
            this.Controls.Add(this.lblTacnoVreme);
            this.Controls.Add(this.btnZatvori);
            this.Controls.Add(this.btnObrisi);
            this.Controls.Add(this.btnIzmeni);
            this.Controls.Add(this.btnDodaj);
            this.Controls.Add(this.dgvListaStudenata);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(721, 516);
            this.Name = "FormGlavna";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "OOProjektovanje";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormGlavna_FormClosing);
            this.Load += new System.EventHandler(this.FormGlavna_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dgvListaStudenata)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvListaStudenata;
        private System.Windows.Forms.Button btnDodaj;
        private System.Windows.Forms.Button btnIzmeni;
        private System.Windows.Forms.Button btnObrisi;
        private System.Windows.Forms.Button btnZatvori;
        private System.Windows.Forms.Label lblTacnoVreme;
        private System.Windows.Forms.Timer tmrTacnoVReme;
        private System.Windows.Forms.Button btnPrikaziSvojstvaZaDataGridVies;
    }
}


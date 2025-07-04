﻿namespace OOP.CustonControl
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
            this.lbxListaOsoba = new System.Windows.Forms.ListBox();
            this.btnSnimiXml = new System.Windows.Forms.Button();
            this.btnUcitajXML = new System.Windows.Forms.Button();
            this.ctrlPodaciOOsobi = new OOP.CustomControls.CtrlPodaciOOsobi();
            this.ctrlDodajOsobu = new OOP.CustomControls.CtrlDodajOsobu();
            this.btnZatvori = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbxListaOsoba
            // 
            this.lbxListaOsoba.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lbxListaOsoba.FormattingEnabled = true;
            this.lbxListaOsoba.Location = new System.Drawing.Point(0, 149);
            this.lbxListaOsoba.Name = "lbxListaOsoba";
            this.lbxListaOsoba.Size = new System.Drawing.Size(315, 121);
            this.lbxListaOsoba.TabIndex = 1;
            this.lbxListaOsoba.SelectedIndexChanged += new System.EventHandler(this.lbxListaOsoba_SelectedIndexChanged);
            // 
            // btnSnimiXml
            // 
            this.btnSnimiXml.Location = new System.Drawing.Point(12, 299);
            this.btnSnimiXml.Name = "btnSnimiXml";
            this.btnSnimiXml.Size = new System.Drawing.Size(75, 23);
            this.btnSnimiXml.TabIndex = 3;
            this.btnSnimiXml.Text = "Snimi XML";
            this.btnSnimiXml.UseVisualStyleBackColor = true;
            this.btnSnimiXml.Click += new System.EventHandler(this.btnSnimiXml_Click);
            // 
            // btnUcitajXML
            // 
            this.btnUcitajXML.Location = new System.Drawing.Point(119, 299);
            this.btnUcitajXML.Name = "btnUcitajXML";
            this.btnUcitajXML.Size = new System.Drawing.Size(75, 23);
            this.btnUcitajXML.TabIndex = 4;
            this.btnUcitajXML.Text = "Ucitaj XML";
            this.btnUcitajXML.UseVisualStyleBackColor = true;
            this.btnUcitajXML.Click += new System.EventHandler(this.btnUcitajXML_Click);
            // 
            // ctrlPodaciOOsobi
            // 
            this.ctrlPodaciOOsobi.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.ctrlPodaciOOsobi.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ctrlPodaciOOsobi.Location = new System.Drawing.Point(0, 2);
            this.ctrlPodaciOOsobi.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ctrlPodaciOOsobi.Name = "ctrlPodaciOOsobi";
            this.ctrlPodaciOOsobi.OsobaValue = null;
            this.ctrlPodaciOOsobi.Size = new System.Drawing.Size(315, 138);
            this.ctrlPodaciOOsobi.TabIndex = 0;
            // 
            // ctrlDodajOsobu
            // 
            this.ctrlDodajOsobu.ImenikValue = null;
            this.ctrlDodajOsobu.Location = new System.Drawing.Point(322, 2);
            this.ctrlDodajOsobu.Name = "ctrlDodajOsobu";
            this.ctrlDodajOsobu.RefreshDlg = null;
            this.ctrlDodajOsobu.Size = new System.Drawing.Size(324, 268);
            this.ctrlDodajOsobu.TabIndex = 2;
            // 
            // btnZatvori
            // 
            this.btnZatvori.Location = new System.Drawing.Point(571, 299);
            this.btnZatvori.Name = "btnZatvori";
            this.btnZatvori.Size = new System.Drawing.Size(75, 23);
            this.btnZatvori.TabIndex = 5;
            this.btnZatvori.Text = "Zatvori";
            this.btnZatvori.UseVisualStyleBackColor = true;
            this.btnZatvori.Click += new System.EventHandler(this.btnZatvori_Click);
            // 
            // FormGlavna
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(658, 334);
            this.Controls.Add(this.btnZatvori);
            this.Controls.Add(this.ctrlDodajOsobu);
            this.Controls.Add(this.btnUcitajXML);
            this.Controls.Add(this.btnSnimiXml);
            this.Controls.Add(this.lbxListaOsoba);
            this.Controls.Add(this.ctrlPodaciOOsobi);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(674, 373);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(674, 373);
            this.Name = "FormGlavna";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "OOProjektovanje";
            this.Load += new System.EventHandler(this.FormGlavna_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private CustomControls.CtrlPodaciOOsobi ctrlPodaciOOsobi;
        private System.Windows.Forms.ListBox lbxListaOsoba;
        private System.Windows.Forms.Button btnSnimiXml;
        private System.Windows.Forms.Button btnUcitajXML;
        private CustomControls.CtrlDodajOsobu ctrlDodajOsobu;
        private System.Windows.Forms.Button btnZatvori;
    }
}


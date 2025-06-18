namespace OOProj.WindowsAplikacija
{
    partial class FormMain
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
            this.btnHelloWorld = new System.Windows.Forms.Button();
            this.btnTacnoVreme = new System.Windows.Forms.Button();
            this.lblDatum = new System.Windows.Forms.Label();
            this.btnKreirajStudenta = new System.Windows.Forms.Button();
            this.btnUnesiNovogStudenta = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnHelloWorld
            // 
            this.btnHelloWorld.Location = new System.Drawing.Point(110, 32);
            this.btnHelloWorld.Name = "btnHelloWorld";
            this.btnHelloWorld.Size = new System.Drawing.Size(177, 47);
            this.btnHelloWorld.TabIndex = 0;
            this.btnHelloWorld.Text = "Prikazi poruku";
            this.btnHelloWorld.UseVisualStyleBackColor = true;
            this.btnHelloWorld.Click += new System.EventHandler(this.btnHelloWorld_Click);
            // 
            // btnTacnoVreme
            // 
            this.btnTacnoVreme.Location = new System.Drawing.Point(331, 32);
            this.btnTacnoVreme.Name = "btnTacnoVreme";
            this.btnTacnoVreme.Size = new System.Drawing.Size(177, 49);
            this.btnTacnoVreme.TabIndex = 1;
            this.btnTacnoVreme.Text = "Prikazi tacno vreme";
            this.btnTacnoVreme.UseVisualStyleBackColor = true;
            this.btnTacnoVreme.Click += new System.EventHandler(this.btnTacnoVreme_Click);
            // 
            // lblDatum
            // 
            this.lblDatum.AutoSize = true;
            this.lblDatum.Location = new System.Drawing.Point(106, 9);
            this.lblDatum.Name = "lblDatum";
            this.lblDatum.Size = new System.Drawing.Size(64, 20);
            this.lblDatum.TabIndex = 2;
            this.lblDatum.Text = "Vreme: ";
            // 
            // btnKreirajStudenta
            // 
            this.btnKreirajStudenta.Location = new System.Drawing.Point(110, 116);
            this.btnKreirajStudenta.Name = "btnKreirajStudenta";
            this.btnKreirajStudenta.Size = new System.Drawing.Size(177, 43);
            this.btnKreirajStudenta.TabIndex = 3;
            this.btnKreirajStudenta.Text = "Kreiraj studenta";
            this.btnKreirajStudenta.UseVisualStyleBackColor = true;
            this.btnKreirajStudenta.Click += new System.EventHandler(this.btnKreirajStudenta_Click);
            // 
            // btnUnesiNovogStudenta
            // 
            this.btnUnesiNovogStudenta.Location = new System.Drawing.Point(110, 220);
            this.btnUnesiNovogStudenta.Name = "btnUnesiNovogStudenta";
            this.btnUnesiNovogStudenta.Size = new System.Drawing.Size(139, 86);
            this.btnUnesiNovogStudenta.TabIndex = 4;
            this.btnUnesiNovogStudenta.Text = "Unesi novog studenta";
            this.btnUnesiNovogStudenta.UseVisualStyleBackColor = true;
            this.btnUnesiNovogStudenta.Click += new System.EventHandler(this.btnUnesiNovogStudenta_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(718, 375);
            this.Controls.Add(this.btnUnesiNovogStudenta);
            this.Controls.Add(this.btnKreirajStudenta);
            this.Controls.Add(this.lblDatum);
            this.Controls.Add(this.btnTacnoVreme);
            this.Controls.Add(this.btnHelloWorld);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormMain";
            this.Opacity = 0.9D;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Ovo je prva forma u C#";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnHelloWorld;
        private System.Windows.Forms.Button btnTacnoVreme;
        private System.Windows.Forms.Label lblDatum;
        private System.Windows.Forms.Button btnKreirajStudenta;
        private System.Windows.Forms.Button btnUnesiNovogStudenta;
    }
}


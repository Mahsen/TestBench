namespace TEST_BENCH
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.BAR_Proccess = new System.Windows.Forms.ProgressBar();
            this.lable_version = new System.Windows.Forms.Label();
            this.txt_explanation = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.En_Next = new System.Windows.Forms.CheckBox();
            this.En_Loop = new System.Windows.Forms.CheckBox();
            this.replay = new System.Windows.Forms.Button();
            this.next = new System.Windows.Forms.Button();
            this.img_connect = new System.Windows.Forms.PictureBox();
            this.restart = new System.Windows.Forms.Button();
            this.txt_state = new System.Windows.Forms.Label();
            this.lable_logo = new System.Windows.Forms.PictureBox();
            this.lbl_view_timeout = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label_device_info = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.lst_devies = new System.Windows.Forms.DataGridView();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.LST_TEST = new System.Windows.Forms.DataGridView();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.BoardPicture = new System.Windows.Forms.PictureBox();
            this.SearchItem = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.img_connect)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lable_logo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lst_devies)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LST_TEST)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BoardPicture)).BeginInit();
            this.SuspendLayout();
            // 
            // BAR_Proccess
            // 
            this.BAR_Proccess.Location = new System.Drawing.Point(135, 515);
            this.BAR_Proccess.Margin = new System.Windows.Forms.Padding(4);
            this.BAR_Proccess.Name = "BAR_Proccess";
            this.BAR_Proccess.Size = new System.Drawing.Size(1109, 29);
            this.BAR_Proccess.Step = 1;
            this.BAR_Proccess.TabIndex = 22;
            // 
            // lable_version
            // 
            this.lable_version.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.lable_version.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.lable_version.Location = new System.Drawing.Point(12, 520);
            this.lable_version.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lable_version.Name = "lable_version";
            this.lable_version.Size = new System.Drawing.Size(120, 26);
            this.lable_version.TabIndex = 142;
            this.lable_version.Text = "v20.14020224";
            this.lable_version.Click += new System.EventHandler(this.lable_version_Click);
            // 
            // txt_explanation
            // 
            this.txt_explanation.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.txt_explanation.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.txt_explanation.Location = new System.Drawing.Point(663, 317);
            this.txt_explanation.Multiline = true;
            this.txt_explanation.Name = "txt_explanation";
            this.txt_explanation.ReadOnly = true;
            this.txt_explanation.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.txt_explanation.Size = new System.Drawing.Size(362, 146);
            this.txt_explanation.TabIndex = 155;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.En_Next);
            this.groupBox1.Controls.Add(this.En_Loop);
            this.groupBox1.Controls.Add(this.replay);
            this.groupBox1.Controls.Add(this.next);
            this.groupBox1.Controls.Add(this.img_connect);
            this.groupBox1.Controls.Add(this.restart);
            this.groupBox1.ForeColor = System.Drawing.Color.Black;
            this.groupBox1.Location = new System.Drawing.Point(663, 140);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(362, 179);
            this.groupBox1.TabIndex = 162;
            this.groupBox1.TabStop = false;
            // 
            // En_Next
            // 
            this.En_Next.AutoSize = true;
            this.En_Next.Location = new System.Drawing.Point(343, 140);
            this.En_Next.Name = "En_Next";
            this.En_Next.Size = new System.Drawing.Size(15, 14);
            this.En_Next.TabIndex = 167;
            this.En_Next.UseVisualStyleBackColor = true;
            this.En_Next.Visible = false;
            // 
            // En_Loop
            // 
            this.En_Loop.AutoSize = true;
            this.En_Loop.Location = new System.Drawing.Point(343, 72);
            this.En_Loop.Name = "En_Loop";
            this.En_Loop.Size = new System.Drawing.Size(15, 14);
            this.En_Loop.TabIndex = 166;
            this.En_Loop.UseVisualStyleBackColor = true;
            // 
            // replay
            // 
            this.replay.Image = ((System.Drawing.Image)(resources.GetObject("replay.Image")));
            this.replay.Location = new System.Drawing.Point(297, 25);
            this.replay.Name = "replay";
            this.replay.Size = new System.Drawing.Size(61, 62);
            this.replay.TabIndex = 165;
            this.replay.UseVisualStyleBackColor = true;
            this.replay.Click += new System.EventHandler(this.replay_Click);
            // 
            // next
            // 
            this.next.Enabled = false;
            this.next.Image = global::TEST_BENCH.Properties.Resources.next;
            this.next.Location = new System.Drawing.Point(297, 92);
            this.next.Name = "next";
            this.next.Size = new System.Drawing.Size(61, 62);
            this.next.TabIndex = 164;
            this.next.UseVisualStyleBackColor = true;
            this.next.Visible = false;
            this.next.Click += new System.EventHandler(this.next_Click);
            // 
            // img_connect
            // 
            this.img_connect.Image = ((System.Drawing.Image)(resources.GetObject("img_connect.Image")));
            this.img_connect.Location = new System.Drawing.Point(7, 25);
            this.img_connect.Margin = new System.Windows.Forms.Padding(4);
            this.img_connect.Name = "img_connect";
            this.img_connect.Size = new System.Drawing.Size(132, 132);
            this.img_connect.TabIndex = 163;
            this.img_connect.TabStop = false;
            // 
            // restart
            // 
            this.restart.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.restart.Cursor = System.Windows.Forms.Cursors.Hand;
            this.restart.Image = ((System.Drawing.Image)(resources.GetObject("restart.Image")));
            this.restart.Location = new System.Drawing.Point(157, 25);
            this.restart.Margin = new System.Windows.Forms.Padding(4);
            this.restart.Name = "restart";
            this.restart.Size = new System.Drawing.Size(133, 130);
            this.restart.TabIndex = 162;
            this.restart.UseVisualStyleBackColor = true;
            this.restart.Click += new System.EventHandler(this.restart_Click);
            // 
            // txt_state
            // 
            this.txt_state.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.txt_state.AllowDrop = true;
            this.txt_state.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.txt_state.AutoEllipsis = true;
            this.txt_state.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.txt_state.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.txt_state.Location = new System.Drawing.Point(663, 113);
            this.txt_state.Name = "txt_state";
            this.txt_state.Size = new System.Drawing.Size(582, 31);
            this.txt_state.TabIndex = 163;
            this.txt_state.Text = "در حال جستجو پورت ارتباطی";
            this.txt_state.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.txt_state.UseCompatibleTextRendering = true;
            // 
            // lable_logo
            // 
            this.lable_logo.Image = ((System.Drawing.Image)(resources.GetObject("lable_logo.Image")));
            this.lable_logo.Location = new System.Drawing.Point(1017, 8);
            this.lable_logo.Margin = new System.Windows.Forms.Padding(4);
            this.lable_logo.Name = "lable_logo";
            this.lable_logo.Size = new System.Drawing.Size(229, 82);
            this.lable_logo.TabIndex = 150;
            this.lable_logo.TabStop = false;
            this.lable_logo.Click += new System.EventHandler(this.lable_logo_Click);
            // 
            // lbl_view_timeout
            // 
            this.lbl_view_timeout.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.lbl_view_timeout.AllowDrop = true;
            this.lbl_view_timeout.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbl_view_timeout.AutoEllipsis = true;
            this.lbl_view_timeout.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lbl_view_timeout.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.lbl_view_timeout.Location = new System.Drawing.Point(663, 465);
            this.lbl_view_timeout.Name = "lbl_view_timeout";
            this.lbl_view_timeout.Size = new System.Drawing.Size(581, 31);
            this.lbl_view_timeout.TabIndex = 164;
            this.lbl_view_timeout.Text = "زمان باقیمانده";
            this.lbl_view_timeout.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.lbl_view_timeout.UseCompatibleTextRendering = true;
            // 
            // label2
            // 
            this.label2.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.label2.AllowDrop = true;
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label2.AutoEllipsis = true;
            this.label2.BackColor = System.Drawing.Color.White;
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label2.Location = new System.Drawing.Point(1027, 147);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(217, 28);
            this.label2.TabIndex = 166;
            this.label2.Text = "سخت افزار های تست شونده";
            this.label2.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.label2.UseCompatibleTextRendering = true;
            // 
            // label_device_info
            // 
            this.label_device_info.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.label_device_info.AllowDrop = true;
            this.label_device_info.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label_device_info.AutoEllipsis = true;
            this.label_device_info.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.label_device_info.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label_device_info.Font = new System.Drawing.Font("Microsoft Sans Serif", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label_device_info.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.label_device_info.Location = new System.Drawing.Point(663, 38);
            this.label_device_info.Name = "label_device_info";
            this.label_device_info.Size = new System.Drawing.Size(346, 51);
            this.label_device_info.TabIndex = 167;
            this.label_device_info.Text = "شماره سریال سخت افزار";
            this.label_device_info.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label_device_info.UseCompatibleTextRendering = true;
            // 
            // label1
            // 
            this.label1.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.label1.AllowDrop = true;
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoEllipsis = true;
            this.label1.BackColor = System.Drawing.Color.White;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.label1.Location = new System.Drawing.Point(663, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(346, 28);
            this.label1.TabIndex = 168;
            this.label1.Text = "شماره سریال سخت افزار مورد تست";
            this.label1.TextAlign = System.Drawing.ContentAlignment.BottomCenter;
            this.label1.UseCompatibleTextRendering = true;
            // 
            // lst_devies
            // 
            this.lst_devies.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.lst_devies.Cursor = System.Windows.Forms.Cursors.Default;
            this.lst_devies.Location = new System.Drawing.Point(1027, 198);
            this.lst_devies.MultiSelect = false;
            this.lst_devies.Name = "lst_devies";
            this.lst_devies.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.lst_devies.Size = new System.Drawing.Size(217, 264);
            this.lst_devies.TabIndex = 169;
            this.lst_devies.MouseClick += new System.Windows.Forms.MouseEventHandler(this.lst_devies_CellContentClick);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.ImeMode = System.Windows.Forms.ImeMode.Hiragana;
            this.tabControl1.Location = new System.Drawing.Point(10, 10);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.tabControl1.RightToLeftLayout = true;
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(647, 486);
            this.tabControl1.TabIndex = 190;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.LST_TEST);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(639, 460);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "مراحل انجام تست";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // LST_TEST
            // 
            this.LST_TEST.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.LST_TEST.Cursor = System.Windows.Forms.Cursors.Default;
            this.LST_TEST.Location = new System.Drawing.Point(0, 0);
            this.LST_TEST.MultiSelect = false;
            this.LST_TEST.Name = "LST_TEST";
            this.LST_TEST.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.LST_TEST.Size = new System.Drawing.Size(639, 460);
            this.LST_TEST.TabIndex = 155;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.BoardPicture);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(639, 460);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "نمای برد تست";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // BoardPicture
            // 
            this.BoardPicture.Location = new System.Drawing.Point(6, 8);
            this.BoardPicture.Name = "BoardPicture";
            this.BoardPicture.Size = new System.Drawing.Size(627, 446);
            this.BoardPicture.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.BoardPicture.TabIndex = 0;
            this.BoardPicture.TabStop = false;
            // 
            // SearchItem
            // 
            this.SearchItem.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.SearchItem.Location = new System.Drawing.Point(1027, 178);
            this.SearchItem.Name = "SearchItem";
            this.SearchItem.Size = new System.Drawing.Size(218, 24);
            this.SearchItem.TabIndex = 191;
            this.SearchItem.TextChanged += new System.EventHandler(this.SearchItem_TextChanged);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ClientSize = new System.Drawing.Size(1257, 551);
            this.Controls.Add(this.SearchItem);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.lst_devies);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label_device_info);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lbl_view_timeout);
            this.Controls.Add(this.txt_state);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.txt_explanation);
            this.Controls.Add(this.lable_logo);
            this.Controls.Add(this.lable_version);
            this.Controls.Add(this.BAR_Proccess);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(178)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "none";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form_KeyDown);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.img_connect)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lable_logo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lst_devies)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.LST_TEST)).EndInit();
            this.tabPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.BoardPicture)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.ProgressBar BAR_Proccess;
        public System.Windows.Forms.Label lable_version;
        public System.Windows.Forms.PictureBox lable_logo;
        public System.Windows.Forms.TextBox txt_explanation;
        private System.Windows.Forms.GroupBox groupBox1;
        public System.Windows.Forms.CheckBox En_Next;
        public System.Windows.Forms.CheckBox En_Loop;
        public System.Windows.Forms.Button replay;
        public System.Windows.Forms.Button next;
        public System.Windows.Forms.PictureBox img_connect;
        public System.Windows.Forms.Button restart;
        public System.Windows.Forms.Label txt_state;
        public System.Windows.Forms.Label lbl_view_timeout;
        public System.Windows.Forms.Label label2;
        public System.Windows.Forms.Label label_device_info;
        public System.Windows.Forms.Label label1;
        public System.Windows.Forms.DataGridView lst_devies;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        public System.Windows.Forms.DataGridView LST_TEST;
        private System.Windows.Forms.TabPage tabPage2;
        public System.Windows.Forms.PictureBox BoardPicture;
        private System.Windows.Forms.TextBox SearchItem;

    }
}


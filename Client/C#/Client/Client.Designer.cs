namespace Client
{
    partial class Client
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
            this.IPLabel = new System.Windows.Forms.Label();
            this.PortLabel = new System.Windows.Forms.Label();
            this.SendButton = new System.Windows.Forms.Button();
            this.DisconnectButton = new System.Windows.Forms.Button();
            this.SendTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.IPValue = new System.Windows.Forms.Label();
            this.PortValue = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.GroupComboBox = new System.Windows.Forms.ComboBox();
            this.LeaveGroupButton = new System.Windows.Forms.Button();
            this.DeleteGroupButton = new System.Windows.Forms.Button();
            this.GroupTextBox = new System.Windows.Forms.TextBox();
            this.CreateGroupButton = new System.Windows.Forms.Button();
            this.JoinGroupButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.UsernameLabel = new System.Windows.Forms.Label();
            this.ChatTextBox = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // IPLabel
            // 
            this.IPLabel.AutoSize = true;
            this.IPLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.IPLabel.Location = new System.Drawing.Point(35, 132);
            this.IPLabel.Name = "IPLabel";
            this.IPLabel.Size = new System.Drawing.Size(28, 18);
            this.IPLabel.TabIndex = 0;
            this.IPLabel.Text = "IP:";
            // 
            // PortLabel
            // 
            this.PortLabel.AutoSize = true;
            this.PortLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.PortLabel.Location = new System.Drawing.Point(35, 158);
            this.PortLabel.Name = "PortLabel";
            this.PortLabel.Size = new System.Drawing.Size(45, 18);
            this.PortLabel.TabIndex = 1;
            this.PortLabel.Text = "Port:";
            // 
            // SendButton
            // 
            this.SendButton.BackColor = System.Drawing.Color.White;
            this.SendButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.SendButton.ForeColor = System.Drawing.Color.LimeGreen;
            this.SendButton.Location = new System.Drawing.Point(562, 312);
            this.SendButton.Name = "SendButton";
            this.SendButton.Size = new System.Drawing.Size(104, 43);
            this.SendButton.TabIndex = 2;
            this.SendButton.Text = "Send";
            this.SendButton.UseVisualStyleBackColor = false;
            this.SendButton.Click += new System.EventHandler(this.SendButton_Click);
            // 
            // DisconnectButton
            // 
            this.DisconnectButton.BackColor = System.Drawing.Color.White;
            this.DisconnectButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.DisconnectButton.ForeColor = System.Drawing.Color.Red;
            this.DisconnectButton.Location = new System.Drawing.Point(65, 195);
            this.DisconnectButton.Name = "DisconnectButton";
            this.DisconnectButton.Size = new System.Drawing.Size(123, 47);
            this.DisconnectButton.TabIndex = 3;
            this.DisconnectButton.Text = "Disconnect";
            this.DisconnectButton.UseVisualStyleBackColor = false;
            this.DisconnectButton.Click += new System.EventHandler(this.DisconnectButton_Click);
            // 
            // SendTextBox
            // 
            this.SendTextBox.Location = new System.Drawing.Point(267, 323);
            this.SendTextBox.Multiline = true;
            this.SendTextBox.Name = "SendTextBox";
            this.SendTextBox.Size = new System.Drawing.Size(278, 32);
            this.SendTextBox.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label1.Location = new System.Drawing.Point(34, 96);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(141, 24);
            this.label1.TabIndex = 7;
            this.label1.Text = "Connected to:";
            // 
            // IPValue
            // 
            this.IPValue.AutoSize = true;
            this.IPValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.IPValue.Location = new System.Drawing.Point(85, 132);
            this.IPValue.Name = "IPValue";
            this.IPValue.Size = new System.Drawing.Size(46, 18);
            this.IPValue.TabIndex = 8;
            this.IPValue.Text = "label2";
            // 
            // PortValue
            // 
            this.PortValue.AutoSize = true;
            this.PortValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.PortValue.Location = new System.Drawing.Point(85, 158);
            this.PortValue.Name = "PortValue";
            this.PortValue.Size = new System.Drawing.Size(46, 18);
            this.PortValue.TabIndex = 9;
            this.PortValue.Text = "label3";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label2.Location = new System.Drawing.Point(263, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 22);
            this.label2.TabIndex = 10;
            this.label2.Text = "Group:";
            // 
            // GroupComboBox
            // 
            this.GroupComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.GroupComboBox.FormattingEnabled = true;
            this.GroupComboBox.Location = new System.Drawing.Point(340, 33);
            this.GroupComboBox.Name = "GroupComboBox";
            this.GroupComboBox.Size = new System.Drawing.Size(144, 21);
            this.GroupComboBox.TabIndex = 11;
            // 
            // LeaveGroupButton
            // 
            this.LeaveGroupButton.BackColor = System.Drawing.Color.White;
            this.LeaveGroupButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.LeaveGroupButton.ForeColor = System.Drawing.Color.Black;
            this.LeaveGroupButton.Location = new System.Drawing.Point(490, 29);
            this.LeaveGroupButton.Name = "LeaveGroupButton";
            this.LeaveGroupButton.Size = new System.Drawing.Size(81, 35);
            this.LeaveGroupButton.TabIndex = 12;
            this.LeaveGroupButton.Text = "Leave";
            this.LeaveGroupButton.UseVisualStyleBackColor = false;
            this.LeaveGroupButton.Click += new System.EventHandler(this.LeaveGroupButton_Click);
            // 
            // DeleteGroupButton
            // 
            this.DeleteGroupButton.BackColor = System.Drawing.Color.White;
            this.DeleteGroupButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.DeleteGroupButton.ForeColor = System.Drawing.Color.Firebrick;
            this.DeleteGroupButton.Location = new System.Drawing.Point(577, 29);
            this.DeleteGroupButton.Name = "DeleteGroupButton";
            this.DeleteGroupButton.Size = new System.Drawing.Size(89, 35);
            this.DeleteGroupButton.TabIndex = 13;
            this.DeleteGroupButton.Text = "Delete";
            this.DeleteGroupButton.UseVisualStyleBackColor = false;
            this.DeleteGroupButton.Click += new System.EventHandler(this.DeleteGroupButton_Click);
            // 
            // GroupTextBox
            // 
            this.GroupTextBox.Location = new System.Drawing.Point(39, 267);
            this.GroupTextBox.Name = "GroupTextBox";
            this.GroupTextBox.Size = new System.Drawing.Size(167, 20);
            this.GroupTextBox.TabIndex = 14;
            // 
            // CreateGroupButton
            // 
            this.CreateGroupButton.BackColor = System.Drawing.Color.White;
            this.CreateGroupButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.CreateGroupButton.ForeColor = System.Drawing.Color.Green;
            this.CreateGroupButton.Location = new System.Drawing.Point(12, 294);
            this.CreateGroupButton.Name = "CreateGroupButton";
            this.CreateGroupButton.Size = new System.Drawing.Size(116, 43);
            this.CreateGroupButton.TabIndex = 15;
            this.CreateGroupButton.Text = "Create group";
            this.CreateGroupButton.UseVisualStyleBackColor = false;
            this.CreateGroupButton.Click += new System.EventHandler(this.CreateGroupButton_Click);
            // 
            // JoinGroupButton
            // 
            this.JoinGroupButton.BackColor = System.Drawing.Color.White;
            this.JoinGroupButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.JoinGroupButton.ForeColor = System.Drawing.Color.Blue;
            this.JoinGroupButton.Location = new System.Drawing.Point(134, 294);
            this.JoinGroupButton.Name = "JoinGroupButton";
            this.JoinGroupButton.Size = new System.Drawing.Size(106, 43);
            this.JoinGroupButton.TabIndex = 16;
            this.JoinGroupButton.Text = "Join request";
            this.JoinGroupButton.UseVisualStyleBackColor = false;
            this.JoinGroupButton.Click += new System.EventHandler(this.JoinGroupButton_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label3.Location = new System.Drawing.Point(12, 18);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(123, 17);
            this.label3.TabIndex = 17;
            this.label3.Text = "Your username:";
            // 
            // UsernameLabel
            // 
            this.UsernameLabel.AutoSize = true;
            this.UsernameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.UsernameLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.UsernameLabel.Location = new System.Drawing.Point(66, 51);
            this.UsernameLabel.Name = "UsernameLabel";
            this.UsernameLabel.Size = new System.Drawing.Size(109, 24);
            this.UsernameLabel.TabIndex = 18;
            this.UsernameLabel.Text = "user name";
            // 
            // ChatTextBox
            // 
            this.ChatTextBox.Location = new System.Drawing.Point(267, 70);
            this.ChatTextBox.Name = "ChatTextBox";
            this.ChatTextBox.ReadOnly = true;
            this.ChatTextBox.Size = new System.Drawing.Size(399, 236);
            this.ChatTextBox.TabIndex = 19;
            this.ChatTextBox.Text = "";
            // 
            // Client
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.ClientSize = new System.Drawing.Size(697, 377);
            this.Controls.Add(this.ChatTextBox);
            this.Controls.Add(this.UsernameLabel);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.JoinGroupButton);
            this.Controls.Add(this.CreateGroupButton);
            this.Controls.Add(this.GroupTextBox);
            this.Controls.Add(this.DeleteGroupButton);
            this.Controls.Add(this.LeaveGroupButton);
            this.Controls.Add(this.GroupComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.PortValue);
            this.Controls.Add(this.IPValue);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SendTextBox);
            this.Controls.Add(this.DisconnectButton);
            this.Controls.Add(this.SendButton);
            this.Controls.Add(this.PortLabel);
            this.Controls.Add(this.IPLabel);
            this.Name = "Client";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Client";
            this.Load += new System.EventHandler(this.Client_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label IPLabel;
        private System.Windows.Forms.Label PortLabel;
        private System.Windows.Forms.Button SendButton;
        private System.Windows.Forms.Button DisconnectButton;
        private System.Windows.Forms.TextBox SendTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label IPValue;
        private System.Windows.Forms.Label PortValue;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox GroupComboBox;
        private System.Windows.Forms.Button LeaveGroupButton;
        private System.Windows.Forms.Button DeleteGroupButton;
        private System.Windows.Forms.TextBox GroupTextBox;
        private System.Windows.Forms.Button CreateGroupButton;
        private System.Windows.Forms.Button JoinGroupButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label UsernameLabel;
        private System.Windows.Forms.RichTextBox ChatTextBox;
    }
}
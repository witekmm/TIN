using System;
using System.Windows.Forms;

namespace Client
{
    public partial class LoginForm : Form
    {
        private Client client;
        private String login;
        private String password;
        private Boolean logged;
        private int loginAttempts;

        public LoginForm(Client client)
        {
            InitializeComponent();
            FormClosing += Client_FormClosing;
            this.client = client;
            this.Show();
            loginAttempts = 0;
            logged = false;
            //tryLogin();
        }

        public Boolean LogedIn
        {
            get { return logged; }
        }

        private void tryLogin()
        {
            while (!logged)
            {
                if(loginAttempts == 5)
                {
                    this.Close();
                }
            }
        }

        private void Client_FormClosing(object sender, FormClosingEventArgs e)
        {
            client.ConnectionManager.Disconnect(true);
            MessageBox.Show("Disconnected", "Connection", MessageBoxButtons.OK, MessageBoxIcon.Information);
            client.ConnectForm.Enabled = true;
        }

        private void LoginForm_Load(object sender, EventArgs e)
        {

        }

        private void LoginButton_Click(object sender, EventArgs e)
        {

            login = LoginTextBox.Text;
            password = PasswordTextBox.Text;
            if (ValidateUser(login, password))
            {
                logged = true;
                this.Hide();
                client.ConnectionManager.ReceiveThread.Start();
                client.Show();
            }
            else
            {
                if (loginAttempts == 5)
                {
                    this.Close();
                }
                MessageBox.Show("Wrong data", "User not found ", MessageBoxButtons.OK, MessageBoxIcon.Information);
                loginAttempts++;
                return;
            }
        }
        private Boolean ValidateUser(string login, string password)
        {
            return client.ConnectionManager.CheckUser(login, password);
        }
    }
}

using System;
using System.Windows.Forms;

namespace Client
{
    public partial class LoginForm : Form
    {
        private Client client;
        private String login;
        private bool logged;
        private int loginAttempts;
        private const int MAX_LOGIN_ATTEMPTS = 5; 

        public LoginForm(Client client)
        {
            InitializeComponent();
            FormClosing += Login_FormClosing;
            loginAttempts = 0;
            logged = false;
            this.client = client;
            this.Show();
            client.ConnectionManager.ReceiveThread.Start();
        }

        public Boolean LogedIn
        {
            get { return logged; }
        }
        private void Login_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(logged == false)
            {
                client.ConnectionManager.Disconnect(true);
                MessageBox.Show("Disconnected", "Connection", MessageBoxButtons.OK, MessageBoxIcon.Information);
                client.ConnectForm.Show();
            }
        }
        private void LoginForm_Load(object sender, EventArgs e)
        {

        }
        private void LoginButton_Click(object sender, EventArgs e)
        {
            ValidateUser(LoginTextBox.Text, PasswordTextBox.Text);
        }
        private void ValidateUser(string login, string password)
        {
            client.ConnectionManager.CheckUser(login, password, this);
        }
        public void AcceptLogin()
        {
            logged = true;
            this.Close();
            client.Username.Text = login;
            client.Show();
        }
        public void RejectLogin(String errorMsg)
        {
            if (loginAttempts == MAX_LOGIN_ATTEMPTS)
            {
                MessageBox.Show("Disconnected", "Too many attempts failed! Disconnecting!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                this.Close();
            }
            MessageBox.Show("Wrong data", errorMsg, MessageBoxButtons.OK, MessageBoxIcon.Information);
            loginAttempts++;
            return;
        }

    }
}

using System;
using System.Net;
using System.Text;
using System.Windows.Forms;

namespace Client
{
    public partial class Client : Form
    {
        private readonly ConnectionManager connectionManager;
        private readonly ConnectForm connectForm;
        private readonly String Login;
        private readonly String password; 
        private byte[] buffer;

        public Client(ConnectForm _connectForm, IPAddress _IP, int _port, String _login, String _password)
        {
            InitializeComponent();
            this.FormClosing += Client_FormClosing;

            connectionManager = new ConnectionManager(_IP, _port, this);
            connectionManager.Connect();

            connectForm = _connectForm;
            IPValue.Text = _IP.ToString();
            PortValue.Text = _port.ToString();
            buffer = new byte[1024];
            Login = _login;
            password = _password;

        }

        public TextBox ChatText
        {
            get{ return ChatTextBox; }
        }

        private void Client_FormClosing(object sender, FormClosingEventArgs e)
        {
            connectionManager.Disconnect(true);
            MessageBox.Show("Disconnected", "Connection", MessageBoxButtons.OK, MessageBoxIcon.Information);
            connectForm.Enabled = true;
        }

        private void SendButton_Click(object sender, EventArgs e)
        {
            string message = SendTextBox.Text;
            buffer = Encoding.ASCII.GetBytes(message);

            connectionManager.Send(buffer);
            SendTextBox.Clear();
        }

        private void DisconnectButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private Boolean checkUser()
        {
            //connectionManager.Send();

            //connectionManager.Receive();
            //if()
            //return true;


            return false;
        }
    }
}

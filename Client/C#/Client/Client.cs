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
        private byte[] buffer;

        public Client(ConnectForm _connectForm, IPAddress _IP, int _port)
        {
            InitializeComponent();
            this.FormClosing += Client_FormClosing;

            connectionManager = new ConnectionManager(_IP, _port, this);
            connectionManager.Connect();

            connectForm = _connectForm;
            IPValue.Text = _IP.ToString();
            PortValue.Text = _port.ToString();
            buffer = new byte[1024];
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

      

        private void Client_Load(object sender, EventArgs e)
        {

        }

        public TextBox ChatText
        {
            get { return ChatTextBox; }
        }

        public ConnectForm ConnectForm
        {
            get { return connectForm; }
        }

        public ConnectionManager ConnectionManager
        {
            get { return connectionManager; }
        }
    } 
}

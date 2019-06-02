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

        public Client(ConnectForm _connectForm, IPAddress _IP, int _port)
        {
            InitializeComponent();
            this.FormClosing += Client_FormClosing;

            connectionManager = new ConnectionManager(_IP, _port, this);
            connectionManager.Connect();

            connectForm = _connectForm;
            IPValue.Text = _IP.ToString();
            PortValue.Text = _port.ToString();
        }

        private void Client_FormClosing(object sender, FormClosingEventArgs e)
        {
            connectionManager.Disconnect(true);
            MessageBox.Show("Disconnected", "Connection", MessageBoxButtons.OK, MessageBoxIcon.Information);
            connectForm.Enabled = true;
        }

        private void SendButton_Click(object sender, EventArgs e)
        {
            String message = SendTextBox.Text,
                    groupName = GroupComboBox.SelectedItem.ToString();

            connectionManager.SendMessage(message, groupName);
            SendTextBox.Clear();
        }

        private void DisconnectButton_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void CreateGroupButton_Click(object sender, EventArgs e)
        {
            String groupName = GroupTextBox.Text;
            GroupTextBox.Clear();
            connectionManager.GroupAction(ClientMessage.Types.groupActionTypes.Create, groupName);
        }

        private void JoinGroupButton_Click(object sender, EventArgs e)
        {
            String groupName = GroupTextBox.Text;
            GroupTextBox.Clear();
            connectionManager.GroupAction(ClientMessage.Types.groupActionTypes.Request, groupName);
        }

        private void LeaveGroupButton_Click(object sender, EventArgs e)
        {
            String groupName = GroupComboBox.SelectedItem.ToString();
            GroupTextBox.Clear();
            connectionManager.GroupAction(ClientMessage.Types.groupActionTypes.Leave, groupName);
        }
        private void DeleteGroupButton_Click(object sender, EventArgs e)
        {
            String groupName = GroupComboBox.SelectedItem.ToString();
            GroupTextBox.Clear();
            connectionManager.GroupAction(ClientMessage.Types.groupActionTypes.Delete, groupName);
        }
        private void Client_Load(object sender, EventArgs e)
        {

        }
        public Label Username
        {
            get { return UsernameLabel; }
        }
        public RichTextBox ChatText
        {
            get { return ChatTextBox; }
        }

        public ComboBox Groups
        {
            get { return GroupComboBox; }
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

using System;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace Client
{
    public partial class ConnectForm : Form
    {
        public ConnectForm()
        {
            InitializeComponent();
        }
        private void Button_Click(object sender, EventArgs e)
        {
            String serverAddress;
            int port;
            IPAddress serverIP;
            serverAddress = textBoxIP.Text;
            if (serverAddress == "test")
            {
                serverAddress = "169.254.203.113";
                serverIP = IPAddress.Parse(serverAddress);
                port = 50011;
            }
            else
            {
                try
                {
                    if (serverAddress == "localhost")
                    {
                        serverAddress = Connection.GetLocalIP();
                    }
                    serverIP = IPAddress.Parse(serverAddress);
                }
                catch (FormatException)
                {
                    MessageBox.Show("Invalid IP", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }

                try
                {
                    port = Int32.Parse(textBoxPort.Text);
                    if (port < 1024 || port > 65500)
                    {
                        throw new Exception();
                    }
                }
                catch (Exception)
                {
                    MessageBox.Show("Invalid port", "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
            }
            try
            {
                Client client = new Client(this, serverIP, port);
                this.Hide();
                LoginForm loginForm = new LoginForm(client);
            }
            catch(SocketException)
            {
                MessageBox.Show("Connection error. Couldn't connect to socket!", "Failed", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
            catch(Exception ex)
            {
                MessageBox.Show("Connection: " + ex.Message, "Info", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void ConnectForm_Load(object sender, EventArgs e)
        {

        }
    }
}

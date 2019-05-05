using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace Client
{
    class ConnectionManager
    {
        private readonly IPAddress IP;
        private readonly int port;
        private readonly Client client;
        private readonly Connection connection;
        private Thread receiveThread;
        private static Boolean connected;

        public ConnectionManager(IPAddress _IP, int _port, Client _client)
        {
            IP = _IP;
            port = _port;
            client = _client;
            connection = new Connection(IP, port);
            connected = false;
        }

        public void Disconnect(Boolean wasConnected)
        {
            try
            {
                connection.End(wasConnected);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Disconnect error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            connected = false;
        }

        public void Connect()
        {
            receiveThread = new Thread(ReceiveThreadMethod);
            try
            {
                int connResult = connection.Connect();
                if (connResult != 0)
                {
                    Disconnect(false);
                    if (connResult == -1)
                        throw new SocketException();
                    else if (connResult == -2)
                        throw new Exception("Canceled");
                }
                connected = true;
                receiveThread.Start();
            }
            catch(Exception ex)
            {
                throw ex;
            }
        }

        public void Send(byte[] buffer)
        {
            try
            {
                connection.Send(buffer);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Send error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void ReceiveThreadMethod()
        {
            byte[] buffer = new byte[1024];
            while (connected)
            {
                int received = connection.Receive(buffer);
                string message = Encoding.ASCII.GetString(buffer);
                
                if (received > 0)
                {
                    client.ChatText.AppendText(message);
                    client.ChatText.AppendText(Environment.NewLine);
                }

                if (!connection.IsConnected())
                {
                    MessageBox.Show("Connection to server lost. Closing client now!", "Connection error", 
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    client.Close();
                }
            }
        }
    }
}

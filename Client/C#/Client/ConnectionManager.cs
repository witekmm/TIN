using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using Google.Protobuf;

namespace Client
{
    public class ConnectionManager
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

        public Thread ReceiveThread
        {
            get { return receiveThread; }
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
                //receiveThread.Start();
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

        public byte[] Receive()
        {
            byte[] buffer = new byte[1024];
            try
            {
                connection.Receive(buffer);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Receive error: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            return buffer;
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
        public Boolean CheckUser(String _login, String _password)
        {
            ClientMessage user = new ClientMessage
            {
                Login = _login,
                Password = _password,
                AuthorizationType = 0,
                MessageType = 0
            };

            byte[] bytes = user.ToByteArray();
            Send(bytes);

            byte[] answer = null;
            do
            {
                answer = Receive();
            } while (answer.Length < 1);

                ClientMessage response = ClientMessage.Parser.ParseFrom(answer);
            if (response.Reply == 0) 
                return true;
            return false;
        }
    }
}

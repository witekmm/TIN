using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using Google.Protobuf;
using System.Collections.Generic;

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
                    receiveThread.Join();
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
                AuthorizationType = ClientMessage.Types.authorizationTypes.LogIn,
                MessageType = ClientMessage.Types.messageTypes.Authorization
            };

            byte[] msg = user.ToByteArray();
            int bytesToSend = msg.Length;

            byte[] empty = new byte[4];
            connection.Socket.Send(empty, 4, SocketFlags.None);
            while (bytesToSend != 0)
            {
                int sent = connection.Socket.Send(msg, bytesToSend, SocketFlags.None);
                if (sent != 0)
                    Console.WriteLine("Sent: " + sent);
                if(sent == -1)
                    Console.WriteLine("Cannot sent");

                bytesToSend -= sent;
                Console.WriteLine("Tosend: " + bytesToSend + " Sent: " + sent);
            }
            Console.WriteLine("Sent all");

            //byte[] bytes = new byte[4];
            //int size = connection.Socket.Send(bytes);
            ////Send(bytes);
            //Console.Write("size: " + size);
            //bytes = user.ToByteArray();
            //connection.Socket.Send(bytes);
            ////Send(bytes);
            //Console.Write("\nsize: " + size);
            byte[] answer = new byte[4];
            int received = connection.Socket.Receive(answer);
            int answerSize = BitConverter.ToInt32(answer, 0);
            Console.WriteLine("Size: " + answerSize);
            byte[] answerMsg = new byte[answerSize];
            String buffer = "";
            List<byte> list = new List<byte>();
            while (answerSize != 0)
            {
                received = connection.Socket.Receive(answerMsg, answerSize, SocketFlags.None);
                //buffer += answerMsg.ToString();
                foreach(byte i in answerMsg)
                {
                    list.Add(i);

                }
                Array.Clear(answerMsg, 0, answerMsg.Length);
                answerSize -= received;

            }
            Console.WriteLine("answer: " + list);
            //Console.WriteLine("boffer: " + buffer);

            //ClientMessage response = ClientMessage.Parser.ParseFrom(Encoding.ASCII.GetBytes(buffer));
            ClientMessage response = ClientMessage.Parser.ParseFrom(list.ToArray());
            if (response.MessageType != ClientMessage.Types.messageTypes.Reply)
                Console.WriteLine("cos nie alo");
            if (response.Reply == ClientMessage.Types.replyStatus.Positive) 
                return true;
            return false;
        }
    }
}

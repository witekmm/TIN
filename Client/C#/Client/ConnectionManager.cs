using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;
using System.Windows.Shell;
using Google.Protobuf;
using System.Collections.Generic;
using System.Drawing;

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
            connected = false;
            connection = new Connection(IP, port);
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
            }
            catch (Exception ex)
            {
                throw ex;
            }
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
        public void GroupAction(ClientMessage.Types.groupActionTypes type, String groupName)
        {
            Console.Write("type: " + type);
            ClientMessage msg = new ClientMessage
            {
                GroupActionType = type,
                MessageType = ClientMessage.Types.messageTypes.Group,
                GroupName = groupName
            };
            SerializeAndSend(msg);
        }
        public void SendMessage(String buffer, String groupName)
        {
            ClientMessage msg = new ClientMessage
            {
                GroupActionType = ClientMessage.Types.groupActionTypes.Message,
                MessageType = ClientMessage.Types.messageTypes.Group,
                MessageContent = buffer,
                GroupName = groupName
            };
            SerializeAndSend(msg);
        }
        public void SendLoginRequest(String _login, String _password)
        {
            ClientMessage user = new ClientMessage
            {
                Login = _login,
                Password = _password,
                AuthorizationType = ClientMessage.Types.authorizationTypes.LogIn,
                MessageType = ClientMessage.Types.messageTypes.Authorization
            };
            SerializeAndSend(user);
        }
        private void SendReply()
        {
            ClientMessage msg = new ClientMessage
            {
                MessageType = ClientMessage.Types.messageTypes.Reply
            };
            SerializeAndSend(msg);
        }
        public void SerializeAndSend(ClientMessage msg)
        {
            byte[] serialized = msg.ToByteArray();
            int msgSize = serialized.Length;
            byte[] result = BitConverter.GetBytes(msgSize);

            byte[] send = new byte[result.Length + msgSize];
            System.Buffer.BlockCopy(result, 0, send, 0, result.Length);
            System.Buffer.BlockCopy(serialized, 0, send, result.Length, msgSize);
            Console.Write("send: " + send.Length);
            int bytesToSend = send.Length;
            while (bytesToSend != 0)
            {
                int sent = connection.Socket.Send(send, bytesToSend, SocketFlags.None);
                bytesToSend -= sent;
            }
        }
        private void ReceiveThreadMethod()
        {
            while (connected)
            {
                int received;
                byte[] answer = new byte[4];
                received = connection.Receive(answer, 0, 4);

                int answerSize = BitConverter.ToInt32(answer, 0);
                byte[] answerMsg = new byte[answerSize];

                List<byte> list = new List<byte>();
                while (answerSize != 0)
                {
                    received = connection.Socket.Receive(answerMsg, answerSize, SocketFlags.None);
                    foreach (byte i in answerMsg)
                    {
                        list.Add(i);
                    }
                    Array.Clear(answerMsg, 0, answerMsg.Length);
                    answerSize -= received;
                }
                ClientMessage response = ClientMessage.Parser.ParseFrom(list.ToArray());

                if (received > 0)
                {
                    HandleResponse(response);
                }

                if (!connection.IsConnected())
                {
                    MessageBox.Show("Connection to server lost. Closing client now!", "Connection error",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    //receiveThread.Join();
                    client.Close();
                }
            }
        }
        private void HandleResponse(ClientMessage response)
        {
            if (response.MessageContent.Length != 0)
            {
                client.ChatText.SelectionColor = Color.Black;
                client.ChatText.AppendText(response.UserName + ": " + response.MessageContent + Environment.NewLine);
            }
            if (response.ReplyContent.Length != 0)
            {
                client.ChatText.SelectionColor = Color.Red;
                client.ChatText.AppendText("Error: " + response.ReplyContent + Environment.NewLine);
            }
            if (response.Reply == ClientMessage.Types.replyStatus.Positive)
            {
                GroupReply(response, response.GroupActionType);
            }
            if (response.Reply == ClientMessage.Types.replyStatus.Negative)
            {
                if(response.GroupName.Length != 0)
                    GroupReply(response, response.GroupActionType);
            }
            if (response.GroupActionType == ClientMessage.Types.groupActionTypes.Request)
            {
                CreateJoinGroupAlert(response.UserName, response.GroupName);
            }

            if (response.GroupActionType == ClientMessage.Types.groupActionTypes.Accept)
            {
                GroupReply(response, response.GroupActionType);
            }

            if (response.MessageType != ClientMessage.Types.messageTypes.Reply)
            {
                SendReply();
            }
        }
        private void GroupReply(ClientMessage response, ClientMessage.Types.groupActionTypes reply)
        {
            switch (reply)
            {
                case ClientMessage.Types.groupActionTypes.Create:
                    {
                        client.ChatText.SelectionColor = Color.Green;
                        client.ChatText.AppendText("Group: '" + response.GroupName + "' created!" + Environment.NewLine);
                        client.Groups.Items.Add(response.GroupName);
                        break;
                    }
                case ClientMessage.Types.groupActionTypes.Delete:
                    {
                        client.ChatText.SelectionColor = Color.Green;
                        client.ChatText.AppendText("Group: '" + response.GroupName + "' deleted!" + Environment.NewLine);
                        client.Groups.Items.Remove(response.GroupName);
                        break;
                    }
                case ClientMessage.Types.groupActionTypes.Leave:
                    {
                        client.ChatText.SelectionColor = Color.Blue;
                        client.ChatText.AppendText("Group: '" + response.GroupName + "' left!" + Environment.NewLine);
                        client.Groups.Items.Remove(response.GroupName);
                        break;
                    }
                case ClientMessage.Types.groupActionTypes.Accept:
                    {
                        client.ChatText.SelectionColor = Color.Green;
                        client.ChatText.AppendText("Request accepted. Joined group: " + response.GroupName + Environment.NewLine);
                        client.Groups.Items.Add(response.GroupName);
                        break;
                    }   
                case ClientMessage.Types.groupActionTypes.Message:
                    {
                        client.Groups.Items.Remove(response.GroupName);
                        break;
                    }
            }
        }
        private void CreateJoinGroupAlert(String username, String groupName)
        {
            MethodInvoker methodInvokerDelegate = delegate ()
            {
                ClientMessage.Types.groupActionTypes type = ClientMessage.Types.groupActionTypes.Decline;
                DialogResult dialog = MessageBox.Show("User: " + username + " wants to join group: " + groupName + "\nAccpet?", "Join request", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
                if (dialog == DialogResult.Yes)
                {
                    type = ClientMessage.Types.groupActionTypes.Accept;
                }
                ClientMessage msg = new ClientMessage
                {
                    MessageType = ClientMessage.Types.messageTypes.Group,
                    GroupActionType = type,
                    UserName = username,
                    GroupName = groupName
                };
                SerializeAndSend(msg);
            };
        }
        public Boolean CheckUser(String _login, String _password)
        {
            SendLoginRequest(_login, _password);

            byte[] answer = new byte[4];
            int received = connection.Receive(answer, 0, 4);

            int answerSize = BitConverter.ToInt32(answer, 0);
            byte[] answerMsg = new byte[answerSize];
            List<byte> list = new List<byte>();
            while (answerSize != 0)
            {
                received = connection.Socket.Receive(answerMsg, answerSize, SocketFlags.None);
                foreach(byte i in answerMsg)
                {
                    list.Add(i);
                }
                Array.Clear(answerMsg, 0, answerMsg.Length);
                answerSize -= received;
            }
            ClientMessage response = ClientMessage.Parser.ParseFrom(list.ToArray());
            foreach(String g in response.Groups)
            {
                client.Groups.Items.Add(g);
            }
            return response.Reply == ClientMessage.Types.replyStatus.Positive;
        }
        public Thread ReceiveThread
        {
            get { return receiveThread; }
        }
    }
    
}

using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Windows.Forms;
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
        private LoginForm loginForm;
        private Thread receiveThread;
        private static bool connected;
        private bool serverConnection;

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
                    if (connResult == -1) // max connections reached, couldn't connect
                        throw new SocketException();
                    else if (connResult == -2)
                        throw new Exception("Canceled");
                }
                connected = serverConnection = true;
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
            connected = serverConnection = false;
        }
        public void GroupAction(ClientMessage.Types.groupActionTypes type, String groupName)
        {
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

            byte[] message = new byte[result.Length + msgSize];
            Buffer.BlockCopy(result, 0, message, 0, result.Length);
            Buffer.BlockCopy(serialized, 0, message, result.Length, msgSize);
            int bytesToSend = message.Length;
            while (bytesToSend != 0)
            {
                int sent = connection.Socket.Send(message, bytesToSend, SocketFlags.None);
                bytesToSend -= sent;
            }
        }
        private void ReceiveThreadMethod()
        {
             while (connected)
            {
                int received = 0, toRead = 4, bytesRead = 0;
                byte[] answer = new byte[4];
                List<byte> answerFull = new List<byte>();
                while (toRead != 0)
                {
                    if ((received = connection.Receive(answer, 0, toRead)) == -1)
                        break;
                    toRead -= received;
                }
                if (received == -1) break;
                int answerSize = BitConverter.ToInt32(answer, 0);
                byte[] answerMsg = new byte[answerSize];

                List<byte> list = new List<byte>();
                while (answerSize != 0)
                {
                    if((received = connection.Receive(answerMsg, 0, answerSize)) == -1)
                        break;
                    foreach (byte i in answerMsg)
                    {
                        list.Add(i);
                    }
                    Array.Clear(answerMsg, 0, answerMsg.Length);
                    answerSize -= received;
                    bytesRead += received;
                }
                if (received == -1) break;
                ClientMessage response = ClientMessage.Parser.ParseFrom(list.ToArray());
                if (bytesRead > 0)
                {
                    HandleResponse(response);
                }
            }
            SendNoConnection();
        }
        private void SendNoConnection()
        {
            if (serverConnection)
            {
                client.Invoke((MethodInvoker)delegate
                {
                    MessageBox.Show("Connection to server lost. Closing client now!", "Connection error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    client.Close();
                });
            }
        }
        private void LoginUser(Boolean correctData, ClientMessage response)
        {
            loginForm.Invoke((MethodInvoker)delegate
                {
                    if (correctData) {
                        InitializeGroups(response);
                        loginForm.AcceptLogin();
                    }
                    else
                    {
                        loginForm.RejectLogin(response.ReplyContent);
                    }
                }
            );
        }
        private void InitializeGroups(ClientMessage respone)
        {
            foreach (String group in respone.Groups)
            {
                client.Groups.Items.Add(group);
            }
        }

        private void HandleResponse(ClientMessage response)
        {
            if (response.Reply == ClientMessage.Types.replyStatus.Positive)
            {
                if (response.AuthorizationType == ClientMessage.Types.authorizationTypes.LogIn)
                    LoginUser(true, response);
                else if (response.GroupActionType != ClientMessage.Types.groupActionTypes.Nogrouptype)
                    GroupReply(response.GroupName, response.GroupActionType);
            }
            else if (response.Reply == ClientMessage.Types.replyStatus.Negative)
            {
                if(response.GroupName.Length != 0 && response.ReplyContent.Length != 0 
                    && response.MessageType == ClientMessage.Types.messageTypes.Reply)
                        GroupReply(response.GroupName, ClientMessage.Types.groupActionTypes.Message);
                if (response.AuthorizationType == ClientMessage.Types.authorizationTypes.LogIn)
                    LoginUser(false, response);
            }
            if (response.MessageType == ClientMessage.Types.messageTypes.Group)
            {
                if (response.GroupActionType == ClientMessage.Types.groupActionTypes.Request)
                    CreateJoinGroupAlert(response.UserName, response.GroupName);
                else if (response.GroupActionType == ClientMessage.Types.groupActionTypes.Accept)
                    GroupReply(response.GroupName, response.GroupActionType);
                else if (response.GroupActionType == ClientMessage.Types.groupActionTypes.Decline)
                    GroupReply(response.GroupName, response.GroupActionType);
            }
            if (response.MessageType != ClientMessage.Types.messageTypes.Reply)
            {
                SendReply();
            }
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
        }
        private void GroupReply(String groupName, ClientMessage.Types.groupActionTypes reply)
        {
            client.Invoke((MethodInvoker)delegate
            {
                switch (reply)
                {
                    case ClientMessage.Types.groupActionTypes.Create:
                        {
                            client.ChatText.SelectionColor = Color.Green;
                            client.ChatText.AppendText("Group: '" + groupName + "' created!" + Environment.NewLine);
                            client.Groups.Items.Add(groupName);
                            break;
                        }
                    case ClientMessage.Types.groupActionTypes.Delete:
                        {
                            client.ChatText.SelectionColor = Color.Green;
                            client.ChatText.AppendText("Group: '" + groupName + "' deleted!" + Environment.NewLine);
                            client.Groups.Items.Remove(groupName);
                            break;
                        }
                    case ClientMessage.Types.groupActionTypes.Leave:
                        {
                            client.ChatText.SelectionColor = Color.Blue;
                            client.ChatText.AppendText("Group: '" + groupName + "' left!" + Environment.NewLine);
                            client.Groups.Items.Remove(groupName);
                            break;
                        }
                    case ClientMessage.Types.groupActionTypes.Accept:
                        {
                            client.ChatText.SelectionColor = Color.Green;
                            client.ChatText.AppendText("Request accepted. Joined group: " + groupName + Environment.NewLine);
                            client.Groups.Items.Add(groupName);
                            break;
                        }
                    case ClientMessage.Types.groupActionTypes.Decline:
                        {
                            client.ChatText.SelectionColor = Color.Red;
                            client.ChatText.AppendText("Request to join group: " + groupName + " rejected!" + Environment.NewLine);
                            break;
                        }
                    case ClientMessage.Types.groupActionTypes.Request:
                        {
                            client.ChatText.SelectionColor = Color.Blue;
                            client.ChatText.AppendText("Request to join group: '" + groupName + "' send!" + Environment.NewLine);
                            break;
                        }
                    case ClientMessage.Types.groupActionTypes.Message:
                        {
                            client.Groups.Items.Remove(groupName);
                            break;
                        }
                }
            }
            );
        }
        private void CreateJoinGroupAlert(String username, String groupName)
        {
            client.Invoke((MethodInvoker)delegate
            {
                ClientMessage.Types.groupActionTypes type = ClientMessage.Types.groupActionTypes.Decline;
                DialogResult dialog = MessageBox.Show("User: '" + username + "' wants to join group: '" + groupName + "'\nAccept?", "Join request", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
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
            });
        }
        public void CheckUser(String _login, String _password, LoginForm loginForm)
        {
            SendLoginRequest(_login, _password);
            this.loginForm = loginForm;       
        }
        public Thread ReceiveThread
        {
            get { return receiveThread; }
        }
    }
    
}

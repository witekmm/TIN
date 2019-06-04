using System;
using System.Net;
using System.Net.Sockets;
using System.Windows.Forms;

namespace Client
{
    class Connection
    {
        private const int MAX_ATTEMPTS = 5;
        private readonly Socket socket;
        private readonly IPEndPoint endPoint;
        public Socket Socket
        {
            get { return socket; }
        }

        public Connection(IPAddress _IP, int _port)
        {
            endPoint = new IPEndPoint(_IP, _port);
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); 
        }

        public int Connect()
        {
            int attempts = 0;
            while (!socket.Connected)
            {
                try
                {
                    attempts++;
                    socket.Connect(endPoint);
                }
                catch(SocketException ex)
                {
                    DialogResult dialog = MessageBox.Show("Connection error: " + ex.Message + 
                        "\nAttempts: " + attempts, "Connection attempt", MessageBoxButtons.RetryCancel, MessageBoxIcon.Information);
                    if(dialog == DialogResult.Cancel)
                    {
                        return -2;
                    }
                }

                if(attempts == MAX_ATTEMPTS)
                {
                    return -1;  
                }
            }
            return 0;
        }

        public void End(Boolean wasConnected)
        {
            if(wasConnected)
                socket.Shutdown(SocketShutdown.Both);
            socket.Close();
        }

        public void Send(byte[] buffer)
        {
            socket.Send(buffer);
        }

        public int Receive(byte[] buffer, int offset, int length)
        {
            if (!IsConnected())
            {
                return -1;
            }
            try
            {
                return socket.Receive(buffer, offset, length, SocketFlags.None);
            }
            catch (SocketException)
            {
                return -1;
            }
        }

        public Boolean IsConnected()
        {
            bool part1 = socket.Poll(1000, SelectMode.SelectRead);
            bool part2 = (socket.Available == 0);
            if (part1 && part2)
                return false;
            else
                return true;
        }

        public static string GetLocalIP()
        {
            IPHostEntry host;
            string localIP = "*";

            host = Dns.GetHostEntry(Dns.GetHostName());
            foreach(IPAddress IP in host.AddressList)
            {
                if(IP.AddressFamily == AddressFamily.InterNetwork)
                {
                    localIP = IP.ToString();
                }
            }
            return localIP;
        }
    }
}

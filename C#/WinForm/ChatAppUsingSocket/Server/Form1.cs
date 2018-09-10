using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Net.Sockets;
using System.Net;

namespace Server
{
    public partial class Form1 : Form
    {
        Socket server;
        IPEndPoint ipEndPoint;
        List<Socket> listClient;
        IPAddress myIP; //Use string instead
        Thread clientOperation;

        public Form1()
        {
            CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();
            this.listClient = new List<Socket>();
        }

        public void getIP()
        {
            //Lấy ip
            IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());

            foreach(IPAddress addr in host.AddressList)
            {
                if(addr.AddressFamily == AddressFamily.InterNetwork)
                {
                    myIP = addr;
                }
            }

            //Thiết lập IPEndPoint và socket chính của server
            ipEndPoint = new IPEndPoint(myIP, 2001);
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            MessageBox.Show("My IP: " + myIP.ToString());
        }


        public void listen()
        {
            //Kết nối socket den IPE
            server.Bind(ipEndPoint);
            server.Listen(3); //accept 3 client in the same time, but the client it served is unlimited.

            while(true)
            {
                Socket sk = server.Accept();

                if(sk != null)
                {
                    listClient.Add(sk);

                    Thread clientProcess = new Thread(myClientThread);
                    clientProcess.IsBackground = true;
                    clientProcess.Start(sk);

                    //
                    rtbMain.SelectionFont = new Font("Arial", 16, FontStyle.Bold);
                    rtbMain.SelectionColor = Color.Green;
                    rtbMain.AppendText("Chấp nhận kết nối từ " + sk.RemoteEndPoint.ToString());
                    rtbMain.ScrollToCaret();    
                }
            }
        }


        public void myClientThread(object obj)
        {
            Socket clientSK = (Socket)obj;

            while (true)
            {

                //receive data 
                byte[] buff = new byte[1024];
                int receive = clientSK.Receive(buff);

                //send data to all others clients
                foreach (Socket sk in listClient)
                {
                    sk.Send(buff, buff.Length, SocketFlags.None);
                }
            }

            //Notice
            clientSK.Close();
        }

        private void richTextBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            e.Handled = true;
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.getIP();
            clientOperation = new Thread(new ThreadStart(listen));
            clientOperation.IsBackground = true;
            clientOperation.Start();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}

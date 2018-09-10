using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using myLib;


namespace Client
{
    public partial class Form1 : Form
    {
        Socket client;
        IPEndPoint ipe;
        Thread connect;
        Thread listen;
        public Form1()
        {
            CheckForIllegalCrossThreadCalls = false;
            InitializeComponent();
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            connect = new Thread(new ThreadStart(connectToServer));
            connect.IsBackground = true;
            connect.Start();
        }

        public void connectToServer()
        {
            ipe = new IPEndPoint(IPAddress.Parse(txtIP.Text),2001);
            client = new Socket(AddressFamily.InterNetwork,SocketType.Stream, ProtocolType.Tcp);
            client.Connect(ipe);

            listen = new Thread(listenToData);
            listen.IsBackground = true;
            listen.Start(client);
        }

        public void listenToData(object obj)
        {
            Socket sk = (Socket)obj;

            while(true)
            {
                byte[] buff = new byte[1024];
                int receive = sk.Receive(buff);

                EncodeText(buff);
            }
           
        }

        private void EncodeText(byte[] buff)
        {
            //Du lieu dang nam o dang mang byte, cho vao Stream
            MemoryStream memStream = new MemoryStream(buff);

            Structure str = new Structure();

            //Dung binaryFormater de giai ma hoa
            BinaryFormatter bformat = new BinaryFormatter();

            //Tra ve 1 kieu object dang Serializable, ep kieu ve Structure
            str = (Structure)bformat.Deserialize(memStream);

            rtbMain.SelectionFont = str.MyFont;
            rtbMain.SelectionColor = str.MyColor;
            rtbMain.AppendText(str.TextChat);
            rtbMain.ScrollToCaret();
        }

        private void lblFont_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            DialogResult dr = fontDialog1.ShowDialog();

            if(dr == DialogResult.OK)
            {
                rtbTextChat.Font = fontDialog1.Font;
            }
        }

        private void lblColor_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            DialogResult dr = colorDialog1.ShowDialog();

            if (dr == DialogResult.OK)
            {
               rtbTextChat.ForeColor = colorDialog1.Color;
            }
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            //Tao 1 doi tuong serializable chua thong tin data gui di de ma hoa
            Structure str = new Structure(rtbTextChat.Text, rtbTextChat.Font, rtbTextChat.ForeColor);

            //Stream va formater
            MemoryStream memStream = new MemoryStream();
            BinaryFormatter bFormat = new BinaryFormatter();

            //Ma hoa str vao Stream
            bFormat.Serialize(memStream, str);

            //Lay du lieu ra buffer
            byte[] buff = new byte[1024];
            buff = memStream.ToArray();

            //gui di bang socket
            client.Send(buff);
            rtbTextChat.Text = "";

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            client.Close();
        }
    }
}

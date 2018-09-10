using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;

namespace TestHttp
{
    public partial class Form1 : Form
    {
        
        //Declare variables
        CookieCollection cookies;
        HttpWebRequest request;
        string postData;
        System.IO.Stream dataStream;

        public Form1()
        {
            InitializeComponent();

            cookies = new CookieCollection();
            request = (HttpWebRequest)WebRequest.Create("http://www.chodansinh.net/action/");

            request.CookieContainer = new CookieContainer();
            request.CookieContainer.Add(cookies);

            request.Method = "POST";
            string tentruycap = "1412477";
            string matkhau = "XTRtn25aq";
            string postData = string.Format("__LASTFOCUS=&__EVENTTARGET=&__EVENTARGUMENT=&__VIEWSTATE=%2FwEPDwULLTE2NjMzMzI0MDcPZBYCZg9kFgICAw9kFggCAQ8WAh4EVGV4dAUeSENNVVMgUG9ydGFsIOKAkyDEkMSDbmcgbmjhuq1wZAIDD2QWAgINDxYCHwBlZAIFDxYCHwAFBTIuMi44ZAIHDxYCHwAFCzIwMDcgLSAyMDE0ZGQeGPluafG%2BizAZN%2FM%2Fdlfdc68KlGHRuQd3r463HqIU%2FQ%3D%3D&ctl00%24ContentPlaceHolder1%24txtUsername={0}&ctl00%24ContentPlaceHolder1%24txtPassword={1}&ctl00%24ContentPlaceHolder1%24btnLogin=%C4%90%C4%83ng+nh%E1%BA%ADp", tentruycap, matkhau);

            postData = "active=member_login&tentruycap=01235789&matkhau=12345&matkhau_hint=M%E1%BA%ADt+kh%E1%BA%A9u&dangky=%C4%90%C4%83ng+nh%E1%BA%ADp";
            ServicePointManager.Expect100Continue = false;
            byte[] byteArray = Encoding.ASCII.GetBytes(postData);
            request.ContentType = "application/x-www-form-urlencoded";

            request.ContentLength = byteArray.Length;
            request.KeepAlive = true;
            dataStream = request.GetRequestStream();
            dataStream.Write(byteArray, 0, byteArray.Length);
            dataStream.Close();

            HttpWebResponse response;
            request.Timeout = 5000;
           
            response = (HttpWebResponse)request.GetResponse();
            dataStream = response.GetResponseStream();
            System.IO.StreamReader reader = new System.IO.StreamReader(dataStream);

            //Lấy kết quả trả về từ web server
            String responseFromServer = "";
            responseFromServer = String.Copy(reader.ReadToEnd());

            //Lưu cookies (session) vào biến cookies để xử dụng lần sau            
            cookies = response.Cookies;

            //Dọn dẹp bộ nhớ
            reader.Close();
            dataStream.Close();
            response.Close();

            //Thông báo khi xử lý xong
            MessageBox.Show("ok");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            request = (HttpWebRequest)WebRequest.Create("http://www.chodansinh.net/action/");

            request.CookieContainer = new CookieContainer();
            request.CookieContainer.Add(cookies);

            request.Method = "POST";
            string tentruycap = "1412477";
            string matkhau = "XTRtn25aq";
           // postData = string.Format("__LASTFOCUS=&__EVENTTARGET=&__EVENTARGUMENT=&__VIEWSTATE=%2FwEPDwULLTE2NjMzMzI0MDcPZBYCZg9kFgICAw9kFggCAQ8WAh4EVGV4dAUeSENNVVMgUG9ydGFsIOKAkyDEkMSDbmcgbmjhuq1wZAIDD2QWAgINDxYCHwBlZAIFDxYCHwAFBTIuMi44ZAIHDxYCHwAFCzIwMDcgLSAyMDE0ZGQeGPluafG%2BizAZN%2FM%2Fdlfdc68KlGHRuQd3r463HqIU%2FQ%3D%3D&ctl00%24ContentPlaceHolder1%24txtUsername={0}&ctl00%24ContentPlaceHolder1%24txtPassword={1}&ctl00%24ContentPlaceHolder1%24btnLogin=%C4%90%C4%83ng+nh%E1%BA%ADp", tentruycap, matkhau);

            postData = "active=dang_nmh_moi&mytopic=&ten=tensp&hangsx=hang&xuatxu=xx&snngay=24&snthang=5&snnam=2016&Editor=<p>noidung1234</p>&traloibaiviet=Đăng%20ký%20mua%20hàng";
            ServicePointManager.Expect100Continue = false;
            byte[] byteArray = Encoding.ASCII.GetBytes(postData);
            request.ContentType = "application/x-www-form-urlencoded";

            request.ContentLength = byteArray.Length;
            request.KeepAlive = true;
            dataStream = request.GetRequestStream();
            dataStream.Write(byteArray, 0, byteArray.Length);
            dataStream.Close();

            HttpWebResponse response;
            request.Timeout = 5000;

            response = (HttpWebResponse)request.GetResponse();
            dataStream = response.GetResponseStream();
            System.IO.StreamReader reader = new System.IO.StreamReader(dataStream);

            //Lấy kết quả trả về từ web server
            String responseFromServer = "";
            responseFromServer = String.Copy(reader.ReadToEnd());

            //Lưu cookies (session) vào biến cookies để xử dụng lần sau            
            cookies = response.Cookies;

            //Dọn dẹp bộ nhớ
            reader.Close();
            dataStream.Close();
            response.Close();

            //Thông báo khi xử lý xong
            MessageBox.Show("ok");  


        }
    }
}

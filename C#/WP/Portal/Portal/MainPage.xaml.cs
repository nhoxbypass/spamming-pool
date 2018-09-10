using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Portal.Resources;
using System.ComponentModel;
using System.Data;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Collections.Specialized;


namespace Portal
{
    public partial class MainPage : PhoneApplicationPage
    {
        string url = "http://portal1.hcmus.edu.vn/Login.aspx";
        int time1 = 0;
        string test;
        //string url = "http://portal1.hcmus.edu.vn/Login.aspx?ReturnUrl=%2fDefault.aspx%3fpid%3d62&pid=62";
        bool isLoggedIn = false;

        string _VIEWSTATE = "%2FwEPDwULLTE2NjMzMzI0MDcPZBYCZg9kFgICAw9kFggCAQ8WAh4EVGV4dAUeSENNVVMgUG9ydGFsIOKAkyDEkMSDbmcgbmjhuq1wZAIDD2QWAgINDxYCHwBlZAIFDxYCHwAFBTIuMi44ZAIHDxYCHwAFCzIwMDcgLSAyMDE0ZGQeGPluafG%2BizAZN%2FM%2Fdlfdc68KlGHRuQd3r463HqIU%2FQ%3D%3D";
       


        // Constructor
        public MainPage()
        {
            InitializeComponent();


            

            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();
        }

       

        private void Login()
        {
            WebBrowser b = new WebBrowser();
            b.LoadCompleted += new LoadCompletedEventHandler(b_LoadCompleted);
            
            b.Navigate(new Uri(url));
            //this.Text = "Đang load!"; 
        }

       

        private void b_LoadCompleted(object sender, NavigationEventArgs e)
        {
            //this.Text = "Đang load!";
            WebBrowser b = sender as WebBrowser;


            string response = b.SaveToString();


            // format our data that we are going to post to the server
            // this will include our post parameters.  They do not need to be in a specific
            //	order, as long as they are concatenated together using an ampersand ( & )
            string postData = "__LASTFOCUS=''&__EVENTTARGET=''&__EVENTARGUMENT=''&__VIEWSTATE=" + _VIEWSTATE + "&ctl00%24ContentPlaceHolder1%24txtUsername=" + txtBox_Id.Text + "&ctl00%24ContentPlaceHolder1%24txtPassword=" + txtBox_Pwd.Password + "&ctl00%24ContentPlaceHolder1%24btnLogin=%C4%90%C4%83ng+nh%E1%BA%ADp&ctl00$ContentPlaceHolder1$ctl00$cboNamHoc_gvDKHPLichThi$ob_CbocboNamHoc_gvDKHPLichThiTB=--T%E1%BA%A5t+c%E1%BA%A3--&ctl00$ContentPlaceHolder1$ctl00$cboNamHoc_gvDKHPLichThi$ob_CbocboNamHoc_gvDKHPLichThiSIS=0&ctl00$ContentPlaceHolder1$ctl00$cboNamHoc_gvDKHPLichThi=0&ctl00$ContentPlaceHolder1$ctl00$cboHocKy_gvDKHPLichThi$ob_CbocboHocKy_gvDKHPLichThiSIS=0&ctl00$ContentPlaceHolder1$ctl00$cboHocKy_gvDKHPLichThi=''&ctl00$ContentPlaceHolder1$ctl00$btnXemDiemThi=Xem+K%E1%BA%BFt+Qu%E1%BA%A3+H%E1%BB%8Dc+T%E1%BA%ADp";
            AsciiEncoding enc = new AsciiEncoding();

            //  we are encoding the postData to a byte array
            b.Navigate(new Uri("http://portal1.hcmus.edu.vn/Login.aspx?ReturnUrl=%2fSinhVien.aspx%3fpid%3d211&pid=211"), enc.GetBytes(postData), "Content-Type: application/x-www-form-urlencoded\r\n");



            // unregisters the first event handler
            // adds a second event handler
            b.LoadCompleted += new LoadCompletedEventHandler(b_DocumentCompleted);

            b.LoadCompleted -= new LoadCompletedEventHandler(b_LoadCompleted);
        }


        private void b_DocumentCompleted(object sender, NavigationEventArgs e)
        {

            WebBrowser b = sender as WebBrowser;

            string response = "";
            response = b.SaveToString();


            string postData = "ctl00_ContentPlaceHolder1_ctl00_ToolkitScriptManager_CauHinh_HiddenField=&__EVENTTARGET=&__EVENTARGUMENT=&__VIEWSTATE=%2FwEPDwUKMTIyNzU5NDYyNA9kFgJmD2QWAgIDD2QWCgIBDxYCHgRUZXh0BQMoMClkAgMPFgIfAAUSxJBvw6BuIEhp4bq%2FdSBUw6JtZAIFD2QWAgIBD2QWAmYPZBYIAgQPDxYIHgtfIURhdGFCb3VuZGceFEFwcGVuZERhdGFCb3VuZEl0ZW1zZx4NU2VsZWN0ZWRWYWx1ZQUFMTQtMTUeC18hSXRlbUNvdW50AgJkFgJmD2QWBGYPDxYCHgdUb29sVGlwZWRkAgEPZBYCAgEPZBYCAgEPZBYEZg9kFghmD2QWAmYPFgIfAAUOLS1U4bqldCBj4bqjLS1kAgEPZBYCZg8WAh8ABQEwZAICD2QWAmYPFgIfAAUOLS1U4bqldCBj4bqjLS1kAgMPZBYCZg8WAh8ABQEwZAIBDw8WBB8ABQUxNC0xNR4FVmFsdWUFBTE0LTE1ZBYEZg9kFgJmDxYCHwAFBTE0LTE1ZAIBD2QWAmYPFgIfAAUFMTQtMTVkAgYPDxYGHwFnHwMFATIfBAICZBYCZg9kFgRmDw8WAh8FZWRkAgEPZBYCAgEPZBYCAgEPZBYEZg8PFgQfAAUBMR8GBQExZBYEZg9kFgJmDxYCHwAFATFkAgEPZBYCZg8WAh8ABQExZAIBDw8WBB8ABQEyHwYFATJkFgRmD2QWAmYPFgIfAAUBMmQCAQ9kFgJmDxYCHwAFATJkAgoPFgIeB1Zpc2libGVoZAIMDxYCHwdnFgICAQ8WAh8EAgkWEgIBD2QWAmYPFQgFMTQtMTUBMgZOTkEwMDIKQW5oIHbEg24gMgMzLjAHMTRDVFQzMQQ3LjAwBDcuNTBkAgIPZBYCZg8VCAUxNC0xNQEyBlRUSDAwMw7EkOG6oWkgc%2BG7kSBCMQMzLjAGMTRDVFQzBCA2LjAENi4wMGQCAw9kFgJmDxUIBTE0LTE1ATIGVFRIMDI2D0dp4bqjaSB0w61jaCBCMQMzLjADSEwxBCA1LjAENS4wMGQCBA9kFgJmDxUIBTE0LTE1ATIGVFRIMDI3D0dp4bqjaSB0w61jaCBCMgMzLjAGMTRDVFQzBCAzLjAEMy4wMGQCBQ9kFgJmDxUIBTE0LTE1ATIGQ1RUMDA4GUvhu7kgVGh14bqtdCBM4bqtcCBUcsOsbmgDNC4wBzE0Q1RUMzEEIDkuNQQ5LjUwZAIGD2QWAmYPFQgFMTQtMTUBMgZEVFYwMTIuTMO9IHRodXnhur90IE3huqFjaCBz4buRIChjaG8gQ8O0bmcgTmdo4buHIFRUKQMzLjAGMTRDVFQzBCA1LjAENS4wMGQCBw9kFgJmDxUIBTE0LTE1ATIGQ1RUMDEwEk5o4bqtcCBtw7RuIENOVFQgMgMzLjAHMTRDVFQzMQQxMC4wBTEwLjAwZAIID2QWAmYPFQgFMTQtMTUBMgZUQ0gwMDINVGjhu4MgZOG7pWMgMgMyLjAHMTRDVFQzMQQgNS4wBDUuMDBkAgkPZBYCZg8VCAUxNC0xNQEyBkRUVjA5MhhUaOG7sWMgaMOgbmggbeG6oWNoIHPhu5EDMS4wBzE0Q1RUMzIEIDkuMAQ5LjAwZAIHDxYCHwAFBTIuMi44ZAIJDxYCHwAFCzIwMDcgLSAyMDE0ZBgBBR5fX0NvbnRyb2xzUmVxdWlyZVBvc3RCYWNrS2V5X18WAgU3Y3RsMDAkQ29udGVudFBsYWNlSG9sZGVyMSRjdGwwMCRjYm9OYW1Ib2NfZ3ZES0hQTGljaFRoaQU2Y3RsMDAkQ29udGVudFBsYWNlSG9sZGVyMSRjdGwwMCRjYm9Ib2NLeV9ndkRLSFBMaWNoVGhp5EqBE0WY4dx7mg4r%2F8fsGwu2GyFCJBYU6p%2F8QvJKE14%3D&ctl00%24ContentPlaceHolder1%24ctl00%24cboNamHoc_gvDKHPLichThi%24ob_CbocboNamHoc_gvDKHPLichThiTB=--T%E1%BA%A5t+c%E1%BA%A3--&ctl00%24ContentPlaceHolder1%24ctl00%24cboNamHoc_gvDKHPLichThi%24ob_CbocboNamHoc_gvDKHPLichThiSIS=0&ctl00%24ContentPlaceHolder1%24ctl00%24cboNamHoc_gvDKHPLichThi=0&ctl00%24ContentPlaceHolder1%24ctl00%24cboHocKy_gvDKHPLichThi%24ob_CbocboHocKy_gvDKHPLichThiSIS=0&ctl00%24ContentPlaceHolder1%24ctl00%24cboHocKy_gvDKHPLichThi=&ctl00%24ContentPlaceHolder1%24ctl00%24btnXemDiemThi=Xem+K%E1%BA%BFt+Qu%E1%BA%A3+H%E1%BB%8Dc+T%E1%BA%ADp";
            AsciiEncoding enc = new AsciiEncoding();

            time1++;

            //  we are encoding the postData to a byte array
            b.Navigate(new Uri("http://portal1.hcmus.edu.vn/SinhVien.aspx?pid=211"), enc.GetBytes(postData), "Content-Type: application/x-www-form-urlencoded\r\n");


           // response = b.DocumentText;


            string res = "";
            if (response.Contains("Điểm Tổng Kết"))
            {
                isLoggedIn = true;
                int index_start = response.IndexOf("Điểm Tổng Kết");
                int index_end = response.IndexOf("</fieldset>");

                res = response.Substring(index_start, (index_end - index_start));
                //textBox2.Text = "<!DOCTYPE html>\r\n<html xmlns='http://www.w3.org/1999/xhtml'>\r\n<head>\r\n\t<title></title>\r\n</head>\r\n<body>\r\n\t<table id='tbDiemThiGK' class='dkhp-table'>\r\n\t\t<thead>\r\n\t\t\t<tr>\r\n\t\t\t\t<th title='Năm Học'>Năm Học</th>\r\n\t\t\t\t<th title='Học Kỳ'>Học Kỳ</th>\r\n\t\t\t\t<th title='Mã MH'>Mã Môn Học</th>\r\n\t\t\t\t<th class='left' title='Môn Học'>Môn Học</th>\r\n\t\t\t\t<th title='Số Tín Chỉ'>Số TC</th>\r\n\t\t\t\t<th title='Lớp'>Lớp</th>\r\n\t\t\t\t<th class='left'>Điểm Thi</th>\r\n\t\t\t<th class='left'>"
                 //   + res
                   // + "</body>\r\n</html>";


            }
            else
            {
                time1++;
                isLoggedIn = false;
            }



            //textBox3.Text = response;


            if (time1 == 2)
            {
                
                b.LoadCompleted -= new LoadCompletedEventHandler(b_DocumentCompleted);
                time1 = 0;

                if (isLoggedIn)
                {
                    txtBox_state.Text = "Thành công!";
                    test = "<!DOCTYPE html>\r\n<html xmlns='http://www.w3.org/1999/xhtml'>\r\n<head>\r\n\t<title></title>\r\n</head>\r\n<body>\r\n\t<table id='tbDiemThiGK' class='dkhp-table'>\r\n\t\t<thead>\r\n\t\t\t<tr>\r\n\t\t\t\t<th title='Năm Học'>Năm Học</th>\r\n\t\t\t\t<th title='Học Kỳ'>Học Kỳ</th>\r\n\t\t\t\t<th title='Mã MH'>Mã Môn Học</th>\r\n\t\t\t\t<th class='left' title='Môn Học'>Môn Học</th>\r\n\t\t\t\t<th title='Số Tín Chỉ'>Số TC</th>\r\n\t\t\t\t<th title='Lớp'>Lớp</th>\r\n\t\t\t\t<th class='left'>Điểm Thi</th>\r\n\t\t\t<th class='left'>"
                + res
                + "</body>\r\n</html>";
                    webBrowser1.NavigateToString(test);
                    isLoggedIn = false;
                    test = "";
                }
                else
                {

                    txtBox_state.Text = "Sai tài khoản \nhoặc mật khẩu!";
                }
            }
        }

        /// <summary>
        /// Silverlight doesn't have an ASCII encoder, so here is one:
        /// </summary>
        public class AsciiEncoding : System.Text.Encoding
        {
            public override int GetMaxByteCount(int charCount)
            {
                return charCount;
            }
            public override int GetMaxCharCount(int byteCount)
            {
                return byteCount;
            }
            public override int GetByteCount(char[] chars, int index, int count)
            {
                return count;
            }
            public override byte[] GetBytes(char[] chars)
            {
                return base.GetBytes(chars);
            }
            public override int GetCharCount(byte[] bytes)
            {
                return bytes.Length;
            }
            public override int GetBytes(char[] chars, int charIndex, int charCount, byte[] bytes, int byteIndex)
            {
                for (int i = 0; i < charCount; i++)
                {
                    bytes[byteIndex + i] = (byte)chars[charIndex + i];
                }
                return charCount;
            }
            public override int GetCharCount(byte[] bytes, int index, int count)
            {
                return count;
            }
            public override int GetChars(byte[] bytes, int byteIndex, int byteCount, char[] chars, int charIndex)
            {
                for (int i = 0; i < byteCount; i++)
                {
                    chars[charIndex + i] = (char)bytes[byteIndex + i];
                }
                return byteCount;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            webBrowser1.NavigateToString("");
            txtBox_state.Text = "Đang load...";
            Login();
            
        }





        // Sample code for building a localized ApplicationBar
        //private void BuildLocalizedApplicationBar()
        //{
        //    // Set the page's ApplicationBar to a new instance of ApplicationBar.
        //    ApplicationBar = new ApplicationBar();

        //    // Create a new button and set the text value to the localized string from AppResources.
        //    ApplicationBarIconButton appBarButton = new ApplicationBarIconButton(new Uri("/Assets/AppBar/appbar.add.rest.png", UriKind.Relative));
        //    appBarButton.Text = AppResources.AppBarButtonText;
        //    ApplicationBar.Buttons.Add(appBarButton);

        //    // Create a new menu item with the localized string from AppResources.
        //    ApplicationBarMenuItem appBarMenuItem = new ApplicationBarMenuItem(AppResources.AppBarMenuItemText);
        //    ApplicationBar.MenuItems.Add(appBarMenuItem);
        //}
    }
}
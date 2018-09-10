using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DemoPaint
{
    public partial class Form1 : Form
    {

        #region Enum
        //Enum để lựa chọn màu trái phải
        public enum ButtonColor
        {
            LEFT, RIGHT,
        }

        //Enum để lựa chọn công cụ vẽ
        public enum ShapeMode
        {
            LINE,
            DRAWRECT,
            DRAWELLIPSE,
            FILLRECT,
            FILLELLIPSE

        }
        #endregion Enum

        //Khai báo biến
        #region DeclareVariables
        private Graphics grs;
        private Point p1, p2;
        private Pen pen;
        private bool _isDown = false;
        private Bitmap _bmp;
        private ButtonColor _currBtColor = ButtonColor.LEFT;
        private Color _currLeftColor, _currRightColor;
        private int _currPenSize =1;
        private ShapeMode _currShapeMode = ShapeMode.LINE;
        private SolidBrush sb;
        #endregion  DeclareVariables

        public Form1()
        {
            InitializeComponent();

            //Khai báo các sự kiện cho form
            this.Paint += Form1_Paint;
            this.MouseDown += Form1_MouseDown;
            this.MouseMove += Form1_MouseMove;
            this.MouseUp += Form1_MouseUp;

            //Khởi tạo các đối tượng cần thiết
            _bmp = new Bitmap(this.Width, this.Height);
            grs = Graphics.FromImage(_bmp);
            SolidBrush slb1 = new SolidBrush(Color.White);
            grs.FillRectangle(Brushes.White, 0, 0, _bmp.Width, _bmp.Height);
            pen = new Pen(_currLeftColor, _currPenSize);

            _currLeftColor = btLeftColor.BackColor;
            _currRightColor = btRightColor.BackColor;

            cbSize.SelectedIndex = 0;

            //Giảm rung khi vẽ
            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
        }


        //Sự kiện paint chạy khi các sự kiện khác thực thi xong, hoặc khi form đc Focus trở lại
        void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (_isDown)
            {
                int width = p2.X - p1.X;
                int height = p2.Y - p1.Y;
                int AnchorX = p1.X, AnchorY = p1.Y;

                //Vẽ nét vẽ tạm thời khi chưa Mouse Up               
                switch (_currShapeMode)
                {
                    case ShapeMode.LINE:
                        pen = new Pen(_currLeftColor, _currPenSize);

                        e.Graphics.DrawLine(pen, p1, p2);
                        break;

                    case ShapeMode.DRAWRECT:
                        pen = new Pen(_currLeftColor, _currPenSize);

                        if (width < 0)
                        {
                            AnchorX = p2.X;
                        }
                        if (height < 0)
                        {
                            AnchorY = p2.Y;
                        }
                        e.Graphics.DrawRectangle(pen, AnchorX, AnchorY, Math.Abs(width), Math.Abs(height));
                        break;

                    case ShapeMode.DRAWELLIPSE:
                        pen = new Pen(_currLeftColor, _currPenSize);

                        e.Graphics.DrawEllipse(pen, p1.X, p1.Y, width, height);
                        break;

                    case ShapeMode.FILLRECT:
                        sb = new SolidBrush(_currLeftColor);

                        if (width < 0)
                        {
                            AnchorX = p2.X;
                        }
                        if (height < 0)
                        {
                            AnchorY = p2.Y;
                        }
                        e.Graphics.FillRectangle(sb, AnchorX, AnchorY, Math.Abs(width), Math.Abs(height));
                        break;

                    case ShapeMode.FILLELLIPSE:
                        sb = new SolidBrush(_currLeftColor);

                        e.Graphics.FillEllipse(sb, p1.X, p1.Y, width, height);
                        break;

                    default:
                        MessageBox.Show("Lỗi");
                        break;
                }
            }
        }


        #region MouseEvent
        void Form1_MouseUp(object sender, MouseEventArgs e) 
        {
            _isDown = false;

            int width = (p2.X - p1.X);
            int height = (p2.Y - p1.Y);
            int AnchorX = p1.X, AnchorY = p1.Y;

            //Vẽ chính thức vào bitmap              
            switch (_currShapeMode)
            {
                case ShapeMode.LINE:
                    pen = new Pen(_currLeftColor, _currPenSize);

                    grs.DrawLine(pen, p1, p2);
                    break;

                case ShapeMode.DRAWRECT:
                    pen = new Pen(_currLeftColor, _currPenSize);

                    if (width < 0)
                    {
                        AnchorX = p2.X;
                    }
                    if (height < 0)
                    {
                        AnchorY = p2.Y;
                    }                  
                    grs.DrawRectangle(pen, AnchorX, AnchorY, Math.Abs(width), Math.Abs(height));
                    break;

                case ShapeMode.DRAWELLIPSE:
                    pen = new Pen(_currLeftColor, _currPenSize);

                    grs.DrawEllipse(pen, p1.X, p1.Y, width, height);
                    break;

                case ShapeMode.FILLRECT:
                    sb = new SolidBrush(_currLeftColor);

                    if (width < 0)
                    {
                        AnchorX = p2.X;
                    }
                    if (height < 0)
                    {
                        AnchorY = p2.Y;
                    }
                    grs.FillRectangle(sb, AnchorX, AnchorY, Math.Abs(width), Math.Abs(height));
                    break;

                case ShapeMode.FILLELLIPSE:
                    sb = new SolidBrush(_currLeftColor);

                    grs.FillEllipse(sb, p1.X, p1.Y, width, height);
                    break;

                default:
                    MessageBox.Show("Lỗi");
                    break;
            }

            //Gán ngược lại background của form
            this.BackgroundImage = (Bitmap)_bmp.Clone();
        }

        void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            if (_isDown)
            {
                p2 = new Point(e.Location.X, e.Location.Y);
                this.Refresh(); //Refresh lại form để khi chuyển qua sự kiện paint nó sẽ vẽ các nét vẽ tạm thời
            }

            lbCoor.Text = e.Location.X.ToString() + ", " + e.Location.Y.ToString() +"px";
        }


        void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            p1 = new Point(e.Location.X, e.Location.Y);
            _isDown = true;
        }
        #endregion MouseEvent


        #region FeatureSelection
        private void btDrawLine_Click(object sender, EventArgs e)
        {
            pen = new Pen(_currLeftColor,_currPenSize);
            _currShapeMode = ShapeMode.LINE;
            this.btDrawLine.FlatStyle = FlatStyle.Flat;
            this.btDrawRect.FlatStyle = FlatStyle.Standard;
            this.btDrawEllipse.FlatStyle = FlatStyle.Standard;
            this.btFillRect.FlatStyle = FlatStyle.Standard;
            this.btFillEllipse.FlatStyle = FlatStyle.Standard;
        }

        private void btDrawRect_Click(object sender, EventArgs e)
        {
            pen = new Pen(_currLeftColor, _currPenSize);
            _currShapeMode = ShapeMode.DRAWRECT;
            this.btDrawLine.FlatStyle = FlatStyle.Standard;
            this.btDrawRect.FlatStyle = FlatStyle.Flat;
            this.btDrawEllipse.FlatStyle = FlatStyle.Standard;
            this.btFillRect.FlatStyle = FlatStyle.Standard;
            this.btFillEllipse.FlatStyle = FlatStyle.Standard;
        }

        private void btDrawEllipse_Click(object sender, EventArgs e)
        {
            pen = new Pen(_currLeftColor, _currPenSize);
            _currShapeMode = ShapeMode.DRAWELLIPSE;
            this.btDrawLine.FlatStyle = FlatStyle.Standard;
            this.btDrawRect.FlatStyle = FlatStyle.Standard;
            this.btDrawEllipse.FlatStyle = FlatStyle.Flat;
            this.btFillRect.FlatStyle = FlatStyle.Standard;
            this.btFillEllipse.FlatStyle = FlatStyle.Standard;
        }

        private void btFillRect_Click(object sender, EventArgs e)
        {
            sb = new SolidBrush(_currLeftColor);
            _currShapeMode = ShapeMode.FILLRECT;
            this.btDrawLine.FlatStyle = FlatStyle.Standard;
            this.btDrawRect.FlatStyle = FlatStyle.Standard;
            this.btDrawEllipse.FlatStyle = FlatStyle.Standard;
            this.btFillRect.FlatStyle = FlatStyle.Flat;
            this.btFillEllipse.FlatStyle = FlatStyle.Standard;
        }

        private void btFillEllipse_Click(object sender, EventArgs e)
        {
            sb = new SolidBrush(_currLeftColor);
            _currShapeMode = ShapeMode.FILLELLIPSE;
            this.btDrawLine.FlatStyle = FlatStyle.Standard;
            this.btDrawRect.FlatStyle = FlatStyle.Standard;
            this.btDrawEllipse.FlatStyle = FlatStyle.Standard;
            this.btFillRect.FlatStyle = FlatStyle.Standard;
            this.btFillEllipse.FlatStyle = FlatStyle.Flat;
        }

        private void btChooseColor_Click(object sender, EventArgs e)
        {
            ColorDialog cld = new ColorDialog();
            if (cld.ShowDialog() == DialogResult.OK)
            {
                if (_currBtColor == ButtonColor.LEFT)
                {
                    btLeftColor.BackColor = cld.Color;
                    _currLeftColor = cld.Color;
                }
                else
                {
                    btRightColor.BackColor = cld.Color;
                    _currRightColor = cld.Color;
                }

            }
        }

        private void btLeftColor_Click(object sender, EventArgs e)
        {
            _currBtColor = ButtonColor.LEFT;
            this.btRightColor.FlatStyle = FlatStyle.Standard;
            this.btLeftColor.FlatStyle = FlatStyle.Flat;
        }

        private void btRightColor_Click(object sender, EventArgs e)
        {
            _currBtColor = ButtonColor.RIGHT;
            this.btLeftColor.FlatStyle = FlatStyle.Standard;
            this.btRightColor.FlatStyle = FlatStyle.Flat;
        }

        private void cbSize_SelectedIndexChanged(object sender, EventArgs e)
        {
            _currPenSize = int.Parse(cbSize.Text);
            pen = new Pen(_currLeftColor, _currPenSize);
        }
        #endregion FeatureSelection


        #region Menu
        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Do you want to save changes to United?","My Paint",MessageBoxButtons.YesNoCancel);
            _bmp = new Bitmap(this.Width, this.Height);
            grs = Graphics.FromImage(_bmp);
            this.Refresh();
            this.BackgroundImage = (Bitmap)_bmp.Clone();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //
            OpenFileDialog ofd = new OpenFileDialog();

            //Bộ lọc đuôi tệp
            ofd.Filter = "Mọi tệp hình ảnh (*.jpg, *.jpeg, *.jpe, *.png, *.bmp, *.tif, *.tiff) | *.jpg; *.jpeg; *.jpe; *.png; *.bmp; *.tif; *.tiff";
            
            if(ofd.ShowDialog() == DialogResult.OK)
            {
                //Lây ảnh từ đường dẫn và thay đôỉ tên form
                Image _img = Image.FromFile(ofd.FileName);
                this.Text = ofd.FileName + " - My Paint";

                //Tạo mới bitmap bằng kích cỡ để chứa ảnh
                _bmp = new Bitmap(_img.Width, _img.Height);

                //Đặt lại đối tượng Graphics cho bitmap
                grs = Graphics.FromImage(_bmp);

                //Tạo đối tượng Rect bằng với bitmap và vẽ lên bitmap vừa tạo
                Rectangle rect = new Rectangle(0, 0, _bmp.Width, _bmp.Height);
                grs.DrawImage(_img, rect);

                //Cập nhật lại form
                this.Refresh();
                this.BackgroundImage = (Bitmap)_bmp.Clone();
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            
            //Bộ lọc đuôi ảnh
            sfd.Filter = "Bitmap Image (*.bmp) | *.bmp | JPEG (*.jpg) | *.jpg | TIFF (*.tiff) | *.tiff | PNG (*.png) | *.png";

            //Show hộp thoại và lưu
            if(sfd.ShowDialog() == DialogResult.OK)
            {
                _bmp.MakeTransparent(Color.White);
                _bmp.Save(sfd.FileName);
                
            }
        }
        #endregion Menu








    }
}

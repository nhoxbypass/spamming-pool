using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MySprite2D
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }


        List<Sprite2D> sprites = new List<Sprite2D>();

       

        private void createDarkSaber(int left, int top)
        {
            List<Bitmap> bmp = new List<Bitmap>();
            bmp.Add(Properties.Resources.darksaber_attack0035);
            bmp.Add(Properties.Resources.darksaber_attack0036);
            bmp.Add(Properties.Resources.darksaber_attack0037);
            bmp.Add(Properties.Resources.darksaber_attack0038);
            bmp.Add(Properties.Resources.darksaber_attack0039);
            bmp.Add(Properties.Resources.darksaber_attack0040);
            bmp.Add(Properties.Resources.darksaber_attack0041);
            bmp.Add(Properties.Resources.darksaber_attack0042);
            bmp.Add(Properties.Resources.darksaber_attack0043);
            bmp.Add(Properties.Resources.darksaber_attack0044);
            bmp.Add(Properties.Resources.darksaber_attack0045);
            bmp.Add(Properties.Resources.darksaber_attack0046);
            bmp.Add(Properties.Resources.darksaber_attack0047);
            bmp.Add(Properties.Resources.darksaber_attack0048);
            bmp.Add(Properties.Resources.darksaber_attack0049);
            bmp.Add(Properties.Resources.darksaber_attack0050);
       

            sprites.Add(new Sprite2D(bmp, left, top, 0, 0));

        }

        public void runDarkSaber(int left, int top)
        {
            List<Bitmap> bmp = new List<Bitmap>();
            bmp.Add(Properties.Resources.darksaber_run0001);
            bmp.Add(Properties.Resources.darksaber_run0002);
            bmp.Add(Properties.Resources.darksaber_run0003);
            bmp.Add(Properties.Resources.darksaber_run0004);
            bmp.Add(Properties.Resources.darksaber_run0005);
            bmp.Add(Properties.Resources.darksaber_run0006);
            bmp.Add(Properties.Resources.darksaber_run0007);
            bmp.Add(Properties.Resources.darksaber_run0008);
            bmp.Add(Properties.Resources.darksaber_run0009);
            bmp.Add(Properties.Resources.darksaber_run0010);
            bmp.Add(Properties.Resources.darksaber_run0011);
            bmp.Add(Properties.Resources.darksaber_run0012);
            bmp.Add(Properties.Resources.darksaber_run0013);
            bmp.Add(Properties.Resources.darksaber_run0014);
            bmp.Add(Properties.Resources.darksaber_run0015);
            bmp.Add(Properties.Resources.darksaber_run0016);
            bmp.Add(Properties.Resources.darksaber_run0017);


            sprites.Add(new Sprite2D(bmp, left, top, 0, 0));
        }

        private void createForest(int left, int top)
        {
            List<Bitmap> bmp = new List<Bitmap>();
            bmp.Add(Properties.Resources.background);
            sprites.Add(new Sprite2D(bmp, left, top, 0, 0));
        }

        private void loadBackground()
        {
            List<Bitmap> bmp = new List<Bitmap>();
            bmp.Add(Properties.Resources.background2);
            sprites.Add(new Sprite2D(bmp, 0, 0, 0, 0));
        }

        protected override void OnPaintBackground(PaintEventArgs e)
        {
            //base.OnPaintBackground(e);
        }

 

       

        private void SelectSprite(int selIdx)
        {
            for (int i = 0; i < sprites.Count; i++)
                sprites[i].SetStatus(i == selIdx);
        }

        private int GetSelectedSprite(int x, int y)
        {
            for (int i = sprites.Count - 1; i >= 0; i--)
                if (sprites[i].IsSelected(x, y))
                    return i;
            return -1;
        }

        private void onMainFormLoad(object sender, EventArgs e)
        {
            loadBackground();
            createForest(100, 100);
            runDarkSaber(0, 50);
            createDarkSaber(100, 0);
            createDarkSaber(100, 100);
        }

        private void onMainFormMouseClick(object sender, MouseEventArgs e)
        {
            int SelIdx = GetSelectedSprite(e.X, e.Y);
            if (SelIdx != -1)
            {

                SelectSprite(SelIdx);
            }
        }

        private void onMainFormPaint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;// screen

            Bitmap backDrop = new Bitmap(this.Width, this.Height);
            Graphics temp = Graphics.FromImage(backDrop);
            temp.Clear(Color.White);
            for (int i = 0; i < sprites.Count; i++)
                sprites[i].Draw(temp);

            g.DrawImage(backDrop, 0, 0);
        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            for (int i = 0; i < sprites.Count; i++)
                sprites[i].Update();
            Invalidate();
        }
    }
}

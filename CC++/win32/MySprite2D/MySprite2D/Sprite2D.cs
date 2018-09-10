using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MySprite2D
{
    public class Sprite2D
    {
        List<Bitmap> mBitmapList = new List<Bitmap>();

        int mBitmapCount;
        int mBitmapIndex;
        Rectangle rect;

        bool bStatus = false;
        int d = 0, d2 = 1;


        public void Update()
        {
            mBitmapIndex = (mBitmapIndex + 1) % mBitmapCount;
            if (bStatus)
            {
                d += d2;
                if (Math.Abs(d) == 10)
                    d2 *= -1;
            }
        }

        public void Draw(Graphics g)
        {
            if (bStatus == false)
            {
                g.DrawImage(mBitmapList[mBitmapIndex], rect.Left, rect.Top);
            }
            else
            {
                g.DrawImage(mBitmapList[mBitmapIndex],
                    new Rectangle(rect.Left - d, rect.Top - d, Rect.Width + d * 2, Rect.Height + d * 2),
                    new Rectangle(0, 0, Rect.Width, Rect.Height),
                    GraphicsUnit.Pixel);
            }
        }

        internal bool IsSelected(int x, int y)
        {
            if (x >= rect.Left && x < rect.Left + Rect.Width &&
                y >= rect.Top && y < rect.Top + Rect.Height)
                return true;
            return false;
        }

        internal void SetStatus(bool v)
        {
            bStatus = v;
        }


        public int BitmapCount
        {
            get { return mBitmapCount; }
            set { mBitmapCount = value; }
        }
        
        public int BitmapIndex
        {
            get { return mBitmapIndex; }
            set { mBitmapIndex = value; }
        }
        

        public List<Bitmap> BitmapList
        {
            get { return mBitmapList; }
            set 
            { 
                mBitmapList = value;
                mBitmapCount = mBitmapList.Count;
                if(mBitmapCount < 1)
                    System.Windows.Forms.MessageBox.Show("Error!");
                mBitmapIndex = 0;
            }
        }

        
        public Rectangle Rect
        {
            get { return rect; }
            set { rect = value; }
        }


        public Sprite2D(List<Bitmap> bmp, 
            int left, int top, int width, int height)
        {
            mBitmapList = bmp;
            
            if (width == 0)
                width = mBitmapList[0].Width;
            if (height == 0)
                height = mBitmapList[0].Height;

            rect = new Rectangle(left, top, width, height);

            mBitmapIndex = 0;
            mBitmapCount = bmp.Count();
        }
    }
}

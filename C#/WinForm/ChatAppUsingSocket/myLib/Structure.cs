using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization;
using System.Drawing;

namespace myLib
{
    [Serializable]
    public class Structure : ISerializable
    {
        private string textChat;
        private Font myFont;
        private Color myColor;

        public Structure()
        {
            this.textChat = "";
            this.myFont = new Font("Arial",11,FontStyle.Regular);
            this.myColor = Color.Aqua;
        }

        public Structure(string text, Font font, Color color)
        {
            this.textChat = text;
            this.myFont = font;
            this.myColor = color;
        }

        public Structure(Structure str)
        {
            this.textChat = str.textChat;
            this.myFont = str.myFont;
            this.myColor = str.myColor;
        }

        public Structure(SerializationInfo info, StreamingContext streamContext)
        {
            this.textChat = (string)info.GetValue("text",typeof(string));
            this.myFont = (Font)info.GetValue("font",typeof(Font));
            this.myColor = (Color)info.GetValue("color",typeof(Color));
        }

        public void GetObjectData(SerializationInfo info, StreamingContext streamContext)
        {
            info.AddValue("text",this.textChat);
            info.AddValue("font",this.myFont);
            info.AddValue("color",this.myColor);
        }

        public Color MyColor
        {
            get { return myColor; }
            set { myColor = value; }
        }

        public Font MyFont
        {
            get { return myFont; }
            set { myFont = value; }
        }

        public string TextChat
        {
            get { return textChat; }
            set { textChat = value; }
        }
    }
}

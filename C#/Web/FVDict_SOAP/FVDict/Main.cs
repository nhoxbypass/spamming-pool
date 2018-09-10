using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace FVDict
{
    public partial class Main : Form
    {
        private FrEnTranslationServiceProxy.FrEnTranslationService frEnTranslationService;
        private EnViTranslationServiceProxy.EnViTranslationService enViTranslationService;

        public Main()
        {
            InitializeComponent();
            frEnTranslationService = new FrEnTranslationServiceProxy.FrEnTranslationService();
            enViTranslationService = new EnViTranslationServiceProxy.EnViTranslationService();
            ShowError("");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ShowError("");
            string frWord = txtFr.Text;

            if (frWord == null || frWord.Length == 0)
            {
                //Keyword is empty
                ShowError("Keyword is empty");
                return;
            }

            //Get English from Frech word
            string enWord = frEnTranslationService.Translate(frWord);

            if (enWord == null)
            {
                //Cannot load data
                ShowError("Cannot load FrEn Dictionary data from XML");
                return;
            }
            else if (enWord.Length == 0)
            {
                //Dictionary do not contain this keyword
                ShowError("FrEn Dictionary do not contain \"" + frWord + "\"");
                return;
            }

            //Get Vietnamese from English word
            string result = enViTranslationService.Translate(enWord);

            if (result == null) {
                //Data not loaded
                ShowError("Cannot load EnVi Dictionary data from XML");
                return;
            }
            else if (result.Length == 0)
            {
                //Dictionary not contain this word
                ShowError("FrEn Dictionary do not contain \"" + enWord + "\"");
                return;
            }

            //Found
            txtVi.Text = result;
        }

        private void ShowError(string message)
        {
            if (message == null || message.Length == 0)
            {
                lblError.Text = "";
                return;
            }

            lblError.Text = "* " + message;
        }

        private void txtVi_TextChanged(object sender, EventArgs e)
        {

        }

        private void txtFr_TextChanged(object sender, EventArgs e)
        {

        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Xml.Linq;

namespace SOAP
{
    /// <summary>
    /// Summary description for FrEnTranslationService
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]
    public class FrEnTranslationService : System.Web.Services.WebService
    {

        [WebMethod]
        public string Translate(string keyword)
        {
            if (keyword == null || keyword.Length == 0)
                return null;

            Dictionary<string, string> dict = loadData("~/App_Data/fr_en.xml");
            //Should prompt if the db not loaded (dict == null)
            if (dict != null && dict.Count > 0)
            {
                try
                {
                    return dict[keyword];
                }
                catch (KeyNotFoundException ex)
                {
                    Console.WriteLine(ex.Message);
                    return "";
                }
            }

            return null;
        }

        private Dictionary<string, string> loadData(string filePath)
        {
            Dictionary<string, string> dataMap = new Dictionary<string, string>();
            string fileName = Server.MapPath(filePath);
            XElement root = XElement.Load(fileName);
            foreach (var ele in root.Elements("word"))
            {
                //Here we can get data of each word
                dataMap.Add(ele.Descendants().ToArray()[0].Value, ele.Descendants().ToArray()[1].Value);
            }

            return dataMap;
        }
    }
}

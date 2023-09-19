using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Windows;
using System.IO;
using System.Drawing;

namespace TEST_BENCH
{
    public class XmlFile : Struct
    {

        XDocument MyXmlFile = null;
        public Struct_Test_Attr[] Test_Attr;
        MainForm My_Form;
        public ExcelFile MyExelFile;
        int Tests_Selected = 0;
        int Tests_Current = 0;

        public XmlFile(String FileName,MainForm My_MainForm)
        {
            My_Form = My_MainForm;


            try
            {
                MyXmlFile = XDocument.Load(FileName);

            }
            catch (Exception error)
            {
                if (!File.Exists(FileName))
                {
                    MessageBox.Show("در دسترس نمی باشد XMLFileTests.xml فایل");
                }
                else
                {
                    MessageBox.Show("درست تعریف نشده است xml فایل");
                }
                Environment.Exit(0);
            }




            try
            {
                MyExelFile = new ExcelFile(My_Form);

            }
            catch (Exception error)
            {
                if (!File.Exists(FileName))
                {
                    MessageBox.Show("در دسترس نمی باشد excel فایل");
                }
                else
                {
                    MessageBox.Show("درست تعریف نشده است excel فایل");
                }
                Environment.Exit(0);
            }


        }


        public Struct_Test_Attr[] Respond()
        {
            IEnumerable<XElement> RForm = MyXmlFile.Descendants("Form");

            foreach (var buffer_RForm in RForm)
            {
                try
                {
                    My_Form.BoudRate = Convert.ToInt32(buffer_RForm.Attribute("BoudRate").Value);
                    My_Form.MySerial = buffer_RForm.Attribute("Serial").Value;
                    My_Form.MyVersion = buffer_RForm.Attribute("Version").Value;
                }
                catch (Exception e)
                {
                    MessageBox.Show("درست تعریف نشده است xml فایل");
                    Environment.Exit(0);
                }
            }



            Tests_Current = 0;
            List<String> List_Tests = new List<String>();
            List_Tests.Clear();
            IEnumerable<XElement> Tests = MyXmlFile.Descendants("Tests");
            foreach (var buffer_Tests in Tests)
            {
                try
                {
                    List_Tests.Add(buffer_Tests.Attribute("Title").Value);
                    Tests_Current++;
                }
                catch (Exception e)
                {
                    MessageBox.Show("درست تعریف نشده است xml فایل");
                    Environment.Exit(0);
                }
            }

            Repeat_Request_Test:
            Tests_Selected = 0;
            if (Tests_Current != 1)
            {
                Tests_Selected = InputMessage.InputListBox("TEST_BENCH", "مجموعه تست خود را انتخاب کنید ؟", List_Tests);
                if (Tests_Selected == 0)
                {
                    MessageBox.Show("موردی برای تست انتخاب نگردید");
                    goto Repeat_Request_Test;
                }

                Tests_Selected--;

            }

            Tests_Current = 0;
            foreach (var buffer_Tests in Tests)
            {
                if (Tests_Selected == Tests_Current)
                {
                    try
                    {
                        My_Form.Text = buffer_Tests.Attribute("Title").Value;//Add title
                        if (buffer_Tests.Attribute("BoardPicture").Value != "")
                        {
                            My_Form.BoardPictureFile = buffer_Tests.Attribute("BoardPicture").Value;                                                    
                        }
                        My_Form.checkboxenableHeader.Checked = Convert.ToBoolean(buffer_Tests.Attribute("AutoEnableChecked").Value);
                        My_Form.EnableLoop = My_Form.En_Loop.Checked = Convert.ToBoolean(buffer_Tests.Attribute("AutoReplay").Value);
                        My_Form.EnableNext = My_Form.En_Next.Checked = Convert.ToBoolean(buffer_Tests.Attribute("AutoNext").Value);

                        MyExelFile.FileLoad(buffer_Tests.Attribute("ExcelFile").Value, buffer_Tests.Attribute("ExcelSheet").Value, buffer_Tests.Attribute("ExcelStartSerialsField").Value, buffer_Tests.Attribute("ExcelCheckSum").Value);
                    
                        IEnumerable<XElement> Test = buffer_Tests.Descendants("Test");

                        int Count = 0;
                        foreach (var buffer_Test in Test)
                        {
                            if (Convert.ToBoolean(buffer_Test.Element("Enable").Attribute("Value").Value))
                            {
                                Count++;
                            }
                        }



                        if (Count == 0)
                        {
                            MessageBox.Show("موردی برای انجام تست موجود نمی باشد");
                            Environment.Exit(0);
                        }


                        My_Form.Max_Test = Count;
                        Test_Attr = new Struct_Test_Attr[My_Form.Max_Test];

                        Count = 0;
                        foreach (var buffer_Test in Test)
                        {
                            if (Convert.ToBoolean(buffer_Test.Element("Enable").Attribute("Value").Value))
                            {
                                Test_Attr[Count].Command = buffer_Test.Attribute("Command").Value;
                                Test_Attr[Count].Enable = buffer_Test.Element("Enable").Attribute("Value").Value;
                                Test_Attr[Count].EnableIf = buffer_Test.Element("EnableIf").Attribute("Value").Value;
                                Test_Attr[Count].EnableLoop = buffer_Test.Element("EnableLoop").Attribute("Value").Value;
                                Test_Attr[Count].EnableNext = buffer_Test.Element("EnableNext").Attribute("Value").Value;
                                Test_Attr[Count].Explanation = buffer_Test.Element("Explanation").Attribute("Value").Value;
                                Test_Attr[Count].Description = buffer_Test.Element("Description").Attribute("Value").Value;
                                Test_Attr[Count].MessageOK = buffer_Test.Element("MessageOK").Attribute("Value").Value;
                                Test_Attr[Count].MessageNO = buffer_Test.Element("MessageNO").Attribute("Value").Value;
                                Test_Attr[Count].RunExe = buffer_Test.Element("RunExe").Attribute("Value").Value;
                                Test_Attr[Count].AskData = buffer_Test.Element("AskData").Attribute("Value").Value;
                                Test_Attr[Count].Data = buffer_Test.Element("Data").Attribute("Value").Value;
                                Test_Attr[Count].MustAnswer = buffer_Test.Element("MustAnswer").Attribute("Value").Value;
                                Test_Attr[Count].ExceptAnswer = buffer_Test.Element("ExceptAnswer").Attribute("Value").Value;
                                Test_Attr[Count].WaitAnswer = buffer_Test.Element("WaitAnswer").Attribute("Value").Value;
                                Test_Attr[Count].Alert = buffer_Test.Element("Alert").Attribute("Value").Value;
                                Test_Attr[Count].Promp = buffer_Test.Element("Promp").Attribute("Value").Value;
                                Test_Attr[Count].ExcelField = buffer_Test.Element("ExcelField").Attribute("Value").Value;
                                Test_Attr[Count].ElementPosX1 = buffer_Test.Element("ElementPosX1").Attribute("Value").Value;
                                Test_Attr[Count].ElementPosX2 = buffer_Test.Element("ElementPosX2").Attribute("Value").Value;
                                Test_Attr[Count].ElementPosY1 = buffer_Test.Element("ElementPosY1").Attribute("Value").Value;
                                Test_Attr[Count].ElementPosY2 = buffer_Test.Element("ElementPosY2").Attribute("Value").Value;

                                Count++;
                            }
                            //else
                            //{
                            //    My_Form.Max_Test--;
                            //}
                        }

                    }
                    catch (Exception e)
                    {
                        MessageBox.Show("فایل های جانبی تکمیل نمی باشند");
                        Environment.Exit(0);
                    }
                }
                Tests_Current++;
            }

            return Test_Attr;
        }

    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using System.IO.Ports;
using System.Diagnostics;
using System.Globalization;


namespace TEST_BENCH
{
    public class TestView : Struct
    {
        XmlFile MyXmlFile;
        MainForm My_Form;
        DataGridView LST_TEST;
        public Boolean mode_test;
        Boolean mode_blink;
        String Buffer_AskData;
        String DateTime_Buffer;

        byte mode_com_txrx = 0;

        int time_out = 0;

        long time_all_tests = 0;

        public int test_number = 0;
        String get_string_port;
        Struct_Test_Attr[] Test_Attr;
        Boolean get_string_port_in = false;

        ProcessContainer RunExe;

        SerialPort T_PORT = new SerialPort("COM0", 115200, Parity.None, 8, StopBits.One);
        public Timer Timer_TEST = new Timer();
        public Timer Timer_BLINK = new Timer();
        public Timer Timer_BLINK_COM_TXRX = new Timer();
        public Timer Timer_Timeout = new Timer();
        public Timer Timer_Timeout_Receive_TagStart = new Timer();        

        public TestView(MainForm My_MainForm)
        {
            LST_TEST = new DataGridView();

            //My_MainForm.LST_TEST.Dispose();

            My_Form = My_MainForm;

            LST_TEST = My_MainForm.LST_TEST;
            MyXmlFile = new XmlFile("XMLFileTests.xml",My_MainForm);
            Test_Attr = MyXmlFile.Respond();

            DataGridViewCellStyle style = new DataGridViewCellStyle();
            style.Font = new Font(LST_TEST.Font.FontFamily, 12, FontStyle.Bold);
            LST_TEST.DefaultCellStyle = style;
            LST_TEST.AllowUserToAddRows = false;
            LST_TEST.RightToLeft = RightToLeft.Yes;
            LST_TEST.RowTemplate.Height = 32;
            LST_TEST.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.None;
            LST_TEST.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.None;
            LST_TEST.AllowUserToResizeRows = false;
            LST_TEST.AllowUserToResizeColumns = false;
            LST_TEST.AutoSize = false;
            LST_TEST.BorderStyle = BorderStyle.None;
            LST_TEST.RowHeadersVisible = false;


            DataGridViewCheckBoxColumn CB_CO1 = new DataGridViewCheckBoxColumn();
            //CB_CO1.Visible = false;
            LST_TEST.Columns.Add(CB_CO1);
            LST_TEST.Columns[0].Width = 20;

            DataGridViewImageColumn IMG_CO = new DataGridViewImageColumn();
            LST_TEST.Columns.Add(IMG_CO);
            LST_TEST.Columns[1].HeaderText = "وضعیت";
            LST_TEST.Columns[1].ReadOnly = true;
            LST_TEST.Columns[1].Width = 60;

            LST_TEST.Columns.Add("Description", "شرح عملکرد");
            LST_TEST.Columns[2].ReadOnly = true;
            LST_TEST.Columns[2].Width = 544;
            
            // add checkbox header
            Rectangle rect = LST_TEST.GetCellDisplayRectangle(0, -1, true);
            // set checkbox header to center of header cell. +1 pixel to position correctly.
            rect.X = (rect.Location.X + (rect.Width / 4))-4;
            rect.Y += 1;
            My_Form.checkboxenableHeader.Name = "checkboxenableHeader";
            My_Form.checkboxenableHeader.Size = new Size(18, 18);
            My_Form.checkboxenableHeader.Location = rect.Location;
            My_Form.checkboxenableHeader.CheckedChanged += new EventHandler(checkboxenableHeader_CheckedChanged);
            LST_TEST.Controls.Add(My_Form.checkboxenableHeader);
            

            My_Form.BAR_Proccess.Maximum = My_Form.Max_Test;

            T_PORT.DiscardNull = true;
            T_PORT.DtrEnable = true;
            T_PORT.RtsEnable = true;
            T_PORT.WriteBufferSize = 20;
            T_PORT.BaudRate = My_Form.BoudRate; 
            T_PORT.DataReceived += new SerialDataReceivedEventHandler(T_PORT_DataReceivedHandler);

            Timer_TEST.Enabled = false;
            Timer_TEST.Tick += new EventHandler(Timering_TEST_Tick);
            Timer_TEST.Interval = 1000;

            LST_TEST.CellValueChanged += new DataGridViewCellEventHandler(LST_TEST_CellValueChanged);

            Timer_BLINK.Enabled = false;
            Timer_BLINK.Tick += new EventHandler(Timering_BLINK_Tick);
            Timer_BLINK.Interval = 500;

            Timer_BLINK_COM_TXRX.Enabled = false;
            Timer_BLINK_COM_TXRX.Tick += new EventHandler(Timering_Blink_COM_TXRX_Tick);
            Timer_BLINK_COM_TXRX.Interval = 600;

            Timer_Timeout.Enabled = true;
            Timer_Timeout.Tick += new EventHandler(Timer_Timeout_Tick);
            Timer_Timeout.Interval = 100;

            Timer_Timeout_Receive_TagStart.Enabled = false;
            Timer_Timeout_Receive_TagStart.Tick += new EventHandler(Timer_Timeout_Receive_TagStart_Tick);
            Timer_Timeout_Receive_TagStart.Interval = 1000;

            RunExe = new ProcessContainer();

        }

        private void Timer_Timeout_Receive_TagStart_Tick(object sender, EventArgs e)
        {
            Timer_Timeout_Receive_TagStart.Enabled = false;
            //MessageBox.Show("تگ شروع از سیستم دریافت نگردید");

            get_string_port = "";
            get_string_port_in = true;


        }

        void Checking_TimeOut_Receive_TagStart()
        {
            if (int.Parse(Test_Attr[test_number].WaitAnswer) <= 60000)
            {
                if (int.Parse(Test_Attr[test_number].WaitAnswer) > 10)
                {
                    Timer_Timeout_Receive_TagStart.Interval = (int.Parse(Test_Attr[test_number].WaitAnswer) - 10);
                }
                else
                {
                    Timer_Timeout_Receive_TagStart.Interval = 1;
                }
            }
            else
            {
                Timer_Timeout_Receive_TagStart.Interval = 60000;
            }

            Timer_Timeout_Receive_TagStart.Enabled = true;
        }

        private void Timer_Timeout_Tick(object sender, EventArgs e)
        {
            try
            {
                if (time_out!=0)
                {
                    time_out-=100;
                }
                My_Form.lbl_view_timeout.Text = "زمان باقیمانده " + time_out + " میلی ثانیه می باشد ";
            }
            catch (Exception er)
            {

            }
        }

        private void T_PORT_DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            if (T_PORT.IsOpen)
            {

                if (get_string_port.IndexOf("<TEST_BENCH:") != -1)
                {
                    Timer_Timeout_Receive_TagStart.Enabled = false;
                }

                get_string_port += T_PORT.ReadExisting();
                get_string_port_in = true;
                mode_com_txrx = 2;
            }
        }

        public Boolean Start_Test(String Com)
        {
            My_Form.BAR_Proccess.Maximum = My_Form.Max_Test + 1;
            My_Form.BAR_Proccess.Value = My_Form.BAR_Proccess.Maximum;

            MessageBox.Show("سریال انتخابی " + My_Form.SerialDeviceInExcel + " می باشد");

            MessageBox.Show("لطفا سیستم تست شونده و تست کننده را ریست نمایید");

            My_Form.lst_devies.Enabled = false;

            T_PORT.Dispose();
            T_PORT.PortName = Com;
            T_PORT.Open();

            time_all_tests = 0;
            Timer_TEST.Start();
            Timer_BLINK_COM_TXRX.Start();

            

            mode_test = true;
            test_number = 0;

            My_Form.txt_explanation.Text = "";
            My_Form.txt_state.Text = "سیستم در حال تست می باشد";
            My_Form.BAR_Proccess.Value = test_number * 10;

            My_Form.Mode_Test = 2;

            try
            {
                My_Form.BoardPicture.Image = Image.FromFile(My_Form.BoardPictureFile);
            }
            catch (Exception er)
            {

            }

            return true;

        }

        public Boolean ReStart_Test(String Com)
        {

            My_Form.lst_devies.Enabled = false;
            System.Windows.Forms.ToolTip My_ToolTip = new System.Windows.Forms.ToolTip();

            //Add items
            LST_TEST.Rows.Clear();
            int index_item = 0;

            foreach (var buffer in Test_Attr)
            {
                LST_TEST.Rows.Add();

                LST_TEST.Rows[index_item].Cells[0].ToolTipText = buffer.Explanation;
                LST_TEST.Rows[index_item].Cells[1].ToolTipText = buffer.Explanation;
                LST_TEST.Rows[index_item].Cells[2].ToolTipText = buffer.Explanation;

                if (My_Form.checkboxenableHeader.Checked == true)
                {
                    LST_TEST.Rows[index_item].Cells[0].Value = true;
                }
                else if (Convert.ToBoolean(buffer.FB_Checked))
                {
                    LST_TEST.Rows[index_item].Cells[0].Value = true;
                }
                else
                {
                    LST_TEST.Rows[index_item].Cells[0].Value = false;
                }

                Test_Attr[index_item].ValueField = "";
                Test_Attr[index_item].Value = "";

                LST_TEST.Rows[index_item].Cells[1].Value = Properties.Resources.none;
                LST_TEST.Rows[index_item].Cells[2].Value = buffer.Description;
                index_item++;
            }
            LST_TEST.Update();


            MessageBox.Show("لطفا موارد تست خود را انتخاب کرده و سپس تست را شروع کنید");

            My_Form.txt_state.Text = "برای شروع کلیک کنید";

            My_Form.Mode_Test = 1;

            return true;
        }

        public void Stop_Test()
        {

            T_PORT.Close();
            Timer_TEST.Stop();
            My_Form.Mode_Test = 0;

            test_number = 0;
            mode_test = true;
            Timer_TEST.Interval = 1;

            mode_com_txrx = 0;


            My_Form.txt_explanation.Text = "";
            My_Form.txt_state.Text = "برای شروع مجدد کلیک کنید";
            My_Form.BAR_Proccess.Value = My_Form.BAR_Proccess.Maximum;
            My_Form.restart.Image = Properties.Resources.reset;

            My_Form.lst_devies.Enabled = true;
            My_Form.next.Enabled = false;
            My_Form.replay.Enabled = false;
            Timer_Timeout_Receive_TagStart.Enabled = false;
            Timer_Timeout.Enabled = false;

            DialogResult dialogResult = MessageBox.Show("آیا اطلاعات تست ذخیره شود ؟", "ExcelFile", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                MyXmlFile.MyExelFile.Save(My_Form.Device_Index_In_Excel, My_Form.SerialDeviceInExcel, Test_Attr, time_all_tests);
            }

            
        }

        private void Timering_BLINK_Tick(object sender, EventArgs e)
        {
            try
            {
                if (mode_test == false)
                {
                    if (mode_blink == true)
                    {
                        try
                        {
                            Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                            Pen PenStyle = new Pen(Color.White, 4);

                            g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2)-int.Parse(Test_Attr[test_number].ElementPosY1)));

                            My_Form.BoardPicture.Refresh();
                        }
                        catch (Exception er)
                        {

                        }

                        LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.White;
                        mode_blink = false;
                    }
                    else
                    {

                        try
                        {
                            Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                            Pen PenStyle = new Pen(Color.CadetBlue, 4);

                            g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                            My_Form.BoardPicture.Refresh();
                        }
                        catch (Exception er)
                        {

                        }

                        LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.CadetBlue;
                        mode_blink = true;
                    }


                    if (get_string_port_in)
                    {
                        if (get_string_port.IndexOf("</TEST_BENCH>") != -1)
                        {
                            Timer_BLINK.Stop();
                            Timer_TEST.Interval = 100;
                        }
                        get_string_port_in = false;
                    }
                }

            }
            catch (Exception we)
            {
                //My_Form.MyLogFile.Save(we.ToString());
            }

        }

        private void Timering_Blink_COM_TXRX_Tick(object sender, EventArgs e)
        {
            try
            {
                if (mode_com_txrx == 1)
                {
                        My_Form.img_connect.Image = Properties.Resources.com_tx;
                        mode_com_txrx = 0;
                }
                else if (mode_com_txrx == 2)
                {
                        My_Form.img_connect.Image = Properties.Resources.com_rx;
                        mode_com_txrx = 0;
                }
                else
                {
                    My_Form.img_connect.Image = Properties.Resources.connect;
                }

            }
            catch (Exception we)
            {
                //My_Form.MyLogFile.Save(we.ToString());
            }
        }

        private void LST_TEST_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            int index_item = 0;
            Boolean Enable_Test = false;
            foreach (var buffer in Test_Attr)
            {
                try
                {
                    Enable_Test = false;
                    Enable_Test = (Convert.ToBoolean(LST_TEST.Rows[index_item].Cells[0].Value));
                    Test_Attr[index_item].FB_Checked = Enable_Test.ToString();
                }
                catch (Exception we)
                {
                    break;
                }
                index_item++;
            }

        }

        private void LST_TEST_Checked_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            int index_item = 0;
            Boolean Enable_Test = false;
            foreach (var buffer in Test_Attr)
            {
                try
                {
                    Enable_Test = false;
                    Enable_Test = (Convert.ToBoolean(LST_TEST.Rows[index_item].Cells[0].Value));
                    Test_Attr[index_item].FB_Checked = Enable_Test.ToString();
                }
                catch (Exception we)
                {
                    break;
                }
                index_item++;
            }

        }

        private void Threading_Proccess_Tick(object state)
        {
            //{
            try
            {
                List<string> output = RunExe.RunProcessGrabOutput(Test_Attr[test_number].RunExe, Test_Attr[test_number].Data);

                get_string_port = "<TEST_BENCH:" + Test_Attr[test_number].Command + ">";
                mode_com_txrx = 2;

                if (output != null)
                {
                    foreach (string line in output)
                    {
                        get_string_port += line;
                    }
                }
                else
                {
                    Console.WriteLine("Unable to start program.");
                }

                get_string_port += "</TEST_BENCH>\r\n";

                Timer_Timeout_Receive_TagStart.Enabled = false;
                get_string_port_in = true;

                //MessageBox.Show(get_string_port);
            }
            catch
            {
                // Log error.
            }
            //}
        }

        private void Timering_TEST_Tick(object sender, EventArgs e)
        {
            if (mode_test)
            {

                if (test_number >= Test_Attr.Length)
                {
                    Stop_Test();
                    return;
                }

                Timer_TEST.Stop();
                My_Form.replay.Enabled = false;
                My_Form.next.Enabled = false;
                try
                {
                    Boolean Enable_Test = false;
                    Enable_Test = (Convert.ToBoolean(LST_TEST.Rows[test_number].Cells[0].Value));
                    mode_test = false;
                    if (Enable_Test)
                    {

                        LST_TEST.CurrentCell = LST_TEST.Rows[test_number].Cells[0];

                        if (Test_Attr[test_number].EnableIf != "")
                        {
                            int index_value = 0;
                            for (index_value = 0; index_value < Test_Attr.Length; index_value++)
                            {
                                if (Test_Attr[index_value].Value != null)
                                {
                                    if (Test_Attr[test_number].EnableIf.IndexOf(Test_Attr[index_value].Value) != -1)
                                    {
                                        index_value = 0;
                                        break;
                                    }
                                }

                            }
                            if ((index_value + 1) >= Test_Attr.Length)
                            {
                                MessageBox.Show("این مورد به دلیل وابستگی انجام نمی شود");
                                test_number++;
                                mode_test = true;
                            }
                        }

                        if(mode_test == false)
                        {
                            get_string_port = T_PORT.ReadExisting();
                            get_string_port = "";
                            String Data_Buffer = Test_Attr[test_number].Data;
                            Boolean Report = false;
                            if (Test_Attr[test_number].EnableLoop != "")
                            {
                                My_Form.En_Loop.Checked = (Convert.ToBoolean(Test_Attr[test_number].EnableLoop));
                            }
                            else
                            {
                                My_Form.En_Loop.Checked = My_Form.EnableLoop;
                            }

                            if (Test_Attr[test_number].EnableNext != "")
                            {
                                My_Form.En_Next.Checked = (Convert.ToBoolean(Test_Attr[test_number].EnableNext));
                            }
                            else
                            {
                                My_Form.En_Next.Checked = My_Form.EnableNext;
                            }

                            My_Form.txt_explanation.Text = Test_Attr[test_number].Explanation;

                            if (Test_Attr[test_number].Alert != "")
                            {
                                MessageBox.Show(Test_Attr[test_number].Alert);
                            }

                            if (Test_Attr[test_number].AskData != "" && Test_Attr[test_number].Data.IndexOf("#AskData") != -1)
                            {
                                InputMessage.InputBox(My_Form.Text, Test_Attr[test_number].AskData, ref Buffer_AskData);
                                Data_Buffer = Test_Attr[test_number].Data.Replace("#AskData", Buffer_AskData);
                            }

                            if (Test_Attr[test_number].Data.IndexOf("#DateTime") != -1)
                            {
                                DateTime Now = DateTime.Now;
                                PersianCalendar pc = new PersianCalendar();

                                Data_Buffer = pc.GetYear(Now).ToString("0000") + "-" + pc.GetMonth(Now).ToString("00") + "-" + pc.GetDayOfMonth(Now).ToString("00") + " " + DateTime.Now.ToString("HH:mm:ss");
                                DateTime_Buffer = Data_Buffer;
                            }
                            else if (Test_Attr[test_number].Data.IndexOf("#Serial") != -1)
                            {
                                Data_Buffer = My_Form.SerialDeviceInExcel;
                            }
                            else if (Test_Attr[test_number].Data.IndexOf("#Report") != -1)
                            {
                                DateTime Now = DateTime.Now;
                                PersianCalendar pc = new PersianCalendar();
                                int Report_Number_Test = 0;
                                Boolean Report_Enable_Test = false;
                                UInt64 Report_Passes_Tests = 0;

                                foreach (var buffer in Test_Attr)
                                {
                                    Report_Enable_Test = (Convert.ToBoolean(LST_TEST.Rows[Report_Number_Test].Cells[0].Value));
                                    if ((buffer.ValueField.IndexOf("#TEST_CHECKED_IN_EXCEL_NO") != -1) || (Report_Enable_Test == false))
                                    {
                                        if ((buffer.Data.IndexOf("#Report") == -1))
                                        {
                                            UInt64 Report_Passes_Tests_Set = 1;
                                            Report_Passes_Tests |= (Report_Passes_Tests_Set << Report_Number_Test);
                                        }
                                    }

                                    Report_Number_Test++; 
                                }

                                Data_Buffer = My_Form.SerialDeviceInExcel + " " + pc.GetYear(Now).ToString("0000") + "/" + pc.GetMonth(Now).ToString("00") + "/" + pc.GetDayOfMonth(Now).ToString("00") + " " + Report_Passes_Tests;
                                Test_Attr[test_number].Data = "#Report " + Data_Buffer;
                            }

                            if (Test_Attr[test_number].RunExe == "")
                            {
                                T_PORT.WriteLine("<TEST_BENCH:" + Test_Attr[test_number].Command + ">" + Data_Buffer + "</TEST_BENCH>" + Environment.NewLine);
                            }
                            else
                            {
                                System.Threading.ThreadPool.QueueUserWorkItem(new System.Threading.WaitCallback(Threading_Proccess_Tick));
                            }

                            Checking_TimeOut_Receive_TagStart();

                            mode_com_txrx = 1;
                            try
                            {
                                Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                Pen PenStyle = new Pen(Color.White, 4);

                                g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                My_Form.BoardPicture.Refresh();
                            }
                            catch (Exception er)
                            {

                            }
                            LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.White;
                            LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.wait;
                            Timer_BLINK.Start();
                            LST_TEST.Refresh();
                            Timer_TEST.Interval = int.Parse(Test_Attr[test_number].WaitAnswer);
                            time_out = Timer_TEST.Interval;

                        }
                    }
                    else
                    {
                        mode_test = true;
                        Timer_TEST.Interval = 1;
                        test_number++;
                    }
                }
                catch (Exception we)
                {
                    mode_test = true;
                }
                Timer_TEST.Start();

            }
            else
            {
                time_all_tests += Timer_TEST.Interval;
                time_out = 0;
                Timer_BLINK.Stop();
                Timer_TEST.Stop();
                try
                {

                    if (Test_Attr[test_number].Promp != "" && get_string_port != "")
                    {
                        DialogResult dialogResult = MessageBox.Show(Test_Attr[test_number].Promp, "Promp", MessageBoxButtons.YesNo);
                        if (dialogResult == DialogResult.Yes)
                        {
                            try
                            {
                                Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                Pen PenStyle = new Pen(Color.Green, 4);

                                g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                My_Form.BoardPicture.Refresh();
                            }
                            catch (Exception er)
                            {

                            }
                            LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Green;
                            LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.ok;
                            LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageOK;
                            Test_Attr[test_number].Value = Test_Attr[test_number].Command;
                        }
                        else if (dialogResult == DialogResult.No)
                        {
                            try
                            {
                                Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                Pen PenStyle = new Pen(Color.Red, 4);

                                g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                My_Form.BoardPicture.Refresh();
                            }
                            catch (Exception er)
                            {

                            }
                            LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Red;
                            LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.error;
                            LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageNO;
                            Test_Attr[test_number].Value = "#Error";
                        }
                    }
                    else if (get_string_port != "")
                    {
                        if (Test_Attr[test_number].MustAnswer != "")
                        {
                            if (Test_Attr[test_number].MustAnswer.IndexOf("#Return_Data") != -1)
                            {
                                int start_get_string_port = get_string_port.IndexOf(">") + 1;
                                int length_get_string_port = get_string_port.IndexOf("</") - start_get_string_port;
                                LST_TEST.Rows[test_number].Cells[2].Value = get_string_port.Substring(start_get_string_port, length_get_string_port);



                                bool error_Words_Returndata = false;
                                if (Test_Attr[test_number].ExceptAnswer != "")
                                {
                                    string[] Words_ExceptAnswer = Test_Attr[test_number].ExceptAnswer.Split('|');
                                    foreach (string buffer in Words_ExceptAnswer)
                                    {
                                        if (LST_TEST.Rows[test_number].Cells[2].Value.ToString().IndexOf(buffer) != -1)
                                        {
                                            error_Words_Returndata = true;
                                            break;
                                        }
                                    }
                                }

                                if (error_Words_Returndata)
                                {
                                    try
                                    {
                                        Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                        Pen PenStyle = new Pen(Color.Red, 4);

                                        g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                        My_Form.BoardPicture.Refresh();
                                    }
                                    catch (Exception er)
                                    {

                                    }
                                    LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Red;
                                    LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.error;
                                    Test_Attr[test_number].Value = "#Error";
                                }
                                else
                                {
                                    try
                                    {
                                        Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                        Pen PenStyle = new Pen(Color.Green, 4);

                                        g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                        My_Form.BoardPicture.Refresh();
                                    }
                                    catch (Exception er)
                                    {

                                    }
                                    LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Green;
                                    LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.ok;
                                    Test_Attr[test_number].Value = Test_Attr[test_number].Command;
                                }
                            }
                            else if (Test_Attr[test_number].MustAnswer.IndexOf("#Return_Date") != -1)
                            {
                                int start_get_string_port = get_string_port.IndexOf(">") + 1;
                                int length_get_string_port = get_string_port.IndexOf("</") - start_get_string_port;

                                LST_TEST.Rows[test_number].Cells[2].Value = get_string_port.Substring(start_get_string_port, length_get_string_port);


                                bool error_Words_Returndata = false;
                                if (Test_Attr[test_number].ExceptAnswer != "")
                                {
                                    string[] Words_ExceptAnswer = Test_Attr[test_number].ExceptAnswer.Split('|');
                                    foreach (string buffer in Words_ExceptAnswer)
                                    {
                                        if (buffer.IndexOf("#DateTime") != -1)
                                        {
                                            if (LST_TEST.Rows[test_number].Cells[2].Value.ToString().IndexOf(DateTime_Buffer) != -1)
                                            {
                                                error_Words_Returndata = true;
                                                break;
                                            }
                                        }
                                        else if (LST_TEST.Rows[test_number].Cells[2].Value.ToString().IndexOf(buffer) != -1)
                                        {
                                            error_Words_Returndata = true;
                                            break;
                                        }
                                    }
                                }

                                if (LST_TEST.Rows[test_number].Cells[2].Value.ToString().IndexOf(DateTime.Now.ToString("yy/MM/dd").ToString()) == -1)
                                {
                                    error_Words_Returndata = true;
                                }



                                if (error_Words_Returndata)
                                {
                                    try
                                    {
                                        Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                        Pen PenStyle = new Pen(Color.Red, 4);

                                        g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                        My_Form.BoardPicture.Refresh();
                                    }
                                    catch (Exception er)
                                    {

                                    }
                                    LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Red;
                                    LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.error;
                                    Test_Attr[test_number].Value = "#Error";
                                }
                                else
                                {
                                    try
                                    {
                                        Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                        Pen PenStyle = new Pen(Color.Green, 4);

                                        g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                        My_Form.BoardPicture.Refresh();
                                    }
                                    catch (Exception er)
                                    {

                                    }
                                    LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Green;
                                    LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.ok;
                                    Test_Attr[test_number].Value = Test_Attr[test_number].Command;
                                }
                            }
                            else
                            {
                                if (Test_Attr[test_number].MustAnswer.IndexOf("#SerialDeviceInExcel") != -1)
                                {
                                    if (get_string_port.IndexOf(My_Form.SerialDeviceInExcel) != -1)
                                    {
                                        try
                                        {
                                            Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                            Pen PenStyle = new Pen(Color.Green, 4);

                                            g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                            My_Form.BoardPicture.Refresh();
                                        }
                                        catch (Exception er)
                                        {

                                        }
                                        LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Green;
                                        LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.ok;
                                        Test_Attr[test_number].Value = Test_Attr[test_number].Command;
                                        LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageOK;
                                    }
                                    else
                                    {
                                        try
                                        {
                                            Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                            Pen PenStyle = new Pen(Color.Red, 4);

                                            g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                            My_Form.BoardPicture.Refresh();
                                        }
                                        catch (Exception er)
                                        {

                                        }
                                        LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Red;
                                        LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.error;
                                        Test_Attr[test_number].Value = "#Error";
                                        LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageNO;
                                    }
                                }
                                else
                                {
                                    if (get_string_port.IndexOf(Test_Attr[test_number].MustAnswer) != -1)
                                    {
                                        try
                                        {
                                            Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                            Pen PenStyle = new Pen(Color.Green, 4);

                                            g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                            My_Form.BoardPicture.Refresh();
                                        }
                                        catch (Exception er)
                                        {

                                        }
                                        LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Green;
                                        LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.ok;
                                        Test_Attr[test_number].Value = Test_Attr[test_number].Command;

                                        if (Test_Attr[test_number].ExceptAnswer != "")
                                        {
                                            if (Test_Attr[test_number].ExceptAnswer.IndexOf("#Return_Date") != -1)
                                            {
                                                int start_get_string_port = get_string_port.IndexOf(">") + 1;
                                                int length_get_string_port = get_string_port.IndexOf("</") - start_get_string_port;

                                                LST_TEST.Rows[test_number].Cells[2].Value = get_string_port.Substring(start_get_string_port, length_get_string_port);
                                            }
                                        }
                                        else
                                        {
                                            LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageOK;
                                        }
                                    }
                                    else
                                    {
                                        try
                                        {
                                            Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                            Pen PenStyle = new Pen(Color.Red, 4);

                                            g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                            My_Form.BoardPicture.Refresh();
                                        }
                                        catch (Exception er)
                                        {

                                        }
                                        LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Red;
                                        LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.error;
                                        Test_Attr[test_number].Value = "#Error";
                                        LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageNO;
                                    }
                                }
                            }
                        }
                        else
                        {
                            try
                            {
                                Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                                Pen PenStyle = new Pen(Color.Green, 4);

                                g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                                My_Form.BoardPicture.Refresh();
                            }
                            catch (Exception er)
                            {

                            }
                            LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Green;
                            LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.ok;
                            Test_Attr[test_number].Value = Test_Attr[test_number].Command;
                            LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageOK;
                        }
                    }
                    else
                    {
                        try
                        {
                            Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                            Pen PenStyle = new Pen(Color.Red, 4);

                            g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                            My_Form.BoardPicture.Refresh();
                        }
                        catch (Exception er)
                        {

                        }
                        LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Red;
                        LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.error;
                        Test_Attr[test_number].Value = "#Error";
                        LST_TEST.Rows[test_number].Cells[2].Value = "تگ شروع از سیستم دریافت نگردید";
                    }
                    Timer_TEST.Interval = 500;

                }
                catch (Exception we)
                {

                    try
                    {
                        Graphics g = Graphics.FromImage(My_Form.BoardPicture.Image);
                        Pen PenStyle = new Pen(Color.Red, 4);

                        g.DrawRectangle(PenStyle, int.Parse(Test_Attr[test_number].ElementPosX1), int.Parse(Test_Attr[test_number].ElementPosY1), (int.Parse(Test_Attr[test_number].ElementPosX2) - int.Parse(Test_Attr[test_number].ElementPosX1)), (int.Parse(Test_Attr[test_number].ElementPosY2) - int.Parse(Test_Attr[test_number].ElementPosY1)));

                        My_Form.BoardPicture.Refresh();
                    }
                    catch (Exception er)
                    {

                    }
                    LST_TEST.Rows[test_number].DefaultCellStyle.BackColor = Color.Red;
                    LST_TEST.Rows[test_number].Cells[1].Value = Properties.Resources.error;
                    Test_Attr[test_number].Value = "#Error";
                    LST_TEST.Rows[test_number].Cells[2].Value = Test_Attr[test_number].MessageNO;
                }

                Test_Attr[test_number].ValueField = "";
                if (Test_Attr[test_number].ExcelField != "")
                {
                    if(LST_TEST.Rows[test_number].Cells[2].Value.ToString().IndexOf(Test_Attr[test_number].MessageOK) != -1)
                    {
                        Test_Attr[test_number].ValueField = "#TEST_CHECKED_IN_EXCEL_OK";
                    }
                    else if (LST_TEST.Rows[test_number].Cells[2].Value.ToString().IndexOf(Test_Attr[test_number].MessageNO) != -1)
                    {
                        Test_Attr[test_number].ValueField = "#TEST_CHECKED_IN_EXCEL_NO";
                    }
                    else
                    {
                        Test_Attr[test_number].ValueField = LST_TEST.Rows[test_number].Cells[2].Value.ToString();
                    }
                }

                if ((Test_Attr[test_number].Value.IndexOf("#Error") != -1) && (My_Form.En_Loop.Checked))
                {
                    Timer_TEST.Start();
                }
                else if ((Test_Attr[test_number].Value.IndexOf("#Error") == -1) && My_Form.En_Next.Checked)
                {
                    test_number++;
                    Timer_TEST.Start();
                }

                get_string_port = "";
                My_Form.replay.Enabled = true;
                My_Form.next.Enabled = true;

                My_Form.BAR_Proccess.Value = test_number + 1;
                mode_test = true;
            }

            LST_TEST.Update();

        }

        private void LST_TEST_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb = (ComboBox)sender;
            string item = cb.Text;

            if (item != null)
            {
                MessageBox.Show(item);
            }
        }

        private void checkboxenableHeader_CheckedChanged(object sender, EventArgs e)
        {
            for (int index_item = 0; index_item < LST_TEST.RowCount; index_item++)
            {
                LST_TEST.Rows[index_item].Cells[0].Value = My_Form.checkboxenableHeader.Checked;
            }

            My_Form.restart.Focus();
            LST_TEST.Update();

        }





    }

      
}

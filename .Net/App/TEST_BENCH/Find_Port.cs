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

namespace TEST_BENCH
{
    public class Find_Port
    {
        MainForm My_Form;
        public Timer Timer_Search_Port = new Timer();
        SerialPort T_PORT = new SerialPort("COM0", 115200, Parity.None, 8, StopBits.One);
        int Port_nummber = 0; //COM0
        Boolean mode_search_port = true;
        public String Port_Find = "";
        String get_string_port;
        List<string> portsname;

        public Find_Port(MainForm My_MainForm)
        {
            My_Form = My_MainForm;

            Timer_Search_Port.Enabled = false;
            Timer_Search_Port.Tick += new EventHandler(Timering_SEARCH_PORT_Tick);
            Timer_Search_Port.Interval = 10;
            Timer_Search_Port.Stop();

            T_PORT.DiscardNull = true;
            T_PORT.DtrEnable = true;
            T_PORT.RtsEnable = true;
            T_PORT.BaudRate = My_Form.BoudRate;
            T_PORT.WriteBufferSize = 20;

            portsname = new List<string>();
            portsname.Clear();
            foreach (string NCom in System.IO.Ports.SerialPort.GetPortNames())
            {
                portsname.Add(NCom);
            }
            My_Form.BAR_Proccess.Maximum = portsname.Count;

        }

        public void Search()
        {

            Port_Find = "";
            Timer_Search_Port.Start();
        }

        private void Timering_SEARCH_PORT_Tick(object sender, EventArgs e)
        {

            try
            {
                if (mode_search_port)
                {

                    if (Port_nummber >= My_Form.BAR_Proccess.Maximum)
                    {
                        Port_nummber = 0;
                    }
                    
                    My_Form.BAR_Proccess.Value = Port_nummber;
                    try
                    {
                        T_PORT.PortName = portsname[Port_nummber];
                        T_PORT.Open();
                        mode_search_port = false;
                        T_PORT.Write("FIND=" + My_Form.MySerial + Environment.NewLine);
                        Timer_Search_Port.Interval = 3000;
                    }
                    catch (Exception we)
                    {
                        //My_Form.MyLogFile.Save(we.ToString());
                        mode_search_port = true;
                    }

                    Port_nummber++;
                }

                else
                {

                    try
                    {

                        if (T_PORT.IsOpen)
                        {
                            get_string_port = T_PORT.ReadExisting();
                        }

                        if (get_string_port.IndexOf("OK\r\n") != -1)
                        {
                            T_PORT.DiscardInBuffer();
                            My_Form.BAR_Proccess.Value = My_Form.BAR_Proccess.Maximum;
                            Timer_Search_Port.Stop();
                            Port_Find = portsname[Port_nummber-1];
                            T_PORT.Close();
                            My_Form.Find_Port();
                        }
                        else
                        {
                            T_PORT.Close();
                        }
                    }
                    catch (Exception we)
                    {
                        //My_Form.MyLogFile.Save(we.ToString());
                        T_PORT.Close();
                    }

                    Timer_Search_Port.Interval = 10;
                    mode_search_port = true;
                }
                //--------------------------------------------------
            }
            catch (Exception we)
            {
                //My_Form.MyLogFile.Save(we.ToString());
            }
        }

    }


}

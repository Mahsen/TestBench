using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml.Linq;
using System.Runtime.InteropServices;
using System.Drawing.Text;
using System.Diagnostics;

namespace TEST_BENCH
{
    public partial class MainForm : Form
    {

        public int BoudRate;
        public int Max_Test;
        public byte Mode_Test = 0;
        public FontFamily My_Font;
        TestView MyListView;
        Find_Port MyFind_Port;
        public CheckBox checkboxenableHeader;

        public int Device_Index_In_Excel = -1;
        public String SerialDeviceInExcel;

        public bool EnableLoop = false;
        public bool EnableNext = false;

        public string BoardPictureFile = "";
        public string MySerial = "";
        public string MyVersion = "";

        public List<string> AllItems;
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {

            checkboxenableHeader = new CheckBox();

            next.Enabled = false;
            replay.Enabled = false;

            En_Loop.Checked = true;
            En_Next.Checked = true;

            System.Windows.Forms.ToolTip ToolTip1 = new System.Windows.Forms.ToolTip();

            ToolTip1.SetToolTip(this.next, "F1");
            ToolTip1.SetToolTip(this.replay, "F2");
            ToolTip1.SetToolTip(this.restart, "F3");

            lable_logo.Focus();
            restart.Image = Properties.Resources.reset;
            restart.Enabled = false;

            MyListView = new TestView(this);
            MyFind_Port = new Find_Port(this);

            MyFind_Port.Search();

        }

        public void Find_Port()
        {
            restart.Enabled = true;
            restart.Focus();

            img_connect.Image = Properties.Resources.connect;
            txt_state.Text = "پورت شناسایی گردید";
        }

        // load font family from byte array
        public FontFamily LoadFontFamily(byte[] buffer)
        {
            var handle = GCHandle.Alloc(buffer, GCHandleType.Pinned);
            try
            {
                var ptr = Marshal.UnsafeAddrOfPinnedArrayElement(buffer, 0);
                using (var pvc = new PrivateFontCollection())
                {
                    pvc.AddMemoryFont(ptr, buffer.Length);
                    return pvc.Families[0];
                }
            }
            finally
            {
                handle.Free();
            }
        }

        private void restart_Click(object sender, EventArgs e)
        {
            if (Mode_Test == 0)
            {
                if (Device_Index_In_Excel != -1)
                {
                    MyListView.ReStart_Test(MyFind_Port.Port_Find);
                    restart.Image = Properties.Resources.Play;
                }
                else
                {
                    MessageBox.Show("سریال سخت افزار انتخاب نشده است");
                }
            }
            else if (Mode_Test == 1)
            {
                MyListView.Start_Test(MyFind_Port.Port_Find);
                restart.Image = Properties.Resources.Stop;
            }
            else
            {
                MyListView.Stop_Test();
                restart.Image = Properties.Resources.reset;
            }


        }

        private void next_Click(object sender, EventArgs e)
        {
            //MyListView.test_number = 0;
            MyListView.mode_test = true;
            MyListView.Timer_TEST.Interval = 1;
            MyListView.test_number++;
            MyListView.Timer_TEST.Start();
        }

        private void replay_Click(object sender, EventArgs e)
        {
            //MyListView.test_number = 0;
            MyListView.mode_test = true;
            MyListView.Timer_TEST.Interval = 1;
            MyListView.Timer_TEST.Start();
        }


        private void Form_KeyDown(object sender, KeyEventArgs e)
        {
            if (next.Enabled && e.KeyCode == Keys.F1)
            {
                MyListView.test_number++;
                MyListView.mode_test = true;
                MyListView.Timer_TEST.Start();
            }
            else if(replay.Enabled && e.KeyCode == Keys.F2)
            {
                MyListView.Timer_TEST.Start();
            }
            else if (restart.Enabled && e.KeyCode == Keys.F3)
            {
                if (Mode_Test == 0)
                {
                    if (Device_Index_In_Excel != -1)
                    {
                        MyListView.ReStart_Test(MyFind_Port.Port_Find);
                        restart.Image = Properties.Resources.Play;
                    }
                    else
                    {
                        MessageBox.Show("سریال سخت افزار انتخاب نشده است");
                    }
                }
                else if (Mode_Test == 1)
                {
                     MyListView.Start_Test(MyFind_Port.Port_Find);
                     restart.Image = Properties.Resources.Stop;
                }
                else
                {
                    MyListView.Stop_Test();
                    restart.Image = Properties.Resources.reset;
                }
            }
        }


        private void lst_devies_CellContentClick(object sender, EventArgs e)
        {
            for (int i = 0; i < AllItems.Count; i++)
            {
                if (AllItems[i].Equals(lst_devies.Rows[lst_devies.CurrentRow.Index].Cells[0].Value.ToString()))
                {
                    Device_Index_In_Excel = i;
                    break;
                }
            }

            SerialDeviceInExcel = lst_devies.Rows[lst_devies.CurrentRow.Index].Cells[0].Value.ToString();
            label_device_info.Text = SerialDeviceInExcel;
        }

        private void lable_version_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Developer : https://Mahsen.ir");
        }

        private void SearchItem_TextChanged(object sender, EventArgs e)
        {
            lst_devies.Rows.Clear();
            String buffer_Serial = "";

            for (int i = 0; i < AllItems.Count; i++)
            {
                buffer_Serial = AllItems[i];
                if (buffer_Serial != "")
                {
                    if (buffer_Serial.IndexOf(SearchItem.Text) != -1)
                    {
                        lst_devies.Rows.Add(buffer_Serial);
                    }
                }
            }
        }

        private void lable_logo_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Company : https://saa.ir");
        }
    }
}

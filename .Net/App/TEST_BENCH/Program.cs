using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace TEST_BENCH
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {

            //Mutex mutex_of_TEST_BENCH = new System.Threading.Mutex(false, "TEST_BENCH");
            //try
            //{
                //if (mutex_of_TEST_BENCH.WaitOne(0, false))
                //{
                    // Run the application
                    Application.EnableVisualStyles();
                    Application.SetCompatibleTextRenderingDefault(false);
                    Application.Run(new MainForm());
                //}
                //else
                //{
                //    Process current = Process.GetCurrentProcess();
                //    foreach (Process process in Process.GetProcessesByName(current.ProcessName))
                //    {
                //        if (process.Id != current.Id)
                //        {
                //            SetForegroundWindow(process.MainWindowHandle);
                //            SetFocus(new HandleRef(null, process.Handle)); 
                //            break;
                //        }
                //    }
                //}
            //}
            //finally
            //{
            //    if (mutex_of_TEST_BENCH != null)
            //    {
            //        mutex_of_TEST_BENCH.Close();
            //        mutex_of_TEST_BENCH = null;
            //    }
            //}
        }

        [DllImport("user32.dll")]
        static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll")]
        static extern IntPtr SetFocus(HandleRef hWnd);
    }
}

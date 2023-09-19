using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace TEST_BENCH
{
    class ProcessContainer
    {
        private Process process;
        private List<string> processOutput = new List<string>();

        public void RunProcess()
        {

        }

        public List<string> RunProcessGrabOutput(string Executable, string Arguments)
        {
            try
            {
                process = new Process();
                processOutput.Clear();

                process.StartInfo.FileName = Executable;
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.WorkingDirectory = Path.GetDirectoryName(Executable);
                process.StartInfo.RedirectStandardInput = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.RedirectStandardError = true;
                process.StartInfo.StandardErrorEncoding = Encoding.UTF8;
                process.StartInfo.StandardOutputEncoding = Encoding.UTF8;
                process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                process.StartInfo.CreateNoWindow = true;

                if (!string.IsNullOrEmpty(Arguments))
                    process.StartInfo.Arguments = Arguments;

                process.EnableRaisingEvents = true;
                process.OutputDataReceived += new DataReceivedEventHandler(ProcessOutputHandler);
                process.ErrorDataReceived += new DataReceivedEventHandler(ProcessOutputHandler);
                process.Start();

                process.BeginOutputReadLine();
                process.BeginErrorReadLine();

                // You can set the priority only AFTER the you started the process.
                process.PriorityClass = ProcessPriorityClass.BelowNormal;
                process.WaitForExit();
            }
            catch
            {
                // This is how we indicate that something went wrong.
                processOutput = null;
            }

            return processOutput;
        }

        private void ProcessOutputHandler(object SendingProcess, DataReceivedEventArgs OutLine)
        {
            try
            {
                processOutput.Add(OutLine.Data + Environment.NewLine);                
            }
            catch
            {

            }
        }
    }
}

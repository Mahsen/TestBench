using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Windows;
using System.IO;
using System;
using Excel = Microsoft.Office.Interop.Excel;
using System.Drawing;
using System.Security.Cryptography;

namespace TEST_BENCH
{
    public class ExcelFile : Struct
    {
        MainForm My_Form;

        Excel.Application xlApp;
        Excel.Workbook xlWorkBook;
        Excel.Worksheet xlWorkSheet;
        Excel.Range xlRange;
        object misValue = System.Reflection.Missing.Value;

        int Start_Excel_Row = 0;
        String ExcelFileName;
        String ExcelSheetName;

        String ExcelCheckSum;

        public ExcelFile(MainForm My_MainForm)
        {
            My_Form = My_MainForm;
        }

        private int ColumnNameToNumber(string col_name)
        {
            int result = 0;

            // Process each letter.
            for (int i = 0; i < col_name.Length; i++)
            {
                result *= 26;
                char letter = col_name[i];

                // See if it's out of bounds.
                if (letter < 'A') letter = 'A';
                if (letter > 'Z') letter = 'Z';

                // Add in the value of this letter.
                result += (int)letter - (int)'A' + 1;
            }
            return result;
        }

        public void FileLoad(String FileName, String SheetName, String StartSerialsField, String CheckSum)
        {
            try
            {

                xlApp = new Excel.Application();
                ExcelFileName = FileName;
                ExcelSheetName = SheetName;

                ExcelCheckSum = CheckSum;

                xlWorkBook = xlApp.Workbooks.Open(Directory.GetCurrentDirectory() + "\\" + ExcelFileName);
                xlWorkSheet = xlWorkBook.Sheets[ExcelSheetName];
                xlWorkSheet = xlWorkBook.ActiveSheet;
                xlRange = xlWorkSheet.UsedRange;


                Start_Excel_Row = int.Parse(StartSerialsField.Substring(1, 1));
                String buffer_Serial = "";

                System.Windows.Forms.DataGridViewCellStyle style = new System.Windows.Forms.DataGridViewCellStyle();
                style.Font = new Font(My_Form.lst_devies.Font.FontFamily, 12, System.Drawing.FontStyle.Bold);
                My_Form.lst_devies.DefaultCellStyle = style;
                My_Form.lst_devies.AllowUserToAddRows = false;
                My_Form.lst_devies.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
                My_Form.lst_devies.RowTemplate.Height = 32;
                My_Form.lst_devies.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.None;
                My_Form.lst_devies.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.None;
                My_Form.lst_devies.AllowUserToResizeRows = false;
                My_Form.lst_devies.AllowUserToResizeColumns = false;
                My_Form.lst_devies.AutoSize = false;
                My_Form.lst_devies.BorderStyle = System.Windows.Forms.BorderStyle.None;
                My_Form.lst_devies.RowHeadersVisible = false;
                My_Form.lst_devies.ColumnHeadersVisible = false;

                My_Form.lst_devies.Columns.Add("","");
                My_Form.lst_devies.Columns[0].ReadOnly = true;
                My_Form.lst_devies.Columns[0].Width = My_Form.lst_devies.Width;

                My_Form.lst_devies.Rows.Clear();
                
                My_Form.AllItems = new List<string>();

                for (int i = Start_Excel_Row; i < 10000000; i++)
                {
                    buffer_Serial = xlRange.Range[StartSerialsField.Substring(0, 1) + i.ToString()].Text;
                    if (buffer_Serial != "")
                    {
                        My_Form.AllItems.Add(buffer_Serial);
                        My_Form.lst_devies.Rows.Add(buffer_Serial);
                    }
                    else
                    {
                        break;
                    }
                }

                xlWorkBook.Close();
            }
            catch (Exception e)
            {
                xlWorkBook.Close();
                MessageBox.Show("خطا در فایل excel");
                Environment.Exit(0);
            }
        }

        public void Save(int Row, String Serial, Struct_Test_Attr[] Test_Attr, long CheckSumA)
        {
            try
            {
                xlWorkBook = xlApp.Workbooks.Open(Directory.GetCurrentDirectory() + "\\" + ExcelFileName);
                xlWorkSheet = xlWorkBook.Sheets[ExcelSheetName];
                xlWorkSheet = xlWorkBook.ActiveSheet;
                xlRange = xlWorkSheet.UsedRange;


                foreach (var buffer in Test_Attr)
                {
                    if (buffer.ValueField.IndexOf("#TEST_CHECKED_IN_EXCEL_OK") != -1)
                    {
                        xlWorkSheet.Cells[Row + Start_Excel_Row, buffer.ExcelField] = "OK";
                        xlWorkSheet.Cells[Row + Start_Excel_Row, buffer.ExcelField].Font.Color = Color.Green;
                    }
                    else if (buffer.ValueField.IndexOf("#TEST_CHECKED_IN_EXCEL_NO") != -1)
                    {
                        xlWorkSheet.Cells[Row + Start_Excel_Row, buffer.ExcelField] = "NO";
                        xlWorkSheet.Cells[Row + Start_Excel_Row, buffer.ExcelField].Font.Color = Color.Red;
                    }
                    else
                    {
                        if (buffer.ValueField != "")
                        {
                            xlWorkSheet.Cells[Row + Start_Excel_Row, buffer.ExcelField] = buffer.ValueField;
                        }
                    }

                }

                String CheckSumB = CalculateMD5Hash(Row.ToString() + "<->" + Serial + "<->" + CheckSumA.ToString());

                xlWorkSheet.Cells[Row + Start_Excel_Row, ExcelCheckSum] = CheckSumA.ToString();
                xlWorkSheet.Cells[Row + Start_Excel_Row, ColumnNameToNumber(ExcelCheckSum) + 1] = CheckSumB;
                xlWorkSheet.Cells[Row + Start_Excel_Row, ColumnNameToNumber(ExcelCheckSum) + 2] = My_Form.MyVersion;

                xlWorkBook.Save();

                xlWorkBook.Close();

                MessageBox.Show("نتایج تست با موفقیت ذخیره گردید");
            }
            catch (Exception e)
            {
                xlWorkBook.Close();
                MessageBox.Show("خطا در فایل excel");
                Environment.Exit(0);
            }
        }

        public void UpdateField(String Value, String Column, int Row, Color FColor)
        {
            try
            {
                xlWorkBook = xlApp.Workbooks.Open(Directory.GetCurrentDirectory() + "\\" + ExcelFileName);
                xlWorkSheet = xlWorkBook.Sheets[ExcelSheetName];
                xlWorkSheet = xlWorkBook.ActiveSheet;
                xlRange = xlWorkSheet.UsedRange;

                xlWorkSheet.Cells[Row + Start_Excel_Row, Column] = Value;
                xlWorkSheet.Cells[Row + Start_Excel_Row, Column].Interior.Color = FColor;

                xlWorkBook.Save();

                xlWorkBook.Close();
            }
            catch (Exception e)
            {
                xlWorkBook.Close();
                MessageBox.Show("خطا در فایل excel");
                Environment.Exit(0);
            }
        }


        private string CalculateMD5Hash(string input)
        {
            // step 1, calculate MD5 hash from input
            MD5 md5 = System.Security.Cryptography.MD5.Create();
            byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(input);
            byte[] hash = md5.ComputeHash(inputBytes);

            // step 2, convert byte array to hex string
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < hash.Length; i++)
            {
                sb.Append(hash[i].ToString("X2"));
            }
            return sb.ToString();
        }
    }





}

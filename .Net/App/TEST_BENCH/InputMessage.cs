using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

class InputMessage
{
    public static DialogResult InputBox(string title, string promptText, ref string value)
    {
        Form form = new Form();
        Label label = new Label();
        TextBox textBox = new TextBox();
        Button buttonOk = new Button();
        Button buttonCancel = new Button();

        form.Text = title;
        label.Text = promptText;
        textBox.Text = value;

        buttonOk.Text = "OK";
        buttonCancel.Text = "Cancel";
        buttonOk.DialogResult = DialogResult.OK;
        buttonCancel.DialogResult = DialogResult.Cancel;

        label.SetBounds(9, 20, 372, 13);
        textBox.SetBounds(12, 36, 372, 20);
        buttonOk.SetBounds(228, 72, 75, 23);
        buttonCancel.SetBounds(309, 72, 75, 23);

        label.AutoSize = true;
        textBox.Anchor = textBox.Anchor | AnchorStyles.Right;
        buttonOk.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
        buttonCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;

        form.ClientSize = new Size(396, 107);
        form.Controls.AddRange(new Control[] { label, textBox, buttonOk, buttonCancel });
        form.ClientSize = new Size(Math.Max(300, label.Right + 10), form.ClientSize.Height);
        form.FormBorderStyle = FormBorderStyle.FixedDialog;
        form.StartPosition = FormStartPosition.CenterScreen;
        form.MinimizeBox = false;
        form.MaximizeBox = false;
        form.AcceptButton = buttonOk;
        form.CancelButton = buttonCancel;

        DialogResult dialogResult = form.ShowDialog();
        value = textBox.Text;
        return dialogResult;
    }


    public static int InputListBox(string title, string promptText, List<String> List)
    {
        Form form = new Form();
        Label label = new Label();
        ComboBox lst_select = new ComboBox();
        Button buttonOk = new Button();



        lst_select.Items.Clear();
        lst_select.Items.Add("انتخاب کنید");
        foreach (var buffer_List in List)
        {
            try
            {
                lst_select.Items.Add(buffer_List.ToString());
            }
            catch(Exception e)
            {

            }
        }
        lst_select.Update();
        lst_select.SelectedIndex = 0;


        form.Text = title;
        label.Text = promptText;

        buttonOk.Text = "OK";
        buttonOk.DialogResult = DialogResult.OK;

        label.SetBounds(270, 20, 372, 13);
        lst_select.SetBounds(12, 36, 512, 20);
        buttonOk.SetBounds(280, 72, 75, 23);

        label.AutoSize = true;
        lst_select.Anchor = lst_select.Anchor | AnchorStyles.Right;
        buttonOk.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;

        form.ClientSize = new Size(536, 107);
        form.Controls.AddRange(new Control[] { label, lst_select, buttonOk });
        form.ClientSize = new Size(Math.Max(440, label.Right + 10), form.ClientSize.Height);
        form.FormBorderStyle = FormBorderStyle.FixedDialog;
        form.StartPosition = FormStartPosition.CenterScreen;
        form.MinimizeBox = false;
        form.MaximizeBox = false;
        form.AcceptButton = buttonOk;

        DialogResult dialogResult = form.ShowDialog();

        if (dialogResult != DialogResult.OK)
        {
            Environment.Exit(0);
        }

        return lst_select.SelectedIndex;
    }

}


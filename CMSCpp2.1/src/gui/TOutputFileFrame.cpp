//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <FileCtrl.hpp>
//�����ؤ��Y���
#include "TOutputFileFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
__fastcall TOutputFileFrame::TOutputFileFrame(TComponent * Owner)
:TFrame(Owner), serialid(0)
{
}

//---------------------------------------------------------------------------
void __fastcall TOutputFileFrame::Button_BrowseDirClick(TObject * Sender)
{
    AnsiString Dir = this->Edit_Directory->Text;
    SelectDirectory("��ܥؿ�", "", Dir);
    this->Edit_Directory->Text = Dir + "\\";
}

//---------------------------------------------------------------------------
void TOutputFileFrame::createDir()
{
    AnsiString dir = this->Edit_Directory->Text;
    if (!DirectoryExists(dir)) {
	bool result = CreateDir(dir);
	if (!result) {
	    ShowMessage("Create " + dir + " is failed.");
	    return;
	}
    }
}

//---------------------------------------------------------------------------
bptr < AnsiString > TOutputFileFrame::getFullPrefix()
{
    String_ptr
	prefix(new AnsiString(this->Edit_Directory->Text + "\\" +
			      this->Edit_Prefix->Text));
    return prefix;
}

//---------------------------------------------------------------------------
bptr < AnsiString > TOutputFileFrame::getOutputFilename()
{
    String_ptr output(new
		      String(*getFullPrefix() +
			     FormatFloat("00", serialid++) + ".xls"));
    return output;
};


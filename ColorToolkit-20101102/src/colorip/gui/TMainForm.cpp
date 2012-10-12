
#pragma hdrstop
#include "TMainForm.h"
//C�t�Τ��                  

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���
#include <addresstype/Address_type.h>
//�����ؤ�gui�Y���
#include <colorip/gui/THSVV2Form.h>
#include <colorip/gui/TCMForm.h>
#include <gui/TExampleForm.h>
#include <colorip/gui/TSharpnessV1Form.h>
#include <colorip/gui/TSharpnessV2Form.h>
#include "include.h"
#include <iostream>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

TForm *FunctionForm;
TForm *CMForm;
TForm *SharpnessV1Form;
TForm *SharpnessV2Form;
TForm *CEForm;
TForm *HSVV1Form;
TForm *HSVV2Form;
TForm *C3DForm;
TForm *SATForm;
TForm *offsetForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner)
{
    //Set Real-Time Priority of process
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    //addr_place = 0;           //0:auo_12401_address.h   1:auo_12401_address.txt
    addressFromFile = false;
    C3D_type = 7;

    using namespace cms::util;
    if (Util::isFileExist("tcon.txt")) {
	setAddressFile("tcon.txt");
    }
    //if (Util::isFileExist("debug.txt")) {
    mn_Header2Address->Visible = true;
    //}


}

//---------------------------------------------------------------------------



void __fastcall TMainForm::mn_EngineerClick(TObject * Sender)
{
    EngineerForm->Show();
}

//---------------------------------------------------------------------------
 
void __fastcall TMainForm::mn_FunctionClick(TObject * Sender)
{
    if (FunctionForm != NULL)
	FunctionForm->Show();
    else {
	//if (TCON_DEV == "11307") {
	FunctionForm = new TFunctionForm(this);
	FunctionForm->Show();
	//}
    }

}

//---------------------------------------------------------------------------



void __fastcall TMainForm::FormClose(TObject * Sender, TCloseAction & Action)
{
    EngineerForm->FormClose(Sender, Action);

    if (FunctionForm != NULL) {
	FunctionForm->Close();
	FunctionForm = NULL;
	delete FunctionForm;
    }

    if (CMForm != NULL) {
	CMForm->Close();
	CMForm = NULL;
	delete CMForm;
    }
    if (SharpnessV1Form != NULL) {
	SharpnessV1Form->Close();
	SharpnessV1Form = NULL;
	delete SharpnessV1Form;
    }
    if (SharpnessV2Form != NULL) {
	SharpnessV2Form->Close();
	SharpnessV2Form = NULL;
	delete SharpnessV2Form;
    }
    if (CEForm != NULL) {
	CEForm->Close();	// mask by Michelle 20100716
	CEForm = NULL;
	delete CEForm;
    }
    if (HSVV1Form != NULL) {
	HSVV1Form->Close();
	HSVV1Form = NULL;
	delete HSVV1Form;
    }
    if (HSVV2Form != NULL) {
	HSVV2Form->Close();
	HSVV2Form = NULL;
	delete HSVV2Form;
    }
    if (C3DForm != NULL) {
	C3DForm->Close();	// mask by Michelle 20100716
	C3DForm = NULL;
	delete C3DForm;
    }
    if (SATForm != NULL) {
	SATForm->Close();
	SATForm = NULL;
	delete SATForm;
    }
    if (offsetForm != NULL) {
	offsetForm->Close();
	offsetForm = NULL;
	delete offsetForm;
    }
}

//---------------------------------------------------------------------------
void TMainForm::closeAllForms()
{

    if (FunctionForm != NULL) {
	FunctionForm->Close();
	FunctionForm = NULL;
    }

    if (CMForm != NULL) {
	CMForm->Close();
	CMForm = NULL;
    }
    if (SharpnessV1Form != NULL) {
	SharpnessV1Form->Close();
	SharpnessV1Form = NULL;
    }
    if (SharpnessV2Form != NULL) {
	SharpnessV2Form->Close();
	SharpnessV2Form = NULL;
    }
    if (HSVV1Form != NULL) {
	HSVV1Form->Close();
	HSVV1Form = NULL;
    }
    if (HSVV2Form != NULL) {
	HSVV2Form->Close();
	HSVV2Form = NULL;
    }
    if (C3DForm != NULL) {
	C3DForm->Close();
	C3DForm = NULL;
    }
    if (SATForm != NULL) {
	SATForm->Close();
	SATForm = NULL;
    }
    if (offsetForm != NULL) {
	offsetForm->Close();
	offsetForm = NULL;
    }
}

void __fastcall TMainForm::AUO_11307Click(TObject * Sender)
{

    if (FunctionForm != NULL) {
	FunctionForm->Close();
	FunctionForm = NULL;
    }

    if (CMForm != NULL) {
	CMForm->Close();
	CMForm = NULL;
    }
    if (SharpnessV1Form != NULL) {
	SharpnessV1Form->Close();
	SharpnessV1Form = NULL;
    }
    if (HSVV1Form != NULL) {
	HSVV1Form->Close();
	HSVV1Form = NULL;
    }
    if (HSVV2Form != NULL) {
	HSVV2Form->Close();
	HSVV2Form = NULL;
    }
    if (C3DForm != NULL) {
	C3DForm->Close();
	C3DForm = NULL;
    }
    if (SATForm != NULL) {
	SATForm->Close();
	SATForm = NULL;
    }
    if (offsetForm != NULL) {
	offsetForm->Close();
	offsetForm = NULL;
    }
    //TCON_DEV = "11307";
    MainForm->Caption = "AUO 11307";
    mn_Function->Enabled = true;
    //mn_TCON->Enabled = true;
    //mn_DCR->Enabled = true;
    //mn_Vender->Enabled = true;
    mn_ImageProc->Enabled = true;
    mn_CE->Enabled = true;
    //mn_HSV->Enabled = true;
    mn_C3D->Enabled = true;
    mn_SAT->Enabled = true;
    mn_offset->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject * Sender)
{

    //TCON_DEV = "11307";               //default device
    //String info = getFileVersionInfo();
    //MainForm->Caption = "AUO 11307";
    MainForm->Caption = "Color Engine Toolkit";
    mn_Function->Enabled = true;
    //mn_TCON->Enabled = true;
    //mn_DCR->Enabled = true;
    //mn_Vender->Enabled = true;
    mn_ImageProc->Enabled = true;
    mn_CM->Enabled = true;
    mn_Sharpness->Enabled = true;
    mn_Sharpness12307->Enabled = true;
    mn_CE->Enabled = true;	// mask by Michelle 20100716
    mn_HSV2->Enabled = true;
    mn_C3D->Enabled = true;
    mn_SAT->Enabled = true;
    mn_offset->Enabled = true;
}

//---------------------------------------------------------------------------
void TMainForm::reload_all(TObject * Sender)
{
    /*mn_TCONClick(Sender);
       mn_FunctionClick(Sender);
       mn_DCRClick(Sender);
       mn_VenderClick(Sender);
       mn_CMClick(Sender);
       mn_SharpnessClick(Sender);
       mn_Sharpness12307Click(Sender);
       mn_CEClick(Sender);
       mn_HSVClick(Sender);
       mn_C3DClick(Sender);
       mn_SATClick(Sender);
       mn_offsetClick(Sender);
       TShiftState Shift;
       WORD Key = 0x40;
       TCONForm->OnKeyDown(Sender, Key, Shift);
       FunctionForm->OnKeyDown(Sender, Key, Shift);
       DCRForm->OnKeyDown(Sender, Key, Shift);
       VenderForm->OnKeyDown(Sender, Key, Shift);
       CMForm->OnKeyDown(Sender, Key, Shift);
       SharpnessForm->OnKeyDown(Sender, Key, Shift);
       SharpnessV2Form->OnKeyDown(Sender, Key, Shift);
       ContrastEnhanceForm->OnKeyDown(Sender, Key, Shift);      //mssk by Michelle 20100716
       HSVForm->OnKeyDown(Sender, Key, Shift);
       C3DForm->OnKeyDown(Sender, Key, Shift);  // mask by Michelle 20100716
       SATForm->OnKeyDown(Sender, Key, Shift);
       offsetForm->OnKeyDown(Sender, Key, Shift); */

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_CMClick(TObject * Sender)
{
    if (CMForm != NULL)
	CMForm->Show();
    else {
	//if (TCON_DEV == "11307") {
	CMForm = new TCMForm(this);
	CMForm->Show();
	//}

    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mn_SharpnessClick(TObject * Sender)
{
    if (SharpnessV1Form != NULL)
	SharpnessV1Form->Show();
    else {
	//if (TCON_DEV == "11307") {
	SharpnessV1Form = new TSharpnessV1Form(this);
	SharpnessV1Form->Show();
	//}

    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::FormMouseDown(TObject * Sender,
					 TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbRight) {
	TPoint pt = MainForm->ClientToScreen(Point(X, Y));
	PopupMenu1->Popup(pt.x, pt.y);
    }

}

//---------------------------------------------------------------------------

 // remove by Michelle 20100716
void __fastcall TMainForm::mn_CEClick(TObject * Sender)
{
    if (CEForm != NULL)
	CEForm->Show();
    else {
	//if (TCON_DEV == "11307") {
	CEForm = new TCEForm(this);
	CEForm->Show();
	//}
    }

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_HSVClick(TObject * Sender)
{
    if (HSVV1Form != NULL)
	HSVV1Form->Show();
    else {
	//if (TCON_DEV == "11307") {
	HSVV1Form = new THSVV1Form(this);
	//HSVForm = new THSVFormNew_(this);
	HSVV1Form->Show();
	//}
    }

}

//---------------------------------------------------------------------------


void __fastcall TMainForm::StatusBar1DblClick(TObject * Sender)
{
    //cb_address_txt->Visible = true;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
 //remove by Michelle 20100716
void __fastcall TMainForm::mn_C3DClick(TObject * Sender)
{
    if (C3DForm != NULL)
	C3DForm->Show();
    else {
	//if (TCON_DEV == "11307") {
	C3DForm = new TC3DForm(this);
	C3DForm->Show();
	//}
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_C3D_777Click(TObject * Sender)
{
    C3D_type = 7;
    if (C3DForm != NULL) {
	if (C3DForm->Hint == C3D_type) {
	    C3DForm->Show();
	    return;
	} else
	    C3DForm->Close();
    }
    //if (TCON_DEV == "11307") {
    C3DForm = new TC3DForm(this);
    C3DForm->Show();
    //}

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_C3D_999Click(TObject * Sender)
{
    C3D_type = 9;
    if (C3DForm != NULL) {
	if (C3DForm->Hint == C3D_type) {
	    C3DForm->Show();
	    return;
	} else
	    C3DForm->Close();
    }
    //if (TCON_DEV == "11307") {
    C3DForm = new TC3DForm(this);
    C3DForm->Show();
    //}

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_SATClick(TObject * Sender)
{
    if (SATForm != NULL)
	SATForm->Show();
    else {
	//if (TCON_DEV == "11307") {
	SATForm = new TSaturationForm(this);
	SATForm->Show();
	//}
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_offsetClick(TObject * Sender)
{
    if (offsetForm != NULL)
	offsetForm->Show();
    else {
	//if (TCON_DEV == "11307") {
	offsetForm = new TOffsetForm(this);
	offsetForm->Show();
	//}
    }
}

//---------------------------------------------------------------------------
String TMainForm::getFileVersionInfo()
{

    DWORD dwVerInfoSize = 0;
    AnsiString szFile = Application->ExeName;
    dwVerInfoSize = GetFileVersionInfoSize(szFile.c_str(), &dwVerInfoSize);
    String caption;
    if (dwVerInfoSize > 0) {
	BYTE *bVerInfoBuf = new BYTE[dwVerInfoSize];
	if (GetFileVersionInfo(szFile.c_str(), 0, dwVerInfoSize, bVerInfoBuf)) {
	    VS_FIXEDFILEINFO *vsInfo;
	    UINT vsInfoSize;
	    if (VerQueryValue(bVerInfoBuf, "\\", (void **) &vsInfo, &vsInfoSize)) {
		int iFileVerMajor = HIWORD(vsInfo->dwFileVersionMS);
		int iFileVerMinor = LOWORD(vsInfo->dwFileVersionMS);
		int iFileVerRelease = HIWORD(vsInfo->dwFileVersionLS);
		int iFileVerBuild = LOWORD(vsInfo->dwFileVersionLS);
		caption = IntToStr(iFileVerMajor) + "."
		    + IntToStr(iFileVerMinor) + "."
		    + IntToStr(iFileVerRelease) + "." + IntToStr(iFileVerBuild);

	    }
	}
	delete bVerInfoBuf;
    }
    return caption;
}


void __fastcall TMainForm::mn_Header2AddressClick(TObject * Sender)
{
    using namespace std;
    OpenDialog1->Filter = "Header Files(*.h)|*.h";
    if (OpenDialog1->Execute()) {
	const AnsiString & header = OpenDialog1->FileName;
	SaveDialog1->Filter = "Address Files(*.txt)|*.txt";
	if (SaveDialog1->Execute()) {
	    const AnsiString & address = SaveDialog1->FileName;
	    header2AddressFile(header, address);
	    ShowMessage("Conversion done!");
	}
    };
}

//---------------------------------------------------------------------------
void TMainForm::header2AddressFile(const AnsiString & header, const AnsiString & address)
{
    using namespace std;
    using namespace cms::util;
    ifstream infile(header.c_str());
    ofstream outfile(address.c_str());

    if (infile.is_open() && outfile.is_open()) {
	string line;
	bool comment = false;
	while (infile.good() && outfile.good()) {
	    getline(infile, line);

	    if (comment || line.size() == 0) {
		if (-1 != line.find("*/", 0)) {
		    comment = false;
		}
		continue;
	    }
	    int beginCommentIndex = line.find("/*", 0);
	    int doubleSlashIndex = line.find("//", 1);
	    if (!comment && -1 != beginCommentIndex && -1 == doubleSlashIndex) {
		comment = true;
		continue;
	    }

	    if (-1 != doubleSlashIndex) {
		line = line.substr(0, doubleSlashIndex - 1);
	    }

	    string_vector_ptr stringvector = StringVector::tokenize(line, " \t");
	    int size = stringvector->size();
	    if (size == 0) {
		continue;
	    }
	    string first = (*stringvector)[0];

	    if ((size == 3 || size == 4) && first.find("#define") == 0) {
		string define = (*stringvector)[2];

		string sub = define.substr(1, define.size() - 2);
		size_t found = sub.find(",");
		if (found != string::npos) {
		    outfile << sub + '\n';
		}
	    }

	}
    }

    outfile.flush();
    outfile.close();
    infile.close();
}

void __fastcall TMainForm::mn_LoadAddressFromFileClick(TObject * Sender)
{
    using namespace std;
    ForceCurrentDirectory = true;
    OpenDialog1->Filter = "T-CON Address Files(*.*)|*.*";
    /*if (0 == OpenDialog1->InitialDir) {
       String appPath = ExtractFilePath(Application->ExeName);
       OpenDialog1->InitialDir = appPath;
       } */
    if (OpenDialog1->Execute()) {
	const AnsiString & header = OpenDialog1->FileName;
	setAddressFile(header);
    };
}

void TMainForm::setAddressFile(AnsiString filename)
{
    AddressFile = filename;
    AnsiString caption = ExtractFileName(filename);
    int dotIndex = caption.Pos(".");
    if (0 != dotIndex) {
	caption = caption.SubString(1, dotIndex - 1);
    }
    MainForm->Caption = caption;
    addressFromFile = true;
    mn_LoadAddressFromFile->Checked = true;
    AbstractBase::resetAddressMap();
    closeAllForms();
}

AnsiString TMainForm::AddressFile;


//---------------------------------------------------------------------------


void __fastcall TMainForm::mn_HSV2Click(TObject * Sender)
{
    if (HSVV2Form != NULL)
	HSVV2Form->Show();
    else {
	//if (TCON_DEV == "11307") {
	//HSVForm = new THSVForm1(this);
	HSVV2Form = new THSVV2Form(this);
	HSVV2Form->Show();
	//}
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_HSV1Click(TObject * Sender)
{
    if (HSVV1Form != NULL)
	HSVV1Form->Show();
    else {
	//if (TCON_DEV == "11307") {
	HSVV1Form = new THSVV1Form(this);
	//HSVForm = new THSVFormNew(this);
	HSVV1Form->Show();
	//}
    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::mn_Sharpness12307Click(TObject * Sender)
{
    if (SharpnessV2Form != NULL) {
	SharpnessV2Form->Show();
    } else {
	//if (TCON_DEV == "11307") {
	SharpnessV2Form = new TSharpnessV2Form(this);
	SharpnessV2Form->Show();
	//}

    }
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Sharpness2Click(TObject * Sender)
{
    /*if (null == SharpnessForm12307_2) {
       SharpnessForm12307_2 = new TSharpnessForm12307_2(this);
       }
       SharpnessForm12307_2->Show(); */
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Example2Click(TObject * Sender)
{
    if (null == ExampleForm) {
	ExampleForm = new TExampleForm(this);
    }
    ExampleForm->Show();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::Sharpnessv211Click(TObject * Sender)
{
    /*if (SharpnessForm12307_2 != NULL) {
       SharpnessForm12307_2->Show();
       } else {
       if (TCON_DEV == "11307") {
       SharpnessForm12307_2 = new TSharpnessForm12307_2(this);
       SharpnessForm12307_2->Show();
       }

       } */
}

//---------------------------------------------------------------------------

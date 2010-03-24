//---------------------------------------------------------------------------


#include <includeall.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "TTargetWhiteForm.h"
#include "TMainForm.h"
#include "TMeasureWindow.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTargetWhiteForm *TargetWhiteForm;
//---------------------------------------------------------------------------
__fastcall TTargetWhiteForm::TTargetWhiteForm(TComponent *
					      Owner):TForm(Owner)
{
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm::ScrollBar_RChange(TObject * Sender)
{
    Edit_R->Text = AnsiString(ScrollBar_R->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm::ScrollBar_GChange(TObject * Sender)
{
    Edit_G->Text = AnsiString(ScrollBar_G->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm::ScrollBar_BChange(TObject * Sender)
{
    Edit_B->Text = AnsiString(ScrollBar_B->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------


void TTargetWhiteForm::scrollBar_Change()
{
    Panel1->Color =
	(TColor) ScrollBar_R->Position + ((ScrollBar_G->Position) << 8) +
	((ScrollBar_B->Position) << 16);
}


//---------------------------------------------------------------------------



void TTargetWhiteForm::setColorimetricValues(double x, double y, double up,
					     double vp)
{

    AnsiString xStr = AnsiString().sprintf("%1.4g", x);
    AnsiString yStr = AnsiString().sprintf("%1.4g", y);

    this->Edit_x->Text = xStr;
    this->Edit_y->Text = yStr;
    this->Edit_targetx->Text = xStr;
    this->Edit_targety->Text = yStr;
    this->Edit_up->Text = AnsiString().sprintf("%1.4g", up);
    this->Edit_vp->Text = AnsiString().sprintf("%1.4g", vp);
}

void __fastcall TTargetWhiteForm::Edit_CTChange(TObject * Sender)
{
    using cms::CorrelatedColorTemperature;
    using Indep::CIExyY;
    using java::lang::IllegalArgumentException;
    using namespace boost;

    AnsiString ctText = this->Edit_CT->Text;
    if (ctText.Length() == 0) {
	setColorimetricValues(-1, -1, -1, -1);
	return;
    }

    int ct = ctText.ToInt();

    try {
	bptr < CIExyY > xyY =
	    CorrelatedColorTemperature::CCT2DIlluminantxyY(ct);
	double_array uvpValues = xyY->getuvPrimeValues();
	setColorimetricValues(xyY->x, xyY->y, uvpValues[0], uvpValues[1]);
    }
    catch(IllegalArgumentException ex) {
	setColorimetricValues(-1, -1, -1, -1);
    }
}

//---------------------------------------------------------------------------

/*
 �y�{
 �ھ�Adjustment Options, �������:
 1. Adjust to xy
  �q�ؼ�xy, ���N���̱���RGB�զX
 2. Adjust by RGB
 �̾ڳ]�w��RGB�@�����I.

 ���oRGB��, �N�ؼ�RGB�@��TargetWhite, �]�w��CA-210�h.
 �]�w�y�{��:
 1. ��pattern > ����(5s) > �q�� (�@RGBW�|��)
 2. �]�wchannel (NO��ID)
 3. �]�w�ե��Ҧ�
 4. �]�w�ե���� RGBW
 5. enter

*/



//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "TMatrixCalibration.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TCA210SettingFrame"
#pragma resource "*.dfm"
TMatrixCalibrationForm *MatrixCalibrationForm;
//---------------------------------------------------------------------------
__fastcall TMatrixCalibrationForm::TMatrixCalibrationForm(TComponent *
							  Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------

bool TMatrixCalibrationForm::setCA210(bptr < cms::measure::meter::CA210 >
				      ca210)
{
    this->ca210 = ca210;
    if (ca210 != null) {
	ca210API = ca210->getCA210API();
	return true;
    } else {
	ShowMessage("CA210 cannot be linked.");
	return false;
    }
}

//---------------------------------------------------------------------------


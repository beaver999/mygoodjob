//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"

//C�t�Τ��
#include <conio.h>
//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "TEngineering.h"
#include <gui/c3d/TC3DForm.h>
#include "TInTargetForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        addr_place = 0;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Engineering1Click(TObject *Sender)
{
        EngineerForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::c3d1Click(TObject *Sender)
{
        C3DForm1->Show();
}
//---------------------------------------------------------------------------


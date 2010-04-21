//---------------------------------------------------------------------------

#ifndef TGammaAdjustmentFormH
#define TGammaAdjustmentFormH
//---------------------------------------------------------------------------
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//�����ؤ��Y���
#include "TOutputFileFrame.h"
//---------------------------------------------------------------------------
class TGammaAdjustmentForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox2;
    TComboBox *ComboBox_LevelStep;
    TLabel *Label9;
    TGroupBox *GroupBox3;
    TGroupBox *GroupBox4;
    TGroupBox *GroupBox5;
    TLabel *Label1;
    TEdit *Edit_GammaW;
    TButton *Button1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TButton *Button2;
    TButton *Button3;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox_AvoidNoise;
    TCheckBox *CheckBox_KeepMax;
    TOutputFileFrame *TOutputFileFrame1;
    void __fastcall FormShow(TObject * Sender);
  private:			// User declarations
     bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
  public:			// User declarations
     __fastcall TGammaAdjustmentForm(TComponent * Owner);
    void setBitDepthProcessor(bptr <
			      cms::lcd::calibrate::BitDepthProcessor >
			      bitDepth);
};
//---------------------------------------------------------------------------
extern PACKAGE TGammaAdjustmentForm *GammaAdjustmentForm;
//---------------------------------------------------------------------------
#endif


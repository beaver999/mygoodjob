//---------------------------------------------------------------------------
#ifndef offsetH
#define offsetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Unit1.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
//Abstract class of offsetForm
class AbstoffsetForm
{
        public:
                virtual TBit* SetChkBx()=0;
                virtual TBit* SetCboBx()=0;
                virtual TBit* SetScrollBar()=0;
                virtual TBit2* SetScrollBar2()=0;
                virtual TBit3* SetLblE3()=0;
                virtual TBit4* SetLblE4()=0;

                int ScrollBar_Nbr;
                int ScrollBar2_Nbr;
                int CboBox_Nbr;
                int ChkBox_Nbr;
                int LblE3_Nbr;
                int LblE4_Nbr;
};

class ToffsetForm : public TForm
{
__published:	// IDE-managed Components
        TBitBtn *btn_reload;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TLabel *Label1;
        TScrollBar *ScrollBar1;
        TStaticText *StaticText1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btn_reloadClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);

        void __fastcall CheckBox_Click(TObject *Sender);
        void __fastcall ComboBox_Click(TObject *Sender);
	void __fastcall ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall ScrollBar2_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall LblE3_KeyPress(TObject *Sender, char &Key);
        void __fastcall LblE4_KeyPress(TObject *Sender, char &Key);

private:	// User declarations
public:		// User declarations
        __fastcall ToffsetForm(TComponent* Owner);

        AbstoffsetForm* OoffsetForm;

        TBit* cb;
        _CHKB** ChkB;

        TBit* cbo;
        _CBOB** CboB;

        TBit* scrlb;
        _ScrollBar** ScrlB;

        TBit2* scrlb2;
        _ScrollBar2** ScrlB2;

        TBit3* lble3;
        _LBLE3** LblE3;

        TBit4* lble4;
        _LBLE4** LblE4;

        bool IsChg;   //�Ψӳ]�w�bFormCreate�Preload��, OnClick�POnchange�����禡���ʧ@

};
//---------------------------------------------------------------------------
extern PACKAGE ToffsetForm *offsetForm1;
//---------------------------------------------------------------------------
#endif

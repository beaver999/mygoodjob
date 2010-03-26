//---------------------------------------------------------------------------

#ifndef Sharpness1H
#define Sharpness1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "Unit1.h"
#include "Engineering.h"
#include <Dialogs.hpp>

/*==========================================================================
AbstSP���@�۩w��class, �㦳�i�Ǧ^IC������Sharpness address�w�q���禡
===========================================================================*/

class AbstSP
{
        public:
                virtual TBit* SetChkBx()=0;     //�Ǧ^CheckBox��address�w�q
                virtual TBit* SetScrollBar()=0;    //�Ǧ^ScrollBar��address�w�q
                virtual TLUT* SetSPLUT()=0;     //�Ǧ^sharpness lookup table��address�w�q

                int SPChkBox_Nbr;
                int SPScrollBar_Nbr;
};



/*====================================================================
TSharpnessForm1���@�~��TForm�κA��class, ��Sharpness������Interface
======================================================================*/
class TSharpnessForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox3;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TScrollBar *ScrollBar1;
        TScrollBar *ScrollBar2;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TScrollBar *ScrollBar3;
        TScrollBar *ScrollBar4;
        TScrollBar *sb_softgain;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TStaticText *st_softgain;
        TGroupBox *GroupBox47;
        TImage *SP_LUT;
        TButton *btn_sp_lut_write;
        TButton *btn_sp_lut_Set;
        TButton *btn_GainSet;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox6;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TRadioGroup *LUT_type;
        TButton *btn_sp_Load;
        TButton *btn_sp_Save;
        TBitBtn *btn_sp_lut_read;
        TBitBtn *Btn_SP_reload;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall CheckBox_Click(TObject *Sender);
        void __fastcall ScrollBar_Change(TObject *Sender);
        void __fastcall SP_LUTMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SP_LUTDblClick(TObject *Sender);
        void __fastcall btn_sp_lut_SetClick(TObject *Sender);
        void __fastcall sb_softgainChange(TObject *Sender);
        void __fastcall btn_GainSetClick(TObject *Sender);
        void __fastcall btn_sp_lut_writeClick(TObject *Sender);
        void __fastcall btn_sp_LoadClick(TObject *Sender);
        void __fastcall btn_sp_SaveClick(TObject *Sender);
        void __fastcall LUT_typeClick(TObject *Sender);
        void __fastcall btn_sp_lut_readClick(TObject *Sender);
        void __fastcall Btn_SP_reloadClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TSharpnessForm1(TComponent* Owner);
        /*
        Sharpness �����ϥΪ��ܼ�
        AbstSP:�O�@��class,�֦��i�Ǧ^Sharpness Address���禡
        OSP: �ŧi��AbstSP�κA���ܼ�
        cb: ��checkbox����ҹ�����address
        ChkB: �㦳checkbox����ҹ�������������Paddress
        scrlb: ��ScrollBar����ҹ�����address
        ScrlB: �㦳ScrollBar����ҹ�������������Paddress
        ChkB: �㦳checkbox����ҹ�������������Paddress
        TBit,TLUT: ���۩w��Address class,�ԲӤ��e�Ѧ�Address_type.h
        _CHKB,_ScrollBar: ���۩w��class, ���t�ϧΤ�������P��m���Ѽ�,�Ա��Ѧ�Unit1.h
        */

        AbstSP* OSP;

        TBit* cb;
        _CHKB** ChkB;

        TBit* scrlb;
        _ScrollBar** ScrlB;

        TLUT* SP_addr;  //lookup table��address
        int SP_lut[32]; //lookup table
        bool SP_Chg ;   //�Ψӳ]�w��������O�_�i�g�J��flag
        int LUT_g[32];
        int gain_flag ;
        void Clear_LUT(bool type);      //�M��table�����W�����I
        bool Load_SP(String Fpath);
};
//---------------------------------------------------------------------------
extern PACKAGE TSharpnessForm1 *SharpnessForm1;
//---------------------------------------------------------------------------


#endif

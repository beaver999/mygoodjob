//---------------------------------------------------------------------------


#ifndef TColorFrameH
#define TColorFrameH
//---------------------------------------------------------------------------

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
//�����ؤ�gui�Y���
//---------------------------------------------------------------------------
class TPointColorFrame:public TFrame {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox44;
    TGroupBox *GroupBox34;
    TImage *Img_c3d_sel;
    TLabel *lb_c3d_selR;
    TLabel *lb_c3d_selH;
    TLabel *lb_c3d_selG;
    TLabel *lb_c3d_selB;
    TLabel *lb_c3d_selV;
    TLabel *lb_c3d_selS;
    TLabel *lb_c3d_selI;
    TLabel *Label190;
    TLabel *Label198;
    TLabel *Label202;
    TLabel *Label206;
    TLabel *Label208;
    TLabel *Label209;
    TLabel *Label213;
    TGroupBox *GroupBox45;
    TLabel *lb_c3d_simR;
    TLabel *lb_c3d_simH;
    TLabel *lb_c3d_simG;
    TLabel *lb_c3d_simB;
    TLabel *lb_c3d_simV;
    TLabel *lb_c3d_simS;
    TLabel *lb_c3d_simI;
    TLabel *Label246;
    TLabel *Label247;
    TLabel *Label248;
    TLabel *Label249;
    TLabel *Label250;
    TLabel *Label251;
    TLabel *Label252;
    TImage *Img_c3d_sim;
  private:			// User declarations
  public:			// User declarations
     __fastcall TPointColorFrame(TComponent * Owner);
    double_array getRGBArray();
    double_array getHSIVArray();
    void setRGBHSIV(double r, double g, double b, double h, double s, double i, double v);
};
//---------------------------------------------------------------------------
extern PACKAGE TPointColorFrame *PointColorFrame;
//---------------------------------------------------------------------------
#endif


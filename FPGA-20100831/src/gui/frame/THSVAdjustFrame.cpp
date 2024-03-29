//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "THSVAdjustFrame.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
#include <gui/event/listener.h>
#include <java/lang.h>
//本項目內gui頭文件

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THSVAdjustFrame *HSVAdjustFrame;
//---------------------------------------------------------------------------
__fastcall THSVAdjustFrame::THSVAdjustFrame(TComponent * Owner)
:TFrame(Owner)
{
    using namespace gui::util;

    /*hueSetter = bptr < HueSetter > (new HueSetter(lb_c3d_Manual39_h, sb_c3d_Manual39_h));
       binder.bind(lb_c3d_Manual39_h, sb_c3d_Manual39_h, hueSetter);

       saturationSetter =
       bptr < SaturationSetter >
       (new
       SaturationSetter(lb_c3d_Manual39_s, sb_c3d_Manual39_s, edt_c3d_satC->Text.ToDouble(), 1));
       binder.bind(lb_c3d_Manual39_s, sb_c3d_Manual39_s, saturationSetter);
       valueSetter =
       bptr < SaturationSetter >
       (new
       SaturationSetter(lb_c3d_Manual39_v, sb_c3d_Manual39_v, edt_c3d_valC->Text.ToDouble(), 1));
       binder.bind(lb_c3d_Manual39_v, sb_c3d_Manual39_v, valueSetter); */
    setHSV(0, .666, 192);
}

//---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::sb_Hue_gainChange(TObject * Sender)
{
    using namespace gui::event;
    using namespace java::lang;

    double_array hsvgain = getHSVGain();
    lb_Hue_gain->Caption = FloatToStr(hsvgain[0]) + "°";
    lb_Sat_gain->Caption = FloatToStr(Math::floor(s * hsvgain[1] * 1000) / 1000);
    lb_Val_gain->Caption = FloatToStr(Math::floor(v * hsvgain[2] * 1000) / 1000);

    foreach(bwptr < ChangeListener > listener, changeListenerVector) {
	bptr < ChangeListener > l = listener.lock();
	if (null != l) {
	    l->stateChanged(Sender);
	}
    }
}

//---------------------------------------------------------------------------
void THSVAdjustFrame::setHSV(double h, double s, double v)
{
    this->h = h;
    this->s = s;
    this->v = v;
    Edit_c3d_Manual39_h_adj->Text = h;
    Edit_c3d_Manual39_s_adj->Text = s;
    Edit_c3d_Manual39_v_adj->Text = v;
    //saturationSetter->setBase(s);
    //valueSetter->setBase(v);
};

void __fastcall THSVAdjustFrame::sb_Sat_gainChange(TObject * Sender)
{
    sb_Hue_gainChange(Sender);
    //binder.active(Sender);
}

//---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::sb_Val_gainChange(TObject * Sender)
{
    //binder.active(Sender);
    sb_Hue_gainChange(Sender);
}

//---------------------------------------------------------------------------
void THSVAdjustFrame::addChangeListener(bptr < gui::event::ChangeListener > listener)
{
    bwptr < gui::event::ChangeListener > wptr(listener);
    changeListenerVector.push_back(wptr);
};

/*void THSVAdjustFrame::addListSelectionListener(bptr < gui::event::ListSelectionListener > listener)
{
    bwptr < gui::event::ListSelectionListener > wptr(listener);
    selectionListenerVector.push_back(wptr);
};*/
double_array THSVAdjustFrame::getHSVGain()
{
    double h = sb_Hue_gain->Position - sb_Hue_gain->Max / 2;
    int spos = sb_Sat_gain->Position - sb_Sat_gain->Max / 2;
    double s = (double) spos / 100. / edt_c3d_satC->Text.ToDouble();
    int vpos = sb_Val_gain->Position - sb_Val_gain->Max / 2;
    double v = (double) vpos / 100. / edt_c3d_valC->Text.ToDouble();
    double_array hsvgain(new double[3]);
    hsvgain[0] = h;
    hsvgain[1] = s;
    hsvgain[2] = v;
    return hsvgain;
};

void THSVAdjustFrame::setColorAdjustable(bool enable)
{
    sb_Hue_gain->Enabled = enable;
    sb_Sat_gain->Enabled = enable;
};

void THSVAdjustFrame::setTStringGrid(TStringGrid * stringGrid)
{
    this->stringGrid = stringGrid;
}

double_array THSVAdjustFrame::getHSVGain(double h, double s, double v, int row)
{
    if (null != stringGrid) {
	double huse = stringGrid->Cells[1][row].ToDouble();
	double suse = stringGrid->Cells[2][row].ToDouble();
	double vuse = stringGrid->Cells[3][row].ToDouble();

	double hgain = huse - h;
	double sgain = ((suse / s) - 1) * 100 * edt_c3d_satC->Text.ToDouble();
	double vgain = ((vuse / v) - 1) * 100 * edt_c3d_valC->Text.ToDouble();

	double_array hsvgain(new double[3]);
	hsvgain[0] = hgain;
	hsvgain[1] = sgain;
	hsvgain[2] = vgain;
	return hsvgain;
    }
    return nil_double_array;
}


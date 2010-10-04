//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "THSVAdjustFrame.h"

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���
#include <gui/event/listener.h>
//�����ؤ�gui�Y���

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THSVAdjustFrame *HSVAdjustFrame;
//---------------------------------------------------------------------------
__fastcall THSVAdjustFrame::THSVAdjustFrame(TComponent * Owner)
:TFrame(Owner)
{
    using namespace gui::util;

    hueSetter = bptr < HueSetter > (new HueSetter(lb_c3d_Manual39_h, sb_c3d_Manual39_h));
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
    binder.bind(lb_c3d_Manual39_v, sb_c3d_Manual39_v, valueSetter);
    setHSV(0, .666, 192);
}

//---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::sb_c3d_Manual39_hChange(TObject * Sender)
{
    using namespace gui::event;
    binder.active(Sender);
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
    saturationSetter->setBase(s);
    valueSetter->setBase(v);
};

void __fastcall THSVAdjustFrame::sb_c3d_Manual39_sChange(TObject * Sender)
{
    binder.active(Sender);
}

//---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::sb_c3d_Manual39_vChange(TObject * Sender)
{
    binder.active(Sender);
}

//---------------------------------------------------------------------------
void THSVAdjustFrame::addChangeListener(bptr < gui::event::ChangeListener > listener)
{
    bwptr < gui::event::ChangeListener > wptr(listener);
    changeListenerVector.push_back(wptr);
};


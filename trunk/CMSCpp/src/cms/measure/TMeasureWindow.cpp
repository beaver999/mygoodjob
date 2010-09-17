//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "TMeasureWindow.h"
#include <cms/colorspace/rgb.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
__fastcall TMeasureWindow::TMeasureWindow(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27) {
	this->Close();
    }
}

//---------------------------------------------------------------------------


void TMeasureWindow::setRGB(int r, int g, int b)
{
    int color = (b << 16) + (g << 8) + r;
    this->Color = (TColor) color;
    this->Update();
}

void TMeasureWindow::setRGB(boost::shared_ptr < cms::colorspace::RGBColor >
			    rgb)
{
    int r = static_cast < int >(rgb->R);
    int g = static_cast < int >(rgb->G);
    int b = static_cast < int >(rgb->B);
    setRGB(r, g, b);
}

//---------------------------------------------------------------------------

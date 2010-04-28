//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件
#include <FileCtrl.hpp>
//本項目內頭文件
#include "TCCTLUTForm.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
__fastcall TCCTLUTForm::TCCTLUTForm(TComponent * Owner)
:TForm(Owner), serialid(0)
{
}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------


void TCCTLUTForm::setMeasureInfo()
{
    using namespace cms::util;
    int start = bitDepth->getMeasureStart();
    int step = bitDepth->getMeasureStep();
    this->Edit_StartLevel->Text = Util::toString(start).c_str();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();
};


//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::RadioButton_RBInterpClick(TObject * Sender)
{
    this->Edit_RBInterpUnder->Enabled = true;
    this->Edit_P1->Enabled = false;
    this->Edit_P2->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_P1P2Click(TObject * Sender)
{
    this->Edit_RBInterpUnder->Enabled = false;
    this->Edit_P1->Enabled = true;
    this->Edit_P2->Enabled = true;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_RunClick(TObject * Sender)
{
    using namespace std;
    using namespace Dep;
    using namespace cms::lcd::calibrate;

    MainForm->getAnalyzer();
    MainForm->setAnalyzerToTargetChannel();

    calibrator.
	reset(new
	      LCDCalibrator(MainForm->getComponentFetcher(), bitDepth));

    //==========================================================================
    // P1P2和RBInterp的選擇
    //==========================================================================
    if (this->RadioButton_P1P2->Checked) {
	//選了P1P2
	int p1 = this->Edit_P1->Text.ToInt();
	int p2 = this->Edit_P2->Text.ToInt();
	calibrator->setP1P2(p1, p2);
    } else if (this->RadioButton_RBInterp->Checked) {
	//選了RBInterp
	int rbunder = this->Edit_RBInterpUnder->Text.ToInt();
	calibrator->setRBInterpolation(rbunder);
    } else {
	calibrator->setNoneDimCorrect();
    }

    //==========================================================================

    //==========================================================================
    // gamma的處理
    //==========================================================================
    if (this->RadioButton_Gamma->Checked) {
	double gamma = this->ComboBox_Gamma->Text.ToDouble();
	calibrator->setGamma(gamma);
    } else if (this->RadioButton_GammaCurve->Checked) {
	double_vector_ptr gammaCurve = rgbGamma->w;
	calibrator->setGammaCurve(gammaCurve);
    }
    calibrator->setGByPass(this->CheckBox_GByPass->Checked);
    //==========================================================================

    //==========================================================================
    // blue correction
    //==========================================================================
    if (this->CheckBox_BGain->Checked) {
	double gain = this->Edit_BGain->Text.ToDouble();
	calibrator->setBIntensityGain(gain);
    }
    calibrator->setBMax(this->CheckBox_BMax->Checked);
    //==========================================================================
    calibrator->setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);
    calibrator->setKeepMaxLuminance(this->CheckBox_KeepMax->Checked);

    try {
	this->TOutputFileFrame1->createDir();

	bptr < MeasureCondition > measureCondition = getMeasureCondition();

	RGB_vector_ptr dglut = calibrator->getCCTDGLut(measureCondition);
	if (dglut == null) {
	    return;
	}

	String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
	string filename = astr->c_str();
	calibrator->storeDGLut(filename, dglut);
	ShowMessage("Ok!");
    }
    catch(java::lang::IllegalStateException & ex) {
	ShowMessage(ex.toString().c_str());
    }

}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::FormCreate(TObject * Sender)
{
    using namespace cms::lcd::calibrate;

    //==========================================================================
    // debug模式的設定
    //==========================================================================
    bool debug = !MainForm->linkCA210;
    this->Button_Debug->Visible = debug;
    this->Button_Reset->Visible = debug;
    //this->RadioButton_None->Visible = debug;
    //==========================================================================

}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_DebugClick(TObject * Sender)
{
    using namespace std;
    OpenDialog1->Filter = "DGCode Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	MainForm->setDummyMeterFilename(string(filename.c_str()));
	ShowMessage("Dummy meter setting Ok!");
    };

}

//---------------------------------------------------------------------------


void __fastcall TCCTLUTForm::Button_ResetClick(TObject * Sender)
{
    MainForm->resetDummyMeter();
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::FormShow(TObject * Sender)
{
    using namespace Dep;

    const MaxValue & input = bitDepth->getInputMaxValue();
    bool avoidNoise = (input == MaxValue::Int6Bit
		       || input == MaxValue::Int8Bit);
    this->CheckBox_AvoidNoise->Enabled = avoidNoise;

    bool tconInput = bitDepth->isTCONInput();
    this->CheckBox_Expand->Visible = !tconInput;

    setMeasureInfo();
}

void __fastcall TCCTLUTForm::RadioButton_GammaCurveClick(TObject * Sender)
{
    using namespace cms::util;
    OpenDialog1->Filter = "Desired Gamma Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	rgbGamma = RGBGamma::loadFromDesiredGamma(filename.c_str());
	unsigned int n = bitDepth->getLevel();
	if (rgbGamma != null && rgbGamma->w->size() == n) {
	    this->RadioButton_GammaCurve->Checked = true;
	    this->CheckBox_GByPass->Visible = true;
	    return;
	} else {
	    ShowMessage("Desired Gamma File Format is wrong!");
	}
    }
    this->RadioButton_Gamma->Checked = true;
}


//---------------------------------------------------------------------------
void TCCTLUTForm::setBitDepthProcessor(bptr <
				       cms::lcd::calibrate::
				       BitDepthProcessor > bitDepth)
{
    this->bitDepth = bitDepth;
}

void __fastcall TCCTLUTForm::
TOutputFileFrame1Button_BrowseDirClick(TObject * Sender)
{
    TOutputFileFrame1->Button_BrowseDirClick(Sender);

}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27 && calibrator != null) {
	calibrator->setStop(true);
	ShowMessage("Interrupt!");
    }
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_GammaClick(TObject * Sender)
{
    this->CheckBox_GByPass->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::ComboBox_GammaChange(TObject * Sender)
{
    RadioButton_GammaClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_ExpandClick(TObject * Sender)
{
    bool checked = this->CheckBox_Expand->Checked;
    this->Panel_Expand->Visible = checked;
}

//---------------------------------------------------------------------------
bptr < cms::lcd::calibrate::MeasureCondition >
    TCCTLUTForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;
    bool expand = this->CheckBox_Expand->Checked;
    bptr < MeasureCondition > condition;
    if (expand) {
	int lowstart = this->Edit_LowStartLevel->Text.ToInt();
	int lowend = this->Edit_LowEndLevel->Text.ToInt();
	int lowstep = this->ComboBox_LowStep->Text.ToInt();
	int highstart = this->Edit_HighStartLevel->Text.ToInt();
	int highend = this->Edit_HighEndLevel->Text.ToInt();
	int highstep = this->ComboBox_HighStep->Text.ToInt();
	condition.reset(new
			MeasureCondition(lowstart, lowend, lowstep,
					 highstart, highend, highstep));
    } else {
	int start = this->Edit_StartLevel->Text.ToInt();
	int end = this->Edit_EndLevel->Text.ToInt();
	int step = this->ComboBox_LevelStep->Text.ToInt();

	//預設的第一階
	int firstStep = bitDepth->getMeasureFirstStep();
	if (bitDepth->getMeasureStart() != start
	    || bitDepth->getMeasureEnd() != end
	    || bitDepth->getMeasureStep() != step) {
	    //如果量測條件被改變, 則不要採用原本的第一階
	    firstStep = step;
	}

	condition.reset(new MeasureCondition(start, end, firstStep, step));
    }
    return condition;

}

//---------------------------------------------------------------------------




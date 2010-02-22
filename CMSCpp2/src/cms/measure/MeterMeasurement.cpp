#include "MeterMeasurement.h"

#include <vcl.h>
#include <cms/measure/meter.h>
#include <cms/measure/cp.h>
#include <cms/patch.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/colorspace/rgb.h>
#include <cms/core.h>

namespace cms {
    namespace measure {
	using namespace boost;
	using namespace cms;
	using namespace Dep;
	using namespace cms::measure::meter;
	using namespace cms::measure::cp;
	using namespace std;
	using namespace java::lang;

	 MeterMeasurement::MeterMeasurement(shared_ptr < Meter >
					    meter,
					    bool calibration):meter(meter),
	    waitTimes(1 /*meter->getSuggestedWaitTimes() */ ),
	 measureWindowClosing(false), titleTouched(false),
	    fakeMeasure(false) {
	    measureWindow = MeasureWindow;
	    if (true == calibration) {
		calibrate();
	    }
	};

	void MeterMeasurement::calibrate() {
	    MeasureUtils::meterCalibrate(*this);
	};

	void MeterMeasurement::close() {
	    setMeasureWindowsVisible(false);
	    measureWindow->Close();
	    meterClose();
	};

	void MeterMeasurement::setMeasureWindowsVisible(bool visible) {
	    if (!fakeMeasure) {
		measureWindow->Visible = visible;
		measureWindowClosing = !visible;
	    }
	};

	Patch_ptr
	    MeterMeasurement::measure(RGB_ptr rgb,
				      const string_ptr patchName) {
	    return measure0(rgb, patchName, nil_string_ptr,
			    nil_string_ptr);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b,
					    const string_ptr patchName) {
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, patchName);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b,
					    string patchName) {
	    string_ptr str(new string(patchName));
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, str);
	};

	void MeterMeasurement::setBlankTimes(int blankTimes) {
	    this->blankTimes = blankTimes;
	};
	void MeterMeasurement::setWaitTimes(int waitTimes) {
	    this->waitTimes = waitTimes;
	};
	void MeterMeasurement::setFakeMeasure(bool fake) {
	    this->fakeMeasure = fake;
	};
	bool MeterMeasurement::isFakeMeasure() {
	    return fakeMeasure;
	};

	bptr < MeasureInterface > MeterMeasurement::getMeasureInterface() {
	    class MI:public MeasureInterface {
	      public:
		bptr < MeasureResult >
		    measureResult(RGB_vector_ptr rgbVec, bool forceTrigger,
				  bool trigger) {
		    int size = rgbVec->size();

		};

		Patch_ptr measure(RGB_ptr rgb, bool forceTrigger,
				  bool trigger) {
		    this->measure(rgb);
		};
		Patch_ptr measure(RGB_ptr rgb) {
		    return mm->measure(rgb, rgb->toString());
		};
		void reset() {
		};

	      private:
		friend class MeterMeasurement;
		MeterMeasurement *mm;
	      MI(MeterMeasurement * mm):mm(mm) {
		};
	    };
	    return bptr < MeasureInterface > (dynamic_cast <
					      MeasureInterface *
					      >(new MI(this)));
	};

	bptr < cms::measure::meter::Meter > MeterMeasurement::getMeter() {
	    return meter;
	};

	void MeterMeasurement::meterClose() {
	    meter->close();
	};

	Patch_ptr
	    MeterMeasurement::measure0(RGB_ptr measureRGB,
				       string_ptr patchName,
				       string_ptr titleNote,
				       string_ptr timeNote) {
	    setMeasureWindowsVisible(true);
	    //�q�����C��, �q�����C��i��P�ɨ㪺�C�⤣�P, �ҥH�S�O�W�ߥX���ܼ�
	    //final RGB measureRGB = processInverseRGB(rgb);
	    //string_ptr name =
	    //  (patchName == NULL) ? measureRGB.toString() : patchName;

	    if (!titleTouched) {
		//�p�Gtitle�S�Q�]�w�L
		if (titleNote != NULL) {
		    //measureWindow.setTitle("Measure Window " + titleNote);
		    /*measureWindow->Caption =
		       AnsiString("Measure Window " + titleNote); */

		} else {
		    //measureWindow.setTitle("Measure Window");
		    measureWindow->Caption = AnsiString("Measure Window");
		}
		/*measureWindow.setNorthLabel1(name + "   " +
		   rgb.toString() + "   " +
		   titleNote); */
	    }
	    //�]�w�n�C��
	    /*Color c =
	       this.isCPCodeLoading()? this.cpBackground : background;
	       measureWindow.setBackground(c); */
	    //measureWindow.setColor(measureRGB.getColor());
	    measureWindow->setRGB(measureRGB);

	    //==========================================================================
	    // �ܴ��������C�⪺�u�Ȱ��d
	    //==========================================================================
	    if (!fakeMeasure) {
		Sleep(waitTimes);
	    }
	    //==========================================================================

	    /*if (meter instanceof DummyMeter) {
	       //�p�G�Odummy, �N�������wRGB, ��dummy�ഫ��XYZ
	       ((DummyMeter) meter).setRGB(measureRGB);
	       } */

	    if (true == measureWindowClosing) {
		//�p�G�����Q����, �N�����q��
		//return shared_ptr < Patch > ((Patch *) NULL);
	    }
	    double_array result = meter->triggerMeasurementInXYZ();

	    /*String measureString = getMeasureString(result);
	       measureWindow.setNorthLabel3(measureString +
	       (softCalibrate ?
	       (" (" +
	       DoubleArray.
	       toString(unSoftCalXYZValues)
	       + " )") : ""));
	       if (informationProvider != null) {
	       String info = informationProvider.getInformation();
	       measureWindow.setSouthLabel(info);
	       }
	       if (timeNote != null) {
	       measureWindow.setNorthLabel2(timeNote);
	       } */
	    XYZ_ptr XYZ(new Indep::CIEXYZ(result));
	    Patch_ptr patch(new Patch(patchName, XYZ, XYZ, measureRGB));
	    return patch;
	};
	void MeasureUtils::
	    meterCalibrate(MeterMeasurement & meterMeasurement) {
	    shared_ptr < Meter > meter = meterMeasurement.meter;
	    TMeasureWindow *measureWindow = meterMeasurement.measureWindow;
	    meterCalibrate( /*measureWindow, */ meter,
			   measureWindow);
	};
	void MeasureUtils::meterCalibrate(	/*Component parentComponent, */
					     shared_ptr < Meter > meter,
					     TMeasureWindow *
					     measureWindow) {
	    if (!meter->isConnected()) {
		throw IllegalStateException("!meter.isConnected()");
	    } else {
		if (measureWindow != NULL) {
		    //show�X�¹�, �קK�v�T�ե�
		    //measureWindow.setColor(Color.black);
		    measureWindow->setRGB(0, 0, 0);
		    measureWindow->Visible = true;
		}
		//string s = meter->getCalibrationDescription();
		AnsiString(meter->getCalibrationDescription()->c_str());
		/*ShowMessage(AnsiString
		   ((*meter.getCalibrationDescription()).
		   c_str())); */
		meter->calibrate();
		if (measureWindow != null) {
		    //�����¹�
		    //measureWindow.setVisible(false);
		    measureWindow->Visible = false;
		}
		ShowMessage(AnsiString("End of calibration"));
		/*JOptionPane.showMessageDialog(parentComponent,
		   "End of calibration",
		   "End of calibration",
		   JOptionPane.
		   INFORMATION_MESSAGE); */
	    };
	};

	MeasureResult::MeasureResult(Patch_vector_ptr result,
				     int practicalMeasureCount):result
	    (result), practicalMeasureCount(practicalMeasureCount) {

	};
    };
};


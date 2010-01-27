#include "MeterMeasurement.h"

#include <vcl.h>
#include <cms/measure/meter.h>
#include <cms/patch.h>
#include <cms/colorspace/ciexyz.h>

namespace cms {
    namespace measure {
	using namespace boost;
	using namespace cms;
	using namespace cms::colorspace;
	using namespace cms::measure::meter;
	using namespace std;
	 MeterMeasurement::MeterMeasurement(shared_ptr <
					    cms::measure::meter::Meter >
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
	    meterCalibrate(*this);
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

	shared_ptr < Patch >
	    MeterMeasurement::measure(RGBColor & rgb,
				      boost::shared_ptr < string >
				      patchName) {
	    /*return measure0(rgb, patchName, nil_string_ptr,
			    nil_string_ptr);*/
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

	void MeterMeasurement::
	    meterCalibrate(MeterMeasurement & meterMeasurement) {
	    shared_ptr < Meter > meter = meterMeasurement.meter;
	    TMeasureWindow *measureWindow = meterMeasurement.measureWindow;
	    meterCalibrate( /*measureWindow, */ meter, measureWindow);
	};

	void MeterMeasurement::meterCalibrate(	/*Component parentComponent, */
						 shared_ptr < Meter >
						 meter,
						 TMeasureWindow *
						 measureWindow) {
	    if (!meter->isConnected()) {
		throw java::lang::
		    IllegalStateException("!meter.isConnected()");
	    } else {
		if (measureWindow != NULL) {
		    //show�X�¹�, �קK�v�T�ե�
		    //measureWindow.setColor(Color.black);
		    measureWindow->setRGB(0, 0, 0);
		    measureWindow->Visible = true;
		}
		//string s = meter->getCalibrationDescription();


		/*ShowMessage(AnsiString
		   ((*meter.getCalibrationDescription()).
		   c_str())); */

		/*JOptionPane.showMessageDialog(parentComponent,
		   meter.
		   getCalibrationDescription
		   (), "Calibration",
		   JOptionPane.
		   INFORMATION_MESSAGE); */
		meter->calibrate();

		if (measureWindow != NULL) {
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


	void MeterMeasurement::meterClose() {
	    meter->close();
	};

	shared_ptr < Patch >
	    MeterMeasurement::measure0(RGBColor & measureRGB,
				       shared_ptr < string > patchName,
				       shared_ptr < string > titleNote,
				       shared_ptr < string > timeNote) {
	    setMeasureWindowsVisible(true);
	    //�q�����C��, �q�����C��i��P�ɨ㪺�C�⤣�P, �ҥH�S�O�W�ߥX���ܼ�
	    //final RGB measureRGB = processInverseRGB(rgb);
	    //shared_ptr < string > name =
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
	    shared_array < double >result =
		meter->triggerMeasurementInXYZ();

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
	    shared_ptr < cms::colorspace::CIEXYZ >
		XYZ(new cms::colorspace::CIEXYZ(result));
	    //return shared_ptr < Patch > ((Patch *) NULL);
	};
    };
};


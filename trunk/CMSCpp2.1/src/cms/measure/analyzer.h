#ifndef ANALYZERH
#define ANALYZERH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <vcl.h>

//�����ؤ��Y���

namespace cms {

    namespace measure {

	class MeterMeasurement;
	class IntensityAnalyzerIF:public jObject {
	  public:
	    virtual RGB_ptr getIntensity(RGB_ptr rgb) = 0;
	    virtual XYZ_ptr getCIEXYZ() = 0;
	    virtual void setupComponent(const Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	    virtual void enter() = 0;
	    virtual void beginAnalyze() = 0;
	    virtual void endAnalyze() = 0;
	    virtual void setWaitTimes(int waitTimes) = 0;
	    virtual void setDefaultWaitTimes() = 0;
	};

	class CA210IntensityAnalyzer:public IntensityAnalyzerIF {
	  protected:
	    int defaultWaitTimes;
	     bptr < cms::measure::meter::CA210 > ca210;
	     bptr < ca210api::CA210API > ca210api;
	    XYZ_ptr XYZ;
	     bptr < MeterMeasurement > mm;
	    static const WideString & CalibrationDataFilename;
	    bool dummyMode;
	    void init();
	     cms::measure::meter::DGLutFileMeter * dgc;
	  public:

	    /*
	       �ĥ�CA210��analyze���G���ӷ�
	     */
	     CA210IntensityAnalyzer(bptr < cms::measure::meter::CA210 >
				    ca210, bptr < MeterMeasurement > mm);
	    /*
	       �ѩ�ʥFCA210, �]���O�HMeterMeasurement����Meter�@��analyze�ӷ�,
	       ��ڤW�O���]Meter��DGLutFileMeter, �]�N�O��Ū���ɮפ���component�@��analyze���G
	     */
	     CA210IntensityAnalyzer(bptr < MeterMeasurement > mm);

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void setChannel(int no, string_ptr id);
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    void setDefaultWaitTimes();
	};

	class StocktonComponentAnayzer:public CA210IntensityAnalyzer {
	  private:
	    Patch_ptr rp, gp, bp, wp;
	  public:
	    StocktonComponentAnayzer(bptr < cms::measure::meter::CA210 >
				     ca210, bptr < MeterMeasurement > mm);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	};

	class MaxMatrixComponentAnalyzer:public IntensityAnalyzerIF {
	  private:
	    const Dep::RGBColorSpace & rgbColorSpace;
	  public:
	     MaxMatrixComponentAnalyzer(const Dep::RGBColorSpace &
					rgbColorSpace);

	    RGB_ptr getIntensity(RGB_ptr rgb) = 0;
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb) = 0;
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	};
    };
};
#endif


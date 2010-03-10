#ifndef ANALYZERH
#define ANALYZERH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <vcl.h>

//�����ؤ��Y���
#include <java/lang.h>

namespace ca210api {
    class CA210API;
};

namespace cms {

    namespace measure {

	class MeterMeasurement;
	class ComponentAnalyzerIF:public jObject {
	  public:
	    virtual RGB_ptr getComponent(RGB_ptr rgb) = 0;
	    virtual XYZ_ptr getCIEXYZ() = 0;
	    virtual void setupComponent(const Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	    virtual void enter() = 0;
	};

	class CA210ComponentAnalyzer:public ComponentAnalyzerIF {
	  protected:
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	    XYZ_ptr XYZ;
	     bptr < MeterMeasurement > mm;
	    static const WideString & CalibrationDataFilename;
	    bool dummyMode;
	    void init();
	     cms::measure::meter::DGCodeFileMeter * dgc;
	  public:

	    /*CA210ComponentAnalyzer(bptr < cms::measure::meter::CA210 >
	       ca210); */
	    /*
	       �ĥ�CA210��analyze���G���ӷ�
	     */
	     CA210ComponentAnalyzer(bptr < cms::measure::meter::CA210 >
				    ca210, bptr < MeterMeasurement > mm);
	    /*
	       �ѩ�ʥFCA210, �]���O�HMeterMeasurement����Meter�@��analyze�ӷ�,
	       ��ڤW�O���]Meter��DGCodeFileMeter, �]�N�O��Ū���ɮפ���component�@��analyze���G
	     */
	     CA210ComponentAnalyzer(bptr < MeterMeasurement > mm);

	    RGB_ptr getComponent(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void setChannel(int no, string_ptr id);
	};

	class StocktonComponentAnayzer:public CA210ComponentAnalyzer {
	  private:
	    Patch_ptr rp, gp, bp, wp;
	  public:
	    StocktonComponentAnayzer(bptr < cms::measure::meter::CA210 >
				     ca210, bptr < MeterMeasurement > mm);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	};

	class MaxMatrixComponentAnalyzer:public ComponentAnalyzerIF {
	  private:
	    const Dep::RGBColorSpace & rgbColorSpace;
	  public:
	     MaxMatrixComponentAnalyzer(const Dep::RGBColorSpace &
					rgbColorSpace);

	    RGB_ptr getComponent(RGB_ptr rgb) = 0;
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb) = 0;
	    void enter();
	};
    };
};
#endif


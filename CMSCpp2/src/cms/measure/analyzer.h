#ifndef ANALYZERH
#define ANALYZERH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace ca210api {
    class CA210API;
};

namespace cms {

    namespace measure {

	class MeterMeasurement;
	class ComponentAnalyzerIF {
	  public:
	    virtual RGB_ptr getComponent(RGB_ptr rgb) = 0;
	    virtual void setupComponent(Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	};

	class CA210ComponentAnayzer:public jObject, ComponentAnalyzerIF {
	  protected:
	    bptr < MeterMeasurement > mm;
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	  public:
	    CA210ComponentAnayzer(bptr < cms::measure::meter::CA210 >
				  ca210);

	    RGB_ptr getComponent(RGB_ptr rgb);
	    void setupComponent(Dep::Channel & ch, RGB_ptr rgb);

	};

	class StocktonComponentAnayzer:public CA210ComponentAnayzer {
	  public:
	    StocktonComponentAnayzer(bptr < cms::measure::meter::CA210 >
				     ca210);

	    RGB_ptr getComponent(RGB_ptr rgb);
	    void setupComponent(Dep::Channel & ch, RGB_ptr rgb);

	};
    };
};
#endif


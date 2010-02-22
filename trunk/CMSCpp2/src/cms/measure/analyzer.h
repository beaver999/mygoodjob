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
	    virtual void setupComponent(const Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	    virtual void enter() = 0;
	};

	class CA210ComponentAnalyzer:public jObject, ComponentAnalyzerIF {
	  protected:
	    bptr < MeterMeasurement > mm;
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	  public:
	    CA210ComponentAnalyzer(bptr < cms::measure::meter::CA210 >
				   ca210);

	    RGB_ptr getComponent(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	};

	class StocktonComponentAnayzer:public CA210ComponentAnalyzer {
	  private:
	    Patch_ptr rp, gp, bp, wp;
	  public:
	    StocktonComponentAnayzer(bptr < cms::measure::meter::CA210 >
				     ca210);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	};
    };
};
#endif


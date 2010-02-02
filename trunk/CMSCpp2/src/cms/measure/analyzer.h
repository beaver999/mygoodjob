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
	    RGB_ptr
		getComponent(RGB_ptr rgb);
	    void setupComponent(Dep::Channel & ch,
				XYZ_ptr XYZ);

	    void setupComponent(Dep::Channel & ch,
				RGB_ptr rgb);
	};

	class CA210ComponentAnayzer:public jObject, ComponentAnalyzerIF {
	  private:
	    bptr < MeterMeasurement > mm;
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	  public:
	    CA210ComponentAnayzer(bptr < cms::measure::meter::CA210 >
				  ca210);

	    RGB_ptr
		getComponent(RGB_ptr rgb);
	    void setupComponent(Dep::Channel & ch,
				RGB_ptr rgb);

	};
    };
};
#endif


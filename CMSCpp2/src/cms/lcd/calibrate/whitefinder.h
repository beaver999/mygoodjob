#ifndef WHITEFINDERH
#define WHITEFINDERH
//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class WhitePointFinder {
	      private:
		bptr < cms::measure::MeterMeasurement > mm;
		RGB_ptr findRGBAround(xyY_ptr xyY);
		RGB_ptr findMatchRGB(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr fixRGB2TouchMax(RGB_ptr rgb);
		 cms::lcd::calibrate::algo::
		    ChromaticAroundAlgorithm & aroundAlgo;
		 cms::lcd::calibrate::algo::
		    CIEuv1960NearestAlgorithm & nearAlgo;
	      public:
		 WhitePointFinder(bptr < cms::measure::MeterMeasurement >
				  mm);
		RGB_ptr findRGB(xyY_ptr xyY);
	    };
	};
    };
};
#endif


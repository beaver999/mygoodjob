#ifndef WHITEFINDERH
#define WHITEFINDERH
//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class WhitePointFinder {
	      private:
		bptr < cms::measure::MeterMeasurement > mm;
		RGB_ptr findMatchRGB0(xyY_ptr xyY, RGB_ptr initRGB);
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


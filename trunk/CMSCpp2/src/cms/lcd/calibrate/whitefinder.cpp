#include "whitefinder.h"

//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���
#include <cms/lcd/calibrate/aroundalgo.h>
#include <cms/lcd/calibrate/nearalgo.h>
#include <cms/colorspace/rgb.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/measure/MeterMeasurement.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::lcd::calibrate::algo;
	    using namespace Dep;
	     WhitePointFinder::WhitePointFinder(bptr <
						cms::measure::
						MeterMeasurement >
						mm):mm(mm),
		aroundAlgo(ChromaticAroundAlgorithm())
	    , nearAlgo(CIEuv1960NearestAlgorithm
		       (XYZ_ptr((Indep::CIEXYZ *) NULL),
			mm->getMeasureInterface()
		       )) {
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		RGB_vector_ptr aroundRGB =
		    aroundAlgo.getAroundRGB(RGBColor::White, 1);
		XYZ_ptr center = xyY->toXYZ();
		 bptr < AlgoResult > algoResult =
		    nearAlgo.getNearestRGB(center, aroundRGB);
	    };
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {

	    };
	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {

	    };

	    /*
	       ���I�M��y�{

	       �ѩ�ʥFmodel�i�H�w���A�����I,
	       1. �]�������G�HR&B�M�䥿�T���I
	       2. �M��A�վ�White��RGB�䤤�@�I��255.
	       3. �A�H���ץ��᪺��, �ץ���l�D255�����I, �Ϧ�׹F��̱����.
	     */
	    RGB_ptr WhitePointFinder::findRGB(xyY_ptr xyY) {
		RGB_ptr initRGB = findRGBAround(xyY);
		RGB_ptr fixRGB = fixRGB2TouchMax(initRGB);
		RGB_ptr finalRGB = findMatchRGB(xyY, fixRGB);
		return finalRGB;
	    };
	};

    };
};


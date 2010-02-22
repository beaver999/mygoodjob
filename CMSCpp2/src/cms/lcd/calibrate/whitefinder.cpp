#include "whitefinder.h"

//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���
#include <cms/lcd/calibrate/aroundalgo.h>
#include <cms/lcd/calibrate/nearalgo.h>
#include <cms/colorspace/rgb.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/patch.h>
#include <cms/measure/MeterMeasurement.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms;
	    using namespace cms::measure;
	    using namespace cms::lcd::calibrate::algo;
	    using namespace Dep;
	    using namespace Indep;
	     WhitePointFinder::WhitePointFinder(bptr <
						MeterMeasurement >
						mm):mm(mm),
		aroundAlgo(ChromaticAroundAlgorithm())
	    , nearAlgo(CIEuv1960NearestAlgorithm
		       (XYZ_ptr((CIEXYZ *) NULL), mm->getMeasureInterface()
		       )) {
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		RGB_ptr nearestRGB = RGBColor::White;
		bool findNearest = false;

		do {
		    RGB_vector_ptr aroundRGB =
			aroundAlgo.getAroundRGB(RGBColor::White, 1);
		    XYZ_ptr center = xyY->toXYZ();
		     bptr < AlgoResult > algoResult =
			nearAlgo.getNearestRGB(center, aroundRGB);
		    XYZ_vector_ptr aroundXYZ = algoResult->aroundXYZ;
		    RGB_ptr nearestRGB = algoResult->nearestRGB;
		     findNearest =
			MeasuredUtils::isFirstNearestXYZInuvPrime(center,
								  aroundXYZ);
		} while (!findNearest);
		 return nearestRGB;
	    };

            /*
              1. ���̤j���W�D
              2. �p��ثexyY�P�ؼЭȤ�delta
              3.
            */
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {
		const Channel & maxChannel = initRGB->getMaxChannel();
		channel_vector_ptr matchChannels =
		    Channel::getBesidePrimaryChannel(maxChannel);
		Patch_ptr patch =
		    mm->measure(initRGB, initRGB->toString());
		double_array delta =
		    nearAlgo.getDelta(xyY->toXYZ(), patch->getXYZ());
	    };
	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {
		const Channel & maxChannel = rgb->getMaxChannel();
		double maxChannelValue = rgb->getValue(maxChannel);
		double diff = 255 - maxChannelValue;
		rgb->addValue(diff);
		return rgb;
	    };

	    /*
	       ���I�M��y�{

	       �ѩ�ʥFmodel�i�H�w���A�����I,
	       1. �]�����HRGB��cube�M�䥿�T���I
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


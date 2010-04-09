#include <includeall.h>
#pragma hdrstop
#include "whitefinder.h"

//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���

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
	    , nearAlgo(CIEuv1960NearestAlgorithm_
		       (XYZ_ptr((CIEXYZ *) null), mm)) {
	    };

	    RGB_ptr WhitePointFinder::findMatchRGB0(xyY_ptr xyY,
						    RGB_ptr initRGB) {
		RGB_ptr nearestRGB = initRGB;
		bool findNearest = false;

		do {
		    RGB_vector_ptr aroundRGB =
			aroundAlgo.getAroundRGB(nearestRGB, 1);
		    XYZ_ptr center = xyY->toXYZ();
		     bptr < AlgoResult > algoResult =
			nearAlgo.getNearestRGB(center, aroundRGB);
		    XYZ_vector_ptr aroundXYZ = algoResult->aroundXYZ;
		     nearestRGB = algoResult->nearestRGB;
		     findNearest =
			MeasuredUtils::isFirstNearestXYZInuvPrime(center,
								  aroundXYZ);
		} while (!findNearest);
		 return nearestRGB;
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		aroundAlgo.setMode(Normal);
		RGB_ptr result = findMatchRGB0(xyY, RGBColor::White);
		return result;
	    };

	    /*
	       �H���ץ��᪺��, �ץ���l�D255�����I, �Ϧ�׹F��̱����.
	       1. ���̤j���W�D
	       2. �p��ثexyY�P�ؼЭȤ�delta
	       3.
	     */
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {
		aroundAlgo.setMode(White);
		RGB_ptr result = findMatchRGB0(xyY, initRGB);
		return result;
	    };

	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {
		/*if (true)
		   return rgb; */
		RGB_ptr clone = rgb->clone();
		//�M��A�վ�White��RGB�䤤�@�I��255.
		const Channel & maxChannel = clone->getMaxChannel();
		double maxChannelValue = clone->getValue(maxChannel);
		double diff = 255 - maxChannelValue;
		clone->addValue(diff);
		return clone;
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
		return initRGB;
	    };
	};

    };
};


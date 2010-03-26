#include "tconparameter.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace i2c {
	TConParameter::TConParameter(int gammaTestAddress,
				     unsigned char gammaTestBit,
				     int testRGBAddress,
				     bool
				     independentRGB):gammaTestAddress
	    (gammaTestAddress), gammaTestBit(gammaTestBit),
	    testRGBAddress(testRGBAddress),
	    independentRGB(independentRGB) {

	};
	int TConParameter::getGammaTestAddress() {
	    return gammaTestAddress;
	};
	int TConParameter::getTestRGBAddress() {
	    return testRGBAddress;
	};
	bool TConParameter::isIndependentRGB() {
	    return independentRGB;
	};
	unsigned char TConParameter::getGammaTestBit() {
	    return gammaTestBit;
	};

    };
};


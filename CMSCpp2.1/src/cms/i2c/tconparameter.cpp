#include "tconparameter.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace i2c {
	TCONParameter::TCONParameter(int gammaTestAddress,
				     unsigned char gammaTestBit,
				     int testRGBAddress,
				     bool independentRGB):gammaTestAddress
	    (gammaTestAddress), gammaTestBit(gammaTestBit),
	    testRGBAddress(testRGBAddress),
	    independentRGB(independentRGB) {

	};
	int TCONParameter::getGammaTestAddress() {
	    return gammaTestAddress;
	};
	int TCONParameter::getTestRGBAddress() {
	    return testRGBAddress;
	};
	bool TCONParameter::isIndependentRGB() {
	    return independentRGB;
	};
	unsigned char TCONParameter::getGammaTestBit() {
	    return gammaTestBit;
	};
    };
};


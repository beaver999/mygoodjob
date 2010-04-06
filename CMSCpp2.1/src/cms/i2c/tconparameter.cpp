#include "tconparameter.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace i2c {
	using namespace Dep;
	 TCONParameter::TCONParameter(int gammaTestAddress,
				      unsigned char gammaTestBit,
				      int testRGBAddress,
				      bool independentRGB,
				      const MaxValue &
				      lutBit):gammaTestAddress
	    (gammaTestAddress), gammaTestBit(gammaTestBit),
	    testRGBAddress(testRGBAddress),
	    independentRGB(independentRGB), lutBit(lutBit) {

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
	const MaxValue & TCONParameter::getLUTBit() {
	    return lutBit;
	};
    };
};


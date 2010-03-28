#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
//nclude <cms/colorformat/excelfile.h>

namespace cms {
    namespace i2c {
	class TCONParameter {
	  private:
	    const int gammaTestAddress;
	    const int testRGBAddress;
	    const bool independentRGB;
	    const unsigned char gammaTestBit;
	    //const int dataAddressLength;
	  public:
	     TCONParameter(int gammaTestAddress,
			   unsigned char gammaTestBit, int testRGBAddress,
			   bool independentRGB);
	    int getGammaTestAddress();
	    int getTestRGBAddress();
	    bool isIndependentRGB();
	    unsigned char getGammaTestBit();
	    //int getDataAddressLength();
	};
    };
};

#endif


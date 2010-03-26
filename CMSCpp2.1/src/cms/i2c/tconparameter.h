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
	class TConParameter {
	  private:
	    const int gammaTestAddress;
	    const int testRGBAddress;
	    const bool independentRGB;
	    const unsigned char gammaTestBit;
	  public:
	     TConParameter(int gammaTestAddress,
			   unsigned char gammaTestBit, int testRGBAddress,
			   bool independentRGB);
	    int getGammaTestAddress();
	    int getTestRGBAddress();
	    bool isIndependentRGB();
	    unsigned char getGammaTestBit();
	};
    };
};

#endif


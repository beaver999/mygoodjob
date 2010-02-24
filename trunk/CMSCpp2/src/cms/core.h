#ifndef COREH
#define COREH

//C�t�Τ��

//C++�t�Τ��
#include <vector>
//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <util.h>

namespace cms {
    class SpectraIF {
      public:
	virtual double_array getData() = 0;
	virtual int getEnd() = 0;
	virtual int getInterval() = 0;
	virtual int getStart() = 0;
    };

    class ColorMatchingFunction:public jObject, SpectraIF {

    };

    enum CCTMethod {
	McCamyInt, McCamyFloat, Exp, ExpCCTOver50k, Robertson
    };

    class CorrelatedColorTemperature:public jObject {
      public:
	static xyY_ptr CCT2DIlluminantxyY(int tempK);


	static double xy2CCTByMcCamyFloat(xyY_ptr xyY);
    };
    class DeltaE:public jObject {
    };
    class Illuminant:public jObject, SpectraIF {
      public:
	double_array getData() {

	};
	int getEnd() {
	};
	int getInterval() {
	};
	int getStart() {
	};
    };

    class Spectra:public jObject, SpectraIF /*, util::NameIF */  {
    };


    class Target:public jObject {
    };

    class ValuePropertyIF {
      public:
	virtual double_array getValues() = 0;
	virtual void setValues(double_array values) = 0;
	virtual double_array getValues(double_array values) = 0;
    };
};
#endif


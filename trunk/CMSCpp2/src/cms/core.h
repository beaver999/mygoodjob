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
	virtual boost::shared_array < double >getData() = 0;
	virtual int getEnd() = 0;
	virtual int getInterval() = 0;
	virtual int getStart() = 0;
    };

    class ColorMatchingFunction:public java::lang::Object, SpectraIF {

    };

    enum CCTMethod {
	McCamyInt, McCamyFloat, Exp, ExpCCTOver50k, Robertson
    };

    class CorrelatedColorTemperature:public java::lang::Object {
      public:
	static xyY_ptr CCT2DIlluminantxyY(int tempK);


	static double xy2CCTByMcCamyFloat(xyY_ptr xyY);
    };
    class DeltaE:public java::lang::Object {
    };
    class Illuminant:public java::lang::Object, SpectraIF {
      public:
	boost::shared_array < double >getData() {

	};
	int getEnd() {
	};
	int getInterval() {
	};
	int getStart() {
	};
    };

    class Spectra:public java::lang::Object, SpectraIF, util::NameIF {
    };


    class Target:public java::lang::Object {
    };

    class ValuePropertyIF {
      public:
	virtual double_array getValues() = 0;
	virtual void setValues(boost::shared_array < double >values) = 0;
	virtual boost::shared_array <
	    double >getValues(boost::shared_array < double >values) = 0;
    };
};
#endif


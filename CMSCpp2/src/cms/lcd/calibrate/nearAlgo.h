#ifndef NEARALGOH
#define NEARALGOH
//C�t�Τ��

//C++�t�Τ��
//#include <list>;
//#include <vector>;

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include "algo.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		class CIEuv1960NearestAlgorithm:public NearestAlgorithm {
		  public:
		    CIEuv1960NearestAlgorithm(XYZ_ptr white,
					      cms::measure::cp::
					      MeasureInterface & mi);
		    double_array getDelta(XYZ_ptr center, XYZ_ptr XYZ);
		  protected:
		    double getIndex(XYZ_ptr center, XYZ_ptr around);
		};
	    };
	};
    };
};
#endif


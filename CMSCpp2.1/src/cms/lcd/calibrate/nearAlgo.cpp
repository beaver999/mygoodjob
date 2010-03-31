#include <includeall.h>
#pragma hdrstop
#include "nearAlgo.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {

		using namespace cms::measure;
		using namespace java::lang;
		 CIEuv1960NearestAlgorithm::
		    CIEuv1960NearestAlgorithm(XYZ_ptr white,
					      bptr < MeterMeasurement >
					      mm):NearestAlgorithm(white,
								   mm) {
		};
		double_array CIEuv1960NearestAlgorithm::
		    getDelta(XYZ_ptr center, XYZ_ptr XYZ) {
		    return MeasuredUtils::getDeltauvPrime(center, XYZ);
		};
	       	double CIEuv1960NearestAlgorithm::getIndex(XYZ_ptr center,
							   XYZ_ptr around)
		{
		    double_array duvp = getDelta(center, around);
		    double de =
			Math::sqrt(Math::sqr(duvp[0]) +
				   Math::sqr(duvp[1]));
		     return de;
		};

	    };
	};
    };
};


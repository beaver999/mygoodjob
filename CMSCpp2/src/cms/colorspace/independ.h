#ifndef INDEPENDH
#define INDEPENDH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "colorspace.h"
#include <java/lang.h>

namespace cms {
    namespace colorspace {
	namespace independ {
	    enum CIEStandard {
		//CIE���Ѫ���
		ActualStandard,
		//�ץ�CIE����(�|���ǽT)
		IntentStandard
	    };
	    enum Degree {
		Two = 2, Ten = 10
	    };

	    enum NormalizeY {
		Normal100 = 100, Normal1 = 1, Not = -1
	    };

	    class CIEXYZ;

	    class DeviceIndependentSpace:public ColorSpace {
	      protected:
		Degree _degree;
		static double epsilon;
		static double kappa;
		 DeviceIndependentSpace();
		int getNumberBands();
	      public:
		 Degree getDegree();
		void setDegree(Degree degree);
		static void setCIEStandard(CIEStandard standard);
		static const double ACTUAL_EPSILON;
		static const double ACTUAL_KAPPA;

		static const double INTENT_EPSILON;
		static const double INTENT_KAPPA;
		virtual boost::shared_ptr < CIEXYZ > toXYZ() = 0;
	    };

	    class NormalizeYOperator {
	      protected:
		NormalizeY _normalizeY;
	      public:
		virtual void normalize(NormalizeY normalizeY) = 0;
		virtual void normalizeY() = 0;

		void normalizeY100();
		void setNormalizeNot();

		const static double NormalFactor;
	    };
	};
    };
};

#endif


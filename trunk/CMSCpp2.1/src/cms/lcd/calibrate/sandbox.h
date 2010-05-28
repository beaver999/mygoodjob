#ifndef SANDBOXH
#define SANDBOXH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "dimdg.h"


namespace cms {
    namespace lcd {
	namespace calibrate {

	    class AdvancedDGLutGenerator:private DimDGLutGenerator {
	      public:
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr <
				       cms::measure::IntensityAnalyzerIF >
				       analyzer);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr
				       luminanceGammaCurve, int turn);
	      private:
		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve,
						int turn);
	    };

	    enum Domain {
		CIEuv, CIEuvPrime
	    };

	    class DimTargetGenerator {
	      public:

		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr
						      luminanceGammaCurve);
		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr
						      luminanceGammaCurve,
						      Domain domain);
		static XYZ_vector_ptr getGammaTarget(XYZ_ptr startXYZ,
						     XYZ_ptr endXYZ,
						     double_vector_ptr
						     luminanceGammaCurve,
						     double gamma);
	    };
	};
    };
};

#endif


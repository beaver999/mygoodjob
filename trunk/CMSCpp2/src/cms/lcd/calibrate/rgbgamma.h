#ifndef RGBGAMMAH
#define RGBGAMMAH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include "rgbop.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class RGBGamma {
	      public:
		double_vector_ptr r, g, b;
		RGBGamma(double_vector_ptr r, double_vector_ptr g,
			 double_vector_ptr b);
		static void storeToExcel(const std::string & filename,
					 RGBGamma_ptr rgbgamma);
	    };

	    class RGBGammaOp:public RGBOp < RGBGamma > {
	      public:

	    };

	    class BIntensityGainOp:public RGBGammaOp {
	      private:
		double gain;
		int start;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
	      public:
		 BIntensityGainOp(double gain);
		 BIntensityGainOp(double gain, int start);
	    };
	    class P1P2GammaOp:public RGBGammaOp {
	      private:
		double p1, p2;
		RGB_vector_ptr dgcode;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
		RGBGamma_ptr processP1(RGBGamma_ptr source);
		RGBGamma_ptr processP1P2(RGBGamma_ptr source);
	      public:
		 P1P2GammaOp(double p1, double p2, RGB_vector_ptr dgcode);
		 P1P2GammaOp(RGBGamma_ptr source, double p1, double p2,
			     RGB_vector_ptr dgcode);
	    };
	};
    };
};
#endif


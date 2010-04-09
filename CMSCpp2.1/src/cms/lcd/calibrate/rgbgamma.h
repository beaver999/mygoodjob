#ifndef RGBGAMMAH
#define RGBGAMMAH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "rgbop.h"
#include <cms/util/rgbarray.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::util;
	    class RGBGammaOp:public RGBOp < RGBGamma > {

	    };

	    class BIntensityGainOp:public RGBGammaOp {
	      private:
		double gain;
		int start;
		 bptr < BitDepthProcessor > bitDepth;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
	      public:
		 BIntensityGainOp(double gain, int start,
				  bptr < BitDepthProcessor > bitDepth);
	    };
	    class P1P2GammaOp:public RGBGammaOp {
	      private:
		double p1, p2;
		RGB_vector_ptr dglut;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
		RGBGamma_ptr processP1(RGBGamma_ptr source);
		RGBGamma_ptr processP1P2(RGBGamma_ptr source);
	      public:
		 P1P2GammaOp(double p1, double p2, RGB_vector_ptr dglut);
		 P1P2GammaOp(RGBGamma_ptr source, double p1, double p2,
			     RGB_vector_ptr dglut);
	    };
	};
    };
};
#endif


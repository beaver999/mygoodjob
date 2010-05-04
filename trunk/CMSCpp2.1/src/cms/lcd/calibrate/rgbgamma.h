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
		int p1, p2;
		RGB_vector_ptr dglut;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
		RGBGamma_ptr processP1(RGBGamma_ptr source);
		RGBGamma_ptr processP1P2(RGBGamma_ptr source);
	      public:
		 P1P2GammaOp(int p1, int p2, RGB_vector_ptr dglut);
		/*P1P2GammaOp(RGBGamma_ptr source, int p1, int p2,
		   RGB_vector_ptr dglut); */
	    };

	    class NewGammaOp:public RGBGammaOp {
	      private:
		int under;
		double gammaShift;
		RGB_vector_ptr dglut;
		int getNonZeroBlueIndex();
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
	      public:
		 NewGammaOp(int under, double gammaShift,
			    RGB_vector_ptr dglut);
	    };
	};
    };
};
#endif


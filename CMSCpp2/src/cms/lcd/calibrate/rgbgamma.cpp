#include "rgbgamma.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���


namespace cms {
    namespace lcd {
	namespace calibrate {
	    //==================================================================
	    // RGBGamma
	    //==================================================================
	    RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g,
			       double_vector_ptr b):r(r), g(g), b(b) {
	    };
	    //==================================================================

	    //==================================================================
	    // RGBGammaOp
	    //==================================================================
	    RGBGamma_ptr RGBGammaOp::createInstance(RGBGamma_ptr source) {
		RGBGamma_ptr rendering = getRendering(source);
		 foreach(bptr < RGBGammaOp > op, opvector) {
		    rendering = op->createInstance(rendering);
		};
		 return rendering;
	    };
	    //==================================================================
	};
    };
};


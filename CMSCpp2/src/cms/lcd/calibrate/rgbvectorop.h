#ifndef RGBVECTOROPH
#define RGBVECTOROPH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include "rgbop.h"
#include "lcdcalibrator.h"

namespace cms {
    namespace lcd {
	namespace calibrate {

	    class DGLutOp:public RGBOp < RGB_vector > {
	    };

	    class LinearOp:public DGLutOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);

	    };
	    class MinusOp:public DGLutOp {
	      private:double minusValue;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 MinusOp(double minusValue);
	    };

	    class P1P2DGOp:public DGLutOp {
	      private:
		double p1, p2;
		bool smooth;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 P1P2DGOp(double p1, double p2);
		 P1P2DGOp(double p1, double p2, bool smooth);

	    };

	    class RBInterpolationOp:public DGLutOp {
	      private:
		double under;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 RBInterpolationOp(double under);
	    };

	    class BMaxOp:public DGLutOp {
	      private:
		const BitDepth & out;
	      public:
		 BMaxOp(const BitDepth & out);
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };

	    class GByPassOp:public DGLutOp {
	      private:
		const BitDepth & in, &out;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 GByPassOp(const BitDepth & in, const BitDepth & out);
	    };

	    class AvoidFRCNoiseOp:public DGLutOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };
	};
    };
}
#endif


#ifndef RGBOPH
#define RGBOPH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    template < class Type > class RGBOp {
	      private:
		Type source;
		//std::vector < bptr < RGBOp > >opvector;
	      protected:
		Type createInstance(Type source) {
		    Type rendering = getRendering(source);
		     foreach(bptr < RGBOp > op, opvector) {
			rendering = op->createInstance(rendering);
		    };
		     return rendering;
		};
		virtual Type getRendering(Type source)
		= 0;

	      public:
		 RGBOp() {
		};
	      RGBOp(Type source):source(source) {
		};
		Type createInstance() {
		    return createInstance(source);
		};
		void setSource(Type source) {
		    this->source = source;
		};
		/*void addOp(bptr < RGBOp > op) {
		   opvector.push_back(op);
		   }; */
	    };

	    /*template <> class RGBGammaOp_ < RGBGamma > {

	       }; */

	    /*template <> class TestOp:public RGBOp < RGBGamma_ptr > {
	       }; */


	};
    };
};
#endif


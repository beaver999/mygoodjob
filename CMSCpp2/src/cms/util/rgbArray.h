#ifndef RGBARRAYH
#define RGBARRAYH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace util {
	class RGBArray {

	};
	class RGBVector {
	  protected:
	    RGB_vector_ptr rgbVector;
	  public:
	    RGBVector(RGB_vector_ptr rgbVector);
	};
	class RGBVectorOp:public RGBVector {
	  public:
	    virtual RGBVectorOp createInstance();
	    void addSource(RGBVectorOp source);
	};
    };
}
#endif


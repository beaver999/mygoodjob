#ifndef TCONCONTROLH
#define TCONCONTROLH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
//nclude <cms/colorformat/excelfile.h>

namespace cms {
    namespace i2c {
	class TCONControl {
	  private:
	    bptr < TCONParameter > parameter;
	    bptr < i2cControl > control;
	  public:
	    TCONControl(bptr < TCONParameter > parameter,
			bptr < i2cControl > control);
	    void setTestRGB(RGB_ptr rgb);
	    void setGammaTest(bool enable);

	};
    };
};

#endif


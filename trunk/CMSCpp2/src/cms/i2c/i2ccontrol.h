#ifndef I2CCONTROLH
#define I2CCONTROLH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace i2c {
	class i2cControl {
	  public:
	    void connect();
	    void disconnect();
	};

	class i2cLPTControl:public i2cControl {

	};

	class i2cUSBControl:public i2cControl {

	};
    };
};

#endif


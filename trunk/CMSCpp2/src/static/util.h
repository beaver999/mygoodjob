#ifndef UTILH
#define UTILH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace util {
    //using namespace std;
    //using namespace boost;
    class Util {
      public:
	static boost::shared_ptr < std::string > toString(wchar_t * wc);
	static boost::shared_array < wchar_t >
	    towchar_t(std::string & str);
    };
    class NameIF {
      public:
	virtual boost::shared_ptr < std::string > getName() = 0;
    };

};
#endif


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
	static string_ptr toString(wchar_t * wc);
	static boost::shared_array < wchar_t >
	    towchar_t(std::string & str);
    };
    class NameIF {
      public:
	virtual string_ptr getName() = 0;
    };

};
#endif


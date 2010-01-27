#ifndef UTILH
#define UTILH

//C�t�Τ��

//C++�t�Τ��
#include <string>
//��L�w�Y���
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
//�����ؤ��Y���

namespace util {
    using namespace std;
    using namespace boost;
    class Util {
      public:
	static shared_ptr < string > toString(wchar_t * wc);
	static shared_array < wchar_t > towchar_t(string & str);
    };
    class NameIF {
      public:
	virtual shared_ptr < string > getName() = 0;
    };

};
#endif


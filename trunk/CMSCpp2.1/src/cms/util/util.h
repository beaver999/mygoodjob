#ifndef UTILH
#define UTILH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <ADODB.hpp>
#include <DB.hpp>

//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace util {
	using namespace std;
	using namespace boost;
	class Util {
	  public:
	    static string_ptr toString(wchar_t * wc);
	    static template < typename T >
		const string Util::toString(const T t) {
		return _toString(t);
	    };
	    static boost::shared_array < wchar_t >
		towchar_t(std::string & str);
	    static wchar_t *towchar_t2(std::string & str);
	    static void deleteExist(const std::string & filename);
	    static bptr < WideString > toWideString(const std::string & s);


	};

	class StringVector {
	  public:
	    static string_vector_ptr fromCString(int count, ...);
	    static string_vector_ptr fromString(int count, ...);

	    static string_vector_ptr fromString(int n, const std::string *
						strings);
	};
	class NameIF {
	  public:
	    virtual string_ptr getName() = 0;
	};

    };
};
#endif


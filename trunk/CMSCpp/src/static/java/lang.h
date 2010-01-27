#ifndef LANGH
#define LANGH

//C�t�Τ��

//C++�t�Τ��
#include <string>
//��L�w�Y���
#include <boost/shared_ptr.hpp>
//�����ؤ��Y���



#define shared_vector_double  shared_ptr < vector < double > >
#define shared_vector_string  shared_ptr < vector < string > >
#define null_string shared_ptr < string > (NULL)

/*
 java->C++�ഫ��h

 *override+overload���D
 c++�ʥFjava��interface, ���M�i�Hpure virtual func�N��,
 ���O�|�J��override+overload�H��hide�����D. �B�ϥΤF�h���~��, �|�ޤJ�����~�Ӫ����D.
 �ҥH�b���P���O��overload�ݨD�ɺɶq�קK, �H��W�ѨM; ���L�n�O���j�q��W���ݭn,
 ���ܪ����b�l���O��Qhide��func�I�s�^��.

 *�T��ϥΫ��ФΰѦ�
 �קK�ѰOdelete�����D, �Hsmart_ptr���N����

 *���󧹥��ĥ�smart_ptr
 �Ѧҷ|���L�k��NULL�����p, �]�����ĥ�smart_ptr, �@������gc���ĪG.
 NULL��smart_ptr���ͤ�k�� shared_array < double >p(NULL);

 *��ͫ��O�}�C�ĥ�smart_ptr(shared_array)
 �º�ĥ�vector����, ���M�i�H�F������java array���S��, ���O�@��local vector����
 ��@ref or ptr�Q�ǥX�h, �_�h�i��|���V�@�ӥ������Ŷ�.

 �ҥH�@��O��ĳ�ĥ�shared_ptr<vector<>>, ���O�o�ا@�k�|��indent(�{���X�榡�ƾ�) �X��!
 �]���{�b�Ϊ�indent�Oc�M�ݪ�, �L�ݤ���template��<< >>...�|��@shift�B��l.
 �X�g���դ��U, ���ӨM�w��define���覡�H  shared_vector_double �N�� shared_ptr < vector < double > >,
 �N�i�H�ױ�indent�����D!

 ���O�����O����...�n�@�����_����(*)[]�h���� (�����->[] �o�ةǻy�k..), �ӳ·ФF,
  �ҥH�^�Y��shared_array

*/


namespace java {
    namespace lang {
	using namespace boost;
	using namespace std;
	class Object;

	class Class {
	  private:
	    friend class Object;
	    const type_info & info;
	     Object & object;
	     Class(Object & object);
	  public:
	     shared_ptr < string > getSimpleName();
	     shared_ptr < string > getName();
	};

	class Object {
	  private:
	    bool null;
	    Class c;
	  public:
	     bool equals(shared_ptr < Object > obj);
	     Class & getClass();
	    int hashCode();
	     shared_ptr < string > toString();
	    bool isNull();
	     Object(bool null);
	     Object();

	  protected:
	     shared_ptr < Object > clone();
	    void finalize();
	};

	class Math {
	  public:
	    static double sqrt(double a);
	    static double pow(double a, double b);
	    static double atan2(double y, double x);
	    static const double PI;
	    static double cos(double x);
	    static double sin(double x);
	};


	class Exception:public Object {
	  public:
	    Exception();
	    Exception(string message);
	    string & toString();
	  private:
	    string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException();
	    RuntimeException(string message);
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(string message);
	};

	class IllegalArgumentException:public RuntimeException {
	  public:
	    IllegalArgumentException();
	    IllegalArgumentException(string message);
	};
    };
};
#endif


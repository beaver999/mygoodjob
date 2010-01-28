#ifndef LANGH
#define LANGH

//C�t�Τ��

//C++�t�Τ��
#include <string>
//��L�w�Y���
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
//�����ؤ��Y���

//==============================================================================
// include template
//==============================================================================
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
//==============================================================================

//==============================================================================
//²��boost::smart_ptr�ϥΤW������
//==============================================================================
#define vector_double_ptr boost::shared_ptr < std::vector < double > >
#define vector_string_ptr boost::shared_ptr < std::vector < std::string > >
#define double_array boost::shared_array<double>
#define float_array boost::shared_array<float>

#define string_ptr boost::shared_ptr < std::string >
#define nil_string_ptr string_ptr ((std::string*)NULL)
//==============================================================================

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
 �X�g���դ��U, ���ӨM�w��define�N�i�H�ױ�indent�����D!

 ���O�����O����...�n�@�����_����(*)[]�h���� (�����->[] �o�ةǻy�k..), �ӳ·ФF,
  �ҥH�^�Y��shared_array

*/


namespace java {
    namespace lang {
	class Object;

	class Class {
	  private:
	    friend class Object;
	    const std::type_info & info;
	     Object & object;
	     Class(Object & object);
	  public:
	     boost::shared_ptr < std::string > getSimpleName();
	     boost::shared_ptr < std::string > getName();
	};

	class Object {
	  private:
	    bool null;
	    Class c;
	  public:
	     bool equals(boost::shared_ptr < Object > obj);
	     Class & getClass();
	    int hashCode();
	     boost::shared_ptr < std::string > toString();
	    bool isNull();
	     Object(bool null);
	     Object();

	  protected:
	     boost::shared_ptr < Object > clone();
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
	    Exception(std::string message);
	    std::string & toString();
	  private:
	    std::string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException();
	    RuntimeException(std::string message);
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(std::string message);
	};

	class IllegalArgumentException:public RuntimeException {
	  public:
	    IllegalArgumentException();
	    IllegalArgumentException(std::string message);
	};
    };
};
#endif


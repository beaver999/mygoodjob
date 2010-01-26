#ifndef LANGH
#define LANGH

#include <string>
#include <vcl.h>
#include <math>
#include <boost/shared_ptr.hpp>
#include <typeinfo>
#include <iostream>
//#include "exception.h"

#define  shared_vector_double shared_ptr < vector < double > >
#define  shared_vector_string shared_ptr < vector < string > >

/*
 java->C++�ഫ��h

 *override+overload���D
 c++�ʥFjava��interface, ���M�i�Hpure virtual func�N��,
 ���O�|�J��override+overload�H��hide�����D. �B�ϥΤF�h���~��, �|�ޤJ�����~�Ӫ����D.
 �ҥH�b���P���O��overload�ݨD�ɺɶq�קK, �H��W�ѨM; ���L�n�O���j�q��W���ݭn,
 ���ܪ����b�l���O��Qhide��func�I�s�^��.

 *�T��ϥΫ��ФΰѦ�
 �קK�ѰOdelete�����D

 *���󧹥��ĥ�smart_ptr
 �Ѧҷ|���L�k��null�����p, �]�����ĥ�smart_ptr, �@������gc���ĪG.
 smart_ptr�����ͤ�k�� shared_array < double >p(NULL);

 *��ͫ��O�}�C�ĥ�smart_ptr(shared_array)
 �º�ĥ�vector����, ���M�i�H�F������java array���S��, ���O�@��local vector�����@ref or ptr�Q�ǥX�h,
 �_�h�i��|���V�@�ӥ������Ŷ�.
 �ҥH�@��O��ĳ�ĥ�shared_ptr<vector<>>, ���O�o�ا@�k�|��indent(�{���X�榡�ƾ�) �X��!
 �]���{�b�Ϊ�indent�Oc�M�ݪ�, �L�ݤ���template��<< >>...�|��@shift�B��l.

 �X�g���դ��U, ���ӨM�w��define���覡�H  shared_vector_double �N�� shared_ptr < vector < double > >,
 �N�i�H�ױ�indent�����D!
 ���O�����O����...�n�@�����_����(*)[]�h����, �ӳ·ФF, �ҥH�^�Y��shared_array

*/


namespace java {
    namespace lang {
	using namespace boost;
	//using std::string;
	using namespace std;
	class Object;

	class Class {
	  private:
	    friend class Object;
	    const type_info & info;
	     Object & object;
	     Class(Object & object):object(object), info(typeid(object)) {

	    };
	  public:

	     shared_ptr < string > getSimpleName() {
		return shared_ptr < string > (new string(info.name()));
	    };

	     shared_ptr < string > getName() {
		return shared_ptr < string > (new string(info.name()));
	    };
	};

	class Object {
	  private:
	    bool null;
	    Class c;
	  public:
	     boolean equals(shared_ptr < Object > obj) {
		//return this->Equals(&obj);
		return false;
	    };

	    Class & getClass() {
		return c;
	    };
	    int hashCode() {
		//return this->Hash();
		return -1;
	    };

	    shared_ptr < string > toString() {
		return shared_ptr < string > (new string());
	    };
	    bool isNull() {
		return null;
	    };
	  Object(bool null = false):null(null), c(*this) {

	    };

	  protected:
	    shared_ptr < Object > clone() {
		return shared_ptr < Object > (new Object());
	    };
	    void finalize() {
	    };


	};



	class Math {
	  public:
	    static double sqrt(double a) {
		return std::sqrt(a);
	    };
	    static double pow(double a, double b) {
		return std::pow(a, b);
	    };
	    static double atan2(double y, double x) {
		return std::atan2(y, x);
	    };
	    static const double PI;
	    static double cos(double x) {
		return std::cos(x);
	    };
	    static double sin(double x) {
		return std::sin(x);
	    };
	};

	class Exception:public Object {
	  public:
	    Exception() {
	    };
	    Exception(string message) {
		this->message = message;
	    };
	    string & toString() {
		return message;
	    };
	  private:
	    string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException() {
	    };
	  RuntimeException(string message):Exception(message) {

	    };
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException() {
	    };
	  IllegalStateException(string message):RuntimeException(message)
	    {

	    };
	};

	class IllegalArgumentException:public RuntimeException {
	  public:
	    IllegalArgumentException() {
	    };
	  IllegalArgumentException(string message):RuntimeException(message)
	    {

	    };
	};


    };
};
#endif


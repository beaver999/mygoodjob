#ifndef LANGH
#define LANGH

//C�t�Τ��

//C++�t�Τ��
#include <string>
#include <vector>
//#pragma hdrstop

//��L�w�Y���
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>
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
//²��java.lang�ϥΤW������
//==============================================================================
#define jObject java::lang::Object
#define null NULL
//==============================================================================

//==============================================================================
//²��boost::smart_ptr�ϥΤW������
//==============================================================================
#define bptr boost::shared_ptr
#define barray boost::shared_array
#define bptr_ boost::scoped_ptr

#define string_ptr bptr < std::string >
#define nil_string_ptr string_ptr ((std::string*)NULL)
#define Object_ptr bptr < jObject >

#define double_vector std::vector < double >
#define double_vector_ptr bptr < double_vector >
#define nil_double_vector_ptr double_vector_ptr ((double_vector*)NULL)
#define nil_double_vector nil_double_vector_ptr

#define int_vector std::vector < double >
#define int_vector_ptr bptr < int_vector >

#define string_vector std::vector < std::string >
#define string_vector_ptr bptr < string_vector >
#define stringp_vector std::vector < string_ptr >
#define stringp_vector_ptr bptr < string_ptr_vector >


#define double_array barray <double>
#define nil_double_array double_array ((double*)NULL)
#define float_array barray <float>
#define nil_float_array float_array ((float*)NULL)



#define foreach BOOST_FOREACH
//==============================================================================

//==============================================================================
//²��cms�ϥΤW������
//==============================================================================
#define Dep cms::colorspace::depend
#define Indep cms::colorspace::independ

#define RGB_ptr bptr < Dep::RGBColor >
#define RGB_array barray < RGB_ptr >
#define RGB_list std::list < RGB_ptr >
#define RGB_list_ptr bptr < RGB_list >
#define RGB_vector std::vector < RGB_ptr >
#define RGB_vector_ptr bptr < RGB_vector >

#define xyY_ptr bptr < Indep::CIExyY >
#define xyY_vector std::vector < xyY_ptr >
#define xyY_vector_ptr bptr < xyY_vector >

#define XYZ_ptr bptr < Indep::CIEXYZ >
#define XYZ_vector std::vector < XYZ_ptr >
#define XYZ_vector_ptr bptr < XYZ_vector >


#define channel_vector std::vector < Dep::Channel >
#define channel_vector_ptr bptr < channel_vector >

#define Patch_ptr bptr < cms::Patch >
#define Patch_list std::list < Patch_ptr >
#define Patch_list_ptr bptr < Patch_list >
#define Patch_vector std::vector < Patch_ptr >
#define Patch_vector_ptr bptr < Patch_vector >
//==============================================================================

//==============================================================================
//²��tnt�ϥΤW������
//==============================================================================
#define longdouble1D TNT::Array1D< long double >
#define longdouble2D TNT::Array2D< long double >
#define longdouble2D_ptr bptr< longdouble2D >

//#define _USE_LONG_DOUBLE_

#ifdef  _USE_LONG_DOUBLE_
#define double1D TNT::Array1D< long double >
#define double2D TNT::Array2D< long double >
#define double3D TNT::Array3D< long double >
#else
#define double1D TNT::Array1D< double >
#define double2D TNT::Array2D< double >
#define double3D TNT::Array3D< double >
#endif

#define double1D_ptr bptr< double1D >
#define double2D_ptr bptr< double2D >
#define double3D_ptr bptr< double3D >

#define float1D TNT::Array1D< float >
#define float2D TNT::Array2D< float >
#define float3D TNT::Array3D< float >
//==============================================================================


namespace cms {
    class Patch;
    class Spectra;
    namespace colorformat {
	namespace logo {
	    class LogoFile;
	};
	class ExcelFileDB;
    };
    namespace colorspace {
	namespace depend {
	    class RGBColor;
	    class Channel;
	    class RGBColorSpace;
	};
	namespace independ {
	    class CIExyY;
	    class CIEXYZ;
	};
    };
    namespace lcd {
	namespace calibrate {
	    class LCDCalibrator;
	    namespace algo {
		class ChromaticAroundAlgorithm;
		class CIEuv1960NearestAlgorithm;
	    };
	};
    };
    namespace measure {
	class MeterMeasurement;
	class MeasureResult;
	class ComponentAnalyzerIF;
	namespace cp {
	    class MeasureInterface;
	};
	namespace meter {
	    class Meter;
	    class CA210;
	};
    };
};

//==============================================================================


/*
 java->C++�ഫ��h

 *override+overload���D
 c++�ʥFjava��interface, ���M�i�Hpure virtual func�N��,
 ���O�|�J��override+overload�H��hide�����D. �B�ϥΤF�h���~��, �|�ޤJ�����~�Ӫ����D.
 �ҥH�b���P���O��overload�ݨD�ɺɶq�קK, �H��W�ѨM; ���L�n�O���j�q��W���ݭn,
 ���ܪ����b�l���O��Qhide��func�I�s�^��.

 *�T��ϥΫ��ФΰѦ�
 �קK�ѰOdelete�����D, �Hsmart_ptr���N����.
 �ҥ~���O, string��@�`�ƪ����p�U, �i�Hconst string &�ϥ�.

 *���󧹥��ĥ�smart_ptr
 �Ѧҷ|���L�k��NULL�����p, �]�����ĥ�smart_ptr, �@������gc���ĪG.
 NULL��smart_ptr���ͤ�k�� shared_array < double >p(NULL);

 *��ͫ��O�}�C�ĥ� ���שT�w: shared_ptr(shared_array)
                   ���פ��w: shared_ptr< vector<> >
 �º�ĥ�vector����, ���M�i�H�F������java array���S��, ���O�@��local vector����
 ��@ref or ptr�Q�ǥX�h, �_�h�i��|���V�@�ӥ������Ŷ�.

 �ҥH�@��O��ĳ�ĥ�shared_ptr< vector<> >, ���O�o�ا@�k�|��indent(�{���X�榡�ƾ�) �X��!
 �]���{�b�Ϊ�indent�Oc�M�ݪ�, �L�ݤ���template��<< >>...�|��@shift�B��l.
 �X�g���դ��U, ���ӨM�w��define�N�i�H�ױ�indent�����D!

 ���O�����O����...�n�@�����_����(*)[]�h���� (�����->[] �o�ةǻy�k..), �ӳ·ФF,
 �ҥH�^�Y��shared_array.

 �V�|���O, shared_array�S��k���D�ۤv������!
 �]��java����double[]�ɶq�Hshared_ptr< vector<> >���N.
 ��List<>�]�wvector<>���N, �]��java���Ϊ�List<>�O�HArrayList��@,
 ��S�ʨ��������STL��vector.

 *�O�_�٭n�ϥΰ}�C?(�Y��ӻ��O���V�ƼƤ���������)
 �ĥ�share_array��i�H���κ޲z�}�C������(��ꤣ�O�}�C, �Y��ӻ��O����).
 ���Oshare_array�ʥF���׸�T, �ݭn�ۤv���@����, share_array����8byte.
 �ĥ�vector+bptr��, ���κ޲z�귽�B���D����, ���Ovector��������24byte.
 double���Ц���4byte�̤�, ���O�\��̳h�F.
 
 �n�O�����֦��O�|���j�q���鲣��, ���share_array.
 �n�O���餣�h, �h���vector+bptr.
 �Y�����D����h��, ��ΫO�I��vector+bptr.

 ��ɿ��share_array: ���פ��ܰ�, ���פw��, �|���j�q����, ������
 ��ɿ��vector+bptr: ���׷|�ܰ�, ���ץ���, ���|���j�q����

 *enum �P Enumeration
 enum�Oc++����, �\��ܮz, �򥻤W�u�O�@�ӱ`�ƥN���Ӥw.
 ���p�G���ݽ������\��, ���enum���F.
 �n�Oenum�ݭn��class�ϥΪ��ɭ�, ��ĳ�ĥ��X�R����Enumeration().
 �w�q��k��: Enumeration(enum_name)
              item1=value, item2=value, ...
             EnumerationEnd();
 �i�H Enumeration::item1�ϥ�, ���n����.
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
	    const string_ptr getSimpleName();
	    const string_ptr getName();
	};

	class Object {
	  private:
	    static int globalID;
	    const int objectID;
	    bool _null;
	    Class c;
	  public:
	    const bool equals(Object_ptr obj);
	     Class & getClass();
	    const int hashCode();
	    const string_ptr toString();
	    const bool isNull();
	     Object(bool _null);
	     Object();
	    const int getObjectID();

	  protected:
	     Object_ptr clone();
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
	    static double sqr(double v);
	    static double round(double v);

	    static double min(double a, double b);
	    static double max(double a, double b);

	    static int maxIndex(double_array values, int n);
	    static int minIndex(double_array values, int n);
	    static int maxIndex(double_vector_ptr values);
	    static int minIndex(double_vector_ptr values);
	};

        /*
          *�ҥ~��t
           ������sjava�ҥ~��t, Exception���̤W�h���O, �䩳�U��RuntimeException.
           ��RuntimeException�U�S���̱`�Ϊ��X�بҥ~.
        */
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
	class UnsupportedOperationException:public RuntimeException {
	  public:
	    UnsupportedOperationException();
	    UnsupportedOperationException(std::string message);
	};
	class IndexOutOfBoundsException:public RuntimeException {
	  public:
	    IndexOutOfBoundsException();
	    IndexOutOfBoundsException(std::string message);
	};

    };
};


#define Enumeration(E) \
struct E \
{ \
public: \
     E(int value = 0) : _value((__Enum)value) { \
     } \
     E& operator=(int value) { \
         this->_value = (__Enum)value; \
         return *this; \
     } \
     operator int() const { \
         return this->_value; \
     } \
\
     enum __Enum {

#define EnumerationEnd() \
     }; \
\
private: \
     __Enum _value; \
};

#endif


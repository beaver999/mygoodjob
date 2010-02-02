#ifndef COLORSPACEH
#define COLORSPACEH

//C�t�Τ��

//C++�t�Τ��
#include <vector>
//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace colorspace {

	class ColorSpace:public java::lang::Object /*, NameIF, virtual ValuePropertyIF  */  {

	  private:
	    bool setValuesLocked;
	  protected:
	    virtual int getNumberBands() = 0;
	    virtual boost::shared_array <
		double >_getValues(boost::shared_array < double >values) =
		0;
	    virtual void _setValues(boost::shared_array < double >values) =
		0;
	     ColorSpace();
	  public:
	    static double_array
		cartesian2polarCoordinatesValues(boost::shared_array <
						 double >cartesianValues);
	    static double_array
		cartesian2polarCoordinatesValues(double x, double y);

	    bool equalsValues(ColorSpace & colorSpace);

	     boost::shared_ptr < std::string > getName();
	     boost::shared_array < double >getValues();
	     boost::shared_array < double >getValues(boost::shared_array <
						     double >values);
	    static boost::shared_array <
		double >polar2cartesianCoordinatesValues(boost::
							 shared_array <
							 double
							 >polarValues);
	    static boost::shared_array <
		double >polar2cartesianCoordinatesValues(double
							 distance, double
							 angle);

	    void setValues(double_array values);
	    void setValues(double value1, double value2, double value3);
	    virtual string_vector_ptr getBandNames() = 0;
	    void setValuesLock(bool lock);

	};
    };
};
#endif


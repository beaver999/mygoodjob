#ifndef REGRESSIONH
#define REGRESSIONH

//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

    namespace math {
	class SVDLib {

	};
	class LinearRegression {
	  public:
	    LinearRegression(double_vector_ptr x, double_vector_ptr y);
	    double getValue(double x);
	    double getSlope();
	    double getIntercept();
	    double getCoefficient();
	  private:

	    double m_a, m_b, m_coeff;
	};
    };

#endif


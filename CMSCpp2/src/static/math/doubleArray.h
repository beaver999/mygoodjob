#ifndef DOUBLEARRAYH
#define DOUBLEARRAYH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace math {
    class DoubleArray {
      public:
	static double_array plus(double_array v1, double v, int n);
	static double_array minus(double_array v1, double_array v2, int n);
	static string_ptr toString(double_array m, int n);
	static double_array times(double_array v1, double v, int n);
	static double_vector_ptr getRangeCopy(double_vector_ptr M, int j1,
					      int j2);
    };
};

#endif


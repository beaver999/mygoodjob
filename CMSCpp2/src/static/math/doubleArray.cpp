#include "doublearray.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <boost/lexical_cast.hpp>

//�����ؤ��Y���

namespace math {
    using namespace boost;
    using namespace java::lang;
    string_ptr DoubleArray::toString(double_array m, int n) {
	using namespace std;
	string_ptr str(new string());
	for (int x = 0; x != n; x++) {
	    *str += lexical_cast < string > (m[x]);
	    //str->insert(m[x]);
	};
	return str;
    };

    double_array DoubleArray::plus(double_array v1, double v, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] + v;
	}
	return array;
    };

    double_array DoubleArray::minus(double_array v1, double_array v2,
				    int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] - v2[i];
	}
	return array;
    };

    double_array DoubleArray::times(double_array v1, double v, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] * v;
	}
	return array;
    }

    double_vector_ptr DoubleArray::getRangeCopy(double_vector_ptr M,
						int j1, int j2) {
	double_vector_ptr copy(new double_vector);
	System::vectorcopy(M, j1, copy, 0, j2 - j1 + 1);
	return copy;
    };
};


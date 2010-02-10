#include "searcher.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include   <math.hpp>
//�����ؤ��Y���

    namespace math {

	int Searcher::sequentialSearch(double_vector_ptr a, double key) {

	    for (int x = 0; x != a->size(); x++) {
		if ((*a)[x] == key) {
		    return x;
		}
	    }
	    return -1;

	};
	int Searcher::sequentialSearch(int_vector_ptr a, int key) {
	    for (int x = 0; x != a->size(); x++) {
		if ((*a)[x] == key) {
		    return x;
		}
	    }
	    return -1;
	};

	int_vector_ptr
	    Searcher::leftNearSequentialSearchAll(double_vector_ptr a,
						  double key) {
	    int_vector_ptr result(new int_vector);
	    int search = leftNearSequentialSearch(a, key);
	    result->
		push_back(leftNearSequentialSearch0(a->size(), search));
	    result->push_back(search);

	    return result;
	};
	int Searcher::leftNearSequentialSearch0(int arrayLength,
						int binarySearchResult) {
	    int result = binarySearchResult;
	    if (result < -1) {
		//interstion�����X
		result = -result;
		if (result > arrayLength) {
		    return -1;
		} else {
		    return result - 2;
		}
	    } else if (result != 0 && result != -1) {
		//�@�몺���X
		return result - 1;
	    } else {
		//��0 or -1�����X
		return result;
	    }
	};
	int Searcher::leftNearSequentialSearch(double_vector_ptr a,
					       double key) {
	    double prev = NaN;
	    for (int x = 0; x != a->size(); x++) {
		double v = (*a)[x];
		if (v == key) {
		    return x;
		} else if (!IsNan(prev) && key > prev && key < v) {
		    return -(x + 1);
		};
		prev = v;
	    }
	    return -1;
	};

    };


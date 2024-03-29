#include "lang.h"
#include <cmath>
//#include <jobject.h>

namespace java {
    namespace lang {
	boolean Object::equals(Object & obj) {
	    //return this->Equals(&obj);
	    return false;
	}
	Class & Object::getClass() {
	    return *new Class();
	}
	int Object::hashCode() {
	    //return this->Hash();
	    return -1;
	}

	void Object::notify() {

	}
	void Object::notifyAll() {
	}

	string & Object::toString() {
	    return *new string();
	}

	void Object::wait() {
	}
	void Object::wait(long timeout, int nanos) {
	}
	void Object::wait(long timeout) {
	}
	bool Object::isNull() {
	    return null;
	}


	Object & Object::clone() {
	    return *new Object();
	}

	void Object::finalize() {
	    //this->~Object();
	}

      Object::Object(bool null = false):null(null) {

	}

      Object::Object():null(false) {
	}

	string & Class::getSimpleName() {
	    return *new string("");
	}
	//using namespace std;
	double Math::sqrt(double a) {
	    return std::sqrt(a);
	}
	double Math::pow(double a, double b) {
	    return std::pow(a, b);
	}
	double Math::atan2(double y, double x) {
	    return std::atan2(y, x);
	}
	double Math::cos(double x) {
	    return std::cos(x);
	}
	double Math::sin(double x) {
	    return std::sin(x);
	}
    };
};


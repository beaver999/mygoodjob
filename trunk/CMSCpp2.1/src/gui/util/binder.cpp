#include <includeall.h>
#pragma hdrstop
#include "binder.h"

//C�t�Τ��
//#include <cstdarg>
//C++�t�Τ��

//��L�w�Y���
//#include <boost/tokenizer.hpp>
//�����ؤ��Y���
//#include <debug.h>

namespace gui {
    namespace util {
	double UIBinder::editToScrollBar(double value) {
	    return value;
	};
	double UIBinder::scrollBarToEdit(double value) {
	    return value;
	};

      UIBinder::UIBinder(TEdit * edit, TScrollBar * scrollBar):edit(edit),
	    scrollBar(scrollBar)
	{

	};
    };
};


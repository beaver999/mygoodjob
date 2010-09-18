#ifndef BINDERH
#define BINDERH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���


namespace gui {
    namespace util {
	class UIBinder {
	  private:
	    TEdit * edit;
	    TScrollBar *scrollBar;
	  protected:
	    double editToScrollBar(double value);
	    double scrollBarToEdit(double value);
	  public:
	     UIBinder(TEdit * edit, TScrollBar * scrollBar);

	};
    };
};

#endif


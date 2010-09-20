#ifndef BINDERH
#define BINDERH

//C�t�Τ��

//C++�t�Τ��
#include <map>
//��L�w�Y���
#include <vcl.h>
#include <Controls.hpp>
//�����ؤ��Y���
#include <java/lang.h>

namespace gui {
    namespace util {
	class UIBinder {
	    enum Type { Edit2ScrollBar, Edit2Edit };
	  private:
	     TEdit * edit;
	    TEdit *edit2;
	    TScrollBar *scrollBar;
	    Type type;
	  protected:
	     virtual double editToScrollBarValue(double value);
	    virtual double scrollBarToEditValue(double value);
	    void edit2ScrollBar(TObject * sender);
	    void edit2Edit(TObject * sender);
	  public:
	     UIBinder(TEdit * edit, TScrollBar * scrollBar);
	     UIBinder(TEdit * edit1, TEdit * edit2);
	    void active(TObject * sender);
	};

	class MultiUIBinder {
	  private:
	    //TWinControl * t;
	    std::map < TWinControl *, binder_ptr > bindebrMap;
	  public:
	    MultiUIBinder();
	    void active(TObject * sender);
	    void bind(TEdit * edit, TScrollBar * scrollBar);
	    void bind(TEdit * edit1, TEdit * edit2);
	};
    };
};

#endif


#ifndef CMFH
#define CMFH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
//#include <vcl.h>
//�����ؤ��Y���

//#define USE_QUERY

namespace cms {
    namespace colorformat {

	class Parser {
	  private:
	    bptr < TStringList > strList;

	  public:
	    Parser(const string & filename);
	    int getCount();
	    string_vector_ptr getTokenize(int index);
	    //virtual void parsing() = 0;
	};
	class ColorMatchingFunctionFile:public Parser {
	  private:
	    double2D_ptr CMF;
	    double2D_ptr filterCMFnTranspose(double2D_ptr cmf);
	  public:
	     ColorMatchingFunctionFile(const string & filename);
	    CMF_ptr getColorMatchingFunction();
	    Spectra_vector_ptr getSpectraVector();
	    void parsing();
	};
    };
};
#endif


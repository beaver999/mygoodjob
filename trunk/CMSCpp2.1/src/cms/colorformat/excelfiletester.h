#ifndef EXCELFILETESTERH
#define EXCELFILETESTERH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <ADODB.hpp>
#include <DB.hpp>
//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace colorformat {
	class ExcelFileTester {
	  private:
	    TADOConnection * ADOConnection1;
	  public:
	    ExcelFileTester(string_ptr filename);
	};
    };
};

#endif


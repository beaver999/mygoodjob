#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
//nclude <cms/colorformat/excelfile.h>

namespace cms {
    namespace i2c {
	class TConParameter {
	  private:
	    const cms::colorformat::ExcelFileDB & excel;
	    string_ptr tcon;
	  public:
	     TConParameter(const cms::colorformat::ExcelFileDB & excel);
	};
    };
};

#endif


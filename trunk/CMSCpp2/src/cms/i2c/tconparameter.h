#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <cms/colorformat/excelfile.h>

namespace cms {
    namespace i2c {
	class TConParameter {
	  private:
	    const ExcelFileDB & excel;
	    string_ptr tcon;
	};
    };
};

#endif


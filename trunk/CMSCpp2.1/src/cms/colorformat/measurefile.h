#ifndef MEASUREFILEH
#define MEASUREFILEH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>


namespace cms {
    namespace colorformat {
	class SimpleExcelReader {
	  private:
	    bptr < ExcelFileDB > excel;
	  public:
	    SimpleExcelReader(const std::string & filename);
	};
	class MeasureFile {
	};
	class RampMeasureFile {
	};
    };
};


#endif


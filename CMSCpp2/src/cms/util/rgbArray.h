#ifndef RGBARRAYH
#define RGBARRAYH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>


namespace cms {
    namespace util {

	class RGBVector {
	  public:
	    static string_ptr toString(RGB_vector_ptr rgbVector);
	    static RGB_vector_ptr getLinearRGBVector(int n);
	    static void storeToExcel(const std::string & filename,
				     RGB_vector_ptr rgbVector);
	    /*static void storeToExcelDB(bptr <
	       cms::colorformat::ExcelFileDB > db,
	       string_ptr tableName,
	       string_vector_ptr header,
	       RGB_vector_ptr rgbVector);
	     */
	    static RGB_vector_ptr clone(RGB_vector_ptr vector);
	    static RGB_vector_ptr deepClone(RGB_vector_ptr vector);
	    //static RGB_vector_ptr
	    static void changeMaxValue(RGB_vector_ptr vector,
				       const Dep::MaxValue & type);
	    static void quantization(RGB_vector_ptr vector,
				     const Dep::MaxValue & maxValue);
	};

    };
}
#endif


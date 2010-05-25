#ifndef MEASUREFILEH
#define MEASUREFILEH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���


namespace cms {
    namespace colorformat {

	class MeasureFile {
	};
	class RampMeasureFile:public ExcelAccessBase {
	  private:
	    static const std::string & Sheet1;
	    int getMaximumSize(Component_vector_ptr wMeasureData,
			       Patch_vector_ptr rMeasureData,
			       Patch_vector_ptr gMeasureData,
			       Patch_vector_ptr bMeasureData);
	  public:
	     RampMeasureFile(const std::string & fileName,
			     const Mode mode);
	     RampMeasureFile(const string_ptr fileName, const Mode mode);
	    void setMeasureData(Component_vector_ptr wMeasureData,
				Patch_vector_ptr rMeasureData,
				Patch_vector_ptr gMeasureData,
				Patch_vector_ptr bMeasureData);
	};
    };
};


#endif


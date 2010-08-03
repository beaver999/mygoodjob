#ifndef DGCODEFILEH
#define DGCODEFILEH
//C系統文件

//C++系統文件

//其他庫頭文件
#include <ADODB.hpp>
#include <DB.hpp>
//本項目內頭文件
#include <java/lang.h>
#include "excelfile.h"

namespace cms {
    namespace colorformat {


	class DGLutProperty;
	class DGLutFile:public ExcelAccessBase {
	  private:
	    string_vector_ptr makeValues(int n, Component_ptr c);
	    string_vector_ptr makeValues(int n,
					 Component_ptr c, RGB_ptr rgbGamma, RGB_ptr rgbGammaFix);
	    static const std::string & GammaTable;
	    static const std::string & RawData;
	    const Dep::MaxValue & maxValue;

	  public:
	     DGLutFile(const std::string & filename, Mode mode);
	     DGLutFile(const std::string & filename, Mode mode, const Dep::MaxValue & maxValue);


	    void setProperty(const DGLutProperty & property);
	     bptr < DGLutProperty > getProperty();


	    void setRawData(Component_vector_ptr componentVector,
			    RGBGamma_ptr initialRGBGamma, RGBGamma_ptr finalRGBGamma);
	    void setGammaTable(RGB_vector_ptr dglut);
	    Component_vector_ptr getComponentVector();
	    RGB_vector_ptr getGammaTable();

	    /*
	       量測的資料不見得是0~255全量, 但是產生的gamma一定是全部
	       該如何整合兩者?兩種作法
	       1. 內插量測值, 使資料為0~255
	       2. 取有量測到的gamma, 但是缺乏的gamma..就缺乏吧...
	       反正產生DG Code的時候還是可以生出來.

	       選擇方案二, 所以不用刻意去縮減rgbgamma, 由setRawData自己去篩 */
	};

	class DGLutProperty {
	    friend class DGLutFile;
	  private:
	    /*
	       static const std::string Start;
	       static const std::string End;
	       static const std::string Step;
	       static const std::string LowStart;
	       static const std::string LowEnd;
	       static const std::string LowStep;
	       static const std::string HighStart;
	       static const std::string HighEnd;
	       static const std::string HighStep;
	       static const std::string P1P2;
	       static const std::string P1;
	       static const std::string P2;
	       static const std::string RB;
	       static const std::string RBUnder;
	       static const std::string In;
	       static const std::string LUT;
	       static const std::string FRC;
	       static const std::string Out;
	       static const std::string Gamma;
	       static const std::string RGamma;
	       static const std::string GGamma;
	       static const std::string BGamma;
	       static const std::string GammaCurve;
	       static const std::string GByPass;
	       static const std::string BGain;
	       static const std::string BMax;
	       static const std::string Gamma256;
	       static const std::string FRC_NR;
	       static const std::string DimCorrect;

	       static const std::string KeepMaxLumi; */
	    static const std::string On;
	    static const std::string Off;

	    //bptr < cms::lcd::calibrate::LCDCalibrator > c;
	     cms::lcd::calibrate::LCDCalibrator * c;
	     bptr < DGLutFile > d;
	    DGLutFile *d2;
	    void store(DGLutFile & dglut) const;
	     std::map < const std::string, string_ptr) propertyMap;
	    void addProperty(const std::string key, string_ptr value);
	    void addProperty(const std::string key, const std::string value);
	    bool initProperty(bptr < DGLutFile > d);
	    bool initProperty(DGLutFile * d);
	  public:
	    //DGLutProperty(bptr < cms::lcd::calibrate::LCDCalibrator > c);
	     DGLutProperty(cms::lcd::calibrate::LCDCalibrator * c);
	     DGLutProperty(bptr < DGLutFile > d);
	     DGLutProperty(DGLutFile * d);
	    string_ptr getProperty(const std::string key);
	    xyY_ptr getReferenceColor(const Dep::Channel & ch);
	};
    };
};
#endif


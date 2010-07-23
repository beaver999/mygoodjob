#ifndef ANALYZERH
#define ANALYZERH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <vcl.h>

//�����ؤ��Y���
#include <cms/colorformat/excelfile.h>

namespace cms {

    namespace measure {

	class MeterMeasurement;
	/*
	   Intensity Analyer����
	   Analyzer���\�δN�O�qXYZ���R�XIntensity
	 */
	class IntensityAnalyzerIF:public jObject {
	  private:
	    string_ptr comment;
	  public:
	    virtual RGB_ptr getIntensity(RGB_ptr rgb) = 0;
	    virtual XYZ_ptr getCIEXYZ() = 0;
	    virtual XYZ_ptr getCIEXYZOnly(RGB_ptr rgb) = 0;
	    virtual void setupComponent(const Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	    void setReferenceColorComment(const string & comment);
	    string_ptr getReferenceColorComment();
	    virtual void enter() = 0;
	    virtual void beginAnalyze() = 0;
	    virtual void endAnalyze() = 0;
	    virtual void setWaitTimes(int waitTimes) = 0;
	    virtual int getWaitTimes() = 0;
	    virtual xyY_ptr getReferenceColor() = 0;
	    virtual xyY_ptr getPrimaryColor(const Dep::Channel & ch) = 0;
	    virtual RGB_ptr getReferenceRGB() = 0;
	    virtual bptr < MeterMeasurement > getMeterMeasurement() = 0;
	};

	/*
	   �Q��CA-210���ت�Analyzer Mode���R Intensity
	 */
	class CA210IntensityAnalyzer:public IntensityAnalyzerIF {
	  private:
	    Patch_ptr rp, gp, bp, wp;
	  protected:
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	    XYZ_ptr XYZ;
	     bptr < MeterMeasurement > mm;
	    bool dummyMode;
	    void init();
	     cms::measure::meter::DGLutFileMeter * dgc;

	  public:

	    /*
	       �ĥ�CA210��analyze���G���ӷ�
	     */
	     CA210IntensityAnalyzer(bptr < cms::measure::meter::CA210 >
				    ca210, bptr < MeterMeasurement > mm);
	    /*
	       �ѩ�ʥFCA210, �]���O�HMeterMeasurement����Meter�@��analyze�ӷ�,
	       ��ڤW�O���]Meter��DGLutFileMeter, �]�N�O��Ū���ɮפ���component�@��analyze���G
	     */
	     CA210IntensityAnalyzer(bptr < MeterMeasurement > mm);

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void setChannel(int no, string_ptr id);
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	     bptr < MeterMeasurement > getMeterMeasurement();
	};

	/*
	   �Q�ίx�}�B�����XIntensity
	 */
	class MaxMatrixIntensityAnayzer:public IntensityAnalyzerIF {
	    friend class IntensityAnayzer;
	  protected:
	     double2D_ptr inverseMatrix;
	    double2D_ptr targetRatio;
	    double2D_ptr rgbValues;
	     bptr < MeterMeasurement > mm;
	    XYZ_ptr XYZ;
	    XYZ_ptr rXYZ, gXYZ, bXYZ, wXYZ;
	    RGB_ptr referenceRGB;

	  public:
	     MaxMatrixIntensityAnayzer(bptr < MeterMeasurement > mm);
	     MaxMatrixIntensityAnayzer();

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    RGB_ptr getIntensity(XYZ_ptr XYZ);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch,
				XYZ_ptr measureXYZ);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	    bool isInverseMatrixNull();
	     bptr < MeterMeasurement > getMeterMeasurement();
	};

	/*
	   �L��!�h�O!
	 */
	class AdvancedMaxMatrixIntensityAnayzer:public
	    MaxMatrixIntensityAnayzer {
	  protected:
	    XYZ_ptr targetWhite;
	    double2D_ptr xtalkRatio;
	  public:
	     AdvancedMaxMatrixIntensityAnayzer();
	    void setupTarget(XYZ_ptr targetXYZ);
	    RGB_ptr getIntensity(XYZ_ptr XYZ);
	    void enter();
	};

	/*
	   �ΨӦX��CA-210�PMaxMatrix��ؤ�k�Ӥ��RIntensity
	   ��ڤW��X���Ȭ�CA-210��, MaxMatrix����X�ȷ|�t�~�s�b�ɮ�
	 */
	class IntensityAnayzer:public IntensityAnalyzerIF {
	  private:
	    bptr < MaxMatrixIntensityAnayzer > matrix;
	    bptr < CA210IntensityAnalyzer > ca210;
	    bptr < cms::colorformat::SimpleExcelAccess > excel;
	    string_vector_ptr fieldNames;
	    int no;
	    XYZ_ptr XYZ;
	  public:
	     IntensityAnayzer(bptr < MaxMatrixIntensityAnayzer >
			      matrix,
			      bptr < CA210IntensityAnalyzer > ca210);
	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	     bptr < MeterMeasurement > getMeterMeasurement();
	};
    };
};
#endif


#ifndef ALGOH
#define ALGOH
//C�t�Τ��

//C++�t�Τ��
//#include <list>;
#include <vector>;

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		enum Mode {
		    White, Green, Normal
		};
		class Algorithm {
		  private:
		    Mode mode;
		  protected:
		    bool isWhiteMode();
		    bool isGreenMode();
		     Algorithm();
		  public:
		    void setMode(Mode mode);
		};

		class AroundAlgorithm:public Algorithm {
		  public:
		    virtual RGB_vector_ptr getAroundRGB(RGB_ptr centerRGB, double
							step) = 0;

		    virtual RGB_vector_ptr
			getAroundRGB(RGB_ptr centerRGB, double_array delta,
				     double step) = 0;
		};

		class AlgoResult:public jObject {
		  public:
		    RGB_ptr nearestRGB;
		    double_vector_ptr indexes;
		    XYZ_vector_ptr aroundXYZ;
		    int indexInArray;
		    RGB_vector_ptr aroundRGB;
		     AlgoResult(RGB_ptr nearestRGB,
				double_vector_ptr indexes,
				RGB_vector_ptr aroundRGB,
				XYZ_vector_ptr aroundXYZ,
				int indexInArray);
		};

		class NearestAlgorithm:public Algorithm {
		  private:
		    bptr < cms::measure::MeterMeasurement > mm;

		  protected:
		    XYZ_ptr white;

		    virtual double_array getDelta(XYZ_ptr center,
						  XYZ_ptr XYZ) = 0;
		     bptr < cms::measure::MeasureResult >
			getMeasureResult(RGB_vector_ptr aroundRGB);
		    virtual double getIndex(XYZ_ptr center,
					    XYZ_ptr around) = 0;
		  public:

		     double_array getDelta(XYZ_ptr XYZ, RGB_ptr rgb);
		     NearestAlgorithm(XYZ_ptr white,
				      bptr <
				      cms::measure::MeterMeasurement > mm);
		     bptr < AlgoResult > getNearestRGB(XYZ_ptr center,
						       RGB_vector_ptr
						       aroundRGB);
		};

		class MeasuredUtils {
		  public:
		    static double_array getDeltauvPrime(XYZ_ptr center,
							XYZ_ptr XYZ);
		    static bool isFirstNearestXYZInuvPrime(XYZ_ptr
							   targetXYZ,
							   XYZ_vector_ptr
							   aroundXYZ);
		};
	    };
	};
    };
};
#endif


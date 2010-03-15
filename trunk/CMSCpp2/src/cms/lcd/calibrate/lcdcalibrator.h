#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <math/regression.h>
#include "rgbgamma.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class Component:public jObject {
	      public:
		Component(RGB_ptr rgb, RGB_ptr intensity);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ,
			  RGB_ptr gamma);
		RGB_ptr rgb;
		RGB_ptr intensity;
		XYZ_ptr XYZ;
		RGB_ptr gamma;
	    };
	    class ComponentFetcher {
	      private:
		bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		//bptr < cms::measure::MeterMeasurement > mm;
		bool stop;
	      public:
		 ComponentFetcher(bptr <
				  cms::measure::IntensityAnalyzerIF >
				  analyzer);
		Component_vector_ptr fetchComponent(int start, int end,
						    int step);
		void setStop(bool stop);
		static void storeToExcel(const std::string & filename,
					 Component_vector_ptr
					 componentVector);
	    };

	    /*
	       DGLutGenerator������XDG Code�����d�j��
	       1. ��������ComponentFetcher���X��rgb,������componet,�G��
	       2. �ǥ�regression��Xcomponet�P�G�ת����Y
	       1/2��init���X

	       3. �ѥؼ�gamma curve�g�B�J�G��������component
	       4. ��compomenet�����XDG Code, DG Code���X
	       3/4��produce���X

	     */
	    using namespace math;
	    class DGLutGenerator {
	      private:
		bptr < PolynomialRegression > regression;
		Component_vector_ptr componentVector;
		double2D_ptr coefs;
		double c, d;
		double minLuminance, maxLuminance;
		 bptr < math::Interpolation1DLUT > rLut;
		 bptr < math::Interpolation1DLUT > gLut;
		 bptr < math::Interpolation1DLUT > bLut;
	      protected:
		void init();
		double getIntensity(double luminance);
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr
							 normalGammaCurve);
		double_vector_ptr getReverse(double_vector_ptr vec);
	      public:
		 DGLutGenerator(Component_vector_ptr componentVector);
		RGB_vector_ptr produce(double_vector_ptr normalGammaCurve);
		RGB_vector_ptr produce(RGBGamma_ptr normalRGBGammaCurve);
		RGBGamma_ptr getRGBGamma(double_vector_ptr
					 normalGammaCurve);
	    };

	    class IntensityGenerator {

	    };

	    enum BitDepth {
		Unknow = 0, Bit6 = 6, Bit8 = 8, Bit10 = 10, Bit12 = 12
	    };

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
	      private:

		 bool p1p2;
		double p1, p2;
		BitDepth in, lut, out;
		double rbInterpUnder;
		bool gByPass;
		double bIntensityGain;
		bool bMax;
		bool gamma256;
		bool avoidFRCNoise;
		bool rgbgamma;
		double gamma, rgamma, ggamma, bgamma;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		 bptr < DGLutGenerator > generator;
		 bptr < ComponentFetcher > fetcher;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		//RGBGamma_ptr getRGBGamma(double_vector_ptr gammaCurve);
		//std::string dglut;

		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		RGBGamma_ptr finalRGBGamma;

		int start, end, step;
		void set(int start, int end, int step);
		int getn();
		int getEffectiven();
	      public:
		//static double_array getGammaCurve(double gamma, int n);
		static double_vector_ptr getGammaCurveVector
		    (double gamma, int n, int effectiven);

		void setP1P2(double p1, double p2);
		void setRBInterpolation(int under);
		void setGamma(double gamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve,
				   double_vector_ptr bgammaCurve);
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setGamma256(bool gamma256);
		void setAvoidFRCNoise(bool avoid);
		void setBitDepth(const BitDepth & in, const BitDepth & lut,
				 const BitDepth & out);

		 LCDCalibrator(bptr < cms::measure::IntensityAnalyzerIF >
			       analyzer);

		RGB_vector_ptr getDGLut(int start, int end, int step);
		RGB_vector_ptr getDGLut(int step);
		void storeDGLut(const std::string & filename,
				RGB_vector_ptr dglut);
		static BitDepth getBitDepth(int bit);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
	    };


	};
    };
};

#endif


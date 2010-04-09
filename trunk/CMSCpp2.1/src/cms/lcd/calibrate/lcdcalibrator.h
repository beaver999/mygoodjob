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
		bool stop;
		 bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
	      public:
		 ComponentFetcher(bptr <
				  cms::measure::IntensityAnalyzerIF >
				  analyzer,
				  bptr < BitDepthProcessor > bitDepth);
		Component_vector_ptr fetchComponent(int start, int end,
						    int firstStep,
						    int step);
		Component_vector_ptr fetchComponent(int_vector_ptr
						    measureCode);
		static int_vector_ptr getMeasureCode(int start, int end,
						     int firstStep,
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
		//const Dep::MaxValue & in, &out;
		bptr < PolynomialRegression > regression;
		Component_vector_ptr componentVector;
		//double2D_ptr coefs;
		double a0, a1, a2, a3, c, d;
		double minLuminance, maxLuminance;
		 bptr < math::Interpolation1DLUT > rLut;
		 bptr < math::Interpolation1DLUT > gLut;
		 bptr < math::Interpolation1DLUT > bLut;
		 bptr < BitDepthProcessor > bitDepth;
	      protected:
		void init();
		double getIntensity(double luminance);
		double getLuminance(double rIntensity, double gIntensity,
				    double bIntensity);
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr
							 normalGammaCurve);
		double_vector_ptr getReverse(double_vector_ptr vec);
		double getMaximumIntensity();
	      public:
		 DGLutGenerator(Component_vector_ptr componentVector,
				bptr < BitDepthProcessor > bitDepth);
		//RGB_vector_ptr produce(double_vector_ptr normalGammaCurve);
		RGB_vector_ptr produce(RGBGamma_ptr normalRGBGammaCurve);
		RGBGamma_ptr getRGBGamma(double_vector_ptr
					 normalGammaCurve);
	    };

	    class IntensityGenerator {

	    };

	    enum Correct {
		P1P2 = 1, RBInterpolation = 2, None = 3
	    };

	    class MeasureCondition {
	      public:
		const int start;
		const int end;
		const int step;
		const int firstStep;

		const int lowStart;
		const int lowEnd;
		const int lowStep;
		const int highStart;
		const int highEnd;
		const int highStep;
		const bool normalCondition;
		 MeasureCondition(const int start, const int end,
				  const int firstStep, const int step);
		 MeasureCondition(const int lowStart, const int lowEnd,
				  const int lowStep, const int highStart,
				  const int highEnd, const int highStep);
		int_vector_ptr getMeasureCode();
	      private:
		 int_vector_ptr getMeasureCode(const int start,
					       const int end,
					       const int firstStep,
					       const int step);
		int_vector_ptr getMeasureCode(const int lowStart,
					      const int lowEnd,
					      const int lowStep,
					      const int highStart,
					      const int highEnd,
					      const int highStep);
		bool isNoRemainder(int start, int end, int step);
	    };

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
	      private:

		 Correct correct;
		double p1, p2;
		//const Dep::MaxValue & in, &lut, &out;
		double rbInterpUnder;
		bool gByPass;
		double bIntensityGain;
		bool bMax;
		bool keepMaxLuminance;
		//bool gamma256;
		bool avoidFRCNoise;
		bool rgbgamma;
		double gamma, rgamma, ggamma, bgamma;
		bool useGammaCurve;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		 bptr < DGLutGenerator > generator;
		 bptr < ComponentFetcher > fetcher;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer;

		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;

		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;
		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve,
				    double_vector_ptr bgammaCurve);
		bool stop;
	      public:
		static double_vector_ptr getGammaCurveVector
		    (double gamma, int n, int effectiven);

		void setP1P2(double p1, double p2);
		void setRBInterpolation(int under);
		void setNoneDimCorrect();
		void setGamma(double gamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve,
				   double_vector_ptr bgammaCurve);
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setAvoidFRCNoise(bool avoid);
		void setKeepMaxLuminance(bool keepMaxLuminance);

		 LCDCalibrator(bptr < cms::measure::IntensityAnalyzerIF >
			       analyzer,
			       bptr < BitDepthProcessor > bitDepth);

		//RGB_vector_ptr getDGLut(int start, int end, int step);
		RGB_vector_ptr getDGLut(bptr < MeasureCondition >
					measureCondition);
		RGB_vector_ptr getDGLut(int start, int end, int firstStep,
					int step);
		RGB_vector_ptr getDGLut(int firstStep, int step);
		void storeDGLut(const std::string & filename,
				RGB_vector_ptr dglut);
		void setStop(bool stop);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
	    };


	};
    };
};

#endif


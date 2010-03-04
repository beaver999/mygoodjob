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
	    class Composition:public jObject {
	      public:
		Composition(RGB_ptr rgb, RGB_ptr component);
		Composition(RGB_ptr rgb, RGB_ptr component, XYZ_ptr XYZ);
		RGB_ptr rgb;
		RGB_ptr component;
		XYZ_ptr XYZ;
	    };
	    class ComponentFetcher {
	      private:
		bptr < cms::measure::ComponentAnalyzerIF > analyzer;
		//bptr < cms::measure::MeterMeasurement > mm;
		bool stop;
	      public:
		 ComponentFetcher(bptr <
				  cms::measure::ComponentAnalyzerIF >
				  analyzer);
		Composition_vector_ptr fetchComposition(int start, int end,
							int step);
		void setStop(bool stop);
		static void storeToExcel(const std::string & filename,
					 Composition_vector_ptr
					 compositionVector);
	    };

	    /*
	       DGCodeProducer������XDG Code�����d�j��
	       1. ��������ComponentFetcher���X��rgb,������componet,�G��
	       2. �ǥ�regression��Xcomponet�P�G�ת����Y
	       1/2��init���X

	       3. �ѥؼ�gamma curve�g�B�J�G��������component
	       4. ��compomenet�����XDG Code, DG Code���X
	       3/4��produce���X

	     */
	    using namespace math;
	    class DGCodeProducer {
	      private:
		bptr < PolynomialRegression > regression;
		Composition_vector_ptr compositionVector;
		double2D_ptr coefs;
		double c, d;
		double minLuminance, maxLuminance;
		 bptr < math::Interpolation1DLUT > rLut;
		 bptr < math::Interpolation1DLUT > gLut;
		 bptr < math::Interpolation1DLUT > bLut;
	      protected:
		void init();
		double getComponent(double luminance);
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr
							 normalGammaCurve);
	      public:
		 DGCodeProducer(Composition_vector_ptr compositionVector);
		RGB_vector_ptr produce(double_vector_ptr normalGammaCurve);
		RGB_vector_ptr produce(RGBGamma_ptr normalRGBGammaCurve);
	    };

	    enum BitDepth {
		Bit6 = 6, Bit8 = 8, Bit10 = 10, Bit12 = 12
	    };

	    class LCDCalibrator {
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
		//int n;
		double_vector_ptr gammaCurve;
		 bptr < DGCodeProducer > producer;
		 bptr < ComponentFetcher > fetcher;
		 bptr < cms::measure::ComponentAnalyzerIF > analyzer;
		RGBGamma_ptr getRGBGamma(double_vector_ptr gammaCurve);
	      public:
		static double_array getGammaCurve(double gamma, int n);
		static double_vector_ptr getGammaCurveVector(double gamma,
							     int n);

		void setP1P2(double p1, double p2);
		void setRBInterpolation(int under);
		void setGamma(double gamma, int n);
		void setGammaCurve(double_array gammaCurve, int n);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setGamma256(bool gamma256);
		void setAvoidFRCNoise(bool avoid);
		void setBitDepth(const BitDepth & in, const BitDepth & lut,
				 const BitDepth & out);

		RGB_vector_ptr getDGCode(int start, int end, int step);
		 LCDCalibrator(bptr < cms::measure::ComponentAnalyzerIF >
			       analyzer);
	    };


	};
    };
};

#endif


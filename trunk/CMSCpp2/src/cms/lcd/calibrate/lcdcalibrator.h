#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

#define Composition_ptr  bptr < Composition >
#define Composition_vector std::vector < Composition_ptr >
#define Composition_vector_ptr bptr < Composition_vector >

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
		bptr < cms::measure::MeterMeasurement > mm;
	      public:
		ComponentFetcher(bptr < cms::measure::MeterMeasurement >
				 mm,
				 bptr < cms::measure::ComponentAnalyzerIF >
				 analyzer);
		ComponentFetcher(bptr < cms::measure::ComponentAnalyzerIF >
				 analyzer);
		//RGB_vector_ptr fetch(int start, int end, int step);
		Composition_vector_ptr fetchComposition(int start,
							int end, int step);
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
	    class DGCodeProducer {
	      protected:
		void init();
	      public:
		 DGCodeProducer(Composition_vector_ptr compositionVector);
		RGB_vector_ptr produce(double_vector_ptr gammaCurve);

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
		int n;
		double_vector_ptr gammaCurve;

	      public:
		static double_array getGammaCurve(double gamma, int n);
		static double_vector_ptr getGammaCurveVector(double gamma,
							     int n);
		//LCDCalibrator();
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
	    };


	};
    };
};

#endif


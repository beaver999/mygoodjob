#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <math/regression.h>
#include "rgbgamma.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;
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
	    class ComponentFetcher:public cms::util::WindowListener {
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
		double_vector_ptr fetchLuminance(int_vector_ptr
						 measureCode);
		static int_vector_ptr getMeasureCode(int start, int end,
						     int firstStep,
						     int step);

		static void storeToExcel(const std::string & filename,
					 Component_vector_ptr
					 componentVector);
		void windowClosing();
		 bptr < cms::measure::IntensityAnalyzerIF > getAnalyzer();
	    };

	    /*
	       �إ�Component���G�׻PIntensity�����Y��
	     */
	    class ComponentRelationIF {
	      public:
		virtual double getIntensity(double luminance) = 0;
		virtual double getLuminance(double rIntensity,
					    double gIntensity,
					    double bIntensity) = 0;
	    };
	    class ComponentLinearRelation:public ComponentRelationIF {
	      private:
		bptr < PolynomialRegression > regression;
		double a0, a1, a2, a3, c, d;
		void init(double2D_ptr input, double2D_ptr output);
		void init(Component_vector_ptr componentVector);
		Component_vector_ptr componentVector;
	      public:
		 ComponentLinearRelation(double2D_ptr input,
					 double2D_ptr output);
		 ComponentLinearRelation(Component_vector_ptr
					 componentVector);
		double getIntensity(double luminance);
		double getLuminance(double rIntensity, double gIntensity,
				    double bIntensity);
	    };

	    /*
	       �إ�Component���G�׻PIntensity�����Y��
	     */
	    class ComponentPLRelation:public ComponentRelationIF {
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

	    class ComponentLUT {
	      private:
		Component_vector_ptr componentVector;
		bptr < math::Interpolation1DLUT > rLut;
		bptr < math::Interpolation1DLUT > gLut;
		bptr < math::Interpolation1DLUT > bLut;
		bptr < math::Interpolation1DLUT > YLut;
	      protected:
		void init(Component_vector_ptr componentVector);

	      public:
		 ComponentLUT(Component_vector_ptr componentVector);
		double getIntensity(const Dep::Channel & ch, double code);
		double getCode(const Dep::Channel & ch, double intensity);
		RGB_ptr getCode(double luminance);
		double correctIntensityInRange(const Dep::Channel & ch,
					       double intensity);
		double getMaxBIntensity();
	    };
	     Enumeration(KeepMaxLuminance)
	     None, TargetWhite, NativeWhite, NativeWhiteAdvanced,
		EnumerationEnd()

		/*
		   �ھڶq�����G, ���ͻݨD��DG Lut
		 */
	    class DGLutGenerator {
	      private:
		enum Mode {
		    Component, WLumi, RGBLumi,
		};
		KeepMaxLuminance keepMaxLuminance;
	      protected:
		 Mode mode;
		Component_vector_ptr componentVector;
		double_vector_ptr luminanceVector;
		double_vector_ptr rLuminanceVector, gLuminanceVector,
		    bLuminanceVector;
		double minLuminance, maxLuminance;
		 bptr < ComponentLUT > lut;
		 bptr < ComponentRelationIF > componentRelation;
		 bptr < Interpolation1DLUT > wlut;
		double getMaximumIntensity();
		void initComponent(Component_vector_ptr componentVector,
				   bool keepTargetWhiteMaxLuminance);
	      public:
		 DGLutGenerator(Component_vector_ptr componentVector);
		/*DGLutGenerator(Component_vector_ptr componentVector,
		   bool keepMaxLuminance); */
		 DGLutGenerator(Component_vector_ptr componentVector,
				KeepMaxLuminance keepMaxLuminance);
		 DGLutGenerator(double_vector_ptr luminanceVector);
		RGB_ptr getDGCode(double rIntensity, double gIntensity,
				  double bIntensity);
		RGB_ptr getDGCode(double rIntensity, double gIntensity,
				  double bIntensity, bool correctInRange);
		RGB_vector_ptr getCCTDGLut(RGBGamma_ptr
					   normalRGBGammaCurve);
		RGB_vector_ptr getGammaDGLut(double_vector_ptr
					     normalGammaCurve);

		//��gamma curve��rgb intensity
		RGBGamma_ptr getRGBGamma(double_vector_ptr
					 normalGammaCurve);
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr
							 normalGammaCurve);
		double getMaxBIntensity();
	    };

	    /*enum Correct {
	       P1P2 = 1, RBInterpolation = 2, None = 3, DefinedDim = 6
	       }; */
	     Enumeration(Correct)
	     P1P2, RBInterpolation, None, DefinedDim, EnumerationEnd()

		/*
		   �ΨӰO���q��������, ��K���Ѽƶǻ�
		 */
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

		//==============================================================
		// �ե��Ѽ�
		//==============================================================
		 Correct correct;
		int p1, p2;
		int under;
		double dimGamma;
		bool gByPass;
		double bIntensityGain;
		bool bMax;
		bool bMax2;
		int bMax2Begin;
		double bMax2Gamma;
		bool avoidFRCNoise;
		bool rgbIndepGamma;
		double gamma, rgamma, ggamma, bgamma;
		bool useGammaCurve;
		bool averageDimDG;
		bool newMethod;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;
		KeepMaxLuminance keepMaxLuminance;
		int keepMaxLumiOver;
		double keepMaxLumiGamma;
		//==============================================================
		 bptr < ComponentFetcher > fetcher;
		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		double_vector_ptr luminanceVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;


		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve,
				    double_vector_ptr bgammaCurve);
		Component_vector_ptr fetchComponentVector(bptr <
							  MeasureCondition
							  >
							  measureCondition);
		double_vector_ptr fetchLuminanceVector(bptr <
						       MeasureCondition >
						       measureCondition);
	      public:
		static double_vector_ptr getGammaCurveVector
		    (double gamma, int n, int effectiven);

		void setP1P2(int p1, int p2);
		void setRBInterpolation(int under);
		void setNonDimCorrect();
		void setDefinedDim(int under, double gamma,
				   bool averageDimDG);
		void setGamma(double gamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve,
				   double_vector_ptr bgammaCurve);
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setBMax2(bool bMax2, int begin, double gamma);
		void setAvoidFRCNoise(bool avoid);
		void setKeepMaxLuminance(KeepMaxLuminance
					 keepMaxLuminance);
		void setKeepMaxLuminanceNativeWhiteAdvanced(int over,
							    double gamma);
		void setNewMethod(bool enable);

		 LCDCalibrator(bptr <
			       cms::lcd::calibrate::ComponentFetcher >
			       fetcher,
			       bptr < BitDepthProcessor > bitDepth);

		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition >
					   measureCondition);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition >
					     measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename,
				   RGB_vector_ptr dglut);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
	    };


	};
    };
};

#endif



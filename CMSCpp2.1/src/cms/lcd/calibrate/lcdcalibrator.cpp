#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "rgbvectorop.h";

namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace cms::measure;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::colorformat;
	    using namespace cms::util;
	    using namespace cms::lcd::calibrate;
	    //==================================================================
	    // Component
	    //==================================================================
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity):rgb(rgb),
		intensity(intensity) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ):rgb(rgb),
		intensity(intensity), XYZ(XYZ) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ, RGB_ptr gamma):rgb(rgb),
		intensity(intensity), XYZ(XYZ), gamma(gamma) {

	    };
	    //==================================================================


	    //==================================================================
	    // ComponentFetcher
	    //==================================================================
	  ComponentFetcher::ComponentFetcher(bptr < IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):analyzer
		(analyzer), bitDepth(bitDepth)
	    {
	    };

	    Component_vector_ptr ComponentFetcher::
		fetchComponent(int start, int end, int firstStep,
			       int step) {
		MeasureCondition measureCondition(start, end, firstStep,
						  step);
		int_vector_ptr measurecode =
		    measureCondition.getMeasureCode();
		return fetchComponent(measurecode);
	    };


	    Component_vector_ptr ComponentFetcher::
		fetchComponent(int_vector_ptr measureCode) {
		RGB_vector_ptr rgbMeasureCode(new RGB_vector());
		foreach(const int &x, *measureCode) {
		    RGB_ptr rgb(new RGBColor(x, x, x));
		    rgbMeasureCode->push_back(rgb);
		}
		return fetchComponent(rgbMeasureCode);
	    };

	    Component_vector_ptr ComponentFetcher::
		fetchComponent(RGB_vector_ptr rgbMeasureCode) {
		Component_vector_ptr result(new Component_vector());

		bool waitingStable = true;
		int waitTimes = analyzer->getWaitTimes();
		analyzer->setWaitTimes(10000);

		analyzer->beginAnalyze();
		foreach(const RGB_ptr & rgb, *rgbMeasureCode) {
		    RGB_ptr intensity = analyzer->getIntensity(rgb);
		    XYZ_ptr XYZ = analyzer->getCIEXYZ();
		    Component_ptr component(new Component(rgb, intensity,
							  XYZ));
		    result->push_back(component);

		    if (true == waitingStable) {
			waitingStable = false;
			analyzer->setWaitTimes(waitTimes);
		    }

		    if (true == stop) {
			stop = false;
			analyzer->endAnalyze();
			return Component_vector_ptr((Component_vector *)
						    null);
		    }
		}
		analyzer->endAnalyze();
		return result;
	    };

	    Component_vector_ptr ComponentFetcher::fetchComponent(bptr <
								  MeasureCondition
								  >
								  measureCondition)
	    {
		if (measureCondition->isRGBType()) {
		    return fetchComponent(measureCondition->
					  getRGBMeasureCode());
		} else {
		    return fetchComponent(measureCondition->
					  getMeasureCode());
		}
	    };

	    double_vector_ptr ComponentFetcher::
		fetchLuminance(int_vector_ptr measureCode) {
		double_vector_ptr result(new double_vector());

		bool waitingStable = true;
		int waitTimes = analyzer->getWaitTimes();
		analyzer->setWaitTimes(10000);

		analyzer->beginAnalyze();
		foreach(const int &x, *measureCode) {
		    RGB_ptr rgb(new RGBColor(x, x, x));
		    XYZ_ptr XYZ = analyzer->getCIEXYZOnly(rgb);
		    result->push_back(XYZ->Y);

		    if (true == waitingStable) {
			waitingStable = false;
			analyzer->setWaitTimes(waitTimes);
		    }

		    if (true == stop) {
			stop = false;
			analyzer->endAnalyze();
			return double_vector_ptr((double_vector *)
						 null);
		    }
		}
		analyzer->endAnalyze();
		return result;
	    };

	    void ComponentFetcher::storeToExcel(const string & filename,
						Component_vector_ptr
						componentVector) {

		//int n = componentVector->size();
		Util::deleteExist(filename);
		DGLutFile dglut(filename, Create);
		dglut.setRawData(componentVector, nil_RGBGamma,
				 nil_RGBGamma);
	    };
	    void ComponentFetcher::windowClosing() {
		//this->setStop(true);
		stop = true;
	    };
	    bptr < IntensityAnalyzerIF > ComponentFetcher::getAnalyzer() {
		return analyzer;
	    };
	    //==================================================================

	    //==================================================================
	    // ComponentLinearRelation
	    //==================================================================
	    void ComponentLinearRelation::init(double2D_ptr input,
					       double2D_ptr output) {
		//==============================================================
		// �p��a/c/d
		//==============================================================
		regression = bptr < PolynomialRegression >
		    (new PolynomialRegression(input, output,
					      Polynomial::COEF_3::BY_3C));
		regression->regress();
		const double *coefs = (*regression->getCoefs())[0];
		a1 = coefs[1];
		a2 = coefs[2];
		a3 = coefs[3];
		a0 = coefs[0];
		c = 1 / (a1 + a2 + a3);
		d = -a0 / (a1 + a2 + a3);
		//==============================================================
	    };

	    void ComponentLinearRelation::
		init(Component_vector_ptr componentVector) {
		//==============================================================
		// �إߦ^�k���
		//==============================================================
		int size = componentVector->size();
		double2D_ptr input(new double2D(size, 3));
		double2D_ptr output(new double2D(size, 1));

		for (int x = 0; x != size; x++) {
		    Component_ptr component = (*componentVector)[x];
		    double Y = component->XYZ->Y;
		    RGB_ptr intensity = component->intensity;

		    (*input)[x][0] = intensity->R;
		    (*input)[x][1] = intensity->G;
		    (*input)[x][2] = intensity->B;
		    (*output)[x][0] = Y;
		}
		//==============================================================

		//==============================================================
		// �p��a/c/d
		//==============================================================
		init(input, output);
		//==============================================================                
	    };

	    ComponentLinearRelation::
		ComponentLinearRelation(double2D_ptr input,
					double2D_ptr output) {
		init(input, output);

	    };
	  ComponentLinearRelation::ComponentLinearRelation(Component_vector_ptr componentVector):componentVector(componentVector)
	    {
		init(componentVector);
	    };
	    double ComponentLinearRelation::getIntensity(double luminance) {
		return c * luminance + d;
	    };
	    double ComponentLinearRelation::
		getLuminance(double rIntensity, double gIntensity,
			     double bIntensity) {
		return a0 + rIntensity * a1 + gIntensity * a2 +
		    bIntensity * a3;
	    };
	    //==================================================================

	    //==================================================================
	    // ComponentLUT
	    //==================================================================
	    void ComponentLUT::init(Component_vector_ptr componentVector) {
		//==============================================================
		// �إߦ^�k���
		//==============================================================
		int size = componentVector->size();
		double_vector_ptr keys(new double_vector(size));
		double_vector_ptr rValues(new double_vector(size));
		double_vector_ptr gValues(new double_vector(size));
		double_vector_ptr bValues(new double_vector(size));
		double_vector_ptr YValues(new double_vector(size));
		double_array values(new double[3]);

		//int index = 0;
		//for (int x = size - 1; x >= 0; x--) {
		for (int x = 0; x != size; x++) {
		    Component_ptr component = (*componentVector)[x];
		    //double Y = component->XYZ->Y;
		    RGB_ptr intensity = component->intensity;

		    RGB_ptr code = component->rgb;
		    code->getValues(values, MaxValue::Double255);

		    (*keys)[x] = values[0];
		    (*rValues)[x] = intensity->R;
		    (*gValues)[x] = intensity->G;
		    (*bValues)[x] = intensity->B;
		    (*YValues)[x] = component->XYZ->Y;
		    //index++;
		}
		//==============================================================

		//==============================================================
		// ����RGB LUT
		//==============================================================
		keys = DoubleArray::getReverse(keys);
		rValues = DoubleArray::getReverse(rValues);
		gValues = DoubleArray::getReverse(gValues);
		bValues = DoubleArray::getReverse(bValues);
		YValues = DoubleArray::getReverse(YValues);
		rLut =
		    bptr < Interpolation1DLUT >
		    (new Interpolation1DLUT(keys, rValues));
		gLut =
		    bptr < Interpolation1DLUT >
		    (new Interpolation1DLUT(keys, gValues));
		bLut =
		    bptr < Interpolation1DLUT >
		    (new Interpolation1DLUT(keys, bValues, Ripple));
		YLut =
		    bptr < Interpolation1DLUT >
		    (new Interpolation1DLUT(keys, YValues));
		//==============================================================                
	    };
	  ComponentLUT::ComponentLUT(Component_vector_ptr componentVector):componentVector(componentVector)
	    {
		init(componentVector);
	    };
	    double ComponentLUT::getIntensity(const Dep::Channel & ch,
					      double code) {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->getValue(code);
		case ChannelIndex::G:
		    return gLut->getValue(code);
		case ChannelIndex::B:
		    return bLut->getValue(code);
		default:
		    throw IllegalArgumentException("Unsupported Channel:" +
						   *ch.toString());
		}
	    };
	    double ComponentLUT::getCode(const Dep::Channel & ch,
					 double intensity) {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->getKey(intensity);
		case ChannelIndex::G:
		    return gLut->getKey(intensity);
		case ChannelIndex::B:
		    return bLut->getKey(intensity);
		default:
		    throw IllegalArgumentException("Unsupported Channel:" +
						   *ch.toString());
		}
	    };
	    RGB_ptr ComponentLUT::getCode(double luminance) {
		luminance = YLut->correctValueInRange(luminance);
		double key = YLut->getKey(luminance);
		RGB_ptr rgb(new RGBColor(key, key, key));
		return rgb;
	    };
	    double ComponentLUT::correctIntensityInRange(const Dep::
							 Channel & ch,
							 double intensity)
	    {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->correctValueInRange(intensity);
		case ChannelIndex::G:
		    return gLut->correctValueInRange(intensity);
		case ChannelIndex::B:
		    return bLut->correctValueInRange(intensity);
		default:
		    throw IllegalArgumentException("Unsupported Channel:" +
						   *ch.toString());
		}
	    };

	    double ComponentLUT::getMaxBIntensity() {
		return bLut->getMaxValue();
	    };
	    //==================================================================

	    //==================================================================
	    // DGLutGenerator
	    //==================================================================
	    /*
	       �N���W�ƪ�gamma curve, �ഫ�����諸�G��curve
	     */
	    double_vector_ptr DGLutGenerator::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve)
	    {
		int size = normalGammaCurve->size();
		double_vector_ptr luminanceGammaCurve(new
						      double_vector(size));
		double differ = maxLuminance - minLuminance;
		for (int x = 0; x != size; x++) {
		    double v =
			differ * (*normalGammaCurve)[x] + minLuminance;
		    (*luminanceGammaCurve)[x] = v;
		}
		return luminanceGammaCurve;
	    };
	    /*
	       �p��i�Ϊ��̤jintensity
	     */
	    double DGLutGenerator::getMaximumIntensity() {
		int maxindex = 0;
		//���̫G�q���I
		Component_ptr maxcomponent = (*componentVector)[maxindex];
		RGB_ptr maxintensity = maxcomponent->intensity;
		//�̤p�Ȫ�channel
		const Channel & minchannel = maxintensity->getMinChannel();
		//�H�̤p�ȱochannel��intensity���̤j��intensity
		double maxvalue = maxintensity->getValue(minchannel);
		return maxvalue;
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
	    void DGLutGenerator::
		initComponent(Component_vector_ptr componentVector,
			      bool keepTargetWhiteMaxLuminance) {
		//==============================================================
		// �p��a/c/d
		//==============================================================
		componentRelation =
		    bptr < ComponentRelationIF >
		    (new ComponentLinearRelation(componentVector));
		//==============================================================

		//==============================================================
		// ����RGB LUT
		//==============================================================
		lut = bptr < ComponentLUT >
		    (new ComponentLUT(componentVector));
		//==============================================================

		double maxintensity = Math::roundTo(getMaximumIntensity());
		if (!keepTargetWhiteMaxLuminance) {
		    maxintensity =
			(maxintensity > 100) ? 100 : maxintensity;
		}

		maxLuminance =
		    componentRelation->getLuminance(maxintensity,
						    maxintensity,
						    maxintensity);
		int size = componentVector->size();
		minLuminance = (*componentVector)[size - 1]->XYZ->Y;
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector):componentVector
		(componentVector), mode(Component),
		keepMaxLuminance(KeepMaxLuminance::TargetWhite) {
		initComponent(componentVector, keepMaxLuminance ==
			      KeepMaxLuminance::TargetWhite);
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector, KeepMaxLuminance keepMaxLuminance):componentVector
		(componentVector),
		mode(Component), keepMaxLuminance(keepMaxLuminance) {
		initComponent(componentVector,
			      keepMaxLuminance ==
			      KeepMaxLuminance::TargetWhite);
	    };
	  DGLutGenerator::DGLutGenerator(double_vector_ptr luminanceVector):luminanceVector(luminanceVector), mode(WLumi)
	    {
		maxLuminance = (*luminanceVector)[0];
		int size = luminanceVector->size();
		minLuminance = (*luminanceVector)[size - 1];
		double_vector_ptr key(new double_vector(size));
		for (int x = 0; x != size; x++) {
		    (*key)[x] = size - x - 1;
		}
		key = DoubleArray::getReverse(key);
		double_vector_ptr value =
		    DoubleArray::getReverse(luminanceVector);

		wlut =
		    bptr < Interpolation1DLUT >
		    (new Interpolation1DLUT(key, value));
	    };

	    RGB_ptr DGLutGenerator::getDGCode(double rIntensity,
					      double gIntensity,
					      double bIntensity,
					      bool correctInRange) {
		if (true == correctInRange) {
		    rIntensity =
			lut->correctIntensityInRange(Channel::R,
						     rIntensity);
		    gIntensity =
			lut->correctIntensityInRange(Channel::G,
						     gIntensity);
		    bIntensity =
			lut->correctIntensityInRange(Channel::B,
						     bIntensity);
		}

		double r = lut->getCode(Channel::R, rIntensity);
		double g = lut->getCode(Channel::G, gIntensity);
		double b = lut->getCode(Channel::B, bIntensity);

		RGB_ptr rgb(new RGBColor(r, g, b));
		return rgb;
	    };

	    RGB_ptr DGLutGenerator::
		getDGCode(double rIntensity, double gIntensity,
			  double bIntensity) {
		return getDGCode(rIntensity, gIntensity, bIntensity, true);
	    }

	    RGB_vector_ptr DGLutGenerator::
		getCCTDGLut(RGBGamma_ptr rgbIntensityCurve) {
		if (mode == WLumi || mode == RGBLumi) {
		    throw
			UnsupportedOperationException
			("DGLutGenerator is in luminanceMode.");
		}

		using namespace Dep;
		double_vector_ptr rIntensityCurve = rgbIntensityCurve->r;
		double_vector_ptr gIntensityCurve = rgbIntensityCurve->g;
		double_vector_ptr bIntensityCurve = rgbIntensityCurve->b;

		int size = rIntensityCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));
		//�Ncode 0�j��]�w��0
		(*dglut)[0] = RGB_ptr(new RGBColor(0, 0, 0));

		for (int x = size - 1; x != 0; x--) {
		    RGB_ptr rgb = getDGCode((*rIntensityCurve)[x],
					    (*gIntensityCurve)[x],
					    (*bIntensityCurve)[x]);
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };

	    RGB_vector_ptr DGLutGenerator::getGammaDGLut(double_vector_ptr
							 normalGammaCurve)
	    {
		double_vector_ptr luminanceGammaCurve =
		    getLuminanceGammaCurve(normalGammaCurve);
		int size = luminanceGammaCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));

		//for (int x = 0; x != size; x++) {
		for (int x = size - 1; x != -1; x--) {
		    double luminance = (*luminanceGammaCurve)[x];
		    RGB_ptr rgb;
		    switch (mode) {
		    case RGBLumi:
			throw java::lang::UnsupportedOperationException();
		    case Component:
			rgb = lut->getCode(luminance);
			break;
		    case WLumi:
			luminance = wlut->correctValueInRange(luminance);
			double key = wlut->getKey(luminance);
			rgb = RGB_ptr(new RGBColor(key, key, key));
			break;

		    }
		    (*dglut)[x] = rgb;
		}

		return dglut;
	    };

	    /*
	       normalGammaCurve��LuminanceGammaCurve�A��intensity
	     */
	    RGBGamma_ptr DGLutGenerator::
		getRGBGamma(double_vector_ptr normalGammaCurve) {
		//gamma curve��luminance curve
		double_vector_ptr luminanceGammaCurve =
		    getLuminanceGammaCurve(normalGammaCurve);
		STORE_DOUBLE_VECTOR("0_lumicurve.xls",
				    luminanceGammaCurve);
		int size = luminanceGammaCurve->size();
		double_vector_ptr rIntenisty(new double_vector(size));
		double_vector_ptr gIntenisty(new double_vector(size));
		double_vector_ptr bIntenisty(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    double luminance = (*luminanceGammaCurve)[x];
		    //luminance curve��intensity
		    double intensity =
			componentRelation->getIntensity(luminance);
		    (*rIntenisty)[x] = intensity;
		    (*gIntenisty)[x] = intensity;
		    (*bIntenisty)[x] = intensity;
		}

		RGBGamma_ptr rgbgamma(new
				      RGBGamma(rIntenisty, gIntenisty,
					       bIntenisty, 100,
					       Intensity));

		return rgbgamma;
	    };
	    double DGLutGenerator::getMaxBIntensity() {
		return lut->getMaxBIntensity();
	    };
	    //==================================================================

	    //==================================================================
	  MeasureCondition::MeasureCondition(const int start, const int end, const int firstStep, const int step):start(start),
		end(end), firstStep(firstStep), step(step), lowStart(0),
		lowEnd(0), lowStep(0), highStart(0), highEnd(0),
		highStep(0), type(Normal) {

	    };
	    MeasureCondition::MeasureCondition(const int lowStart,
					       const int lowEnd,
					       const int lowStep,
					       const int highStart,
					       const int highEnd, const int
					       highStep):start(0), end(0),
		firstStep(0), step(0), lowStart(lowStart), lowEnd(lowEnd),
		lowStep(lowStep), highStart(highStart), highEnd(highEnd),
		highStep(highStep), type(Extend) {
	    };
	  MeasureCondition::MeasureCondition(int_vector_ptr measureCode):start(0), end(0),
		firstStep(0), step(0), lowStart(0), lowEnd(0), lowStep(0),
		highStart(0), highEnd(0), highStep(0), type(Plain) {
		this->measureCode = measureCode;
	    };
	  MeasureCondition::MeasureCondition(RGB_vector_ptr rgbMeasureCode):start(0), end(0),
		firstStep(0), step(0), lowStart(0), lowEnd(0), lowStep(0),
		highStart(0), highEnd(0), highStep(0), type(RGB) {
		this->rgbMeasureCode = rgbMeasureCode;
	    };
	    int_vector_ptr MeasureCondition::getMeasureCode() {
		switch (type) {
		case Normal:
		    return getMeasureCode(start, end, firstStep, step);
		case Extend:
		    return getMeasureCode(lowStart, lowEnd, lowStep,
					  highStart, highEnd, highStep);
		case Plain:
		    return measureCode;
		case RGB:
		    throw new IllegalStateException();
		}

		/*if (normalCondition) {
		   return getMeasureCode(start, end, firstStep, step);
		   } else {
		   return getMeasureCode(lowStart, lowEnd, lowStep,
		   highStart, highEnd, highStep);
		   } */
	    };
	    RGB_vector_ptr MeasureCondition::getRGBMeasureCode() {
		if (isRGBType()) {
		    return rgbMeasureCode;
		} else {
		    throw new IllegalStateException();
		}
	    };
	    bool MeasureCondition::isRGBType() {
		return type == RGB;
	    };
	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int start, const int end,
			       const int firstStep, const int step) {
		int_vector_ptr measureCode(new int_vector());
		int measureStep = firstStep;
		bool first = true;

		for (int x = start; x >= end; x -= measureStep) {
		    if (x != start && true == first) {
			first = false;
			measureStep = step;
		    }
		    measureCode->push_back(x);
		}
		if ((*measureCode)[measureCode->size() - 1] != end) {
		    measureCode->push_back(end);
		}

		return measureCode;
	    };
	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int lowStart, const int lowEnd,
			       const int lowStep, const int highStart,
			       const int highEnd, const int highStep) {
		int_vector_ptr measureCode(new int_vector());

		int start = isNoRemainder(highStart, highEnd,
					  highStep) ? highStart : highStart
		    + 1;

		for (int x = start; x >= highEnd; x -= highStep) {
		    int code = x > 255 ? 255 : x;
		    measureCode->push_back(code);
		}
		start =
		    (lowStart == highEnd) ? (lowStart - lowStep) : highEnd;
		for (int x = start; x >= lowEnd; x -= lowStep) {
		    measureCode->push_back(x);
		}

		return measureCode;
	    };

	    bool MeasureCondition::isNoRemainder(int start, int end,
						 int step) {
		double dividend = ((double) start - end) / step;
		bool noremainder =
		    dividend == static_cast < int >(dividend);
		return noremainder;
	    }
	    //==================================================================


	    //==================================================================
	    // LCDCalibrator
	    //==================================================================

	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double gamma, int n,
						   int effectiven) {
		double_vector_ptr result(new double_vector(n));
		for (int x = 0; x < effectiven; x++) {
		    double normal =
			static_cast < double >(x) / (effectiven - 1);
		    double v = Math::pow(normal, gamma);
		    (*result)[x] = v;
		};
		for (int x = effectiven; x < n; x++) {
		    (*result)[x] = 1;
		}
		return result;
	    };
	    void LCDCalibrator::setP1P2(int p1, int p2) {
		this->p1 = p1;
		this->p2 = p2;
		this->correct = Correct::P1P2;
	    };
	    void LCDCalibrator::setRBInterpolation(int under) {
		this->correct = Correct::RBInterpolation;
		this->under = under;
	    };
	    void LCDCalibrator::setNonDimCorrect() {
		this->correct = Correct::None;
	    };

	    /*void LCDCalibrator::setDefinedDim(int under, bool averageDimDG) {
	       this->correct = Correct::DefinedDim;
	       this->under = under;
	       this->averageDimDG = averageDimDG;
	       }; */
	    void LCDCalibrator::setDefinedDim(int under, double gamma,
					      bool averageDimDG) {
		this->correct = Correct::DefinedDim;
		this->under = under;
		this->dimGamma = gamma;
		this->averageDimDG = averageDimDG;
	    } void LCDCalibrator::setGamma(double gamma) {
		this->gamma = gamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		setGammaCurve0(getGammaCurveVector(gamma, n, effectiven));
		useGammaCurve = false;
		rgbIndepGamma = false;
	    };
	    void LCDCalibrator::setGamma(double rgamma, double ggamma,
					 double bgamma) {
		this->rgamma = rgamma;
		this->ggamma = ggamma;
		this->bgamma = bgamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		setGammaCurve0(getGammaCurveVector
			       (rgamma, n, effectiven),
			       getGammaCurveVector(ggamma, n,
						   effectiven),
			       getGammaCurveVector(bgamma, n, effectiven));
		useGammaCurve = false;
		rgbIndepGamma = true;
	    };
	    void LCDCalibrator::
		setGammaCurve0(double_vector_ptr gammaCurve) {
		this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve0(double_vector_ptr rgammaCurve,
			       double_vector_ptr ggammaCurve,
			       double_vector_ptr bgammaCurve) {
		this->rgammaCurve = rgammaCurve;
		this->ggammaCurve = ggammaCurve;
		this->bgammaCurve = bgammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr gammaCurve) {
		setGammaCurve0(gammaCurve);
		useGammaCurve = true;
		rgbIndepGamma = false;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr rgammaCurve,
			      double_vector_ptr ggammaCurve,
			      double_vector_ptr bgammaCurve) {
		setGammaCurve0(rgammaCurve, ggammaCurve, bgammaCurve);
		useGammaCurve = true;
		rgbIndepGamma = true;
	    };
	    void LCDCalibrator::setGByPass(bool byPass) {
		this->gByPass = byPass;
	    };
	    void LCDCalibrator::setBIntensityGain(double gain) {
		this->bIntensityGain = gain;
	    };
	    void LCDCalibrator::setBMax(bool bMax) {
		this->bMax = bMax;
	    };
	    void LCDCalibrator::setBMax2(bool bMax2, int begin,
					 double gamma) {
		this->bMax2 = bMax2;
		bMax2Begin = begin;
		bMax2Gamma = gamma;
	    };
	    void LCDCalibrator::setAvoidFRCNoise(bool avoid) {
		this->avoidFRCNoise = avoid;
	    };
	    void LCDCalibrator::
		setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance) {
		if (keepMaxLuminance ==
		    KeepMaxLuminance::NativeWhiteAdvanced) {
		    throw
			UnsupportedOperationException
			("Please call setKeepMaxLuminanceNativeWhiteAdvanced().");
		}
		this->keepMaxLuminance = keepMaxLuminance;
	    };
	    void LCDCalibrator::
		setKeepMaxLuminanceNativeWhiteAdvanced(int over,
						       double gamma) {
		this->keepMaxLuminance =
		    KeepMaxLuminance::NativeWhiteAdvanced;
		this->keepMaxLumiOver = over;
		this->keepMaxLumiGamma = gamma;
	    };
	    void LCDCalibrator::setNewMethod(bool enable) {
		this->newMethod = enable;
	    };
	  LCDCalibrator::LCDCalibrator(bptr < ComponentFetcher > fetcher, bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {
		rgbIndepGamma = false;
		useGammaCurve = false;
		bIntensityGain = 1;
		under = 0;
		p1 = p2 = 0;
		gamma = rgamma = ggamma = bgamma = -1;
		this->fetcher = fetcher;
		averageDimDG = false;
		newMethod = false;
		bMax = bMax2 = false;
		bTargetIntensity = -1;
	    };

	    Component_vector_ptr LCDCalibrator::
		fetchComponentVector(bptr < MeasureCondition >
				     measureCondition) {
		this->measureCondition = measureCondition;
		//�q��start->end�o�쪺coponent/Y
		int_vector_ptr measurecode =
		    measureCondition->getMeasureCode();
		componentVector = fetcher->fetchComponent(measurecode);

		if (componentVector == null
		    || measurecode->size() != componentVector->size()) {
		    return Component_vector_ptr((Component_vector *)
						null);
		} else {
		    return componentVector;
		}
	    };

	    double_vector_ptr LCDCalibrator::
		fetchLuminanceVector(bptr < MeasureCondition >
				     measureCondition) {
		this->measureCondition = measureCondition;
		//�q��start->end�o�쪺coponent/Y
		int_vector_ptr measurecode =
		    measureCondition->getMeasureCode();
		luminanceVector = fetcher->fetchLuminance(measurecode);

		if (luminanceVector == null
		    || measurecode->size() != luminanceVector->size()) {
		    return double_vector_ptr((double_vector *)
					     null);
		} else {
		    return luminanceVector;
		}
	    };

	    /*
	       CCT + Gamma
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr <
						      MeasureCondition
						      > measureCondition) {

		if (null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		Component_vector_ptr componentVector =
		    fetchComponentVector(measureCondition);
		if (componentVector == null) {
		    return RGB_vector_ptr((RGB_vector *) null);
		}

		STORE_COMPONENT("o_fetch.xls", componentVector);
		DGLutGenerator generator(componentVector,
					 keepMaxLuminance);
		STORE_DOUBLE_VECTOR("0_gammacurve.xls", gammaCurve);
		MaxValue quantizationBit = bitDepth->getLutMaxValue();

		if (true == newMethod) {
		    //==========================================================
		    // �s��k
		    //==========================================================
		    bptr < IntensityAnalyzerIF > analyzer =
			fetcher->getAnalyzer();
		    AdvancedDGLutGenerator
			advgenerator(componentVector, analyzer);
		    //analyzer�Y�S���]�w�Ltarget color, �|�Ϧ��B�J����
		    XYZ_ptr targetWhite =
			analyzer->getReferenceColor()->toXYZ();
		    double_vector_ptr luminanceGammaCurve =
			generator.getLuminanceGammaCurve(gammaCurve);
		    STORE_DOUBLE_VECTOR("1_lumigammacurve.xls",
					luminanceGammaCurve);
		    double dimgammaParameter = 3.5;
		    int underParameter = 50;
		    double brightgammaParameter = 2.2;
		    int overParameter = 200;

		    if (correct == Correct::DefinedDim) {
			dimgammaParameter = dimGamma;
			underParameter = under;
		    }

		    if (keepMaxLuminance ==
			KeepMaxLuminance::NativeWhiteAdvanced) {
			brightgammaParameter = keepMaxLumiGamma;
			overParameter = keepMaxLumiOver;
		    } else {
		    }

		    if (this->bTargetIntensity != -1) {
			advgenerator.setBTargetIntensity(bTargetIntensity);
		    }

		    dglut =
			advgenerator.produce(targetWhite,
					     luminanceGammaCurve,
					     underParameter,
					     overParameter,
					     dimgammaParameter,
					     brightgammaParameter);
		    STORE_RGBVECTOR("3_dgcode.xls", dglut);
		    //==========================================================
		} else {
		    //==========================================================
		    // �Ѥ�k
		    //==========================================================
		    RGBGamma_ptr rgbgamma =
			generator.getRGBGamma(gammaCurve);
		    initialRGBGamma = rgbgamma->clone();

		    STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);


		    /* TODO : bIntensityGain�n�T�{ */
		    if (bIntensityGain != 1.0) {
			//���s���ͥؼ�gamma curve
			bptr < BIntensityGainOp >
			    bgain(new
				  BIntensityGainOp(bIntensityGain, 236,
						   bitDepth));

			RGBGammaOp gammaop;
			gammaop.setSource(rgbgamma);
			gammaop.addOp(bgain);
			rgbgamma = gammaop.createInstance();
			STORE_RGBGAMMA("2_rgbgamma_bGain.xls", rgbgamma);
		    }
		    //�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
		    dglut = generator.getCCTDGLut(rgbgamma);
		    STORE_RGBVECTOR("3_dgcode.xls", dglut);
		    //==============================================================
		    //�Ĥ@���q�ƳB�z
		    //==============================================================
		    //�q��
		    //MaxValue quantizationBit = bitDepth->getLutMaxValue();
		    RGBVector::quantization(dglut, quantizationBit);
		    //==============================================================

		    if (correct == Correct::P1P2) {
			//==========================================================
			//p1p2�Ĥ@���q, ��gamma���վ�
			//==========================================================
			bptr < P1P2GammaOp >
			    p1p2(new P1P2GammaOp(p1, p2, dglut));
			RGBGammaOp gammaop;
			gammaop.setSource(rgbgamma);
			gammaop.addOp(p1p2);

			//���ͭץ��᪺gamma2(�Y�S��p1p2,�h����ʤ���)
			rgbgamma = gammaop.createInstance();
			STORE_RGBGAMMA("4_rgbgamma_p1p2.xls", rgbgamma);

			//�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
			dglut = generator.getCCTDGLut(rgbgamma);
			//�q��
			STORE_RGBVECTOR("4.9_dgcode_p1p2g.xls", dglut);
			RGBVector::quantization(dglut, quantizationBit);
			STORE_RGBVECTOR("5_dgcode_p1p2g.xls", dglut);
			//==========================================================


			//==========================================================
			//p1p2�ĤG���q, ��dg code�վ�
			//==========================================================
			DGLutOp dgop;
			dgop.setSource(dglut);
			bptr < DGLutOp >
			    op(new P1P2DGOp(p1, p2, quantizationBit));
			dgop.addOp(op);
			dglut = dgop.createInstance();
			//�q��
			STORE_RGBVECTOR("6_dgcode_p1p2dg.xls", dglut);
			//==========================================================
		    }		/*else if (correct == Correct::DefinedDim) {
				   // DimDGLutGenerator
				   // in: target white , gamma(Y)
				   // out: DG Code
				   bptr < IntensityAnalyzerIF > analyzer =
				   fetcher->getAnalyzer();
				   DimDGLutGenerator dimgenerator(componentVector,
				   analyzer);
				   //analyzer�Y�S���]�w�Ltarget color, �|�Ϧ��B�J����
				   XYZ_ptr targetWhite =
				   analyzer->getReferenceColor()->toXYZ();
				   double_vector_ptr luminanceGammaCurve =
				   generator.getLuminanceGammaCurve(gammaCurve);

				   RGB_vector_ptr dimdglut =
				   dimgenerator.produce(targetWhite,
				   luminanceGammaCurve,
				   under, dimGamma);
				   int size = dimdglut->size();
				   //======================================================
				   // �� Dim DG�@����
				   //======================================================
				   if (true == averageDimDG) {
				   for (int x = 1; x < size - 1; x++) {
				   //(*dglut)[x] = (*dimdglut)[x];
				   RGB_ptr rgb0 = (*dimdglut)[x - 1];
				   RGB_ptr rgb1 = (*dimdglut)[x];
				   RGB_ptr rgb2 = (*dimdglut)[x + 1];
				   rgb1->R = (rgb0->R + rgb2->R) / 2.;
				   rgb1->G = (rgb0->G + rgb2->G) / 2.;
				   rgb1->B = (rgb0->B + rgb2->B) / 2.;
				   }
				   }
				   //======================================================
				   for (int x = 0; x < size; x++) {
				   (*dglut)[x] = (*dimdglut)[x];
				   }
				   RGBVector::quantization(dglut, quantizationBit);
				   } */
		    finalRGBGamma = rgbgamma;
		    //==========================================================
		}

		//==============================================================
		// DG Code Op block
		//==============================================================
		//�q��
		RGB_vector_ptr result = getDGLutOpResult(dglut);
		//==============================================================

		STORE_RGBVECTOR("7_dgcode_final.xls", result);
		//�վ�max value
		RGBVector::changeMaxValue(result,
					  bitDepth->getLutMaxValue());

		this->dglut = result;
		return result;
	    };

	    RGB_vector_ptr LCDCalibrator::getGammaDGLut(bptr <
							MeasureCondition
							>
							measureCondition) {

		if (false == rgbIndepGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		} else if (true == rgbIndepGamma
			   && (null == rgammaCurve
			       || null == ggammaCurve
			       || null == bgammaCurve)) {
		    throw new
			IllegalStateException
			("null == rgammaCurve || null == ggammaCurve || null == bgammaCurve");
		}


		RGB_vector_ptr dglut;
		if (true == rgbIndepGamma) {
		    //�Ȥ�����
		    dglut = RGB_vector_ptr((RGB_vector *) null);
		    return dglut;
		} else {
		    /*Component_vector_ptr componentVector =
		       fetchComponentVector(measureCondition); */
		    double_vector_ptr luminanceVector =
			fetchLuminanceVector(measureCondition);
		    STORE_DOUBLE_VECTOR("o_fetch.xls", luminanceVector);

		    if (luminanceVector == null) {
			return RGB_vector_ptr((RGB_vector *) null);
		    }

		    DGLutGenerator generator(luminanceVector);
		    dglut = generator.getGammaDGLut(gammaCurve);

		}
		//�q��
		MaxValue quantizationBit = bitDepth->getLutMaxValue();
		RGBVector::quantization(dglut, quantizationBit);
		//�վ�max value
		RGBVector::changeMaxValue(dglut,
					  bitDepth->getLutMaxValue());

		this->dglut = dglut;
		return dglut;
	    };

	    bptr < DGLutFile >
		LCDCalibrator::storeDGLutFile(const std::
					      string & filename,
					      RGB_vector_ptr dglut) {
		//int n = bitDepth->getLevel();
		//int n = true == gamma256 ? 257 : 256;
		//�屼�w�s�b��
		Util::deleteExist(filename);
		//���ͷs��
		bptr < DGLutFile > file(new DGLutFile(filename, Create));
		//DGLutFile file(filename, Create);
		//����property����
		//bptr < LCDCalibrator > thisbptr(this);
		DGLutProperty property(this);
		//�g�Jproperty
		file->setProperty(property);
		//�g�Jdgcode
		file->setGammaTable(dglut);
		if (null != componentVector) {
		    //�g�Jraw data
		    file->setRawData(componentVector, initialRGBGamma,
				     finalRGBGamma);
		}
		return file;
	    };

	    RGB_vector_ptr LCDCalibrator::
		getDGLutOpResult(RGB_vector_ptr dglut) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		DGLutOp dgop;
		dgop.setSource(dglut);

		//==============================================================
		// dim�ץ�
		//==============================================================
		if (correct == Correct::RBInterpolation) {
		    bptr < DGLutOp > op(new RBInterpolationOp(under));
		    dgop.addOp(op);
		}
		//==============================================================

		if (bMax) {
		    //bmax���վ�
		    bptr < DGLutOp > bmax(new BMaxOp(bitDepth));
		    dgop.addOp(bmax);
		} else if (bMax2) {
		    //bmax2���վ�
		    bptr < DGLutOp >
			bmax2(new
			      BMax2Op(bitDepth, bMax2Begin, bMax2Gamma));
		    dgop.addOp(bmax2);
		}
		if (gByPass) {
		    //g bypass���վ�
		    bptr < DGLutOp > gbypass(new GByPassOp(bitDepth));
		    dgop.addOp(gbypass);
		}
		if (avoidFRCNoise) {
		    //frc noise���վ�
		    bptr < DGLutOp > avoidNoise(new FrcNROp(bitDepth));
		    dgop.addOp(avoidNoise);
		}

		if (KeepMaxLuminance::NativeWhite == keepMaxLuminance) {
		    //keep�̤j�G��
		    bptr < DGLutOp >
			KeepMax(new KeepMaxLuminanceOp(bitDepth));
		    dgop.addOp(KeepMax);
		}
		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };

	    void LCDCalibrator::
		setBTargetIntensity(double bTargetIntensity) {
		this->bTargetIntensity = bTargetIntensity;
	    };
	    //==================================================================

	};
    };
};


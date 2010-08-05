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
	    // DGLutGenerator
	    //==================================================================
	    /*
	       �N���W�ƪ�gamma curve, �ഫ�����諸�G��curve
	     */
	    double_vector_ptr DGLutGenerator::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve) {
		int size = normalGammaCurve->size();
		double_vector_ptr luminanceGammaCurve(new double_vector(size));
		double differ = maxLuminance - minLuminance;
		for (int x = 0; x != size; x++) {
		    double v = differ * (*normalGammaCurve)[x] + minLuminance;
		     (*luminanceGammaCurve)[x] = v;
		} return luminanceGammaCurve;
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
		    bptr < ComponentRelationIF > (new ComponentLinearRelation(componentVector));
		//==============================================================

		//==============================================================
		// ����RGB LUT
		//==============================================================
		lut = bptr < ComponentLUT > (new ComponentLUT(componentVector));
		//==============================================================

		double maxintensity = Math::roundTo(getMaximumIntensity());
		if (!keepTargetWhiteMaxLuminance) {
		    maxintensity = (maxintensity > 100) ? 100 : maxintensity;
		}

		maxLuminance =
		    componentRelation->getLuminance(maxintensity, maxintensity, maxintensity);
		int size = componentVector->size();
		minLuminance = (*componentVector)[size - 1]->XYZ->Y;
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector):componentVector
		(componentVector), mode(Component),
		keepMaxLuminance(KeepMaxLuminance::TargetWhite) {
		initComponent(componentVector, keepMaxLuminance == KeepMaxLuminance::TargetWhite);
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector, KeepMaxLuminance keepMaxLuminance):componentVector
		(componentVector),
		mode(Component), keepMaxLuminance(keepMaxLuminance) {
		initComponent(componentVector, keepMaxLuminance == KeepMaxLuminance::TargetWhite);
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
		double_vector_ptr value = DoubleArray::getReverse(luminanceVector);

		wlut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(key, value));
	    };

	    RGB_ptr DGLutGenerator::getDGCode(double rIntensity,
					      double gIntensity,
					      double bIntensity, bool correctInRange) {
		if (true == correctInRange) {
		    rIntensity = lut->correctIntensityInRange(Channel::R, rIntensity);
		    gIntensity = lut->correctIntensityInRange(Channel::G, gIntensity);
		    bIntensity = lut->correctIntensityInRange(Channel::B, bIntensity);
		}

		double r = lut->getCode(Channel::R, rIntensity);
		double g = lut->getCode(Channel::G, gIntensity);
		double b = lut->getCode(Channel::B, bIntensity);

		RGB_ptr rgb(new RGBColor(r, g, b));
		return rgb;
	    };

	    RGB_ptr DGLutGenerator::
		getDGCode(double rIntensity, double gIntensity, double bIntensity) {
		return getDGCode(rIntensity, gIntensity, bIntensity, true);
	    }

	    RGB_vector_ptr DGLutGenerator::getCCTDGLut(RGBGamma_ptr rgbIntensityCurve) {
		if (mode == WLumi || mode == RGBLumi) {
		    throw UnsupportedOperationException("DGLutGenerator is in luminanceMode.");
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

	    RGB_vector_ptr DGLutGenerator::getGammaDGLut(double_vector_ptr normalGammaCurve) {
		double_vector_ptr luminanceGammaCurve = getLuminanceGammaCurve(normalGammaCurve);
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
	    RGBGamma_ptr DGLutGenerator::getRGBGamma(double_vector_ptr normalGammaCurve) {
		//gamma curve��luminance curve
		double_vector_ptr luminanceGammaCurve = getLuminanceGammaCurve(normalGammaCurve);
		STORE_DOUBLE_VECTOR("0_lumicurve.xls", luminanceGammaCurve);
		int size = luminanceGammaCurve->size();
		double_vector_ptr rIntenisty(new double_vector(size));
		double_vector_ptr gIntenisty(new double_vector(size));
		double_vector_ptr bIntenisty(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    double luminance = (*luminanceGammaCurve)[x];
		    //luminance curve��intensity
		    double intensity = componentRelation->getIntensity(luminance);
		    (*rIntenisty)[x] = intensity;
		    (*gIntenisty)[x] = intensity;
		    (*bIntenisty)[x] = intensity;
		}

		RGBGamma_ptr rgbgamma(new
				      RGBGamma(rIntenisty, gIntenisty, bIntenisty, 100, Intensity));

		return rgbgamma;
	    };
	    double DGLutGenerator::getMaxBIntensity() {
		return lut->getMaxBIntensity();
	    };
	    //==================================================================

	    //==================================================================
	  MeasureCondition::MeasureCondition(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth):start(bitDepth->getMeasureStart()),
		end(bitDepth->getMeasureEnd()), firstStep(bitDepth->getMeasureFirstStep()),
		step(bitDepth->getMeasureStep()), type(Normal) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode(start, end, firstStep, step), Channel::W,
				      bitDepth->getMeasureMaxValue());
	    };
	  MeasureCondition::MeasureCondition(const int start, const int end, const int firstStep, const int step, const Dep::MaxValue & maxValue):start(start),
		end(end), firstStep(firstStep), step(step),
		type(Normal) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode(start, end, firstStep, step), Channel::W,
				      maxValue);
	    };
	    MeasureCondition::MeasureCondition(const int lowStart,
					       const int lowEnd,
					       const int lowStep,
					       const int highStart, const int highEnd, const int
					       highStep,
					       const Dep::MaxValue & maxValue):lowStart(lowStart),
		lowEnd(lowEnd), lowStep(lowStep), highStart(highStart), highEnd(highEnd),
		highStep(highStep), type(Extend) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode
				      (lowStart, lowEnd, lowStep, highStart, highEnd, highStep),
				      Channel::W, maxValue);
	    };

	  MeasureCondition::MeasureCondition(RGB_vector_ptr rgbMeasureCode):type(Normal)
	    {
		this->rgbMeasureCode = rgbMeasureCode;
	    };

	    RGB_vector_ptr MeasureCondition::getRGBMeasureCode() {
		return rgbMeasureCode;
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
					  highStep) ? highStart : highStart + 1;

		for (int x = start; x >= highEnd; x -= highStep) {
		    int code = x > 255 ? 255 : x;
		    measureCode->push_back(code);
		}
		start = (lowStart == highEnd) ? (lowStart - lowStep) : highEnd;
		for (int x = start; x >= lowEnd; x -= lowStep) {
		    measureCode->push_back(x);
		}

		return measureCode;
	    };

	    bool MeasureCondition::isNoRemainder(int start, int end, int step) {
		double dividend = ((double) start - end) / step;
		bool noremainder = dividend == static_cast < int >(dividend);
		return noremainder;
	    }
	    RGB_vector_ptr MeasureCondition::getRGBMeasureCode(int_vector_ptr measureCode,
							       const Dep::Channel & channel) {
		return getRGBMeasureCode(measureCode, channel, MaxValue::Int8Bit);
	    }
	    RGB_vector_ptr MeasureCondition::getRGBMeasureCode(int_vector_ptr measureCode,
							       const Dep::Channel & channel,
							       const MaxValue & maxValue) {
		RGB_vector_ptr rgbMeasureCode(new RGB_vector());
		foreach(int c, *measureCode) {
		    RGB_ptr rgb(new RGBColor(maxValue));
		    rgb->setValue(channel, c);
		    rgbMeasureCode->push_back(rgb);
		}
		return rgbMeasureCode;
	    };
	    //==================================================================


	    //==================================================================
	    // LCDCalibrator
	    //==================================================================

	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double gamma, int n, int effectiven) {
		double_vector_ptr result(new double_vector(n));
		for (int x = 0; x < effectiven; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
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

	    void LCDCalibrator::setDefinedDim(int under, double gamma, bool averageDimDG) {
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
	    void LCDCalibrator::setGamma(double rgamma, double ggamma, double bgamma) {
		this->rgamma = rgamma;
		this->ggamma = ggamma;
		this->bgamma = bgamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		setGammaCurve0(getGammaCurveVector(rgamma, n, effectiven),
			       getGammaCurveVector(ggamma, n, effectiven),
			       getGammaCurveVector(bgamma, n, effectiven));
		useGammaCurve = false;
		rgbIndepGamma = true;
	    };
	    void LCDCalibrator::setGammaCurve0(double_vector_ptr gammaCurve) {
		this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve0(double_vector_ptr rgammaCurve,
			       double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve) {
		this->rgammaCurve = rgammaCurve;
		this->ggammaCurve = ggammaCurve;
		this->bgammaCurve = bgammaCurve;
	    };
	    void LCDCalibrator::setGammaCurve(double_vector_ptr gammaCurve) {
		setGammaCurve0(gammaCurve);
		useGammaCurve = true;
		rgbIndepGamma = false;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr rgammaCurve,
			      double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve) {
		setGammaCurve0(rgammaCurve, ggammaCurve, bgammaCurve);
		useGammaCurve = true;
		rgbIndepGamma = true;
	    };
	    void LCDCalibrator::setOriginalGamma() {
		this->originalGamma = true;
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
	    void LCDCalibrator::setBMax2(bool bMax2, int begin, double gamma) {
		this->bMax2 = bMax2;
		bMax2Begin = begin;
		bMax2Gamma = gamma;
	    };
	    void LCDCalibrator::setAvoidFRCNoise(bool avoid) {
		this->avoidFRCNoise = avoid;
	    };
	    void LCDCalibrator::setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance) {
		if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		    throw
			UnsupportedOperationException
			("Please call setKeepMaxLuminanceNativeWhiteAdvanced().");
		}
		this->keepMaxLuminance = keepMaxLuminance;
	    };
	    void LCDCalibrator::setKeepMaxLuminanceNativeWhiteAdvanced(int over, double gamma) {
		this->keepMaxLuminance = KeepMaxLuminance::NativeWhiteAdvanced;
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
		originalGamma = false;
	    };

	    Component_vector_ptr LCDCalibrator::
		fetchComponentVector(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		//�q��start->end�o�쪺coponent/Y
		componentVector = fetcher->fetchComponent(measureCondition);
		RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();

		if (componentVector == null || rgbMeasureCode->size() != componentVector->size()) {
		    return Component_vector_ptr((Component_vector *)
						null);
		} else {
		    return componentVector;
		}
	    };

	    double_vector_ptr LCDCalibrator::
		fetchLuminanceVector(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		//�q��start->end�o�쪺coponent/Y
		luminanceVector = fetcher->fetchLuminance(measureCondition);

		if (luminanceVector == null /*|| measurecode->size() != luminanceVector->size() */ ) {
		    return double_vector_ptr((double_vector *)
					     null);
		} else {
		    return luminanceVector;
		}
	    };

	    double_vector_ptr LCDCalibrator::getGammaCurve(Component_vector_ptr componentVector) {
		double_vector_ptr keys(new double_vector());
		double_vector_ptr values(new double_vector());
		int size = componentVector->size();

		Component_ptr white = (*componentVector)[0];
		Component_ptr black = (*componentVector)[size - 1];
		double maxLuminance = white->XYZ->Y;
		double minLuminance = black->XYZ->Y;
		double max = white->rgb->getMaxValue().max;


		for (int x = size - 1; x != -1; x--) {
		    Component_ptr c = (*componentVector)[x];
		    double gray = c->rgb->getValue(Channel::W);
		    double normal = gray / max;
		    double luminance = c->XYZ->Y;
		    double normalLuminance =
			(luminance - minLuminance) / (maxLuminance - minLuminance);
		    keys->push_back(normal);
		    values->push_back(normalLuminance);
		}

		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		Interpolation1DLUT lut(keys, values);
		double_vector_ptr gammaCurve(new double_vector());

		for (int x = 0; x != effectiven; x++) {
		    double normal = ((double) x) / (effectiven - 1);
		    double value = lut.getValue(normal);
		    gammaCurve->push_back(value);
		}
		for (int x = effectiven; x != n; x++) {
		    gammaCurve->push_back(1);
		}

		return gammaCurve;
	    };

	    /*
	       CCT + Gamma
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		if (false == originalGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		Component_vector_ptr componentVector = fetchComponentVector(measureCondition);
		if (componentVector == null) {
		    return RGB_vector_ptr((RGB_vector *) null);
		}
		if (true == originalGamma) {
		    //�Y�n�ĥ�original gamma, �q�q�����G�ԥXgamma, ��@�ؼ�gamma curve
		    double_vector_ptr gammaCurve = getGammaCurve(componentVector);
		    setGammaCurve(gammaCurve);
		}

		STORE_COMPONENT("o_fetch.xls", componentVector);
		DGLutGenerator generator(componentVector, keepMaxLuminance);
		STORE_DOUBLE_VECTOR("0_gammacurve.xls", gammaCurve);
		MaxValue quantizationBit = bitDepth->getLutMaxValue();

		if (true == newMethod) {
		    //==========================================================
		    // �s��k
		    //==========================================================
		    bptr < IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		    AdvancedDGLutGenerator advgenerator(componentVector, fetcher);
		    //analyzer�Y�S���]�w�Ltarget color, �|�Ϧ��B�J����
		    XYZ_ptr targetWhite = analyzer->getReferenceColor()->toXYZ();
		    //�ǥѶǲ�generator����luminance gamma curve
		    double_vector_ptr luminanceGammaCurve =
			generator.getLuminanceGammaCurve(gammaCurve);
		    STORE_DOUBLE_VECTOR("1_lumigammacurve.xls", luminanceGammaCurve);
		    double dimgammaParameter = 3.5;
		    int underParameter = 50;
		    double brightgammaParameter = 2.2;
		    int overParameter = 200;

		    if (correct == Correct::DefinedDim) {
			dimgammaParameter = dimGamma;
			underParameter = under;
		    }

		    if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
			brightgammaParameter = keepMaxLumiGamma;
			overParameter = keepMaxLumiOver;
		    } else {
		    }

		    if (this->bTargetIntensity != -1) {
			advgenerator.setBTargetIntensity(bTargetIntensity);
		    }

		    if (multiGen) {
			advgenerator.setMultiGen(multiGen, multiGenTimes);
		    }

		    dglut =
			advgenerator.produce(targetWhite,
					     luminanceGammaCurve,
					     underParameter,
					     overParameter,
					     dimgammaParameter, brightgammaParameter);
		    STORE_RGBVECTOR("3_dgcode.xls", dglut);
		    //==========================================================
		} else {
		    //==========================================================
		    // �Ѥ�k
		    //==========================================================
		    RGBGamma_ptr rgbgamma = generator.getRGBGamma(gammaCurve);
		    initialRGBGamma = rgbgamma->clone();

		    STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);


		    /* TODO : bIntensityGain�n�T�{ */
		    if (bIntensityGain != 1.0) {
			//���s���ͥؼ�gamma curve
			bptr < BIntensityGainOp >
			    bgain(new BIntensityGainOp(bIntensityGain, 236, bitDepth));

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
			bptr < P1P2GammaOp > p1p2(new P1P2GammaOp(p1, p2, dglut));
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
			bptr < DGLutOp > op(new P1P2DGOp(p1, p2, quantizationBit));
			dgop.addOp(op);
			dglut = dgop.createInstance();
			//�q��
			STORE_RGBVECTOR("6_dgcode_p1p2dg.xls", dglut);
			//==========================================================
		    }
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
		//�վ�max value, �վ��LUT�u����max value
		RGBVector::changeMaxValue(result, bitDepth->getLutMaxValue());

		this->dglut = result;
		return result;
	    };

	    RGB_vector_ptr LCDCalibrator::getGammaDGLut(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;

		if (false == rgbIndepGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		} else if (true == rgbIndepGamma
			   && (null == rgammaCurve || null == ggammaCurve || null == bgammaCurve)) {
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
		    double_vector_ptr luminanceVector = fetchLuminanceVector(measureCondition);
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
		RGBVector::changeMaxValue(dglut, bitDepth->getLutMaxValue());

		this->dglut = dglut;
		return dglut;
	    };

	    bptr < DGLutFile >
		LCDCalibrator::storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut) {
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
		    file->setRawData(componentVector, initialRGBGamma, finalRGBGamma);
		}
		return file;
	    };

	    void LCDCalibrator::storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut,
					       bptr < cms::colorformat::DGLutFile > dglutFile) {
		//int n = bitDepth->getLevel();
		//int n = true == gamma256 ? 257 : 256;
		//�屼�w�s�b��
		//Util::deleteExist(filename);
		//���ͷs��
		//bptr < DGLutFile > file(new DGLutFile(filename, Create));
		//DGLutFile file(filename, Create);
		//����property����
		//bptr < LCDCalibrator > thisbptr(this);
		DGLutProperty property(this);
		//�g�Jproperty
		dglutFile->setProperty(property);
		//�g�Jdgcode
		dglutFile->setGammaTable(dglut);
		if (null != componentVector) {
		    //�g�Jraw data
		    dglutFile->setRawData(componentVector, initialRGBGamma, finalRGBGamma);
		}
		//return file;
	    };

	    RGB_vector_ptr LCDCalibrator::getDGLutOpResult(RGB_vector_ptr dglut) {
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
		    bptr < DGLutOp > bmax2(new BMax2Op(bitDepth, bMax2Begin, bMax2Gamma));
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
		    bptr < DGLutOp > KeepMax(new KeepMaxLuminanceOp(bitDepth));
		    dgop.addOp(KeepMax);
		}
		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };

	    void LCDCalibrator::setBTargetIntensity(double bTargetIntensity) {
		this->bTargetIntensity = bTargetIntensity;
	    };

	    void LCDCalibrator::setMultiGen(bool enable, int times) {
		this->multiGen = enable;
		this->multiGenTimes = times;
	    };
	    //==================================================================

	};
    };
};


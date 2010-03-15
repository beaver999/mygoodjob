#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

#include <math/doublearray.h>
#include <math/interpolation.h>
#include "rgbvectorop.h"
#include "rgbgamma.h"
#include <gui/UIConfig.h>



#ifdef _DEBUG
#include <cms/util/rgbarray.h>
#define _ std::string
#define debug_dir _(DEBUG_DIR)

#define STORE_COMPOSITION( filename , result ) \
ComponentFetcher::storeToExcel(debug_dir + _(filename), result);
#define STORE_RGBGAMMA( filename , result ) \
cms::lcd::calibrate::RGBGamma::storeToExcel(debug_dir + _(filename), result);
#define STORE_RGBVECTOR( filename , result ) \
RGBVector::storeToExcel(debug_dir + _(filename), result);

#else
#define STORE_COMPOSITION( filename , result )
#define STORE_RGBGAMMA( filename , result )
#define STORE_RGBVECTOR( filename , result )
#endif

namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace cms::measure;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::colorformat;
	    using namespace cms::util;
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
	  ComponentFetcher::ComponentFetcher(bptr < IntensityAnalyzerIF > analyzer):analyzer
		(analyzer)
	    {

	    };

	    Component_vector_ptr ComponentFetcher::
		fetchComponent(int start, int end, int step) {

		Component_vector_ptr result(new Component_vector());
		for (int x = start; x >= end; x -= step) {
		    RGB_ptr rgb(new RGBColor(x, x, x));
		    RGB_ptr intensity = analyzer->getIntensity(rgb);
		    XYZ_ptr XYZ = analyzer->getCIEXYZ();
		    Component_ptr component(new
						Component(rgb,
							    intensity,
							    XYZ));
		    result->push_back(component);
		    if (true == stop) {
			break;
		    }
		};
		return result;
	    };
	    void ComponentFetcher::setStop(bool stop) {
		this->stop = stop;
	    };
	    void ComponentFetcher::storeToExcel(const string & filename,
						Component_vector_ptr
						componentVector) {

		int n = componentVector->size();
		ExcelFileDB::deleteExist(filename);
		DGLutFile dglut(filename, n);
		dglut.setRawData(componentVector);
	    };
	    //==================================================================

	    //==================================================================
	    // DGLutGenerator
	    //==================================================================
	    /*
	       DGLutGenerator������XDG Code�����d�j��
	       1. ��������ComponentFetcher���X��rgb,������componet,�G��
	       2. �ǥ�regression��Xcomponet�P�G�ת����Y
	       1/2��init���X

	       3. �ѥؼ�gamma curve�g�B�J�G��������component
	       4. ��compomenet�����XDG Code, DG Code���X
	       3/4��produce���X

	     */
	    void DGLutGenerator::init() {
		//==============================================================
		// �إߦ^�k���
		//==============================================================
		int size = componentVector->size();
		double2D_ptr input(new double2D(size, 3));
		double2D_ptr output(new double2D(size, 1));
		double_vector_ptr keys(new double_vector(size));
		double_vector_ptr rValues(new double_vector(size));
		double_vector_ptr gValues(new double_vector(size));
		double_vector_ptr bValues(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    Component_ptr component = (*componentVector)[x];
		    double Y = component->XYZ->Y;
		    RGB_ptr intensity = component->intensity;

		    (*input)[x][0] = intensity->R;
		    (*input)[x][1] = intensity->G;
		    (*input)[x][2] = intensity->B;
		    (*output)[x][0] = Y;

		    (*keys)[x] = component->rgb->getValue(Channel::W);
		    (*rValues)[x] = intensity->R;
		    (*gValues)[x] = intensity->G;
		    (*bValues)[x] = intensity->B;
		}
		//==============================================================

		//==============================================================
		// �p��c/d
		//==============================================================
		regression.reset(new PolynomialRegression(input, output,
							  Polynomial::
							  COEF_3::BY_3C));
		regression->regress();
		coefs = regression->getCoefs();
		c = 1 / ((*coefs)[0][1] + (*coefs)[0][2] + (*coefs)[0][3]);
		d = -(*coefs)[0][0] / ((*coefs)[0][1] + (*coefs)[0][2] +
				       (*coefs)[0][3]);
		//==============================================================

		maxLuminance = (*output)[0][0];
		minLuminance = (*output)[size - 1][0];

		//==============================================================
		// ����RGB LUT
		//==============================================================
		keys = getReverse(keys);
		rValues = getReverse(rValues);
		gValues = getReverse(gValues);
		bValues = getReverse(bValues);
		rLut.reset(new Interpolation1DLUT(keys, rValues));
		gLut.reset(new Interpolation1DLUT(keys, gValues));
		bLut.reset(new Interpolation1DLUT(keys, bValues));
		//==============================================================
	    };
	    double DGLutGenerator::getIntensity(double luminance) {
		return c * luminance + d;
	    };
	    double_vector_ptr DGLutGenerator::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve)
	    {
		int size = normalGammaCurve->size();
		double_vector_ptr luminanceGammaCurve(new
						      double_vector(size));
		double differ = maxLuminance - minLuminance;
		for (int x = 0; x != size; x++) {
		    double lumi =
			differ * (*normalGammaCurve)[x] + minLuminance;
		    (*luminanceGammaCurve)[x] = lumi;
		}
		return luminanceGammaCurve;
	    };
	    double_vector_ptr DGLutGenerator::
		getReverse(double_vector_ptr vec) {
		int size = vec->size();
		double_vector_ptr result(new double_vector(size));
		for (int x = 0; x != size; x++) {
		    (*result)[x] = (*vec)[size - 1 - x];
		}
		return result;
	    };
	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector):componentVector
		(componentVector)
	    {
		init();
	    };
	    RGB_vector_ptr DGLutGenerator::
		produce(double_vector_ptr normalGammaCurve) {
		double_vector_ptr luminanceGammaCurve =
		    getLuminanceGammaCurve(normalGammaCurve);
		int size = luminanceGammaCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));

		for (int x = 0; x != size; x++) {
		    double lumi = (*luminanceGammaCurve)[x];
		    double intensity = getIntensity(lumi);
		    double r = rLut->getKey(intensity);
		    double g = gLut->getKey(intensity);
		    double b = bLut->getKey(intensity);
		    RGB_ptr rgb(new RGBColor(r, g, b));
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };

	    RGB_vector_ptr DGLutGenerator::
		produce(RGBGamma_ptr normalRGBGammaCurve) {
		double_vector_ptr rluminanceGammaCurve =
		    getLuminanceGammaCurve(normalRGBGammaCurve->r);
		double_vector_ptr gluminanceGammaCurve =
		    getLuminanceGammaCurve(normalRGBGammaCurve->g);
		double_vector_ptr bluminanceGammaCurve =
		    getLuminanceGammaCurve(normalRGBGammaCurve->b);

		int size = rluminanceGammaCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));
		double luminance[3], intensity[3];

		for (int x = 0; x != size; x++) {
		    luminance[0] = (*rluminanceGammaCurve)[x];
		    luminance[1] = (*gluminanceGammaCurve)[x];
		    luminance[2] = (*bluminanceGammaCurve)[x];

		    intensity[0] = getIntensity(luminance[0]);
		    intensity[1] = getIntensity(luminance[1]);
		    intensity[2] = getIntensity(luminance[2]);

		    double r =
			(rLut->isValueInRange(intensity[0])) ? rLut->
			getKey(intensity[0]) : 0;
		    double g =
			(gLut->isValueInRange(intensity[1])) ? gLut->
			getKey(intensity[1]) : 0;
		    double b =
			(bLut->isValueInRange(intensity[2])) ? bLut->
			getKey(intensity[2]) : 0;

		    RGB_ptr rgb(new RGBColor(r, g, b));
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };
	    //==================================================================

	    //==================================================================
	    // LCDCalibrator
	    //==================================================================
	    void LCDCalibrator::set(int start, int end, int step) {
		this->start = start;
		this->end = end;
		this->step = step;
	    };

	    int LCDCalibrator::getn() {
		return (out == 12) ? 257 : 256;
	    };

	    int LCDCalibrator::getEffectiven() {
		return (in == 6 && out == 6) ? 253 : (in == 8) ? 256 : 257;
	    };

	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double gamma, int n,
						   int effectiven) {
		double_vector_ptr result(new double_vector(n));
		for (int x = 0; x < effectiven; x++) {
		    double normal =
			static_cast < double >(x) / (effectiven - 1);
		    double v = java::lang::Math::pow(normal, gamma);
		    (*result)[x] = v;
		}
		for (int x = effectiven; x < n; x++) {
		    (*result)[x] = 1;
		}
		return result;
	    };
	    void LCDCalibrator::setP1P2(double p1, double p2) {
		this->p1 = p1;
		this->p2 = p2;
		this->p1p2 = true;
	    };
	    void LCDCalibrator::setRBInterpolation(int under) {
		this->p1p2 = false;
		this->rbInterpUnder = under;
	    };
	    void LCDCalibrator::setGamma(double gamma) {
		this->gamma = gamma;
		setGammaCurve(getGammaCurveVector
			      (gamma, getn(), getEffectiven()));
	    };
	    void LCDCalibrator::setGamma(double rgamma, double ggamma,
					 double bgamma) {
		this->rgamma = rgamma;
		this->ggamma = ggamma;
		this->bgamma = bgamma;
		int n = getn();
		int effectiven = getEffectiven();
		setGammaCurve(getGammaCurveVector(rgamma, n, effectiven),
			      getGammaCurveVector(ggamma, n, effectiven),
			      getGammaCurveVector(bgamma, n, effectiven));
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr gammaCurve) {
		this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr rgammaCurve,
			      double_vector_ptr ggammaCurve,
			      double_vector_ptr bgammaCurve) {
		this->rgammaCurve = rgammaCurve;
		this->ggammaCurve = ggammaCurve;
		this->bgammaCurve = bgammaCurve;
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
	    void LCDCalibrator::setGamma256(bool gamma256) {
		this->gamma256 = gamma256;
	    };
	    void LCDCalibrator::setAvoidFRCNoise(bool avoid) {
		this->avoidFRCNoise = avoid;
	    };
	    void LCDCalibrator::setBitDepth(const
					    BitDepth & in, const
					    BitDepth & lut, const
					    BitDepth & out) {
		this->in = in;
		this->lut = lut;
		this->out = out;
	    };

	  LCDCalibrator::LCDCalibrator(bptr < IntensityAnalyzerIF > analyzer):analyzer(analyzer)
	    {
		rgbgamma = false;
		bIntensityGain = 1;
		rbInterpUnder = 0;
		gamma = rgamma = ggamma = bgamma = -1;
		fetcher.reset(new ComponentFetcher(analyzer));
		in = lut = out = Unknow;
	    };

	    /*
	       CCT + Gamma
	     */
	    RGB_vector_ptr LCDCalibrator::
		getDGLut(int start, int end, int step) {
		set(start, end, step);
		if (null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}
#ifdef _DEBUG
		if (!DirectoryExists(DEBUG_DIR)) {
		    CreateDir(DEBUG_DIR);
		}
#endif

		//�q��start->end�o�쪺coponent/Y
		componentVector =
		    fetcher->fetchComponent(start, end, step);

		STORE_COMPOSITION("0_fetch.xls", componentVector);

		//����generator
		generator.reset(new DGLutGenerator(componentVector));
		//RGBGamma_ptr rgbgamma = getRGBGamma(gammaCurve);
		RGBGamma_ptr rgbgamma =
		    RGBGammaOp::getRGBGamma(gammaCurve);
		STORE_RGBGAMMA("1_rgbgamma1.xls", rgbgamma);

		RGBGammaOp gammaop;
		gammaop.setSource(rgbgamma);

		/* TODO : �n�T�{ */
		if (bIntensityGain != 1.0) {
		    //���s���ͥؼ�gamma curve
		    bptr < BIntensityGainOp >
			bgain(new BIntensityGainOp(bIntensityGain));
		    gammaop.addOp(bgain);
		    rgbgamma = gammaop.createInstance();
		};
		STORE_RGBGAMMA("2_rgbgamma2.xls", rgbgamma);

		//�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
		RGB_vector_ptr dglut = generator->produce(rgbgamma);
		STORE_RGBVECTOR("3_dgcode1.xls", dglut);

		if (p1p2) {
		    //==========================================================
		    //p1p2�Ĥ@���q, ��gamma���վ�
		    //==========================================================
		    bptr < P1P2GammaOp >
			p1p2(new P1P2GammaOp(p1, p2, dglut));
		    gammaop.addOp(p1p2);

		    //���ͭץ��᪺gamma2(�Y�S��p1p2,�h����ʤ���)
		    rgbgamma = gammaop.createInstance();
		    STORE_RGBGAMMA("4_rgbgamma2.xls", rgbgamma);

		    //����generator
		    //generator.reset(new DGLutGenerator(compositionVector));
		    //�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
		    dglut = generator->produce(rgbgamma);
		    STORE_RGBVECTOR("5_dgcode2.xls", dglut);
		    //==========================================================


		    //==========================================================
		    //p1p2�ĤG���q, ��dg code�վ�
		    //==========================================================
		    DGLutOp dgop;
		    dgop.setSource(dglut);
		    bptr < DGLutOp > op(new P1P2DGOp(p1, p2, in == Bit6));
		    dgop.addOp(op);
		    dglut = dgop.createInstance();
		    //==========================================================
		};
		//RGB_vector_ptr dgcode2 = dglut;
		finalRGBGamma = rgbgamma;

		//==============================================================
		// DG Code Op block
		//==============================================================
		const MaxValue & maxValue = (lut == 10) ?
		    MaxValue::Int10Bit : MaxValue::Int12Bit;
		//�q��
		RGBVector::quantization(dglut, maxValue);
		RGB_vector_ptr result = getDGLutOpResult(dglut);
		//==============================================================
		STORE_RGBVECTOR("6_dgcode.xls", result);
		//�վ�max value
		RGBVector::changeMaxValue(result, maxValue);

		this->dglut = result;
		return result;
	    };

	    /*
	       Gamma Only
	     */
	    RGB_vector_ptr LCDCalibrator::getDGLut(int step) {
		set(255, 0, step);
	    };

	    void LCDCalibrator::storeDGLut(const std::string & filename,
					   RGB_vector_ptr dglut) {

		int n = true == gamma256 ? 257 : 256;
		//�屼�w�s�b��
		ExcelFileDB::deleteExist(filename);
		//���ͷs��
		DGLutFile file(filename, n);
		//����property����
		DGLutProperty property(*this);
		//�g�Jproperty
		file.setProperty(property);
		//�g�Jdgcode
		file.setGammaTable(dglut);
		//�g�Jraw data
		file.setRawData(componentVector, finalRGBGamma);

	    };

	    BitDepth LCDCalibrator::getBitDepth(int bit) {
		switch (bit) {
		case 6:
		    return Bit6;
		case 8:
		    return Bit8;
		case 10:
		    return Bit10;
		case 12:
		    return Bit12;
		};
	    };

	    RGB_vector_ptr LCDCalibrator::
		getDGLutOpResult(RGB_vector_ptr dglut) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		DGLutOp dgop;
		dgop.setSource(dglut);

		/*if (p1p2) {
		   //p1p2�ĤG���q, ��dg code�վ�
		   bptr < DGLutOp > op(new P1P2DGOp(p1, p2, in == Bit6));
		   dgop.addOp(op);
		   } else { */
		if (!p1p2) {
		    //�Y���Op1p2�N�ORBInterp(�ܤ֥ثe�O�p��)
		    bptr < DGLutOp >
			op(new RBInterpolationOp(rbInterpUnder));
		    dgop.addOp(op);
		}

		if (bMax) {
		    //bmax���վ�
		    bptr < DGLutOp > bmax(new BMaxOp(out));
		    dgop.addOp(bmax);
		}
		if (gByPass) {
		    //g bypass���վ�
		    bptr < DGLutOp > gbypass(new GByPassOp(in, out));
		    dgop.addOp(gbypass);
		}
		if (avoidFRCNoise) {
		    //frc noise���վ�
		    bptr < DGLutOp > avoidNoise(new AvoidFRCNoiseOp());
		    dgop.addOp(avoidNoise);
		}
		if (gamma256) {

		}
		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };


	    //==================================================================

	};
    };
};


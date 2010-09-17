#include <includeall.h>
#pragma hdrstop
#include "sandbox.h"
#include <debug.h>


//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::colorformat;
	    using namespace Indep;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::lcd::calibrate;

	    //==================================================================
	    // AdvancedDGLutGenerator
	    //==================================================================
	     AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < cms::lcd::calibrate::ComponentFetcher > fetcher,
				       bptr < IntensityAnalyzerIF > analyzer1,
				       bptr < IntensityAnalyzerIF > analyzer2,
				       bptr < BitDepthProcessor >
				       bitDepth):DimDGLutGenerator(componentVector, analyzer1),
		fetcher(fetcher), useMaxTargetBIntensity(false), bTargetIntensity(-1),
		stopMeasure(false), multiGen(false), analyzer2(analyzer2), bitDepth(bitDepth),
		smoothMode(true) {
	    };

	     AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < ComponentFetcher >
				       fetcher,
				       bptr < BitDepthProcessor >
				       bitDepth):DimDGLutGenerator
		(componentVector, fetcher->getAnalyzer()),
		fetcher(fetcher), useMaxTargetBIntensity(false),
		bTargetIntensity(-1), stopMeasure(false), multiGen(false),
		bitDepth(bitDepth), smoothMode(false) {
	    };
	    XYZ_vector_ptr AdvancedDGLutGenerator::getTargetXYZVector(XYZ_ptr targetWhite,
								      double_vector_ptr
								      luminanceGammaCurve,
								      int dimTurn, int brightTurn,
								      double dimGamma,
								      double brightGamma,
								      int brightWidth) {
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;
		 return getTargetXYZVector(targetWhite, nativeWhite, luminanceGammaCurve, dimTurn,
					   brightTurn, dimGamma, brightGamma, brightWidth);
	    };
	    XYZ_vector_ptr AdvancedDGLutGenerator::getTargetXYZVector(XYZ_ptr targetWhite,
								      XYZ_ptr nativeWhite,
								      double_vector_ptr
								      luminanceGammaCurve,
								      int dimTurn, int brightTurn,
								      double dimGamma,
								      double brightGamma,
								      int brightWidth) {
		//==============================================================
		// ��T�ǳ�
		//==============================================================
		XYZ_ptr blackXYZ = (*componentVector)[componentVector->size() - 1]->XYZ;
		//XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;
		XYZ_vector_ptr targetXYZVector;
		this->brightTurn = brightTurn;

		//�D�ؼЭȦ��u
		if (true == autoParameter) {
		    int turn = brightTurn;
		    int width = -1;
		    for (; turn >= 100; turn--) {
			width = bitDepth->getEffectiveLevel() - turn;
			targetXYZVector =
			    getTarget0(blackXYZ, targetWhite, nativeWhite, luminanceGammaCurve,
				       dimTurn, turn, dimGamma, brightGamma, width);

			if (true == checkTargetXYZVector(targetXYZVector, turn, turn + width, 3)) {
			    //�ˬd�Y�̤j��dab�p��threshold, �N���X
			    break;
			}
		    };
		    this->autoBrightTurn = turn;
		    this->autoBrightWidth = width;
		} else {
		    targetXYZVector =
			getTarget0(blackXYZ, targetWhite, nativeWhite, luminanceGammaCurve, dimTurn,
				   brightTurn, dimGamma, brightGamma, brightWidth);
		}
		return targetXYZVector;
	    }

	    /*
	       ��i�������ͤ覡
	       1.�����ͤ@��DG Lut
	       2.��Ӳ�DG���q�����@Raw Data
	       3.�A���Ӳհ�Raw Data����DG Lut
	       4.�Y��ǫ׭n��,�N���ư��캡�N����
	     */
	    RGB_vector_ptr AdvancedDGLutGenerator::produce(XYZ_vector_ptr targetXYZVector) {
		STORE_XYZXY_VECTOE("target.xls", targetXYZVector);
		//==============================================================
		/*
		   �Y���Fsmooth target(�򥻤Wadv dg lut�]�u��smooth target���\��)
		   ���Oanalyzer�̪�primary color�ä��Onative white��primary color,
		   �ҥH���X�Ӫ�native target�L�k�p�w���|�O(255,255,255)
		   ���F�ѨM�o�Ӱ��D, �����n�����primary color;
		   �Ĥ@�յ�target white��, �ĤG�յ�native white��.
		   ���D�b��p��V�γo���primary color?

		   ��k1. �H���analyer�����ͤ@��DG, �M��Abright turn��end�o�q, �Hgain�Ȱ������B�z.
		 */
		if (multiGen) {
		    return produceDGLutMulti(targetXYZVector, componentVector);
		} else {
		    if (smoothMode) {
			//target white���ͪ����G
			RGB_vector_ptr result1 = produceDGLut(targetXYZVector, componentVector,
							      analyzer, panelRegulator1);
			//native white���ͪ����G
			RGB_vector_ptr result2;
			if (componentVector2 != null) {
			    result2 =
				produceDGLut(targetXYZVector, componentVector2, analyzer2,
					     panelRegulator2);
			} else {
			    result2 =
				produceDGLut(targetXYZVector, componentVector, analyzer2,
					     panelRegulator1);
			}

			//�N��ӵ��G�α��_��
			return smooth(result1, result2, bitDepth, brightTurn);
		    } else {
			RGB_vector_ptr result =
			    produceDGLut(targetXYZVector, componentVector, analyzer,
					 panelRegulator1);
			return result;
		    }
		}
	    }

	    RGB_vector_ptr AdvancedDGLutGenerator::
		smooth(RGB_vector_ptr result1, RGB_vector_ptr result2,
		       bptr < BitDepthProcessor > bitDepth, int brightTurn) {
		RGB_vector_ptr result = RGBVector::deepClone(result1);

		int level = bitDepth->getLevel();
		int part = level - brightTurn;
		int part13 = part / 3;
		int part13Start = level - part13;
		int size = result1->size();
		for (int x = brightTurn; x < part13Start; x++) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr rgb1 = (*result1)[x];
		    RGB_ptr rgb2 = (*result2)[x];
		    double gain2 = (((double) x) - brightTurn) / (part13Start - brightTurn);
		    double gain = 1. - gain2;
		    rgb->R = gain * rgb1->R + gain2 * rgb2->R;
		    rgb->G = gain * rgb1->G + gain2 * rgb2->G;
		    rgb->B = gain * rgb1->B + gain2 * rgb2->B;
		}
		for (int x = part13Start; x < level; x++) {
		    (*result)[x] = (*result2)[x]->clone();
		}
		/*STORE_RGBVECTOR("sm-result1.xls", result1);
		STORE_RGBVECTOR("sm-result2.xls", result2);
		STORE_RGBVECTOR("sm-result.xls", result);*/

		return result;
	    };
	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLutMulti(XYZ_vector_ptr targetXYZVector,
				  Component_vector_ptr componentVector) {
		//�����ͪ�B���G
		RGB_vector_ptr initRGBVector = produceDGLut(targetXYZVector, componentVector,
							    analyzer, panelRegulator1);

		/*
		   1. RGB���δ�, ���w255
		   2. RGB���ĥΤW�@����DG Code
		   �Y�O�p��, �@�w�n�D�X��GL��DG�~�i�H�~��U�@��
		 */
		RGB_vector_ptr result = initRGBVector;
		if (null == fetcher) {
		    throw new IllegalStateException("null == fetcher");
		}
		STORE_RGBVECTOR("MultiGen_0.xls", result);

		for (int t = 0; t < multiGenTimes; t++) {
		    bptr < MeasureCondition >
			measureCondition(new MeasureCondition(RGBVector::reverse(result)));
		    Component_vector_ptr componentVectorPrime =
			fetcher->fetchComponent(measureCondition);

		    result =
			produceDGLut(targetXYZVector, componentVectorPrime, analyzer,
				     bptr < PanelRegulator > ((PanelRegulator *) null));
		    STORE_RGBVECTOR("MultiGen_" + _toString(t + 1) + ".xls", result);
		}

		return result;
	    };



	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLut(XYZ_vector_ptr targetXYZVector,
			     Component_vector_ptr componentVector,
			     bptr < cms::measure::IntensityAnalyzerIF > analyzer,
			     bptr < PanelRegulator > panelRegulator) {

		int size = targetXYZVector->size();
		RGB_vector_ptr result(new RGB_vector(size));
		//==============================================================
		//primary color�u���target white~
		XYZ_ptr rXYZ = analyzer->getPrimaryColor(Channel::R)->toXYZ();
		XYZ_ptr gXYZ = analyzer->getPrimaryColor(Channel::G)->toXYZ();
		XYZ_ptr bXYZ = analyzer->getPrimaryColor(Channel::B)->toXYZ();

#ifdef DEBUG_CCTLUT_NEWMETHOD
		Component_vector_ptr maxComponentVector(new Component_vector());
#endif
		for (int x = size - 1; x != -1; x--) {
		    XYZ_ptr targetXYZ = (*targetXYZVector)[x];

		    bptr < MaxMatrixIntensityAnayzer > ma(new MaxMatrixIntensityAnayzer());
		    ma->setupComponent(Channel::R, rXYZ);
		    ma->setupComponent(Channel::G, gXYZ);
		    ma->setupComponent(Channel::B, bXYZ);
		    ma->setupComponent(Channel::W, targetXYZ);
		    ma->enter();

		    Component_vector_ptr newcomponentVector =
			fetchNewComponent(ma, componentVector);

#ifdef DEBUG_CCTLUT_NEWMETHOD
#ifdef DEBUG_CCTLUT_NEWMETHOD_STEP
		    STORE_COMPONENT(_toString(x) + ".xls", newcomponentVector);
#endif
		    //��Ĥ@�Ӧs�_��, �Ĥ@�ө����O�̤j��
		    RGB_ptr grayLevel(new RGBColor(x, x, x));
		    Component_ptr c(new Component(grayLevel,
						  (*newcomponentVector)[0]->intensity, targetXYZ));
		    maxComponentVector->push_back(c);
#endif
		    DGLutGenerator lutgen(newcomponentVector);
		    //B��100��?
		    if (bTargetIntensity == -1) {
			bTargetIntensity = useMaxTargetBIntensity ? lutgen.getMaxBIntensity() : 100;
		    };
		    RGB_ptr rgb = lutgen.getDGCode(100, 100,
						   bTargetIntensity);
		    (*result)[x] = rgb;
		}
#ifdef DEBUG_CCTLUT_NEWMETHOD
		STORE_COMPONENT("maxIntensity.xls", maxComponentVector);
#endif
		if (null != panelRegulator) {
		    result = panelRegulator->remapping(result);
		}
		return result;
	    };
	    bool AdvancedDGLutGenerator::isAvoidHook(XYZ_ptr targetXYZ, double offsetK) {
		XYZ_ptr XYZOffset = getXYZ(targetXYZ, offsetK);
		return isDuplicateBlue100(XYZOffset);
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getXYZ(XYZ_ptr XYZ, double offsetK) {
		//==============================================================
		// ���Ʒǳ�
		//==============================================================
		xyY_ptr xyY(new CIExyY(XYZ));
		double cct = CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		xyY_ptr xyYOriginal = CorrelatedColorTemperature::CCT2DIlluminantxyY(cct);
		double cctOffset = cct + offsetK;
		xyY_ptr xyYOffset = CorrelatedColorTemperature::CCT2DIlluminantxyY(cctOffset);
		//==============================================================

		//==============================================================
		// shift
		//==============================================================
		double_array dxy = xyY->getDeltaxy(xyYOriginal);
		xyYOffset->x += dxy[0];
		xyYOffset->y += dxy[1];
		//==============================================================

		xyYOffset->Y = XYZ->Y;
		XYZ_ptr XYZOffset = xyYOffset->toXYZ();
		return XYZOffset;
	    };
	    bool AdvancedDGLutGenerator::isDuplicateBlue100(XYZ_ptr targetXYZ) {
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

		bptr < MaxMatrixIntensityAnayzer > mmia(new MaxMatrixIntensityAnayzer());
		mmia->setupComponent(Channel::R, rxyY->toXYZ());
		mmia->setupComponent(Channel::G, gxyY->toXYZ());
		mmia->setupComponent(Channel::B, bxyY->toXYZ());
		mmia->setupComponent(Channel::W, targetXYZ);
		mmia->enter();

		Component_vector_ptr newcomponentVector = fetchNewComponent(mmia, componentVector);

		return isDuplicateBlue100(newcomponentVector);
	    };

	    /*
	       ����smooth target�٬O���Ӱ��D, �N�Oluminance.
	       �{�b���@�k�O�έ쥻��Target White���G�רӲ���Luminance(�]�N�O�̤j�G��),
	       ����ڤW���Ƕ���Target White�w�g�Q����, �ҥH�̤j�G�פ]���P�F.
	       �Y�����H���Ƕ���Target White���̤j�G��, �������Ƕ��o�S�L�k���ͬۦP�G�פάۦP��׮y�Ъ�DG
	     */
	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTarget0(XYZ_ptr startXYZ, XYZ_ptr targetXYZ, XYZ_ptr endXYZ,
			   double_vector_ptr luminanceGammaCurve, int dimTurn, int brightTurn,
			   double dimGamma, double brightGamma, int brightWidth) {
		int size = luminanceGammaCurve->size();
		double_array dimendValues = targetXYZ->getxyValues();

		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim�Ϭq
		//==============================================================
		XYZ_vector_ptr dimResult = getDimGammaTarget(luminanceGammaCurve,
							     startXYZ,
							     targetXYZ, dimGamma,
							     dimTurn);
		int dimSize = dimResult->size();
		for (int x = 0; x < dimSize; x++) {
		    (*result)[x] = (*dimResult)[x];
		}
		//==============================================================

		//==============================================================
		// �����Ϭq
		//==============================================================
		for (int x = dimTurn; x < brightTurn; x++) {
		    //��Y���ܤ�
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x] = getTargetXYZ(dimendValues[0], dimendValues[1], Y);
		}
		//==============================================================

		//==============================================================
		// bright�Ϭq
		//==============================================================
		XYZ_vector_ptr brightResult = getBrightGammaTarget(luminanceGammaCurve,
								   targetXYZ,
								   endXYZ, brightGamma,
								   brightTurn, brightWidth,
								   bitDepth);
		int brightSize = brightResult->size();
		for (int x = 0; x < brightSize; x++) {
		    (*result)[x + brightTurn] = (*brightResult)[x];
		}
		//==============================================================
		return result;
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getDimGammaTarget(double_vector_ptr
				  luminanceGammaCurve,
				  XYZ_ptr startXYZ, XYZ_ptr endXYZ, double dimGamma, int dimTurn) {
		//==============================================================
		// dim�Ϭq
		//==============================================================
		XYZ_vector_ptr result(new XYZ_vector(dimTurn));
		double_array dimstartValues = startXYZ->getxyValues();
		double_array dimendValues = endXYZ->getxyValues();
		double dimbase = dimTurn - 1;

		for (int x = 0; x < dimTurn; x++) {
		    double normal = ((double) x) / dimbase;
		    double gamma = Math::pow(normal, dimGamma) * dimbase;
		    //�buv'�W�u���ܤ�
		    double u = Interpolation::linear(0, dimbase,
						     dimendValues[0],
						     dimstartValues[0],
						     gamma);
		    double v = Interpolation::linear(0, dimbase,
						     dimendValues[1],
						     dimstartValues[1],
						     gamma);
		    int index = dimbase - x;
		    double Y = (*luminanceGammaCurve)[index];

		    (*result)[index] = getTargetXYZ(u, v, Y);
		}
		//==============================================================
		return result;
	    };


	    XYZ_vector_ptr
		AdvancedDGLutGenerator::
		getBrightGammaTarget(double_vector_ptr
				     luminanceGammaCurve,
				     XYZ_ptr startXYZ,
				     XYZ_ptr endXYZ, double brightGamma,
				     int brightTurn, int brightWidth,
				     bptr < BitDepthProcessor > bitDepth) {
		//==============================================================
		// bright�Ϭq
		//==============================================================
		int size = luminanceGammaCurve->size();
		int brightEnd = brightTurn + brightWidth;
		int resultSize = size - brightTurn;
		XYZ_vector_ptr result(new XYZ_vector(resultSize));
		double_array brightstartValues = startXYZ->getxyValues();
		double_array brightendValues = endXYZ->getxyValues();
		double brightbase = brightEnd - 1 - brightTurn;

		for (int x = brightTurn; x < brightEnd; x++) {
		    double normal = ((double) x - brightTurn) / brightbase;
		    double gamma = Math::pow(normal, brightGamma) * brightbase + brightTurn;
		    //�buv'�W�u���ܤ�
		    double u = Interpolation::linear(brightTurn, brightEnd - 1,
						     brightstartValues[0],
						     brightendValues[0],
						     gamma);
		    double v = Interpolation::linear(brightTurn, brightEnd - 1,
						     brightstartValues[1],
						     brightendValues[1],
						     gamma);
		    double Y = (*luminanceGammaCurve)[x];

		    (*result)[x - brightTurn] = getTargetXYZ(u, v, Y);
		}
		XYZ_ptr XYZ = (*result)[brightEnd - 1 - brightTurn];
		for (int x = brightEnd; x < size; x++) {
		    (*result)[x - brightTurn] = XYZ;
		}
		return result;
		//==============================================================
	    };

	    void AdvancedDGLutGenerator::setUseMaxTargetBIntensity(bool useMaxTargetBIntensity) {
		this->useMaxTargetBIntensity = useMaxTargetBIntensity;
	    };
	    void AdvancedDGLutGenerator::setBTargetIntensity(double bTargetIntensity) {
		this->bTargetIntensity = bTargetIntensity;
	    }
	    void AdvancedDGLutGenerator::windowClosing() {
		stopMeasure = true;
	    };
	    void AdvancedDGLutGenerator::setMultiGen(bool enable, int times) {
		if (null == fetcher) {
		    throw IllegalStateException("null == fetcher");
		}
		this->multiGen = enable;
		this->multiGenTimes = times;
	    };
	    XYZ_vector_ptr AdvancedDGLutGenerator::getTargetXYZVector() {
		return targetXYZVector;
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1, double v2, double v3,
							 Domain domain) {
		double_array targetValues(new double[3]);
		targetValues[0] = v1;
		targetValues[1] = v2;
		targetValues[2] = v3;

		CIExyY targetxyY;
		switch (domain) {
		case CIExy:
		    targetxyY.setValues(targetValues);
		case CIEuv:
		    targetxyY.setuvYValues(targetValues);
		case CIEuvPrime:
		    targetxyY.setuvPrimeYValues(targetValues);
		};
		return targetxyY.toXYZ();
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1, double v2, double v3) {
		CIExyY targetxyY;
		targetxyY.x = v1;
		targetxyY.y = v2;
		targetxyY.Y = v3;
		return targetxyY.toXYZ();
	    };
	    bool AdvancedDGLutGenerator::isDuplicateBlue100(Component_vector_ptr componentVector) {
		int size = componentVector->size();
		int timesOfB100 = 0;
		for (int x = size - 1; x > 0; x--) {
		    Component_ptr c0 = (*componentVector)[x];
		    Component_ptr c1 = (*componentVector)[x - 1];
		    if (c0->intensity->B > 100
			&& c1->intensity->B < 100 || c0->intensity->B < 100
			&& c1->intensity->B > 100 ||
			//��n����100, ���ӫ���
			c0->intensity->B == 100 ||
			//�̫�@�ӹG��100, �]����100
			(c0->intensity->B > 99.0 && x == size - 1)) {
			timesOfB100++;
		    }
		}
		return timesOfB100 == 2;
	    };
	    void AdvancedDGLutGenerator::setAutoParameter(bool autoParameter) {
		this->autoParameter = autoParameter;
	    };
	    bool AdvancedDGLutGenerator::checkTargetXYZVector(XYZ_vector_ptr targetXYZVector,
							      int start, int end,
							      double deltaabThreshold) {
		int size = targetXYZVector->size();
		XYZ_ptr white = (*targetXYZVector)[size - 1];
		int checkSize = end - start;
		double_vector_ptr checkResult(new double_vector(checkSize));

		for (int x = start + 1; x < end; x++) {
		    XYZ_ptr x0 = (*targetXYZVector)[x - 1];
		    XYZ_ptr x1 = (*targetXYZVector)[x];
		    Lab_ptr lab0(new CIELab(x0, white));
		    Lab_ptr lab1(new CIELab(x1, white));
		    DeltaE de(lab0, lab1);
		    double dab = de.getCIE2000Deltaab();
		    (*checkResult)[x - (start + 1)] = dab;
		}
		double max = Math::max(checkResult);
		return max < deltaabThreshold;
	    };
	    int AdvancedDGLutGenerator::getAutoBrightTurn() {
		return autoBrightTurn;
	    };
	    int AdvancedDGLutGenerator::getAutoBrightWidth() {
		return autoBrightWidth;
	    };
	    void AdvancedDGLutGenerator::setComponentVector2(Component_vector_ptr componentVector2,
							     bptr < PanelRegulator >
							     panelRegulator2) {
		this->componentVector2 = componentVector2;
		this->panelRegulator2 = panelRegulator2;
	    };
	    void AdvancedDGLutGenerator::setPanelRegulator(bptr < PanelRegulator > panelRegulator) {
		this->panelRegulator1 = panelRegulator;
	    };
	    //==================================================================

	    //==================================================================
	    // DimTargetGenerator
	    //==================================================================
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve) {
		return getLinearTarget(startXYZ, endXYZ, luminanceGammaCurve, CIEuvPrime);
	    };
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve, Domain domain) {
		int size = luminanceGammaCurve->size();
		double_array startuvValues;
		double_array enduvValues;
		switch (domain) {
		case CIEuv:
		    startuvValues = startXYZ->getuvValues();
		    enduvValues = endXYZ->getuvValues();
		case CIEuvPrime:
		    startuvValues = startXYZ->getuvPrimeValues();
		    enduvValues = endXYZ->getuvPrimeValues();
		};
		XYZ_vector_ptr result(new XYZ_vector(size));
		for (int x = 0; x < size; x++) {
		    //�buv'�W�u���ܤ�
		    double u = Interpolation::linear(0, size - 1,
						     startuvValues[0], enduvValues[0], x);
		    double v = Interpolation::linear(0, size - 1,
						     startuvValues[1], enduvValues[1], x);
		    double Y = (*luminanceGammaCurve)[x];
		    double_array targetValues(new double[3]);
		    targetValues[0] = u;
		    targetValues[1] = v;
		    targetValues[2] = Y;
		    xyY_ptr targetxyY(new CIExyY());
		    switch (domain) {
		    case CIEuv:
			targetxyY->setuvYValues(targetValues);
		    case CIEuvPrime:
			targetxyY->setuvPrimeYValues(targetValues);
		    };
		    (*result)[x] = targetxyY->toXYZ();
		};
		return result;
	    }

	    XYZ_vector_ptr DimTargetGenerator::
		getGammaTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
			       double_vector_ptr luminanceGammaCurve, double gamma) {
		/* TODO : getGammaTarget */
	    };
	    //==================================================================
	};
    };
};

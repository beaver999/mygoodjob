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

	    //==================================================================
	    // AdvancedDGLutGenerator
	    //==================================================================
	    void AdvancedDGLutGenerator::
		setTargetBIntensity(double intensity) {
		this->targetBIntensity = targetBIntensity;
	    };
	     AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < IntensityAnalyzerIF >
				       analyzer):DimDGLutGenerator
		(componentVector, analyzer),
		useMaxTargetBIntensity(false), targetBIntensity(-1) {
	    };

	    RGB_vector_ptr AdvancedDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int dimTurn,
			int brightTurn, double dimGamma,
			double brightGamma) {
		return produce(targetWhite, luminanceGammaCurve, dimTurn,
			       brightTurn, dimGamma, brightGamma, false);
	    };

	    RGB_vector_ptr AdvancedDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int dimTurn,
			int brightTurn, double dimGamma,
			double brightGamma, bool avoidHook) {
		//==============================================================
		// ��T�ǳ�
		//==============================================================
		XYZ_ptr blackXYZ =
		    (*componentVector)[componentVector->size() - 1]->XYZ;
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;

		//�D�ؼЭȦ��u
		XYZ_vector_ptr targetXYZVector;

		if (avoidHook) {
		    targetXYZVector = getAvoidHookTarget(blackXYZ,
							 nativeWhite,
							 luminanceGammaCurve,
							 dimTurn,
							 brightTurn,
							 dimGamma);
		} else {
		    targetXYZVector = getTarget(blackXYZ,
						targetWhite,
						nativeWhite,
						luminanceGammaCurve,
						dimTurn, brightTurn,
						dimGamma, brightGamma);
		}
		STORE_XYZXY_VECTOE("target.xls", targetXYZVector);
		//==============================================================
		int size = targetXYZVector->size();
		RGB_vector_ptr result(new RGB_vector(size));

		//primary color�u���target white~
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);
		//double targetBIntensity = -1;

		for (int x = size - 1; x != -1; x--) {
		    XYZ_ptr targetXYZ = (*targetXYZVector)[x];
		    bptr < MaxMatrixIntensityAnayzer >
			mmia(new MaxMatrixIntensityAnayzer());

		    mmia->setupComponent(Channel::R, rxyY->toXYZ());
		    mmia->setupComponent(Channel::G, gxyY->toXYZ());
		    mmia->setupComponent(Channel::B, bxyY->toXYZ());
		    mmia->setupComponent(Channel::W, targetXYZ);
		    mmia->enter();

		    Component_vector_ptr newcomponentVector =
			fetchComponent(mmia, componentVector);
#ifdef DEBUG_CCTLUT_NEWMETHOD
		    STORE_COMPONENT(_toString(x) + ".xls",
				    newcomponentVector);
#endif
		    DGLutGenerator lutgen(newcomponentVector);
		    //��100��?
		    if (targetBIntensity == -1) {
			targetBIntensity =
			    useMaxTargetBIntensity ? lutgen.
			    getMaxBIntensity() : 100;
		    };
		    RGB_ptr rgb = lutgen.getDGCode(100, 100,
						   targetBIntensity);
		    (*result)[x] = rgb;
		};

		return result;
	    };
	    bool AdvancedDGLutGenerator::isAvoidHook(XYZ_ptr targetXYZ,
						     double offsetK) {
		XYZ_ptr XYZOffset = getXYZ(targetXYZ, offsetK);
		return isDuplicateBlue100(XYZOffset);
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getXYZ(XYZ_ptr XYZ,
						   double offsetK) {
		//==============================================================
		// ���Ʒǳ�
		//==============================================================
		xyY_ptr xyY(new CIExyY(XYZ));
		double cct =
		    CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		xyY_ptr xyYOriginal =
		    CorrelatedColorTemperature::CCT2DIlluminantxyY(cct);
		double cctOffset = cct + offsetK;
		xyY_ptr xyYOffset =
		    CorrelatedColorTemperature::
		    CCT2DIlluminantxyY(cctOffset);
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
	    bool AdvancedDGLutGenerator::
		isDuplicateBlue100(XYZ_ptr targetXYZ) {
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

		bptr < MaxMatrixIntensityAnayzer >
		    mmia(new MaxMatrixIntensityAnayzer());
		mmia->setupComponent(Channel::R, rxyY->toXYZ());
		mmia->setupComponent(Channel::G, gxyY->toXYZ());
		mmia->setupComponent(Channel::B, bxyY->toXYZ());
		mmia->setupComponent(Channel::W, targetXYZ);
		mmia->enter();

		Component_vector_ptr newcomponentVector =
		    fetchComponent(mmia, componentVector);

		return isDuplicateBlue100(newcomponentVector);
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getAvoidHookTarget(XYZ_ptr startXYZ, XYZ_ptr targetXYZ,
				   double_vector_ptr luminanceGammaCurve,
				   int dimTurn, int brightTurn,
				   double dimGamma) {
		int size = luminanceGammaCurve->size();
		double_array dimendValues = targetXYZ->getxyValues();

		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim�Ϭq
		//==============================================================
		XYZ_vector_ptr dimResult =
		    getDimGammaTarget(luminanceGammaCurve, startXYZ,
				      targetXYZ, dimGamma, dimTurn);
		int dimSize = dimResult->size();
		for (int x = 0; x < dimSize; x++) {
		    (*result)[x] = (*dimResult)[x];
		}
		//==============================================================

		//==============================================================
		// �����Ϭq+bright�Ϭq
		//==============================================================
		for (int x = dimTurn; x < size; x++) {
		    //��Y���ܤ�
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x] =
			getTargetXYZ(dimendValues[0], dimendValues[1], Y);
		}
		//==============================================================

		//==============================================================
		// bright�Ϭq
		//==============================================================
		for (int x = size - 1; x >= brightTurn; x--) {
		    XYZ_ptr XYZ = (*result)[x];
		    if (!isDuplicateBlue100(XYZ)) {
			int offsetK = 0;
			for (int x = 10; x < 3000; x += 10) {
			    if (isAvoidHook(XYZ, x)) {
				//�Y�i�H�קK�N���}
				offsetK = x;
				break;
			    }
			}
			(*result)[x] = getXYZ(XYZ, offsetK);
		    }
		}
		//==============================================================
		return result;
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTarget(XYZ_ptr startXYZ,
			  XYZ_ptr targetXYZ,
			  XYZ_ptr endXYZ,
			  double_vector_ptr
			  luminanceGammaCurve,
			  int dimTurn,
			  int brightTurn,
			  double dimGamma, double brightGamma) {
		int size = luminanceGammaCurve->size();
		double_array dimendValues = targetXYZ->getxyValues();

		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim�Ϭq
		//==============================================================
		XYZ_vector_ptr dimResult =
		    getDimGammaTarget(luminanceGammaCurve, startXYZ,
				      targetXYZ, dimGamma, dimTurn);
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
		    (*result)[x] =
			getTargetXYZ(dimendValues[0], dimendValues[1], Y);
		}
		//==============================================================

		//==============================================================
		// bright�Ϭq
		//==============================================================
		XYZ_vector_ptr brightResult =
		    getBrightGammaTarget(luminanceGammaCurve, targetXYZ,
					 endXYZ, brightGamma, brightTurn);
		int brightSize = brightResult->size();
		for (int x = 0; x < brightSize; x++) {
		    (*result)[x + brightTurn] = (*brightResult)[x];
		}
		//==============================================================
		return result;
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getDimGammaTarget(double_vector_ptr luminanceGammaCurve,
				  XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				  double dimGamma, int dimTurn) {
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
		getBrightGammaTarget(double_vector_ptr luminanceGammaCurve,
				     XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				     double brightGamma, int brightTurn) {
		//==============================================================
		// bright�Ϭq
		//==============================================================
		int size = luminanceGammaCurve->size();
		int resultSize = size - brightTurn;
		XYZ_vector_ptr result(new XYZ_vector(resultSize));
		double_array brightstartValues = startXYZ->getxyValues();
		double_array brightendValues = endXYZ->getxyValues();
		double brightbase = size - 1 - brightTurn;

		for (int x = brightTurn; x < size; x++) {
		    double normal = ((double) x - brightTurn) / brightbase;
		    double gamma = Math::pow(normal,
					     brightGamma) * brightbase +
			brightTurn;
		    //�buv'�W�u���ܤ�
		    double u = Interpolation::linear(brightTurn, size - 1,
						     brightstartValues[0],
						     brightendValues[0],
						     gamma);
		    double v = Interpolation::linear(brightTurn, size - 1,
						     brightstartValues[1],
						     brightendValues[1],
						     gamma);
		    double Y = (*luminanceGammaCurve)[x];

		    //(*result)[x] = getTargetXYZ(u, v, Y);
		    (*result)[x - brightTurn] = getTargetXYZ(u, v, Y);
		}
		return result;
		//==============================================================
	    };

	    void AdvancedDGLutGenerator::
		setUseMaxTargetBIntensity(bool useMaxTargetBIntensity) {
		this->useMaxTargetBIntensity = useMaxTargetBIntensity;
	    };

	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1,
							 double v2,
							 double v3,
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
	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1,
							 double v2,
							 double v3) {
		CIExyY targetxyY;
		targetxyY.x = v1;
		targetxyY.y = v2;
		targetxyY.Y = v3;
		return targetxyY.toXYZ();
	    };
	    bool AdvancedDGLutGenerator::
		isDuplicateBlue100(Component_vector_ptr componentVector) {
		int size = componentVector->size();
		int timesOfB100 = 0;
		for (int x = size - 1; x > 0; x--) {
		    Component_ptr c0 = (*componentVector)[x];
		    Component_ptr c1 = (*componentVector)[x - 1];
		    if (c0->intensity->B > 100 && c1->intensity->B < 100 ||
			c0->intensity->B < 100 && c1->intensity->B > 100 ||
			//��n����100, ���ӫ���
			c0->intensity->B == 100 ||
			//�̫�@�ӹG��100, �]����100
			(c0->intensity->B > 99.0 && x == size - 1)) {
			timesOfB100++;
		    }
		}
		return timesOfB100 == 2;
	    };


	    //==================================================================
	    //==================================================================
	    // DimTargetGenerator
	    //==================================================================
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve) {
		return getLinearTarget(startXYZ, endXYZ,
				       luminanceGammaCurve, CIEuvPrime);
	    };
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr
				luminanceGammaCurve, Domain domain) {
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
						     startuvValues[0],
						     enduvValues[0],
						     x);
		    double v = Interpolation::linear(0, size - 1,
						     startuvValues[1],
						     enduvValues[1],
						     x);
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
			       double_vector_ptr
			       luminanceGammaCurve, double gamma) {
	    };
	    //==================================================================
	};
    };
};


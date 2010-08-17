#include <includeall.h>
#pragma hdrstop
#include "dimdg.h"


//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::colorformat;
	    /*
	       �NcomponentVector�Hanalyzer���s�p��Component
	     */
	    Component_vector_ptr DimDGLutGenerator::fetchNewComponent(bptr <
								      MaxMatrixIntensityAnayzer
								      >
								      analyzer,
								      Component_vector_ptr
								      componentVector) {
		Component_vector_ptr result(new Component_vector());
		//��������
		 foreach(const Component_ptr c, *componentVector) {
		    RGB_ptr intensity = analyzer->getIntensity(c->XYZ);
		    Component_ptr component(new Component(c->rgb, intensity, c->XYZ));
		     result->push_back(component);
		};
		 return result;
	    };
	    XYZ_vector_ptr DimDGLutGenerator::getTarget(XYZ_ptr startXYZ,
							XYZ_ptr endXYZ,
							double_vector_ptr luminanceGammaCurve) {
		XYZ_vector_ptr targetXYZVector =
		    DimTargetGenerator::getLinearTarget(startXYZ, endXYZ, luminanceGammaCurve);
		 return targetXYZVector;
	    };
	    XYZ_vector_ptr DimDGLutGenerator::getTarget(XYZ_ptr startXYZ,
							XYZ_ptr endXYZ,
							double_vector_ptr
							luminanceGammaCurve, double gamma) {
		XYZ_vector_ptr targetXYZVector =
		    DimTargetGenerator::getGammaTarget(startXYZ, endXYZ,
						       luminanceGammaCurve,
						       gamma);
		return targetXYZVector;
	    };
	  DimDGLutGenerator::DimDGLutGenerator(Component_vector_ptr componentVector, bptr < IntensityAnalyzerIF > analyzer):componentVector(componentVector),
		analyzer(analyzer)
	    {
	    };
	    RGB_vector_ptr DimDGLutGenerator::
		produce(XYZ_ptr targetWhite, double_vector_ptr luminanceGammaCurve, int under) {
		return produce(targetWhite, luminanceGammaCurve, -1);
	    };

	    RGB_vector_ptr DimDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int under, double gamma) {
		using namespace Dep;
		//==============================================================
		// ��T�ǳ�
		//==============================================================
		XYZ_ptr blackXYZ = (*componentVector)
		    [componentVector->size() - 1]->XYZ;
		int size = under - 1;
		double_vector_ptr partGammaCurve = DoubleArray::getRangeCopy(luminanceGammaCurve,
									     0, size);
		//�D�ؼЭȦ��u
		XYZ_vector_ptr targetXYZVector = gamma != -1 ?
		    getTarget(blackXYZ, targetWhite, partGammaCurve, gamma)
		    : getTarget(blackXYZ, targetWhite, partGammaCurve);
		STORE_XYZXY_VECTOE("target.xls", targetXYZVector);
		//==============================================================
		RGB_vector_ptr result(new RGB_vector());
		//primary color�u���target white~
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

		foreach(const XYZ_ptr targetXYZ, *targetXYZVector) {
		    bptr < MaxMatrixIntensityAnayzer > analyzer(new MaxMatrixIntensityAnayzer());
		    analyzer->setupComponent(Channel::R, rxyY->toXYZ());
		    analyzer->setupComponent(Channel::G, gxyY->toXYZ());
		    analyzer->setupComponent(Channel::B, bxyY->toXYZ());
		    analyzer->setupComponent(Channel::W, targetXYZ);
		    analyzer->enter();
		    Component_vector_ptr
			newcomponentVector = fetchNewComponent(analyzer, componentVector);
		    //STORE_COMPONENT(_toString(x++) + ".xls",
		    //newcomponentVector);
		    DGLutGenerator lutgen(newcomponentVector);
		    //��100��?
		    RGB_ptr rgb = lutgen.getDGCode(100, 100, 100);
		    result->push_back(rgb);
		};
		return result;
	    };
	};
    };
};

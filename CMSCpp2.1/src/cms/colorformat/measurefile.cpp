#include <includeall.h>
#pragma hdrstop
#include "measurefile.h"
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace colorformat {
	using namespace Dep;
	using namespace Indep;
	using namespace java::lang;
	using namespace cms::util;
	const std::string & RampMeasureFile::Sheet1 = "Sheet1";
	const std::string & RampMeasureFile::Sheet2 = "Sheet2";

	 RampMeasureFile::RampMeasureFile(const std::string & fileName,
					  const Mode mode):ExcelAccessBase(fileName, mode) {
	    initSheet(Sheet1, 18, "Gray Level", "W_x", "W_y", "W_Y (nit)",
		      "W_CCT", "�GUV", "W_R", "W_G", "W_B", "R_x", "R_y",
		      "R_Y (nit)", "G_x", "G_y", "G_Y (nit)", "B_x", "B_y", "B_Y (nit)");
	    initSheet(Sheet2, 18, "Gray Level", "W_X", "W_Y (nit)", "W_Z",
		      "W_CCT", "�GUV", "W_R", "W_G", "W_B", "R_X", "R_Y (nit)",
		      "R_Z", "G_X", "G_Y (nit)", "G_Z", "B_X", "B_Y (nit)", "B_Z");
	};

	int RampMeasureFile::
	    getMaximumSize(Component_vector_ptr wMeasureData,
			   Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData) {
	    using namespace math;
	    int wsize = wMeasureData != null ? wMeasureData->size() : 0;
	    int rsize = rMeasureData != null ? rMeasureData->size() : 0;
	    int gsize = gMeasureData != null ? gMeasureData->size() : 0;
	    int bsize = bMeasureData != null ? bMeasureData->size() : 0;
	    int_array sizes(new int[4]);
	     sizes[0] = wsize;
	     sizes[1] = rsize;
	     sizes[2] = gsize;
	     sizes[3] = bsize;
	     return IntArray::max(sizes, 4);
	};

	void RampMeasureFile::
	    setMeasureData(Component_vector_ptr wMeasureData,
			   Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData) {
	    setMeasureData(wMeasureData, rMeasureData, gMeasureData, bMeasureData, false);
	    //==================================================================
	    // �ˬd�ӷ����
	    //==================================================================
	    /*int size = getMaximumSize(wMeasureData, rMeasureData,
	       gMeasureData, bMeasureData);
	       //==================================================================
	       //==================================================================
	       // ��l��Ƴ]�w
	       //==================================================================
	       string_vector_ptr values(new string_vector(18));
	       //==================================================================
	       //==================================================================
	       // �j��B�z
	       //==================================================================
	       for (int x = 0; x < size; x++) {
	       if (wMeasureData != null) {
	       Component_ptr c = (*wMeasureData)[x];
	       int w = static_cast < int >(c->rgb->getValue(Channel::W));
	       (*values)[0] = _toString(w);
	       xyY_ptr xyY(new CIExyY(c->XYZ));
	       (*values)[1] = _toString(xyY->x);
	       (*values)[2] = _toString(xyY->y);
	       (*values)[3] = _toString(xyY->Y);
	       double cct = CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
	       //�p��X�Ӫ�cct�O�_���N�q 

	       (*values)[4] = _toString(static_cast < int >(cct));

	       double duv = CorrelatedColorTemperature::getduvWithDIlluminant(c->XYZ);
	       (*values)[5] = _toString(duv);

	       RGB_ptr intensity = c->intensity;
	       if (null != intensity) {
	       (*values)[6] = _toString(intensity->R);
	       (*values)[7] = _toString(intensity->G);
	       (*values)[8] = _toString(intensity->B);
	       } else {
	       StringVector::setContent(values, "0", 3, 6, 7, 8);
	       }
	       }
	       else {
	       StringVector::setContent(values, "0", 9, 0, 1, 2, 3, 4, 5, 6, 7, 8);
	       }

	       if (rMeasureData != null) {
	       Patch_ptr p = (*rMeasureData)[x];
	       xyY_ptr rxyY(new CIExyY(p->getXYZ()));
	       (*values)[9] = _toString(rxyY->x);
	       (*values)[10] = _toString(rxyY->y);
	       (*values)[11] = _toString(rxyY->Y);
	       } else {
	       StringVector::setContent(values, "0", 3, 9, 10, 11);
	       }
	       if (gMeasureData != null) {
	       Patch_ptr p = (*gMeasureData)[x];
	       xyY_ptr gxyY(new CIExyY(p->getXYZ()));
	       (*values)[12] = _toString(gxyY->x);
	       (*values)[13] = _toString(gxyY->y);
	       (*values)[14] = _toString(gxyY->Y);
	       } else {
	       StringVector::setContent(values, "0", 3, 12, 13, 14);
	       }
	       if (bMeasureData != null) {
	       Patch_ptr p = (*bMeasureData)[x];
	       xyY_ptr bxyY(new CIExyY(p->getXYZ()));
	       (*values)[15] = _toString(bxyY->x);
	       (*values)[16] = _toString(bxyY->y);
	       (*values)[17] = _toString(bxyY->Y);
	       } else {
	       StringVector::setContent(values, "0", 3, 15, 16, 17);
	       }

	       this->insertData(Sheet1, values, false);
	       }
	     */ }

	void RampMeasureFile::
	    setMeasureData(Component_vector_ptr wMeasureData,
			   Patch_vector_ptr rMeasureData,
			   Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData,
			   bool XYZMode) {
	    //==================================================================
	    // �ˬd�ӷ����
	    //==================================================================
	    int size = getMaximumSize(wMeasureData, rMeasureData,
				      gMeasureData, bMeasureData);
	    //==================================================================
	    //==================================================================
	    // ��l��Ƴ]�w
	    //==================================================================
	    string_vector_ptr values(new string_vector(18));
	    //==================================================================
	    //==================================================================
	    // �j��B�z
	    //==================================================================
	    for (int x = 0; x < size; x++) {
		if (wMeasureData != null) {
		    Component_ptr c = (*wMeasureData)[x];
		    int w = static_cast < int >(c->rgb->getValue(Channel::W));
		    (*values)[0] = _toString(w);
		    double_array XYZValues = getValues(c->XYZ, XYZMode);
		    (*values)[1] = _toString(XYZValues[0]);
		    (*values)[2] = _toString(XYZValues[1]);
		    (*values)[3] = _toString(XYZValues[2]);
		    xyY_ptr xyY(new CIExyY(c->XYZ));
		    double cct = CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		    //�p��X�Ӫ�cct�O�_���N�q 
		    /*cct =
		       CorrelatedColorTemperature::
		       isCCTMeaningful(xyY) ? cct : -1; */
		    cct = cct > 40000 ? -1 : cct;
		    (*values)[4] = _toString(static_cast < int >(cct));

		    double duv = CorrelatedColorTemperature::getduvWithDIlluminant(c->XYZ);
		    (*values)[5] = _toString(duv);

		    RGB_ptr intensity = c->intensity;
		    if (null != intensity) {
			(*values)[6] = _toString(intensity->R);
			(*values)[7] = _toString(intensity->G);
			(*values)[8] = _toString(intensity->B);
		    } else {
			StringVector::setContent(values, "0", 3, 6, 7, 8);
		    }
		} else {
		    StringVector::setContent(values, "0", 9, 0, 1, 2, 3, 4, 5, 6, 7, 8);
		}

		if (rMeasureData != null) {
		    Patch_ptr p = (*rMeasureData)[x];
		    double_array XYZValues = getValues(p->getXYZ(), XYZMode);
		    (*values)[9] = _toString(XYZValues[0]);
		    (*values)[10] = _toString(XYZValues[1]);
		    (*values)[11] = _toString(XYZValues[2]);
		} else {
		    StringVector::setContent(values, "0", 3, 9, 10, 11);
		}
		if (gMeasureData != null) {
		    Patch_ptr p = (*gMeasureData)[x];
		    double_array XYZValues = getValues(p->getXYZ(), XYZMode);
		    (*values)[12] = _toString(XYZValues[0]);
		    (*values)[13] = _toString(XYZValues[1]);
		    (*values)[14] = _toString(XYZValues[2]);
		} else {
		    StringVector::setContent(values, "0", 3, 12, 13, 14);
		}
		if (bMeasureData != null) {
		    Patch_ptr p = (*bMeasureData)[x];
		    double_array XYZValues = getValues(p->getXYZ(), XYZMode);
		    (*values)[15] = _toString(XYZValues[0]);
		    (*values)[16] = _toString(XYZValues[1]);
		    (*values)[17] = _toString(XYZValues[2]);
		} else {
		    StringVector::setContent(values, "0", 3, 15, 16, 17);
		}

		this->insertData(XYZMode ? Sheet2 : Sheet1, values, false);
	    }
	}
	double_array RampMeasureFile::getValues(XYZ_ptr XYZ, bool XYZMode) {
	    double_array values(new double[3]);
	    if (XYZMode) {
		XYZ->getValues(values);
	    } else {
		CIExyY xyY(XYZ);
		xyY.getValues(values);
	    }
	    return values;
	}

	//==================================================================
    };
};


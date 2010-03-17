#include <includeall.h>
#pragma hdrstop
#include "rgbvectorop.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/util/rgbarray.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    //==================================================================
	    using namespace Dep;
	    using namespace cms::util;
	    RGB_vector_ptr LinearOp::getRendering(RGB_vector_ptr source) {

		int size = source->size();
		RGB_vector_ptr result(new RGB_vector());
		for (int x = 0; x < size; x++) {
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb2->G = rgb2->B = x;
		     result->push_back(rgb2);
		};
		 return result;
	    };
	    //==================================================================

	    //==================================================================
	    RGB_vector_ptr MinusOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result(new RGB_vector());
		 foreach(RGB_ptr rgb, *source) {
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb->R - minusValue;
		     rgb2->G = rgb->G - minusValue;
		     rgb2->B = rgb->B - minusValue;
		     result->push_back(rgb2);
		};
		return result;
	    };
	  MinusOp::MinusOp(double minusValue):minusValue(minusValue)
	    {
	    };
	    //==================================================================
	    // P1P2DGOp
	    //==================================================================
	    RGB_vector_ptr P1P2DGOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGB_ptr rgbp1 = (*result)[p1];

		for (int x = 0; x != p1; x++) {
		    double v = x * rgbp1->G / p1;
		    double d = java::lang::Math::roundTo(v * 4);
		    RGB_ptr rgb = (*result)[x];
		    rgb->setValues(v, v, v);
		    rgb->quantization(maxValue);
                    double d2=rgb->getValue(Channel::G);
		}

		//if (true == smooth) {
		RGB_ptr rgbp0 = (*result)[p1 - 1];
		//RGB_ptr rgbp1 = (*result)[p1];
		RGB_ptr rgbp2 = (*result)[p1 + 1];
		rgbp1->R = (rgbp0->R + rgbp2->R) / 2;
		rgbp1->G = (rgbp0->G + rgbp2->G) / 2;
		rgbp1->B = (rgbp0->B + rgbp2->B) / 2;
		rgbp1->quantization(maxValue);
		//};

		return result;
	    };
	  P1P2DGOp::P1P2DGOp(double p1, double p2, const MaxValue & maxValue):p1(p1), p2(p2), maxValue(maxValue)
	    {
	    };
	    //==================================================================

	    //==================================================================
	    // RBInterpolation
	    //==================================================================
	    RGB_vector_ptr RBInterpolationOp::
		getRendering(RGB_vector_ptr source) {
		//int size = source->size();

		double rInterval = (*source)[under]->R / under;
		double gInterval = (*source)[under]->G / under;
		double bInterval = (*source)[under]->B / under;
		RGB_vector_ptr result = RGBVector::deepClone(source);


		for (int x = 0; x != under; x++) {
		    //做RB interpolation
		    RGB_ptr rgb = (*result)[x];

		    rgb->R = rInterval * x;
		    rgb->G = gInterval * x;
		    rgb->B = bInterval * x;
		}
		return result;
	    };
	  RBInterpolationOp::RBInterpolationOp(double under):under(under)
	    {
	    };
	    //==================================================================

	    //==================================================================
	    BMaxOp::BMaxOp(const Dep::MaxValue & out):out(out) {

	    };
	    RGB_vector_ptr BMaxOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		int size = result->size();
		RGB_ptr bmax = (*result)[size - 1];
		if (out == MaxValue::Int6Bit) {
		    bmax->B = 252;
		} else if (out == MaxValue::Int8Bit) {
		    bmax->B = 255;
		}


		for (int x = size - 1; x != 1; x--) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr nextrgb = (*result)[x - 1];
		    double diff = x > 252 ? 10 : (x > 232 ? 8 : 6);

		    if (rgb->B > nextrgb->B) {
			nextrgb->B = rgb->B - diff;
		    } else {
			rgb->B =
			    ((*result)[x + 1]->B +
			     (*result)[x - 1]->B) / 2;
			break;
		    }


		}

		return result;
	    };
	    //==================================================================
	    RGB_vector_ptr GByPassOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		if (in == MaxValue::Int8Bit && out == MaxValue::Int6Bit) {
		    for (int x = 0; x != 245; x++) {
			(*result)[x]->G = x;
		    };
		    for (int x = 245; x != 251; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 0.5;
		    };
		    for (int x = 251; x != 256; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 1;
		    };
		} else if (in == MaxValue::Int6Bit
			   && out == MaxValue::Int6Bit) {
		    for (int x = 0; x != 252; x++) {
			(*result)[x]->G = x;
		    };
		    for (int x = 252; x != 256; x++) {
			(*result)[x]->G = 252;
		    };
		}
		return result;
	    };

	  GByPassOp::GByPassOp(const Dep::MaxValue & in, const Dep::MaxValue & out):in(in),
		out(out)
	    {

	    };
	    //==================================================================
	    RGB_vector_ptr FrcNROp::getRendering(RGB_vector_ptr source) {
		int size = source->size();
		RGB_vector_ptr result = RGBVector::clone(source);

		RGB_ptr rgb255 = (*result)[255];

		foreach(const Channel & ch, *Channel::RGBChannel) {
		    if (rgb255->getValue(ch) >= 248.5) {
			(*source)[255]->setValue(ch, 252);
			(*source)[254]->setValue(ch, 250);
			(*source)[253]->setValue(ch, 248);

			for (int x = 252; x != -1; x--) {
			    RGB_ptr thisRGB = (*source)[x];
			    RGB_ptr nextRGB = (*source)[x + 1];
			    if (thisRGB->getValue(ch) >=
				nextRGB->getValue(ch)) {
				thisRGB->setValue(ch, nextRGB->
						  getValue(ch) - 2);
			    } else {
				break;
			    }
			}
		    }
		}

		for (int x = 1; x != 31; x++) {
		    RGB_ptr rgb = (*source)[x];
		}
	    };
	    //==================================================================
	};
    };
};


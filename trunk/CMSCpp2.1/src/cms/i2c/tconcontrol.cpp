#include <includeall.h>
#pragma hdrstop
#include "tconcontrol.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace i2c {
	using namespace cms::util;
	 TCONControl::TCONControl(bptr < TCONParameter >
				  parameter,
				  bptr < i2cControl >
				  control):parameter(parameter),
	    control(control), dualTCON(false) {

	};
	 TCONControl::TCONControl(bptr < TCONParameter > parameter,
				  bptr < i2cControl > control1,
				  bptr < i2cControl >
				  control2):parameter(parameter),
	    control(control1), control2(control2), dualTCON(true) {

	};
	void TCONControl::setTestRGB(RGB_ptr rgb) {
	    //double_array rgbValues(new double[3]);
	    //rgb->getValues(rgbValues/*, Dep::MaxValue::Int12Bit*/);
	    int r = _toInt(rgb->R);
	    int g = _toInt(rgb->G);
	    int b = _toInt(rgb->B);
	    setTestRGB(r, g, b);
	    /*bptr < ByteBuffer > data;

	       if (parameter->isIndependentRGB()) {
	       //�p�Gtest RGB�U�ۿW��
	       //BBLL 00BH GGLL 00GH RRLL 00RH
	       data.reset(new ByteBuffer(6));
	       (*data)[0] = r >> 8;
	       (*data)[1] = r & 255;
	       (*data)[2] = g >> 8;
	       (*data)[3] = g & 255;
	       (*data)[4] = b >> 8;
	       (*data)[5] = b & 255;

	       } else {
	       //�p�Gtest RGB�S���W��
	       //00BH BBLL GGLL GHRH RRLL
	       data.reset(new ByteBuffer(5));
	       (*data)[0] = r & 255;
	       (*data)[1] = r >> 8 + g >> 8 & 15 << 4;
	       (*data)[2] = g & 255;
	       (*data)[3] = b & 255;
	       (*data)[4] = g >> 8 & 15;
	       }
	       int address = parameter->getTestRGBAddress();
	       control->write(address, data);
	       if (true == dualTCON) {
	       control2->write(address, data);
	       } */
	};
	void TCONControl::setTestRGB(int r, int g, int b) {
	    /*int r = _toInt(rgb->R);
	       int g = _toInt(rgb->G);
	       int b = _toInt(rgb->B); */
	    bptr < ByteBuffer > data;

	    if (parameter->isIndependentRGB()) {
		//�p�Gtest RGB�U�ۿW��
		//BBLL 00BH GGLL 00GH RRLL 00RH
		data.reset(new ByteBuffer(6));
		(*data)[0] = r >> 8;
		(*data)[1] = r & 255;
		(*data)[2] = g >> 8;
		(*data)[3] = g & 255;
		(*data)[4] = b >> 8;
		(*data)[5] = b & 255;

	    } else {
		//�p�Gtest RGB�S���W��
		//00BH BBLL GGLL GHRH RRLL
		data.reset(new ByteBuffer(5));
		(*data)[0] = r & 255;
		(*data)[1] = r >> 8 + g >> 8 & 15 << 4;
		(*data)[2] = g & 255;
		(*data)[3] = b & 255;
		(*data)[4] = g >> 8 & 15;
	    }
	    int address = parameter->getTestRGBAddress();
	    control->write(address, data);
	    if (true == dualTCON) {
		control2->write(address, data);
	    }
	};
	void TCONControl::setGammaTest(bool enable) {
	    int address = parameter->getGammaTestAddress();
	    unsigned char bit = parameter->getGammaTestBit();
	    unsigned char data = enable << (bit - 1);
	    control->writeByte(address, data);
	    if (true == dualTCON) {
		control2->writeByte(address, data);
	    }
	};

	unsigned char TCONControl::readByte(int dataAddress) {
	    return control->readByte(dataAddress);
	};
	void TCONControl::writeByte(int dataAddress, unsigned char data) {
	    control->writeByte(dataAddress, data);
	    if (true == dualTCON) {
		control2->writeByte(dataAddress, data);
	    }
	};
	const Dep::MaxValue & TCONControl::getLUTBit() {
	    return parameter->getLUTBit();
	};
    };
};


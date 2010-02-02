#include "whitefinder.h"

//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���
//#include <cms/colorspace/rgb.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	     WhitePointFinder::
		WhitePointFinder(MeterMeasurement & mm):mm(mm) {
	    };

	    RGB_ptr WhitePointFinder::findRB(xyY_ptr xyY) {

	    };
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {

	    };
	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {

	    };

	    /*
	       ���I�M��y�{

	       �ѩ�ʥFmodel�i�H�w���A�����I,
	       1. �]�������G�HR&B�M�䥿�T���I
	       2. �M��A�վ�White��RGB�䤤�@�I��255.
	       �A�H���ץ��᪺��, �ץ���l�D255�����I, �Ϧ�׹F��̱����.
	     */
	    RGB_ptr WhitePointFinder::findRGB(xyY_ptr xyY) {
		RGB_ptr initRGB = findRB(xyY);
		RGB_ptr fixRGB = fixRGB2TouchMax(initRGB);
		RGB_ptr finalRGB = findMatchRGB(xyY, fixRGB);
		return finalRGB;
	    };
	};

    };
};


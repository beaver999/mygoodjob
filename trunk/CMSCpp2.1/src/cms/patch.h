#ifndef PATCHH
#define PATCHH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <cms/util/util.h>

namespace cms {
    class Patch:public jObject, cms::util::NameIF {

      protected:
	bptr < std::string > name;
	//CIELab _Lab = null;
	XYZ_ptr XYZ;
	XYZ_ptr normalizedXYZ;
	RGB_ptr rgb;
	RGB_ptr intensity;
	//shared_ptr < RGBColor > originalRGB = null;
	 bptr < Spectra > spectra;
	 bptr < Spectra > reflectSpectra;
      public:
	 Patch(bptr < std::string > name,
	       XYZ_ptr XYZ, XYZ_ptr normalizedXYZ, RGB_ptr rgb);
	 Patch(bptr < std::string > name,
	       XYZ_ptr XYZ,
	       XYZ_ptr normalizedXYZ, RGB_ptr rgb, RGB_ptr intensity);
	 bptr < std::string > getName();
	XYZ_ptr getXYZ();
	XYZ_ptr getNormalizedXYZ();
	RGB_ptr getRGB();
	RGB_ptr getIntensity();
    };

};
#endif

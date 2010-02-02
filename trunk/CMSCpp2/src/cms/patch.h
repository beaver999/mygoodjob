#ifndef PATCHH
#define PATCHH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <util.h>

namespace cms {

    /*using std::string;
       using namespace boost;
       using java::lang::Object;
       using util::NameIF;
       using cms::colorspace::RGBColor;
       using cms::colorspace::CIEXYZ; */

    class Patch:public java::lang::Object, util::NameIF {

      protected:
	bptr < std::string > name;
	//CIELab _Lab = null;
	XYZ_ptr XYZ;
	XYZ_ptr normalizedXYZ;
	RGB_ptr rgb;
	//shared_ptr < RGBColor > originalRGB = null;
	bptr < Spectra > spectra;
	bptr < Spectra > reflectSpectra;
      public:
	Patch(bptr < std::string > name,
	      XYZ_ptr XYZ,
	      XYZ_ptr normalizedXYZ,
	      RGB_ptr rgb);
	bptr < std::string > getName();
	XYZ_ptr getXYZ();
	XYZ_ptr getNormalizedXYZ();
	RGB_ptr getRGB();
    };

};
#endif


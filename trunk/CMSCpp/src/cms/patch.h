#ifndef PATCHH
#define PATCHH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <util.h>

namespace cms {

    class Spectra;
    namespace colorspace {
	class RGBColor;
	class CIEXYZ;
    };
};

namespace cms {

    using std::string;
    using namespace boost;
    using java::lang::Object;
    using util::NameIF;
    using cms::colorspace::RGBColor;
    using cms::colorspace::CIEXYZ;

    class Patch:public Object, NameIF {

      protected:
	shared_ptr < string > name;
	//CIELab _Lab = null;
	shared_ptr < CIEXYZ > XYZ;
	shared_ptr < CIEXYZ > normalizedXYZ;
	shared_ptr < RGBColor > rgb;
	//shared_ptr < RGBColor > originalRGB = null;
	shared_ptr < Spectra > spectra;
	shared_ptr < Spectra > reflectSpectra;
      public:
	Patch(shared_ptr < string > name, shared_ptr < CIEXYZ > XYZ,
	      shared_ptr < CIEXYZ > normalizedXYZ,
	      shared_ptr < RGBColor > rgb);
    };

};
#endif


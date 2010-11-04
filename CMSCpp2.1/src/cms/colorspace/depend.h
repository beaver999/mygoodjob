#ifndef DEPENDH
#define DEPENDH

//C系統文件
#include <cstdarg>
//C++系統文件

//其他庫頭文件
#include <vcl.h>
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <tnt/tnt_array2d.h>
#ifdef __BORLANDC__
# pragma pack(pop)
#endif

//本項目內頭文件
#include <cms/core.h>
#include "colorspace.h"

#define MaxValue_vector std::vector < MaxValue >

namespace cms {
    namespace colorspace {

	namespace depend {

	    class DeviceDependentSpace:public ColorSpace {
	      protected:
		int getNumberBands();

		static double_array XYZ2LinearRGBValues(double_array XYZValues,
							const RGBColorSpace & colorSpace);
		static RGB_ptr XYZ2LinearRGB(XYZ_ptr XYZ, const RGBColorSpace & colorSpace);
	    };


	     Enumeration(CSType)
	     AdobeRGB, CIERGB, sRGB, sRGB_gamma22, sRGB_gamma18,
		ProPhotoRGB, WideGamutRGB, BetaRGB, BruceRGB, ECIRGB,
		LStarRGB, AppleRGB, BestRGB, skyRGB, NTSCRGB,
		EktaSpacePS5RGB, Unknow, AdobeRGBD50, AdobeRGB1998, SMPTE_C, EnumerationEnd();

	    class RGBBase;
	    //using cms::Illuminant;

	    class RGBColorSpace {
		friend class RGBBase;
		friend class RGBColor;
	      private:



		 RGBColorSpace(const CSType & type,
			       const cms::Illuminant & referenceWhite, const double gamma);
		 RGBColorSpace(const CSType & type, const cms::Illuminant & referenceWhite,
			       double toXYZMatrix[9], const double gamma);

		 RGBColorSpace(const CSType & type, const double gamma, const
			       cms::Illuminant & referenceWhite, double m0,
			       double m1, double m2, double m3, double m4, double m5,
			       double m6, double m7, double m8);
	      public:
		static const RGBColorSpace & unknowRGB;
		static const RGBColorSpace & sRGB;
		static const RGBColorSpace & sRGB_gamma22;
		const double gamma_;
		const CSType & type_;
		const cms::Illuminant & referenceWhite;
		double2D_ptr toXYZMatrix_;
		double2D_ptr toRGBMatrix_;

		inline bool operator==(const RGBColorSpace & that) const {
		    return type_ == that.type_;
		};

		 RGBColorSpace(const CSType & type, const cms::Illuminant & referenceWhite,
			       double2D_ptr toXYZMatrix, const double gamma);
	    };


	    class RGBBase:public DeviceDependentSpace {
	      public:
		static double_array linearToRGBValues(double_array linearRGBValues,
						      RGBColorSpace rgbColorSpace);
		static double_array linearToRGBValues(double_array linearRGBValues, double gamma);

		static double_array toLinearRGBValues(double_array RGBValues, double gamma);

		static double2D_ptr calculateRGBXYZMatrix(xyY_ptr r, xyY_ptr g, xyY_ptr b,
							  XYZ_ptr white);
		static double2D_ptr calculateRGBXYZMatrix(double rx, double ry,
							  double gx, double gy, double bx,
							  double by, double_array whiteXYZValues);
	    };

	    enum Round {
		//尚未執行
		NotYet,
		//四捨五入
		RoundOff,
		//無條件捨去
		RoundDown
	    };

	     Enumeration(ChannelIndex)
	     R = 1, G = 2, B = 3, Y = 4, M = 5, C = 6, W = 7, EnumerationEnd();

	    class Channel:public jObject {
	      public:

		static const Channel & R;
		static const Channel & G;
		static const Channel & B;
		static const Channel & Y;
		static const Channel & M;
		static const Channel & C;
		static const Channel & W;
	      private:

		 std::string fullname;
		 Channel(int index, const TColor & color, std::string fullname);
		 Channel(int index, const TColor & color,
			 std::string fullname, const ChannelIndex chindex);

		static bool isPrimaryColorChannel(const Channel & channel);
		static bool isSecondaryColorChannel(const Channel & channel);
		static Channel_vector_ptr getChannelVector(int count, ...);
	      public:
		const ChannelIndex chindex;
		//const int index;
		const TColor & color;

		inline bool operator==(const Channel & that) const {
		    return chindex == that.chindex;
		};
		inline bool operator!=(const Channel & that) const {
		    return !(chindex == that.chindex);
		};
		//Channel();

		const string_ptr toString() const;
		const int getArrayIndex() const;
		bool isPrimaryColorChannel() const;
		bool isSecondaryColorChannel() const;
		static Channel_vector_ptr getBesidePrimaryChannel(const
								  Channel & primaryColorChannel);

		static const Channel & getChannel(boolean R, boolean G, boolean B);
		static const Channel & getChannel(int chIndex);
		static const Channel & getChannelByArrayIndex(int
							      arrayIndex);

		static const Channel_vector_ptr RGBYMCChannel;
		static const Channel_vector_ptr RGBYMCWChannel;
		static const Channel_vector_ptr RGBChannel;
		static const Channel_vector_ptr RGBWChannel;
		static const Channel_vector_ptr WRGBChannel;
		static const Channel_vector_ptr YMCChannel;

	    };


	    class MaxValue:public jObject {
	      public:
		const double max;
		const bool integer;
		const bool divisible;
		const int bit;
	      private:

		 MaxValue(double max, bool integer,
			  bool divisible, int bit):max(max),
		    integer(integer), divisible(divisible), bit(bit) {
		};
		 MaxValue(double max):max(max), integer(false), divisible(false), bit(-1) {
		};
		static bptr < MaxValue_vector > make(int count, ...);
		static const bptr < MaxValue_vector > MaxValueVector;
	      public:

		static const MaxValue & Double1;
		static const MaxValue & Double100;
		static const MaxValue & Int5Bit;
		static const MaxValue & Int6Bit;
		static const MaxValue & Int7Bit;
		static const MaxValue & Int8Bit;
		static const MaxValue & Double255;
		static const MaxValue & Int9Bit;
		static const MaxValue & Double1020;
		static const MaxValue & Int10Bit;
		static const MaxValue & RealInt10Bit;
		static const MaxValue & Int11Bit;
		static const MaxValue & Double4080;
		static const MaxValue & Int12Bit;
		static const MaxValue & Real12Bit;
		static const MaxValue & Int13Bit;
		static const MaxValue & Int14Bit;
		static const MaxValue & Int15Bit;
		static const MaxValue & Int16Bit;
		static const MaxValue & Int20Bit;
		static const MaxValue & Int24Bit;
		static const MaxValue & Int31Bit;
		static const MaxValue & DoubleUnlimited;


		static MaxValue getIntegerMaxValueByLevel(int level);
		static MaxValue getIntegerMaxValueByMax(int max);
		double getStepIn255();

		inline bool operator==(const MaxValue & that) const {
		    return max == that.max
			&& integer == that.integer && divisible == that.divisible;
		};
		inline bool operator!=(const MaxValue & that) const {
		    return !(*this == that);
		};
		//MaxValue & operator=(const MaxValue & that);
		//static MaxValue getMaxValue(BitDepth bitDepth);
		static const MaxValue & getByIntegerBit(int bit);
		const string_ptr toString() const;
		static const MaxValue & valueOf(string_ptr stringValue);
	    };
	};
    };
};

#endif


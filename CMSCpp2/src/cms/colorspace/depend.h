#ifndef DEPENDH
#define DEPENDH

//C�t�Τ��
#include <cstdarg>
//C++�t�Τ��

//��L�w�Y���
#include <vcl.h>
//�����ؤ��Y���
#include <java/lang.h>
#include <cms/core.h>
#include "colorspace.h"

//enum TColor;

namespace cms {
    namespace colorspace {

	namespace depend {

	    class DeviceDependentSpace:public ColorSpace {
		int getNumberBands();
	    };

	     Enumeration(CSType)
	     AdobeRGB, CIERGB, sRGB, sRGB_gamma22, sRGB_gamma18,
		ProPhotoRGB, WideGamutRGB, BetaRGB, BruceRGB, ECIRGB,
		LStarRGB, AppleRGB, BestRGB, skyRGB, NTSCRGB,
		EktaSpacePS5RGB, Unknow, AdobeRGBD50, AdobeRGB1998,
		SMPTE_C, EnumerationEnd();
	    class RGBBase;
	    //using cms::Illuminant;

	    class RGBColorSpace {
		friend class RGBBase;
	      private:

		const double _gamma;
		const CSType & _type;
		const cms::Illuminant & referenceWhite;
		/*RGBColorSpace(CSType csType, Illuminant referenceWhite,
		   double[][]toXYZMatrix,
		   double gamma):_type(csType), _gamma(gamma),
		   referenceWhite(referenceWhite) {
		   this.toXYZMatrix = toXYZMatrix;
		   //this.toRGBMatrix = toXYZMatrix !=;
		   //null ? DoubleArray.inverse(toXYZMatrix) : null;
		   }; */
	      public:
		static const RGBColorSpace & unknowRGB;
		static const RGBColorSpace & sRGB;
		 RGBColorSpace::RGBColorSpace(const CSType & cstype,
					      const cms::
					      Illuminant & referenceWhite,
					      const double _gamma);
		inline bool operator==(const RGBColorSpace & that) const {
		    return _type == that._type;
		};
	    };


	    class RGBBase:public DeviceDependentSpace {
	      public:
		static double_array linearToRGBValues(double_array
						      linearRGBValues,
						      RGBColorSpace
						      rgbColorSpace);
	    };

	     Enumeration(ChannelIndex)
	     R = 1, G = 2, B = 3, Y = 4, M = 5, C = 6,
		W = 7,
             EnumerationEnd();

	    enum Round {
		//�|������
		NotYet,
		//�|�ˤ��J
		RoundOff,
		//�L����˥h
		RoundDown
	    };



	    /*Enumeration(ChannelIndex)
	       R, G, B, Y, M, C, W, EnumerationEnd(); */


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
		 Channel(int index, const TColor & color,
			 std::string fullname);
		 Channel(int index, const TColor & color,
			 std::string fullname, ChannelIndex chindex);

		static bool isPrimaryColorChannel(const Channel & channel);
		static bool isSecondaryColorChannel(const Channel &
						    channel);
		static channel_vector_ptr getChannelVector(int count, ...);
	      public:
		const ChannelIndex & chindex;
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
		int getArrayIndex();
		bool isPrimaryColorChannel() const;
		bool isSecondaryColorChannel() const;
		static channel_vector_ptr getBesidePrimaryChannel(const
								  Channel &
								  primaryColorChannel);

		static const Channel & getChannel(boolean R, boolean G,
						  boolean B);
		static const Channel & getChannel(int chIndex);
		static const Channel & getChannelByArrayIndex(int
							      arrayIndex);

		static const channel_vector_ptr RGBYMCChannel;
		static const channel_vector_ptr RGBYMCWChannel;
		static const channel_vector_ptr RGBChannel;
		static const channel_vector_ptr RGBWChannel;
		static const channel_vector_ptr WRGBChannel;
		static const channel_vector_ptr YMCChannel;

	    };


	    class MaxValue {
	      public:
		const double max;
		const bool integer;
		const bool divisible;
	      private:

		 MaxValue(double max, bool integer,
			  bool divisible):max(max), integer(integer),
		    divisible(divisible) {
		};
	      public:
		 MaxValue(double max):max(max), integer(false),
		    divisible(false) {
		};
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
		static const MaxValue & Int11Bit;
		static const MaxValue & Double4080;
		static const MaxValue & Int12Bit;
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
			&& integer == that.integer
			&& divisible == that.divisible;
		};
		inline bool operator!=(const MaxValue & that) const {
		    return !(*this == that);
		};
		//MaxValue & operator=(const MaxValue & that);

	    };
	};
    };
};

#endif


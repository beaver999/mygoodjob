#ifndef BITDEPTHPROCESSORH
#define BITDEPTHPROCESSORH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "rgbgammaop.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class BitDepthProcessor {

		enum BitDepth {
		    b10_10, b10_8, b8_8, b8_6, b6_6, Unknow
		};
	      private:
		const Dep::MaxValue * in, *lut, *out;
		BitDepth bitDepth;
		static BitDepth getBitDepth(const Dep::MaxValue & in, const Dep::MaxValue & out);
		bool tconInput;
	      public:
		 BitDepthProcessor(int inBit, int lutBit, int outBit, bool tconinput);

		/*
		   量測起始點
		 */
		int getMeasureStart();
		/*
		   量測終止點
		 */
		int getMeasureEnd();
		/*
		   量測間隔
		 */
		int getMeasureStep();
		/*
		   量測第一次間隔(可能與其他間隔不同)
		 */
		int getMeasureFirstStep();
		/*
		   最大的DG值(廢棄)
		 */
		double getMaxDigitalCount();

		/*
		   輸入端最大的DG(訊號)
		 */
		double getInputMaxDigitalCount();
		/*
		   輸出端最大的DG(to Panel)
		 */
		double getOutputMaxDigitalCount();

		/*
		   DG的總階數 (一律是257:0~256)
		 */
		int getLevel();
		/*
		   TCon下的實際DG總階數
		 */
		int getLevelInTCon();
		/*
		   可呈現出差異的階數
		 */
		int getEffectiveInputLevel();

		bool is8in8Out();
		bool is8in6Out();
		bool is6in6Out();
		bool is10in8Out();
		bool is10in10Out();
		const Dep::MaxValue & getInputMaxValue();
		const Dep::MaxValue & getLutMaxValue();
		const Dep::MaxValue & getOutputMaxValue();
		bool isTCONInput();

		void setTCONInput(bool tconInput);
		void setInBit(int inBit);
		void setLUTBit(int lutBit);
		void setOutBit(int outBit);
		string_ptr getFRCAbility();
		const Dep::MaxValue & getFRCAbilityBit();
		const Dep::MaxValue & getMeasureMaxValue();

	    };
	};
    };
};
#endif


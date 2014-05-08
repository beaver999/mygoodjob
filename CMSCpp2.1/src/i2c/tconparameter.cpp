#include "tconparameter.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace i2c {
    using namespace Dep;
     TCONParameter::TCONParameter(int gammaTestAddress,
				  unsigned char gammaTestBit,
				  int directGammaRGBAddress,
				  bool independentRGB,
				  const MaxValue &
				  lutBit):gammaTestAddress
	(gammaTestAddress), gammaTestBit(gammaTestBit),
	directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(independentRGB ? DirectGammaType::
			IndependentInstance : DirectGammaType::DependentInstance),
	DGLutAddress(-1), dgLUTType(-1), DGAddress(-1), DGBit(0), gammaTest(true), FRCAddress(-1), FRCBit(0),
	hideENAddress(-1), hideENBit(-1), hideEn(false), agingAGBSDebugAddress(-1),
        agingAGBSDebugBit(-1), agingModeSelectAddress(-1),
        agingModeSelectBit(-1), agingPatternSelectAddress(-1), agingPatternSelectValue(-1),
        agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1), agingRasterGrayAddress(-1),
        agingModeType(agingModeType), agingMode(false), agingManuSelectAddress(-1), agingManuSelectBit(-1),
        secondGamma(false), DG2Address(-1), DG2Bit(0), DG2LutAddress(-1), gammaTest2Address(-1), gammaTest2Bit(0),
        directGamma2RGBAddress(-1), FRC2Address(-1), FRC2Bit(0),
        pgMode(false),pgEnableAddress(-1), pgEnableBit(-1),
        pgModeAddress(-1), pgModeStartBit(-1), pgModeEndBit(-1),
        pgPatternMSBAddress(-1), pgPatternMSBStartBit(-1), pgPatternMSBEndBit(-1),
        pgPatternLSBAddress(-1), pgPatternLSBStartBit(-1), pgPatternLSBEndBit(-1),
        pgHblkMSBAddress(-1), pgHblkMSBStartBit(-1), pgHblkMSBEndBit(-1),
        pgHblkLSBAddress(-1), pgHblkLSBStartBit(-1), pgHblkLSBEndBit(-1),
        pgHblkValue(-1),
        pgVblkMSBAddress(-1), pgVblkMSBStartBit(-1), pgVblkMSBEndBit(-1),
        pgVblkLSBAddress(-1), pgVblkLSBStartBit(-1), pgVblkLSBEndBit(-1),
        pgVblkValue(-1) {
    };
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
				 DGLutAddress, const AnsiString dgLUTType,
                                 const int DGAddress, const unsigned char
				 DGBit, const int gammaTestAddress,
				 const unsigned char gammaTestBit,
				 const int directGammaRGBAddress,
				 const DirectGammaType & directGammaType, const int FRCAddress,
				 const unsigned char FRCBit):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(directGammaType), DGLutAddress(DGLutAddress), dgLUTType(dgLUTType),
        DGAddress(DGAddress), DGBit(DGBit), gammaTest(true), FRCAddress(FRCAddress),
        FRCBit(FRCBit), hideENAddress(-1), hideENBit(-1), hideEn(false), agingAGBSDebugAddress(-1),
        agingAGBSDebugBit(-1), agingModeSelectAddress(-1),
        agingModeSelectBit(-1), agingPatternSelectAddress(-1), agingPatternSelectValue(-1),
        agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1), agingRasterGrayAddress(-1),
        agingModeType(agingModeType), agingMode(false), agingManuSelectAddress(-1), agingManuSelectBit(-1),
        secondGamma(false), DG2Address(-1), DG2Bit(0), DG2LutAddress(-1), gammaTest2Address(-1), gammaTest2Bit(0),
        directGamma2RGBAddress(-1), FRC2Address(-1), FRC2Bit(0),
        pgMode(false),pgEnableAddress(-1), pgEnableBit(-1),
        pgModeAddress(-1), pgModeStartBit(-1), pgModeEndBit(-1),
        pgPatternMSBAddress(-1), pgPatternMSBStartBit(-1), pgPatternMSBEndBit(-1),
        pgPatternLSBAddress(-1), pgPatternLSBStartBit(-1), pgPatternLSBEndBit(-1),
        pgHblkMSBAddress(-1), pgHblkMSBStartBit(-1), pgHblkMSBEndBit(-1),
        pgHblkLSBAddress(-1), pgHblkLSBStartBit(-1), pgHblkLSBEndBit(-1),
        pgHblkValue(-1),
        pgVblkMSBAddress(-1), pgVblkMSBStartBit(-1), pgVblkMSBEndBit(-1),
        pgVblkLSBAddress(-1), pgVblkLSBStartBit(-1), pgVblkLSBEndBit(-1),
        pgVblkValue(-1) {
    };
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
				 DGLutAddress, const AnsiString dgLUTType, const int DGAddress,
                                 const unsigned char DGBit,
                                 const int gammaTestAddress,
				 const unsigned char gammaTestBit,
				 const int directGammaRGBAddress,
				 const DirectGammaType & directGammaType, const int FRCAddress,
				 const unsigned char FRCBit, const int hideENAddress,
				 const unsigned char hideENBit):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(directGammaType), DGLutAddress(DGLutAddress), dgLUTType(dgLUTType),
        DGAddress(DGAddress), DGBit(DGBit), gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit),
	hideENAddress(hideENAddress), hideENBit(hideENBit), hideEn(true), agingAGBSDebugAddress(-1),
        agingAGBSDebugBit(-1), agingModeSelectAddress(-1),
        agingModeSelectBit(-1), agingPatternSelectAddress(-1), agingPatternSelectValue(-1),
        agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1), agingRasterGrayAddress(-1),
        agingModeType(agingModeType), agingMode(false), agingManuSelectAddress(-1), agingManuSelectBit(-1),
        secondGamma(false), DG2Address(-1), DG2Bit(0), DG2LutAddress(-1), gammaTest2Address(-1), gammaTest2Bit(0),
        directGamma2RGBAddress(-1), FRC2Address(-1), FRC2Bit(0),
        pgMode(false),pgEnableAddress(-1), pgEnableBit(-1),
        pgModeAddress(-1), pgModeStartBit(-1), pgModeEndBit(-1),
        pgPatternMSBAddress(-1), pgPatternMSBStartBit(-1), pgPatternMSBEndBit(-1),
        pgPatternLSBAddress(-1), pgPatternLSBStartBit(-1), pgPatternLSBEndBit(-1),
        pgHblkMSBAddress(-1), pgHblkMSBStartBit(-1), pgHblkMSBEndBit(-1),
        pgHblkLSBAddress(-1), pgHblkLSBStartBit(-1), pgHblkLSBEndBit(-1),
        pgHblkValue(-1),
        pgVblkMSBAddress(-1), pgVblkMSBStartBit(-1), pgVblkMSBEndBit(-1),
        pgVblkLSBAddress(-1), pgVblkLSBStartBit(-1), pgVblkLSBEndBit(-1),
        pgVblkValue(-1) {
    };

    //for aging mode. byBS++
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
                                 DGLutAddress, const AnsiString dgLUTType, const int DGAddress,
                                 const unsigned char DGBit, const int gammaTestAddress,
                                 const unsigned char gammaTestBit,
                                 const int directGammaRGBAddress,
                                 const DirectGammaType & directGammaType, const int FRCAddress,
                                 const unsigned char FRCBit,
                                 const int agingAGBSDebugAddress,
                                 const unsigned char agingAGBSDebugBit,
                                 const int agingModeSelectAddress,
                                 const unsigned char agingModeSelectBit,
                                 const int agingPatternSelectAddress,
                                 const unsigned char agingPatternSelectValue,
                                 const unsigned char agingPatternSelectStartBit,
                                 const unsigned char agingPatternSelectEndBit,
                                 const int agingRasterGrayAddress,
                                 const DirectGammaType & agingModeType,
                                 const unsigned char agingManuSelectAddress,
                                 const int agingManuSelectBit):gammaTestAddress(gammaTestAddress),
        gammaTestBit(gammaTestBit), directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(directGammaType), DGLutAddress(DGLutAddress), dgLUTType(dgLUTType), DGAddress(DGAddress),
	DGBit(DGBit), gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(-1),
	hideENBit(-1), hideEn(false), agingAGBSDebugAddress(agingAGBSDebugAddress),
        agingAGBSDebugBit(agingAGBSDebugBit), agingModeSelectAddress(agingModeSelectAddress),
        agingModeSelectBit(agingModeSelectBit), agingPatternSelectAddress(agingPatternSelectAddress),
        agingPatternSelectValue(agingPatternSelectValue),
        agingPatternSelectStartBit(agingPatternSelectStartBit),
        agingPatternSelectEndBit(agingPatternSelectEndBit), agingRasterGrayAddress(agingRasterGrayAddress),
        agingModeType(agingModeType), agingMode(true), agingManuSelectAddress(-1), agingManuSelectBit(-1),
        secondGamma(false), DG2Address(-1), DG2Bit(0), DG2LutAddress(-1), gammaTest2Address(-1), gammaTest2Bit(0),
        directGamma2RGBAddress(-1), FRC2Address(-1), FRC2Bit(0),
        pgMode(false),pgEnableAddress(-1), pgEnableBit(-1),
        pgModeAddress(-1), pgModeStartBit(-1), pgModeEndBit(-1),
        pgPatternMSBAddress(-1), pgPatternMSBStartBit(-1), pgPatternMSBEndBit(-1),
        pgPatternLSBAddress(-1), pgPatternLSBStartBit(-1), pgPatternLSBEndBit(-1),
        pgHblkMSBAddress(-1), pgHblkMSBStartBit(-1), pgHblkMSBEndBit(-1),
        pgHblkLSBAddress(-1), pgHblkLSBStartBit(-1), pgHblkLSBEndBit(-1),
        pgHblkValue(-1),
        pgVblkMSBAddress(-1), pgVblkMSBStartBit(-1), pgVblkMSBEndBit(-1),
        pgVblkLSBAddress(-1), pgVblkLSBStartBit(-1), pgVblkLSBEndBit(-1),
        pgVblkValue(-1) {
    };

    //for aging mode + SecondGamma   byBS++
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
                                 DGLutAddress, const AnsiString dgLUTType, const int DGAddress,
                                 const unsigned char DGBit, const int gammaTestAddress,
                                 const unsigned char gammaTestBit,
                                 const int directGammaRGBAddress,
                                 const DirectGammaType & directGammaType, const int FRCAddress,
                                 const unsigned char FRCBit,
                                 const int agingAGBSDebugAddress,
                                 const unsigned char agingAGBSDebugBit,
                                 const int agingModeSelectAddress,
                                 const unsigned char agingModeSelectBit,
                                 const int agingPatternSelectAddress,
                                 const unsigned char agingPatternSelectValue,
                                 const unsigned char agingPatternSelectStartBit,
                                 const unsigned char agingPatternSelectEndBit,
                                 const int agingRasterGrayAddress,
                                 const DirectGammaType & agingModeType,
                                 const unsigned char agingManuSelectAddress,
                                 const int agingManuSelectBit,
                                 const int DG2Address, const unsigned char DG2Bit,
                                 const int DG2LutAddress, const int gammaTest2Address,
                                 const unsigned char gammaTest2Bit, const int directGamma2RGBAddress,
                                 const int FRC2Address, const unsigned char FRC2Bit):
        gammaTestAddress(gammaTestAddress),
        gammaTestBit(gammaTestBit), directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(directGammaType), DGLutAddress(DGLutAddress), dgLUTType(dgLUTType), DGAddress(DGAddress),
	DGBit(DGBit), gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(-1),
	hideENBit(-1), hideEn(false), agingAGBSDebugAddress(agingAGBSDebugAddress),
        agingAGBSDebugBit(agingAGBSDebugBit), agingModeSelectAddress(agingModeSelectAddress),
        agingModeSelectBit(agingModeSelectBit), agingPatternSelectAddress(agingPatternSelectAddress),
        agingPatternSelectValue(agingPatternSelectValue),
        agingPatternSelectStartBit(agingPatternSelectStartBit),
        agingPatternSelectEndBit(agingPatternSelectEndBit), agingRasterGrayAddress(agingRasterGrayAddress),
        agingModeType(agingModeType), agingMode(true), agingManuSelectAddress(agingManuSelectAddress),
        agingManuSelectBit(agingManuSelectBit),
        secondGamma(true), DG2Address(DG2Address), DG2Bit(DG2Bit), DG2LutAddress(DG2LutAddress),
        gammaTest2Address(gammaTest2Address), gammaTest2Bit(gammaTest2Bit), directGamma2RGBAddress(directGamma2RGBAddress),
        FRC2Address(FRC2Address), FRC2Bit(FRC2Bit),
        pgMode(false),pgEnableAddress(-1), pgEnableBit(-1),
        pgModeAddress(-1), pgModeStartBit(-1), pgModeEndBit(-1),
        pgPatternMSBAddress(-1), pgPatternMSBStartBit(-1), pgPatternMSBEndBit(-1),
        pgPatternLSBAddress(-1), pgPatternLSBStartBit(-1), pgPatternLSBEndBit(-1),
        pgHblkMSBAddress(-1), pgHblkMSBStartBit(-1), pgHblkMSBEndBit(-1),
        pgHblkLSBAddress(-1), pgHblkLSBStartBit(-1), pgHblkLSBEndBit(-1),
        pgHblkValue(-1),
        pgVblkMSBAddress(-1), pgVblkMSBStartBit(-1), pgVblkMSBEndBit(-1),
        pgVblkLSBAddress(-1), pgVblkLSBStartBit(-1), pgVblkLSBEndBit(-1),
        pgVblkValue(-1) {
    };

    //For PGMode    byBS+
    TCONParameter::TCONParameter(const int FRCAddress, const unsigned char FRCBit,
                                 const int pgEnableAddress, const unsigned char pgEnableBit,
                                 const int pgModeAddress, const unsigned char pgModeStartBit, const unsigned char pgModeEndBit,
                                 const int pgPatternMSBAddress, const unsigned char pgPatternMSBStartBit, const unsigned char pgPatternMSBEndBit,
                                 const int pgPatternLSBAddress, const unsigned char pgPatternLSBStartBit, const unsigned char pgPatternLSBEndBit,
                                 const int pgHblkMSBAddress, const unsigned char pgHblkMSBStartBit, const unsigned char pgHblkMSBEndBit,
                                 const int pgHblkLSBAddress, const unsigned char pgHblkLSBStartBit, const unsigned char pgHblkLSBEndBit,
                                 const int pgHblkValue,
                                 const int pgVblkMSBAddress, const unsigned char pgVblkMSBStartBit, const unsigned char pgVblkMSBEndBit,
                                 const int pgVblkLSBAddress, const unsigned char pgVblkLSBStartBit, const unsigned char pgVblkLSBEndBit,
                                 const int pgVblkValue):

        FRCAddress(FRCAddress), FRCBit(FRCBit),
        pgMode(true),pgEnableAddress(pgEnableAddress), pgEnableBit(pgEnableBit),
        pgModeAddress(pgModeAddress), pgModeStartBit(pgModeStartBit), pgModeEndBit(pgModeEndBit),
        pgPatternMSBAddress(pgPatternMSBAddress), pgPatternMSBStartBit(pgPatternMSBStartBit), pgPatternMSBEndBit(pgPatternMSBEndBit),
        pgPatternLSBAddress(pgPatternLSBAddress), pgPatternLSBStartBit(pgPatternLSBStartBit), pgPatternLSBEndBit(pgPatternLSBEndBit),
        pgHblkMSBAddress(pgHblkMSBAddress), pgHblkMSBStartBit(pgHblkMSBStartBit), pgHblkMSBEndBit(pgHblkMSBEndBit),
        pgHblkLSBAddress(pgHblkLSBAddress), pgHblkLSBStartBit(pgHblkLSBStartBit), pgHblkLSBEndBit(pgHblkLSBEndBit),
        pgHblkValue(pgHblkValue),
        pgVblkMSBAddress(pgVblkMSBAddress), pgVblkMSBStartBit(pgVblkMSBStartBit), pgVblkMSBEndBit(pgVblkMSBEndBit),
        pgVblkLSBAddress(pgVblkLSBAddress), pgVblkLSBStartBit(pgVblkLSBStartBit), pgVblkLSBEndBit(pgVblkLSBEndBit),
        pgVblkValue(pgVblkValue),

        gammaTestAddress(-1), gammaTestBit(-1),
	directGammaRGBAddress(-1), lutBit(lutBit),
	directGammaType(DirectGammaType::IndependentInstance),   //不知給啥，先隨便給
	DGLutAddress(-1), dgLUTType(-1), DGAddress(-1), DGBit(0), gammaTest(true),
	hideENAddress(-1), hideENBit(-1), hideEn(false), agingAGBSDebugAddress(-1),
        agingAGBSDebugBit(-1), agingModeSelectAddress(-1),
        agingModeSelectBit(-1), agingPatternSelectAddress(-1), agingPatternSelectValue(-1),
        agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1), agingRasterGrayAddress(-1),
        agingModeType(agingModeType), agingMode(false), agingManuSelectAddress(-1), agingManuSelectBit(-1),
        secondGamma(false), DG2Address(-1), DG2Bit(0), DG2LutAddress(-1), gammaTest2Address(-1), gammaTest2Bit(0),
        directGamma2RGBAddress(-1), FRC2Address(-1), FRC2Bit(0)

        {
    };


    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int DGLutAddress,
				 const AnsiString dgLUTType, const int DGAddress,
				 const unsigned char DGBit, const int FRCAddress,
				 const unsigned char FRCBit):gammaTestAddress(-1), gammaTestBit(-1),
	directGammaRGBAddress(-1), lutBit(lutBit), directGammaType(directGammaType),
	DGLutAddress(DGLutAddress), dgLUTType(dgLUTType), DGAddress(DGAddress), DGBit(DGBit),
        gammaTest(false), FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(-1),
        hideENBit(-1), hideEn(false), agingAGBSDebugAddress(-1), agingAGBSDebugBit(-1),
        agingModeSelectAddress(-1), agingModeSelectBit(-1), agingPatternSelectAddress(-1),
        agingPatternSelectValue(-1), agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1),
        agingRasterGrayAddress(-1), agingModeType(agingModeType), agingMode(false), agingManuSelectAddress(-1), agingManuSelectBit(-1),
        secondGamma(false), DG2Address(-1), DG2Bit(0), DG2LutAddress(-1), gammaTest2Address(-1), gammaTest2Bit(0),
        directGamma2RGBAddress(-1), FRC2Address(-1), FRC2Bit(0),
        pgMode(false),pgEnableAddress(-1), pgEnableBit(-1),
        pgModeAddress(-1), pgModeStartBit(-1), pgModeEndBit(-1),
        pgPatternMSBAddress(-1), pgPatternMSBStartBit(-1), pgPatternMSBEndBit(-1),
        pgPatternLSBAddress(-1), pgPatternLSBStartBit(-1), pgPatternLSBEndBit(-1),
        pgHblkMSBAddress(-1), pgHblkMSBStartBit(-1), pgHblkMSBEndBit(-1),
        pgHblkLSBAddress(-1), pgHblkLSBStartBit(-1), pgHblkLSBEndBit(-1),
        pgHblkValue(-1),
        pgVblkMSBAddress(-1), pgVblkMSBStartBit(-1), pgVblkMSBEndBit(-1),
        pgVblkLSBAddress(-1), pgVblkLSBStartBit(-1), pgVblkLSBEndBit(-1),
        pgVblkValue(-1) {
    };
    DirectGammaType::DirectGammaType(const int rLowBit, const int rHighBit,
				     const int gLowBit, const int gHighBit,
				     const int bLowBit, const int bHighBit, const int totalByte,
				     const int patternBit)
    :rLowBit(rLowBit), rHighBit(rHighBit), gLowBit(gLowBit), gHighBit(gHighBit), bLowBit(bLowBit),
	bHighBit(bHighBit), totalByte(totalByte), patternBit(patternBit) {

    };
    bool TCONParameter::isGammaTestEnable() {
	return gammaTest;
    };
    //Aging Mode byBS+
    bool TCONParameter::isAgingModeEnable() {
	return agingMode;
    };
    bool TCONParameter::isPGModeEnable() {
	return pgMode;
    };
    bool TCONParameter::isHideEnable() {
	return hideEn;
    };

    bool DirectGammaType::operator==(const DirectGammaType & t) const {
	return this->rLowBit == t.rLowBit && this->rHighBit == t.rHighBit &&
	    this->gLowBit == t.gLowBit && this->gHighBit == t.gHighBit &&
	    this->bLowBit == t.bLowBit && this->bHighBit == t.bHighBit &&
	    this->totalByte == t.totalByte && this->patternBit == t.patternBit;

    };



    //format: RL RH GL GH BL BH TOTALBYTE BIT

    //12401 |RH |RL|GH |GL|BH |BL|
    const DirectGammaType DirectGammaType::IndependentInstance(8, 0, 24, 16, 40, 32, 6, 12);
    //12403 |RL|RHGH|GL|BL|BH  |
    const DirectGammaType DirectGammaType::DependentInstance(0, 8, 16, 12, 24, 32, 5, 12);
    //62301 |BHGHRH |RL|GL|BL|
    const DirectGammaType DirectGammaType::TCON62301Instance(8, 4, 16, 2, 24, 0, 4, 10);
    //1H501 |RL|RH |GL|GH |BL|BH |
    const DirectGammaType DirectGammaType::TCON1H501Instance(0, 8, 16, 24, 32, 40, 6, 10);
    //12409 Aging |RHRL1|RL2GHGL1|GL2BHBL1|BL2
    const DirectGammaType DirectGammaType::TCON12409AgingInstance(2, 0, 12, 10, 22, 20, 4, 10);
    //12409 |RH |RLGH|GL|BH |BL|
    const DirectGammaType DirectGammaType::TCON12409Instance(12, 0, 16, 8, 36, 24, 5, 12);
    //11311  |RH |RL|GH |GL|BH |BL|
    const DirectGammaType DirectGammaType::TCON11311Instance(14, 0, 30, 16, 46, 32, 6, 10);
    //12411 Aging |GRAY_H |GRAY_L|
    const DirectGammaType DirectGammaType::TCON12411AgingInstance(0, 0, 0, 0, 0, 0, 0, 10); //格式不同，參數沒用到，DEFULE=0
    //12411 |RH |RL|GH |GL|BH |BL|
    const DirectGammaType DirectGammaType::TCON12411Instance(12, 0, 28, 16, 36, 32, 6, 12);

    const DirectGammaType DirectGammaType::NotAssignInstance(0, 0, 0, 0, 0, 0, 0, 12);
};


#include "analyzer.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <ca210api/CA210API.h>
#include <cms/measure/meter.h>
#include <cms/measure/MeterMeasurement.h>
#include <cms/colorspace/rgb.h>
#include <cms/patch.h>

namespace cms {
    namespace measure {

	using namespace cms::measure::meter;
	using namespace Dep;
	using namespace ca210api;

	 CA210ComponentAnayzer::
	    CA210ComponentAnayzer(bptr < CA210 > ca210):ca210(ca210),
	    ca210api(ca210->getCA210API()), mm(bptr < MeterMeasurement >
					       (new
						MeterMeasurement(ca210,
								 false))) {
	};

	 bptr < RGBColor >
	    CA210ComponentAnayzer::getComponent(bptr < RGBColor > rgb) {
	    bptr < Patch > patch = mm->measure(rgb, rgb->toString());
	    bptr < CAMeasureResult > measureResult =
		ca210api->getMeasureResult();
	    bptr < RGBColor >
		component(new
			  RGBColor(measureResult->R, measureResult->G,
				   measureResult->B));

	};

	void CA210ComponentAnayzer::setupComponent(Channel & ch,
						   bptr < RGBColor > rgb) {
	    switch (ch.chindex) {
	    //case Dep::ChannelEnum::R:
	    };
	};

      StocktonComponentAnayzer::StocktonComponentAnayzer(bptr < CA210 > ca210):CA210ComponentAnayzer(ca210)
	{
	};

	bptr < RGBColor >
	    StocktonComponentAnayzer::getComponent(bptr < RGBColor > rgb) {
	    bptr < Patch > patch = mm->measure(rgb, rgb->toString());
	    bptr < CAMeasureResult > measureResult =
		ca210api->getMeasureResult();
	    bptr < RGBColor >
		component(new
			  RGBColor(measureResult->R, measureResult->G,
				   measureResult->B));

	};

	void StocktonComponentAnayzer::setupComponent(Channel & ch,
						      bptr < RGBColor >
						      rgb) {
	};

    };
};


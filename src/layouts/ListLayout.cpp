#include <amber/layouts/ListLayout.hpp>

using namespace geode::prelude;


AxisLayout* ListLayout::create(float scrollLayerHeight, float gap) {
	auto ret = ColumnLayout::create()
		->setGap(gap)
		->setAxisReverse(true)
		->setAxisAlignment(AxisAlignment::End)
		->setAutoGrowAxis(scrollLayerHeight);

	return ret;
}
#include <amber/layouts/ListLayout.hpp>

using namespace geode::prelude;


ListLayout* ListLayout::create(float scrollLayerHeight, float gap) {
	auto ret = new ListLayout(scrollLayerHeight, gap);

	ret->autorelease();
	return ret;
}

ListLayout::ListLayout(float scrollLayerHeight, float gap) : ColumnLayout() {
	this
		->setGap(gap)
		->setAxisReverse(true)
		->setAxisAlignment(AxisAlignment::End)
		->setAutoGrowAxis(scrollLayerHeight);
}
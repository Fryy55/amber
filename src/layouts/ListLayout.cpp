#include <amber/layouts/ListLayout.hpp>

using namespace amber::layouts;
using namespace geode::prelude;


ListLayout::ListLayout() : AxisLayout(Axis::Column) {}

ListLayout* ListLayout::create(float scrollLayerHeight, float gap) {
	auto ret = new ListLayout;

	if (ret->init(scrollLayerHeight, gap)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ListLayout::init(float scrollLayerHeight, float gap) {
	this
		->setGap(gap)
		->setAxisReverse(true)
		->setAxisAlignment(AxisAlignment::End)
		->setAutoGrowAxis(scrollLayerHeight);

	return true;
}
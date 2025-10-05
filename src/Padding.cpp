#include "Padding.hpp"

using namespace geode::prelude;


Padding* Padding::create(float side) {
	return create(side, side);
}

Padding* Padding::create(float width, float height) {
	auto ret = new Padding;

	if (ret->init(width, height)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool Padding::init(float width, float height) {
	if (!CCNode::init())
		return false;

	this->setContentSize({ width, height });

	return true;
}
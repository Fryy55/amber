#include "Separator.hpp"

using namespace geode::prelude;


Separator* Separator::create(ccColor3B const& color, float fadeLength, float totalLength, float width) {
	auto ret = new Separator;

	if (ret->init(color, fadeLength, totalLength, width)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

void Separator::resize(float newLength) {
	this->CCNodeRGBA::setContentWidth(newLength);

	bool addMiddle = newLength > m_fadeLength * 2.f;
	float middleLength = addMiddle ? newLength - m_fadeLength * 2.f : 0.f;
	float fadeLength = addMiddle ? m_fadeLength : newLength / 2.f;

	m_leftGradient->setContentWidth(fadeLength);
	m_middle->setContentWidth(middleLength);
	m_rightGradient->setContentWidth(fadeLength);

	m_middle->setPositionX(fadeLength);
	m_rightGradient->setPositionX(fadeLength + middleLength);

	return;
}

void Separator::setColor(ccColor3B const& color) {
	m_leftGradient->setStartColor(color);
	m_middle->setColor(color);
	m_rightGradient->setStartColor(color);

	return;
}

void Separator::setOpacity(GLubyte opacity) {
	m_leftGradient->setStartOpacity(opacity);
	m_middle->setOpacity(opacity);
	m_rightGradient->setStartOpacity(opacity);

	return;
}

bool Separator::init(ccColor3B const& color, float fadeLength, float totalLength, float width) {
	if (!CCNode::init())
		return false;

	m_fadeLength = fadeLength;
	this->CCNodeRGBA::setContentHeight(width);
	this->setAnchorPoint({ 0.5f, 0.5f });

	auto color4b = to4B(color);
	m_leftGradient = CCLayerGradient::create(color4b, {}, { -1.f, 0.f });
	m_leftGradient->setID("left-gradient");
	m_middle = CCLayerColor::create(color4b);
	m_middle->setID("middle");
	m_rightGradient = CCLayerGradient::create(color4b, {}, { 1.f, 0.f });
	m_rightGradient->setID("right-gradient");

	m_leftGradient->setContentHeight(width);
	m_middle->setContentHeight(width);
	m_rightGradient->setContentHeight(width);
	this->addChild(m_leftGradient);
	this->addChild(m_middle);
	this->addChild(m_rightGradient);

	this->resize(totalLength);

	return true;
}
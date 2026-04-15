#include <amber/classes/Separator.hpp>

using namespace amber;
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

bool Separator::init(ccColor3B const& color, float fadeLength, float totalLength, float width) {
	if (!CCNodeRGBA::init())
		return false;

	m_fadeLength = fadeLength;
	m_color = color;

	this->setAnchorPoint({ 0.5f, 0.5f });

	auto color4B = to4B(m_color);

	m_leftGradient = CCLayerGradient::create(color4B, {}, { -1.f, 0.f });
	m_leftGradient->setID("left-gradient");
	m_middle = CCLayerColor::create(color4B);
	m_middle->setID("middle");
	m_rightGradient = CCLayerGradient::create(color4B, {}, { 1.f, 0.f });
	m_rightGradient->setID("right-gradient");

	this->addChild(m_leftGradient);
	this->addChild(m_middle);
	this->addChild(m_rightGradient);

	this->setContentSize({ totalLength, width });

	return true;
}

void Separator::setContentSize(CCSize const& size) {
	CCNodeRGBA::setContentSize(size);

	auto width = size.width;
	auto height = size.height;

	bool addMiddle = m_fadeLength * 2.f < width;
	float middleLength = addMiddle ? width - m_fadeLength * 2.f : 0.f;
	float fadeLength = addMiddle ? m_fadeLength : width / 2.f;

	m_leftGradient->setContentSize({ fadeLength, height });
	m_middle->setContentSize({ middleLength, height });
	m_rightGradient->setContentSize({ fadeLength, height });

	m_middle->setPositionX(fadeLength);
	m_rightGradient->setPositionX(fadeLength + middleLength);

	return;
}

void Separator::setFadeLength(float fadeLength) {
	m_fadeLength = fadeLength;

	this->setContentSize(this->getContentSize());

	return;
}

void Separator::setColor(ccColor3B const& color) {
	m_color = color;

	m_leftGradient->setStartColor(color);
	m_middle->setColor(color);
	m_rightGradient->setStartColor(color);

	return;
}

void Separator::setOpacity(GLubyte opacity) {
	m_opacity = opacity;

	m_leftGradient->setStartOpacity(opacity);
	m_middle->setOpacity(opacity);
	m_rightGradient->setStartOpacity(opacity);

	return;
}
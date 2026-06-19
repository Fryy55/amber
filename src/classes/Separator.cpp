#include "include/classes/Separator.hpp"

using namespace amber;
using namespace geode::prelude;


struct Separator::Impl final {
	CCLayerGradient* leftGradient;
	CCLayerColor* middle;
	CCLayerGradient* rightGradient;
	float fadeLength;
	ccColor3B color;
	GLubyte opacity = 255u;
};

Separator::Separator() : m_impl(std::make_unique<Impl>()) {}

Separator::~Separator() = default;


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

	m_impl->fadeLength = fadeLength;
	m_impl->color = color;

	this->setAnchorPoint({ 0.5f, 0.5f });

	auto color4B = to4B(color);


	auto& leftGradient = m_impl->leftGradient;
	auto& middle = m_impl->middle;
	auto& rightGradient = m_impl->rightGradient;

	leftGradient = CCLayerGradient::create(color4B, {}, { -1.f, 0.f });
	leftGradient->setID("left-gradient");
	middle = CCLayerColor::create(color4B);
	middle->setID("middle");
	rightGradient = CCLayerGradient::create(color4B, {}, { 1.f, 0.f });
	rightGradient->setID("right-gradient");

	this->addChild(leftGradient);
	this->addChild(middle);
	this->addChild(rightGradient);

	this->setContentSize({ totalLength, width });

	return true;
}


void Separator::setContentSize(CCSize const& size) {
	CCNodeRGBA::setContentSize(size);

	auto width = size.width;
	auto height = size.height;
	auto fadeLengthMember = m_impl->fadeLength;

	bool addMiddle = fadeLengthMember * 2.f < width;
	float middleLength = addMiddle ? width - fadeLengthMember * 2.f : 0.f;
	float fadeLength = addMiddle ? fadeLengthMember : width / 2.f;

	m_impl->leftGradient->setContentSize({ fadeLength, height });
	m_impl->middle->setContentSize({ middleLength, height });
	m_impl->rightGradient->setContentSize({ fadeLength, height });

	m_impl->middle->setPositionX(fadeLength);
	m_impl->rightGradient->setPositionX(fadeLength + middleLength);

	return;
}

float Separator::getFadeLength() const noexcept {
	return m_impl->fadeLength;
}

void Separator::setFadeLength(float fadeLength) {
	m_impl->fadeLength = fadeLength;

	this->setContentSize(this->getContentSize());

	return;
}

ccColor3B const& Separator::getColor() noexcept {
	return m_impl->color;
}

void Separator::setColor(ccColor3B const& color) {
	m_impl->color = color;

	m_impl->leftGradient->setStartColor(color);
	m_impl->middle->setColor(color);
	m_impl->rightGradient->setStartColor(color);

	return;
}

GLubyte Separator::getOpacity() noexcept {
	return m_impl->opacity;
}

void Separator::setOpacity(GLubyte opacity) {
	m_impl->opacity = opacity;

	m_impl->leftGradient->setStartOpacity(opacity);
	m_impl->middle->setOpacity(opacity);
	m_impl->rightGradient->setStartOpacity(opacity);

	return;
}
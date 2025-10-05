#include "LimitedTextArea.hpp"

using namespace geode::prelude;


LimitedTextArea* LimitedTextArea::create(
	CCSize const& size,
	std::string const& text,
	std::size_t charLimit,
	char const* font,
	cocos2d::CCPoint const& textOffset,
	ccColor4B const& bgColor
) {
	auto ret = new LimitedTextArea;

	if (ret->init(size, text, charLimit, font, textOffset, bgColor)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool LimitedTextArea::init(
	CCSize const& size,
	std::string const& text,
	std::size_t charLimit,
	char const* font,
	cocos2d::CCPoint const& textOffset,
	ccColor4B const& bgColor
) {
	if (!CCNode::init())
		return false;

	m_charLimit = charLimit;



	m_bg = CCScale9Sprite::create("square02b_001.png");
	m_bg->setScale(0.5f);
	m_bg->setColor(to3B(bgColor));
	m_bg->setOpacity(bgColor.a);
	m_bg->setID("background");


	m_textLabel = CCLabelBMFont::create("", font);
	m_textLabel->setID("text-label");


	this->setContentSize(size);
	this->addChildAtPosition(m_bg, Anchor::Center);
	this->addChildAtPosition(m_textLabel, Anchor::Center, textOffset);
	this->setText(text);

	return true;
}

void LimitedTextArea::setText(std::string const& text) {
	m_text = text;

	if (text.size() > m_charLimit)
		m_textLabel->setString(text.substr(0, m_charLimit).append("...").c_str());
	else
		m_textLabel->setString(text.c_str());

	this->updateLabelWidth();

	return;
}

void LimitedTextArea::setContentSize(CCSize const& size) {
	CCNode::setContentSize(size);
	m_bg->setContentSize(size * 2.f);

	this->updateLabelWidth();

	return;
}

void LimitedTextArea::updateLabelWidth() {
	m_textLabel->limitLabelWidth(this->getContentWidth() - 4.f, 1.f, 0.1f);

	return;
}
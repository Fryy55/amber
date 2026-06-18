#include "include/classes/LimitedTextArea.hpp"

using namespace amber;
using namespace geode::prelude;


struct LimitedTextArea::Impl final {
	std::string text;
	geode::NineSlice* bg;
	cocos2d::CCLabelBMFont* textLabel;
	std::size_t charLimit;
};

LimitedTextArea::LimitedTextArea() : m_impl(std::make_unique<Impl>()) {}

LimitedTextArea::~LimitedTextArea() = default;


LimitedTextArea* LimitedTextArea::create(
	CCSize const& size,
	ZStringView text,
	std::size_t charLimit,
	ZStringView font,
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
	ZStringView text,
	std::size_t charLimit,
	ZStringView font,
	cocos2d::CCPoint const& textOffset,
	ccColor4B const& bgColor
) {
	if (!CCNode::init())
		return false;

	m_impl->charLimit = charLimit;



	auto bg = m_impl->bg;
	bg = NineSlice::create("square02b_001.png");
	bg->setScale(0.5f);
	bg->setColor(to3B(bgColor));
	bg->setOpacity(bgColor.a);
	bg->setID("background");


	auto textLabel = m_impl->textLabel;
	textLabel = CCLabelBMFont::create("", font.c_str());
	textLabel->setID("text-label");


	this->setContentSize(size);
	this->addChildAtPosition(bg, Anchor::Center);
	this->addChildAtPosition(textLabel, Anchor::Center, textOffset);
	this->setText(text);

	return true;
}

ZStringView LimitedTextArea::getText() const noexcept {
	return m_impl->text;
}

void LimitedTextArea::setText(ZStringView text) {
	m_impl->text = text;

	if (text.size() > m_impl->charLimit) {
		m_impl->textLabel->setString(
			fmt::format("{}...", text.view().substr(0, m_impl->charLimit)).c_str()
		);
	} else {
		m_impl->textLabel->setString(text.c_str());
	}

	this->updateLabelWidth();

	return;
}

CCLabelBMFont* LimitedTextArea::getLabel() const noexcept {
	return m_impl->textLabel;
}

void LimitedTextArea::setContentSize(CCSize const& size) {
	CCNode::setContentSize(size);
	m_impl->bg->setContentSize(size * 2.f);

	this->updateLabelWidth();

	return;
}

void LimitedTextArea::updateLabelWidth() {
	m_impl->textLabel->limitLabelWidth(this->getContentWidth() - 4.f, 1.f, 0.1f);

	return;
}
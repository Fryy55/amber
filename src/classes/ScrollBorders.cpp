#include <amber/classes/ScrollBorders.hpp>

using namespace amber;
using namespace geode::prelude;


ScrollBorders* ScrollBorders::create(CCSize const& size) {
	return create(size, "");
}

ScrollBorders* ScrollBorders::create(CCSize const& size, char const* title, char const* font) {
	auto ret = new ScrollBorders;

	if (ret->init(size, title, font)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

ScrollBorders* ScrollBorders::create(ScrollLayer* childScrollLayer) {
	auto ret = create(
		childScrollLayer->getScaledContentSize() + CCSize(40.f, 23.f)
	);

	childScrollLayer->setPosition(20.f, 31.f);
	ret->addChild(childScrollLayer);

	return ret;
}

bool ScrollBorders::init(CCSize const& size, char const* title, char const* font) {
	if (!CCNode::init())
		return false;

	m_title = ColoredLabel::create(title, font);
	m_title->setID("title");
	this->addChild(m_title, 11);

	m_top = NineSlice::createWithSpriteFrameName("GJ_table_top_001.png");
	m_top->setID("top-sprite");
	this->addChild(m_top, 10);

	m_bottom = NineSlice::createWithSpriteFrameName("GJ_table_bottom_001.png");
	m_bottom->setID("bottom-sprite");
	this->addChild(m_bottom, 10);

	m_left = CCScale9Sprite::createWithSpriteFrameName("GJ_table_side_001.png");
	m_left->setID("left-sprite");
	this->addChild(m_left, 9);

	m_right = CCScale9Sprite::createWithSpriteFrameName("GJ_table_side_001.png");
	m_right->setRotation(180.f);
	m_right->setID("right-sprite");
	this->addChild(m_right, 9);

	this->setAnchorPoint({ 0.5f, 0.5f });
	this->setContentSize(size);

	return true;
}

void ScrollBorders::addBackground(ZStringView sprite) {
	if (m_bg)
		m_bg->removeFromParent();

	m_bg = NineSlice::create(sprite);
	m_bg->setID("background");
	this->addChild(m_bg, -10);

	this->positionBG();

	return;
}

void ScrollBorders::positionBG() {
	auto size = this->getContentSize();

	m_bg->setPosition(size / 2.f);
	m_bg->setContentSize(size - CCSize(25.f, 45.f));

	return;
}

void ScrollBorders::setTitle(ZStringView title) {
	m_title->setText(title);

	return;
}

void ScrollBorders::setString(ZStringView title) {
	m_title->setString(title.c_str());

	return;
}

void ScrollBorders::setContentSize(CCSize const& size) {
	CCNode::setContentSize(size + CCSize(0.f, 40.f));

	m_title->setPosition(size.width / 2.f, size.height + 27.f);
	m_title->limitLabelWidth(size.width - 70.f, 0.95f, 0.1f);

	m_top->setPosition(size.width / 2.f, size.height + 19.f);
	m_top->setContentWidth(size.width);

	m_bottom->setPosition(size.width / 2.f, 19.f);
	m_bottom->setContentWidth(size.width - 2.f); // adjust for side sprites

	m_left->setPosition(s_sideSpriteOffset,	size.height / 2.f + 19.f);
	m_left->setContentHeight(size.height);

	m_right->setPosition(size.width - s_sideSpriteOffset, size.height / 2.f + 19.f);
	m_right->setContentHeight(size.height);

	if (m_bg)
		this->positionBG();

	return;
}
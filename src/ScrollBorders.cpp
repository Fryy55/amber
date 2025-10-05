#include "ScrollBorders.hpp"

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

bool ScrollBorders::init(CCSize const& size, char const* title, char const* font) {
	if (!CCNode::init())
		return false;

	m_title = CCLabelBMFont::create(title, font);
	m_title->setID("title");
	this->addChild(m_title, 11);

	m_top = CCScale9Sprite::createWithSpriteFrameName("GJ_table_top_001.png");
	m_top->setID("top-sprite");
	this->addChild(m_top, 10);

	m_bottom = CCScale9Sprite::createWithSpriteFrameName("GJ_table_bottom_001.png");
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

void ScrollBorders::setContentSize(CCSize const& size) {
	CCNode::setContentSize(size);

	m_title->setPosition(size.width / 2.f, size.height + 8.f);
	m_title->limitLabelWidth(size.width - 70.f, 0.95f, 0.1f);

	m_top->setPosition(size.width / 2.f, size.height);
	m_top->setContentWidth(size.width);

	m_bottom->setPosition(size.width / 2.f, 0.f);
	m_bottom->setContentWidth(size.width - 2.f); // adjust for side sprites

	m_left->setPosition(s_sideSpriteOffset,	size.height / 2.f);
	m_left->setContentHeight(size.height);

	m_right->setPosition(size.width - s_sideSpriteOffset, size.height / 2.f);
	m_right->setContentHeight(size.height);

	return;
}
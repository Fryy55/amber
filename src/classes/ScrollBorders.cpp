#include "include/classes/ScrollBorders.hpp"

#include "../../include/classes/ColoredLabel.hpp"

using namespace amber;
using namespace geode::prelude;


static constexpr float s_sideSpriteOffset = 15.f;

struct ScrollBorders::Impl final {
	ColoredLabel* title;
	NineSlice* top;
	NineSlice* bottom;
	CCScale9Sprite* left;
	CCScale9Sprite* right;
	NineSlice* bg = nullptr;
};

ScrollBorders::ScrollBorders() : m_impl(std::make_unique<Impl>()) {}

ScrollBorders::~ScrollBorders() = default;


ScrollBorders* ScrollBorders::create(CCSize const& size) {
	return create(size, "");
}

ScrollBorders* ScrollBorders::create(CCSize const& size, ZStringView title, ZStringView font) {
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

	if (!ret)
		return nullptr;

	childScrollLayer->removeFromParent();
	childScrollLayer->setPosition(20.f, 31.f);
	ret->addChild(childScrollLayer);

	return ret;
}

bool ScrollBorders::init(CCSize const& size, ZStringView title, ZStringView font) {
	if (!CCNode::init())
		return false;

	m_impl->title = ColoredLabel::create(title, font);
	m_impl->title->setID("title");
	this->addChild(m_impl->title, 11);

	m_impl->top = NineSlice::createWithSpriteFrameName("GJ_table_top_001.png");
	m_impl->top->setID("top-sprite");
	this->addChild(m_impl->top, 10);

	m_impl->bottom = NineSlice::createWithSpriteFrameName("GJ_table_bottom_001.png");
	m_impl->bottom->setID("bottom-sprite");
	this->addChild(m_impl->bottom, 10);

	m_impl->left = CCScale9Sprite::createWithSpriteFrameName("GJ_table_side_001.png");
	m_impl->left->setID("left-sprite");
	this->addChild(m_impl->left, 9);

	m_impl->right = CCScale9Sprite::createWithSpriteFrameName("GJ_table_side_001.png");
	m_impl->right->setRotation(180.f);
	m_impl->right->setID("right-sprite");
	this->addChild(m_impl->right, 9);

	this->setAnchorPoint({ 0.5f, 0.5f });
	this->setContentSize(size);

	return true;
}

void ScrollBorders::addBackground(Background background) {
	this->addBackground(
		fmt::format("GJ_square0{}.png", static_cast<int>(background))
	);

	return;
}

void ScrollBorders::addBackground(ZStringView sprite) {
	auto& bg = m_impl->bg;
	if (bg)
		bg->removeFromParent();

	bg = NineSlice::create(sprite);
	bg->setID("background");
	this->addChild(bg, -10);

	this->positionBG();

	return;
}

void ScrollBorders::positionBG() {
	auto size = this->getContentSize();

	m_impl->bg->setPosition(size / 2.f);
	m_impl->bg->setContentSize(size - CCSize(25.f, 45.f));

	return;
}

void ScrollBorders::setTitle(ZStringView title) {
	m_impl->title->setText(title);

	return;
}

void ScrollBorders::setString(ZStringView title) {
	m_impl->title->setString(title.c_str());

	return;
}

void ScrollBorders::setContentSize(CCSize const& size) {
	CCNode::setContentSize(size + CCSize(0.f, 40.f));

	m_impl->title->setPosition(size.width / 2.f, size.height + 27.f);
	m_impl->title->limitLabelWidth(size.width - 70.f, 0.95f, 0.1f);

	m_impl->top->setPosition(size.width / 2.f, size.height + 19.f);
	m_impl->top->setContentWidth(size.width);

	m_impl->bottom->setPosition(size.width / 2.f, 19.f);
	m_impl->bottom->setContentWidth(size.width - 2.f); // adjust for side sprites

	m_impl->left->setPosition(s_sideSpriteOffset,	size.height / 2.f + 19.f);
	m_impl->left->setContentHeight(size.height);

	m_impl->right->setPosition(size.width - s_sideSpriteOffset, size.height / 2.f + 19.f);
	m_impl->right->setContentHeight(size.height);

	if (m_impl->bg)
		this->positionBG();

	return;
}
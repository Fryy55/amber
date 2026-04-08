/*
	vendored and modified from https://github.com/geode-sdk/geode/blob/main/loader/src/ui/nodes/Notification.cpp
	a90d204

	list of changes:
	remove `showNextNotification`
	replace `Notification` with `QuickNotification`
	replace #include for `Notification` to `QuickNotification`
	add `using namespace amber;`
	remove constexpr globals as they are defined in `QuickNotification.hpp`
	replace `CCLabelBMFont` with `ColoredLabel` in `init` for `m_impl->label`
	remove all mentions of `s_queue` and `showNextNotification`, adjust code logically
	replace "info-alert.png"_spr with "geode.loader/info-alert.png", silence the warning
	add `CCRemoveSelf` before `nullptr` in `hide`
*/
#include <amber/classes/QuickNotification.hpp>

#include <amber/classes/ColoredLabel.hpp>

#include <Geode/loader/Mod.hpp>
#include <Geode/ui/LoadingSpinner.hpp>
#include <Geode/ui/OverlayManager.hpp>

using namespace geode::prelude;
using namespace amber;


class QuickNotification::Impl final {
public:
	NineSlice* bg;
	CCLabelBMFont* label;
	CCNodeRGBA* content;
	CCNode* icon = nullptr;
	float time;
	bool showing = false;
};

QuickNotification::QuickNotification() : m_impl(std::make_unique<Impl>()) { }

QuickNotification::~QuickNotification() { }

bool QuickNotification::init(ZStringView text, CCNode* icon, float time) {
	if (!CCNodeRGBA::init()) return false;

	m_impl->icon = icon;
	m_impl->time = time;

	m_impl->bg = NineSlice::create("square02b_small.png", { 0, 0, 40, 40 });
	m_impl->bg->setColor({ 0, 0, 0 });
	this->addChild(m_impl->bg);

	m_impl->content = cocos2d::CCNodeRGBA::create();
	m_impl->content->setAnchorPoint({ .5f, .5f });
	m_impl->content->setCascadeOpacityEnabled(true);
	m_impl->content->setLayout(
		RowLayout::create()
			->setGap(5.f)
			->setAutoGrowAxis(0.f)
			->setAutoScale(false)
	);
	this->addChild(m_impl->content);

	if (icon) {
		m_impl->content->addChild(icon);
	}

	m_impl->label = ColoredLabel::create(text.c_str());
	m_impl->label->setScale(.6f);
	m_impl->content->addChild(m_impl->label);

	this->setScale(.75f);
	this->updateLayout();

	return true;
}

void QuickNotification::updateLayout() {
	if (m_impl->icon) {
		limitNodeWidth(m_impl->icon, 19.f, 1.f, 0.f);
	}

	m_impl->content->updateLayout();
	auto size = m_impl->content->getContentSize();
	m_impl->bg->setContentSize(size + CCSize{ 10.f, 10.f });
}

CCNode* QuickNotification::createIcon(NotificationIcon icon) {
	switch (icon) {
		default:
		case NotificationIcon::None: {
			return nullptr;
		} break;

		case NotificationIcon::Loading: {
			// gets resized later so size doesn't matter
			return LoadingSpinner::create(20.f);
		} break;

		case NotificationIcon::Success: {
			return CCSprite::createWithSpriteFrameName("GJ_completesIcon_001.png");
		} break;

		case NotificationIcon::Warning: {
			// @geode-ignore(unknown-resource)
			return CCSprite::createWithSpriteFrameName("geode.loader/info-alert.png");
		} break;

		case NotificationIcon::Error: {
			return CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
		} break;

		case NotificationIcon::Info: {
			return CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
		} break;
	}
}

QuickNotification* QuickNotification::create(ZStringView text, NotificationIcon icon, float time) {
	return QuickNotification::create(text, createIcon(icon), time);
}

QuickNotification* QuickNotification::create(ZStringView text, CCNode* icon, float time) {
	auto ret = new QuickNotification();
	if (ret->init(text, icon, time)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

void QuickNotification::setString(ZStringView text) {
	m_impl->label->setString(text.c_str());
	this->updateLayout();
}

void QuickNotification::setIcon(NotificationIcon icon) {
	this->setIcon(createIcon(icon));
}

void QuickNotification::setIcon(CCNode* icon) {
	if (m_impl->icon) {
		m_impl->icon->removeFromParent();
	}

	m_impl->icon = icon;

	if (icon) {
		m_impl->content->addChild(icon);
	}

	this->updateLayout();
}

CCNode* QuickNotification::getIcon() {
	return m_impl->icon;
}

void QuickNotification::setTime(float time) {
	m_impl->time = time;
	this->waitThenHide(); // reset timer
}

float QuickNotification::getTime() {
	return m_impl->time;
}

NineSlice* QuickNotification::getBG() {
	return m_impl->bg;
}

CCLabelBMFont* QuickNotification::getLabel() {
	return m_impl->label;
}

CCNodeRGBA* QuickNotification::getContent() {
	return m_impl->content;
}

bool QuickNotification::isShowing() {
	return m_impl->showing;
}

void QuickNotification::show() {
	if (m_impl->showing) return;

	auto winSize = CCDirector::get()->getWinSize();
	this->setPosition(winSize.width / 2, winSize.height / 4);
	this->setZOrder(CCScene::get()->getChildrenCount() > 0 ? CCScene::get()->getHighestChildZ() + 2 : 10);

	OverlayManager::get()->addChild(this);
	m_impl->showing = true;

	m_impl->content->setOpacity(0);
	m_impl->content->setScale(.6f);
	m_impl->content->setPositionY(-60.f);
	m_impl->bg->setOpacity(0);
	m_impl->bg->setScale(.6f);
	m_impl->bg->setPositionY(-60.f);

	this->runAction(CCSequence::create(
		CallFuncExt::create([this] {
			m_impl->content->runAction(CCFadeTo::create(NOTIFICATION_FADEIN, 255));
			m_impl->content->runAction(CCEaseExponentialOut::create(CCScaleTo::create(NOTIFICATION_FADEIN, 1.f, 1.f)));
			m_impl->content->runAction(CCEaseExponentialOut::create(CCMoveBy::create(NOTIFICATION_FADEIN, { 0.f, 60.f })));

			m_impl->bg->runAction(CCFadeTo::create(NOTIFICATION_FADEIN, 150));
			m_impl->bg->runAction(CCEaseExponentialOut::create(CCScaleTo::create(NOTIFICATION_FADEIN, 1.f, 1.f)));
			m_impl->bg->runAction(CCEaseExponentialOut::create(CCMoveBy::create(NOTIFICATION_FADEIN, { 0.f, 60.f })));
		}),

		CCDelayTime::create(NOTIFICATION_FADEIN),
		CCCallFunc::create(this, callfunc_selector(QuickNotification::waitThenHide)),
		nullptr
	));
}

void QuickNotification::waitThenHide() {
	this->stopAllActions();

	if (m_impl->time != 0.f) {
		this->runAction(CCSequence::create(
			CCDelayTime::create(m_impl->time),
			CCCallFunc::create(this, callfunc_selector(QuickNotification::hide)),
			nullptr
		));
	}
}

void QuickNotification::hide() {
	this->stopAllActions();

	this->runAction(CCSequence::create(
		CallFuncExt::create([this] {
			m_impl->content->runAction(CCEaseExponentialIn::create(CCFadeTo::create(NOTIFICATION_FADEOUT, 0)));
			m_impl->content->runAction(CCEaseExponentialIn::create(CCMoveBy::create(NOTIFICATION_FADEOUT, { 0.f, -25.f })));

			m_impl->bg->runAction(CCEaseExponentialIn::create(CCFadeTo::create(NOTIFICATION_FADEOUT, 0)));
			m_impl->bg->runAction(CCEaseExponentialIn::create(CCMoveBy::create(NOTIFICATION_FADEOUT, { 0.f, -25.f })));
		}),

		CCDelayTime::create(NOTIFICATION_FADEOUT * .25f),

		CallFuncExt::create([this] {
			m_impl->content->runAction(CCEaseExponentialIn::create(CCScaleTo::create(NOTIFICATION_FADEOUT, .2f, .2f)));
			m_impl->bg->runAction(CCEaseExponentialIn::create(CCScaleTo::create(NOTIFICATION_FADEOUT, .2f, .2f)));
		}),

		CCDelayTime::create(NOTIFICATION_FADEOUT * .75f),
		CCRemoveSelf::create(),
		nullptr
	));
}

void QuickNotification::cancel() {
	if (m_impl->showing) return this->hide();
}
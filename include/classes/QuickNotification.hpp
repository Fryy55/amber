/*
	vendored and modified from https://github.com/geode-sdk/geode/blob/main/loader/include/Geode/ui/Notification.hpp
	1376878

	list of changes:
	replace `namespace geode` with `namespace amber`
	remove `GEODE_DLL`
	remove doxygen
	replace `Notification` with `QuickNotification`
	remove `NotificationIcon` enum
	put constexpr globals as static members (including globals from `Notification.cpp`)
	adjust namespace indent
	make the dtor `override`
	add `geode::` qualification wherever needed
	include `ColoredLabel` and replace `CCLabelBMFont` with it in the getter
	remove `showNextNotification`
*/
#pragma once

#include "ColoredLabel.hpp"

#include <cocos2d.h>
#include <cocos-ext.h>
#include <Geode/binding/TextAlertPopup.hpp>
#include <Geode/ui/NineSlice.hpp>

namespace amber {

class QuickNotification : public cocos2d::CCNodeRGBA {
	class Impl;
	std::unique_ptr<Impl> m_impl;
protected:
	QuickNotification();
	~QuickNotification() override;

	bool init(geode::ZStringView text, cocos2d::CCNode* icon, float time);
	void updateLayout();

	static cocos2d::CCNode* createIcon(geode::NotificationIcon icon);

	void waitThenHide();

	geode::NineSlice* getBG();
	ColoredLabel* getLabel();
	cocos2d::CCNodeRGBA* getContent();

public:
	static QuickNotification* create(
		geode::ZStringView text,
		geode::NotificationIcon icon = geode::NotificationIcon::None,
		float time = NOTIFICATION_DEFAULT_TIME
	);

	static QuickNotification* create(
		geode::ZStringView text,
		cocos2d::CCNode* icon,
		float time = NOTIFICATION_DEFAULT_TIME
	);

	void setString(geode::ZStringView text);
	void setIcon(geode::NotificationIcon icon);
	void setIcon(cocos2d::CCNode* icon);
	cocos2d::CCNode* getIcon();
	void setTime(float time);

	float getTime();
	bool isShowing();

	void show();

	void hide();

	void cancel();

// Fields
public:
	static constexpr float NOTIFICATION_DEFAULT_TIME = 1.8f;
	static constexpr float NOTIFICATION_LONG_TIME = 4.f;
	static constexpr float NOTIFICATION_FADEIN = .3f;
	static constexpr float NOTIFICATION_FADEOUT = .5f;
};

} // namespace amber
/*
	vendored and modified from https://github.com/geode-sdk/geode/blob/main/loader/include/Geode/ui/Notification.hpp
	3987441

	list of changes:
	replace `namespace geode` with `namespace amber`
	replace `GEODE_DLL` with `AMBER_DLL` and include internal
	remove doxygen
	replace `Notification` with `QuickNotification`
	remove `NotificationIcon` enum
	include Geode/ui/Notification.hpp for the enum
	put constexpr globals as static members (including globals from `Notification.cpp`)
	adjust namespace indent
	make the dtor `override`
	add `geode::` qualification wherever needed
	remove `showNextNotification`
*/
#pragma once

#include "../_internal/common.hpp"

#include <Geode/binding/TextAlertPopup.hpp>
#include <Geode/ui/NineSlice.hpp>
#include <Geode/ui/Label.hpp>
#include <Geode/ui/Notification.hpp>

namespace amber {

class AMBER_DLL QuickNotification : public cocos2d::CCNodeRGBA {
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
	geode::Label* getLabel();
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

public: // Fields
	static constexpr float NOTIFICATION_DEFAULT_TIME = 1.8f;
	static constexpr float NOTIFICATION_LONG_TIME = 4.f;
	static constexpr float NOTIFICATION_FADEIN = .3f;
	static constexpr float NOTIFICATION_FADEOUT = .5f;
};

} // namespace amber
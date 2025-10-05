#pragma once

#include "prelude.hpp" // IWYU pragma: keep

#include <Geode/ui/Notification.hpp>


namespace amber {

class QuickNotification final : public geode::Notification {
public:
	static QuickNotification* create(
		std::string const& text,
		geode::NotificationIcon icon = geode::NotificationIcon::None,
		float time = geode::NOTIFICATION_DEFAULT_TIME
	);

	static QuickNotification* create(
		std::string const& text,
		cocos2d::CCSprite* icon,
		float time = geode::NOTIFICATION_DEFAULT_TIME
	);

private:
	bool init(std::string const&, cocos2d::CCSprite*, float);

	cocos2d::CCLabelBMFont* parseText(std::string const&);
	std::optional<std::string> collectTag(std::size_t, std::string const&);
	cocos2d::ccColor3B colorForTag(std::string const& tag);

public:
	void show();
	void hide();

private:
	void wait();
	void kill();
};

}
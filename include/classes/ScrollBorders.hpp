#pragma once

#include "../_internal/common.hpp"

#include <Geode/cocos/base_nodes/CCNode.h>


namespace amber {

class AMBER_DLL ScrollBorders : public cocos2d::CCNode {
	struct Impl;
	std::unique_ptr<Impl> m_impl;

protected:
	ScrollBorders();
	~ScrollBorders() override;

public:
	enum class Background : std::uint8_t {
		Brown = 1u,
		Blue,
		Green,
		Purple,
		Gray,
		White,
		Transparent
	};

public:
	static ScrollBorders* create(cocos2d::CCSize const& size);
	static ScrollBorders* create(
		cocos2d::CCSize const& size,
		geode::ZStringView title,
		geode::ZStringView font = "bigFont.fnt"
	);
	static ScrollBorders* create(geode::ScrollLayer* childScrollLayer);

protected:
	bool init(cocos2d::CCSize const&, geode::ZStringView, geode::ZStringView);

public:
	void addBackground(Background background = Background::Brown);
	void addBackground(geode::ZStringView sprite);

protected:
	void positionBG();

public:
	void setTitle(geode::ZStringView title);
	void setString(geode::ZStringView title);

	void setContentSize(cocos2d::CCSize const& size) override;
};

} // namespace amber
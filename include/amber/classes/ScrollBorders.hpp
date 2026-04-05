#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>

#include <amber/classes/ColoredLabel.hpp>


namespace amber {

class ScrollBorders final : public cocos2d::CCNode {
public:
	static ScrollBorders* create(cocos2d::CCSize const& size);
	static ScrollBorders* create(
		cocos2d::CCSize const& size,
		char const* title,
		char const* font = "bigFont.fnt"
	);
	static ScrollBorders* create(geode::ScrollLayer* childScrollLayer);

private:
	bool init(cocos2d::CCSize const&, char const*, char const*);

public:
	void addBackground(geode::ZStringView sprite = "GJ_square01.png");

private:
	void positionBG();

public:
	void setTitle(geode::ZStringView title);
	void setString(geode::ZStringView title);

	void setContentSize(cocos2d::CCSize const& size) override;
	void setContentWidth(float width) { setContentSize({ width, getContentHeight() }); }
	void setContentHeight(float height) { setContentSize({ getContentWidth(), height }); }

// Fields
private:
	static constexpr float s_sideSpriteOffset = 15.f;

	ColoredLabel* m_title;
	geode::NineSlice* m_top;
	geode::NineSlice* m_bottom;
	cocos2d::extension::CCScale9Sprite* m_left;
	cocos2d::extension::CCScale9Sprite* m_right;
	geode::NineSlice* m_bg = nullptr;
};

} // namespace amber
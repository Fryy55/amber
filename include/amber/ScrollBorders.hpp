#pragma once

#include <prelude/prelude.hpp> // IWYU pragma: keep

#include <Geode/cocos/base_nodes/CCNode.h>


namespace amber {

class ScrollBorders final : public cocos2d::CCNode {
public:
	static ScrollBorders* create(cocos2d::CCSize const& size);
	static ScrollBorders* create(
		cocos2d::CCSize const& size,
		char const* title,
		char const* font = "bigFont.fnt"
	);

private:
	bool init(cocos2d::CCSize const&, char const*, char const*);

	// Fields
	cocos2d::CCLabelBMFont* m_title;
	cocos2d::extension::CCScale9Sprite* m_top;
	cocos2d::extension::CCScale9Sprite* m_bottom;
	cocos2d::extension::CCScale9Sprite* m_left;
	cocos2d::extension::CCScale9Sprite* m_right;

	static constexpr float s_sideSpriteOffset = 15.f;

public:
	void setContentSize(cocos2d::CCSize const& size) override;
	void setContentWidth(float width) { setContentSize({ width, getContentHeight() }); }
	void setContentHeight(float height) { setContentSize({ getContentWidth(), height }); }
};

} // namespace amber
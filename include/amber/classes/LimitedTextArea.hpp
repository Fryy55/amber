#pragma once

#include <amber/prelude.hpp> // IWYU pragma: keep

#include <Geode/cocos/base_nodes/CCNode.h>


namespace amber {

class LimitedTextArea final : public cocos2d::CCNode {
public:
	static LimitedTextArea* create(
		cocos2d::CCSize const& size,
		std::string const& text,
		std::size_t charLimit = 16,
		char const* font = "bigFont.fnt",
		cocos2d::CCPoint const& textOffset = { 0.f, 2.f },
		cocos2d::ccColor4B const& bgColor = { 0, 0, 0, 90 }
	);

private:
	bool init(
		cocos2d::CCSize const&,
		std::string const&,
		std::size_t,
		char const*,
		cocos2d::CCPoint const&,
		cocos2d::ccColor4B const&
	);

public:
	[[nodiscard]] std::string const& getText() const { return m_text; }
	void setText(std::string const& text);
	[[nodiscard]] cocos2d::CCLabelBMFont* getLabel() const { return m_textLabel; }

	void setContentSize(cocos2d::CCSize const& size) override;
	void setContentWidth(float width) { setContentSize({ width, getContentHeight() }); }
	void setContentHeight(float height) { setContentSize({ getContentWidth(), height }); }

private:
	void updateLabelWidth();

	// Fields
	cocos2d::extension::CCScale9Sprite* m_bg;
	std::string m_text;
	cocos2d::CCLabelBMFont* m_textLabel;
	std::size_t m_charLimit;
};

} // namespace amber
#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>


namespace amber {

class LimitedTextArea final : public cocos2d::CCNode {
public:
	static LimitedTextArea* create(
		cocos2d::CCSize const& size,
		geode::ZStringView text,
		std::size_t charLimit = 16z,
		geode::ZStringView font = "bigFont.fnt",
		cocos2d::CCPoint const& textOffset = { 0.f, 2.f },
		cocos2d::ccColor4B const& bgColor = { .r=0u, .g=0u, .b=0u, .a=90u }
	);

private:
	bool init(
		cocos2d::CCSize const&,
		geode::ZStringView,
		std::size_t,
		geode::ZStringView,
		cocos2d::CCPoint const&,
		cocos2d::ccColor4B const&
	);

public:
	[[nodiscard]] geode::ZStringView getText() const { return m_text; }
	void setText(geode::ZStringView text);
	[[nodiscard]] cocos2d::CCLabelBMFont* getLabel() const { return m_textLabel; }

	void setContentSize(cocos2d::CCSize const& size) override;

private:
	void updateLabelWidth();

	// Fields
	geode::NineSlice* m_bg;
	std::string m_text;
	cocos2d::CCLabelBMFont* m_textLabel;
	std::size_t m_charLimit;
};

} // namespace amber
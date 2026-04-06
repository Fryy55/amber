#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>
#include <Geode/ui/TextRenderer.hpp>


namespace amber {

class ScrollTextArea final : public cocos2d::CCNode {
public:
	static ScrollTextArea* create(
		std::string_view text,
		cocos2d::CCSize const& size,
		float fontScale = 0.75f,
		std::string_view bmFont = "chatFont.fnt",
		cocos2d::ccColor4B const& bgColor = { 0, 0, 0, 75 }
	);

private:
	bool init(
		std::string_view,
		cocos2d::CCSize const&,
		float,
		std::string_view,
		cocos2d::ccColor4B const&
	);

public:
	~ScrollTextArea() override;

	[[nodiscard]] geode::ZStringView getFont() const { return m_font; }
	void setFont(std::string_view bmFont, bool updateLabel = true);
	[[nodiscard]] float getFontScale() const { return m_fontScale; }
	void setFontScale(float fontScale, bool updateLabel = true);
	[[nodiscard]] geode::ZStringView getText() const { return m_text; }
	void setText(std::string_view text, bool updateLabel = true);

	void updateLabel();

private:
	bool parseAndRenderText();
	std::optional<std::string> collectTag(std::size_t);
	cocos2d::ccColor3B colorForTag(std::string const&);

	// Fields
	float m_fontScale;
	std::string m_font;
	std::string m_text;
	cocos2d::CCSize m_size;
	geode::ScrollLayer* m_scrollLayer;
	cocos2d::CCMenu* m_contentMenu;
	geode::TextRenderer* m_textRenderer;

	static constexpr float s_totalScrollLayerOffset = 15.f;
};

} // namespace amber
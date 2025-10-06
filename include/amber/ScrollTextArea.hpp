#pragma once

#include <amber/prelude.hpp> // IWYU pragma: keep

#include <Geode/cocos/base_nodes/CCNode.h>
#include <Geode/ui/TextRenderer.hpp>


namespace amber {

class ScrollTextArea final : public cocos2d::CCNode {
public:
	static ScrollTextArea* create(
		std::string const& text,
		cocos2d::CCSize const& size,
		float fontScale = 0.75f,
		char const* bmFont = "chatFont.fnt",
		cocos2d::ccColor4B const& bgColor = { 0, 0, 0, 75 }
	);

private:
	bool init(
		std::string const&,
		cocos2d::CCSize const&,
		float,
		char const*,
		cocos2d::ccColor4B const&
	);

public:
	~ScrollTextArea() override;

	[[nodiscard]] char const* getFont() const { return m_font; }
	void setFont(char const* bmFont) { m_font = bmFont; }
	[[nodiscard]] float getFontScale() const { return m_fontScale; }
	void setFontScale(float fontScale) { m_fontScale = fontScale; }
	[[nodiscard]] std::string const& getText() const { return m_text; }
	void setText(std::string const& text);

	void updateLabel();

private:
	bool parseAndRenderText();
	std::optional<std::string> collectTag(std::size_t);
	cocos2d::ccColor3B colorForTag(std::string const&);

	// Fields
	float m_fontScale;
	char const* m_font;
	std::string m_text;
	cocos2d::CCSize m_size;
	geode::ScrollLayer* m_scrollLayer;
	cocos2d::CCMenu* m_contentMenu;
	geode::TextRenderer* m_textRenderer;

	static constexpr float s_totalScrollLayerOffset = 15.f;
};

} // namespace amber
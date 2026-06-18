#pragma once

#include "../_internal/common.hpp"

#include <Geode/cocos/base_nodes/CCNode.h>
#include <Geode/ui/TextRenderer.hpp>


namespace amber {

class AMBER_DLL ScrollTextArea : public cocos2d::CCNode {
	struct Impl;
	std::unique_ptr<Impl> m_impl;

protected:
	ScrollTextArea();
	~ScrollTextArea() override;

public:
	static ScrollTextArea* create(
		std::string_view text,
		cocos2d::CCSize const& size,
		float fontScale = 0.75f,
		std::string_view bmFont = "chatFont.fnt",
		cocos2d::ccColor4B const& bgColor = { .r=0u, .g=0u, .b=0u, .a=75u }
	);

protected:
	bool init(
		std::string_view,
		cocos2d::CCSize const&,
		float,
		std::string_view,
		cocos2d::ccColor4B const&
	);

public:
	[[nodiscard]] geode::ZStringView getFont() const noexcept;
	void setFont(std::string_view bmFont, bool updateLabel = true);
	[[nodiscard]] float getFontScale() const noexcept;
	void setFontScale(float fontScale, bool updateLabel = true);
	[[nodiscard]] geode::ZStringView getText() const noexcept;
	void setText(std::string_view text, bool updateLabel = true);

	void updateLabel();

protected:
	bool parseAndRenderText();
	std::optional<std::string> collectTag(std::size_t);
	cocos2d::ccColor3B colorForTag(std::string const&);
};

} // namespace amber
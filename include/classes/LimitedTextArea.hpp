#pragma once

#include "../_internal/common.hpp"

#include <Geode/cocos/base_nodes/CCNode.h>


namespace amber {

class AMBER_DLL LimitedTextArea : public cocos2d::CCNode {
	struct Impl;
	std::unique_ptr<Impl> m_impl;

protected:
	LimitedTextArea();
	~LimitedTextArea() override;

public:
	static LimitedTextArea* create(
		cocos2d::CCSize const& size,
		geode::ZStringView text,
		std::size_t charLimit = 16z,
		geode::ZStringView font = "bigFont.fnt",
		cocos2d::CCPoint const& textOffset = { 0.f, 2.f },
		cocos2d::ccColor4B const& bgColor = { .r=0u, .g=0u, .b=0u, .a=90u }
	);

protected:
	bool init(
		cocos2d::CCSize const&,
		geode::ZStringView,
		std::size_t,
		geode::ZStringView,
		cocos2d::CCPoint const&,
		cocos2d::ccColor4B const&
	);

public:
	[[nodiscard]] geode::ZStringView getText() const noexcept;
	void setText(geode::ZStringView text);
	[[nodiscard]] cocos2d::CCLabelBMFont* getLabel() const noexcept;

	void setContentSize(cocos2d::CCSize const& size) override;

protected:
	void updateLabelWidth();
};

} // namespace amber
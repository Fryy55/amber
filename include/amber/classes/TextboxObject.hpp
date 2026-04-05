#pragma once

#include <Geode/binding/DialogObject.hpp>


namespace amber {

class TextboxObject final : public DialogObject {
public:
	static TextboxObject* create(
		std::string_view name, cocos2d::ccColor3B const& nameColor,
		std::string_view text, cocos2d::CCSprite* sprite,
		float textScale = 1.f, float spriteScale = 1.f,
		cocos2d::CCPoint const& spriteOffset = { 0, 0 }, bool skippable = false
	);

private:
	bool init(
		std::string_view name, cocos2d::ccColor3B const& nameColor,
		std::string_view text, cocos2d::CCSprite* sprite,
		float textScale, float spriteScale,
		cocos2d::CCPoint const& spriteOffset, bool skippable
	);

public:
	// Fields
	geode::Ref<cocos2d::CCSprite> m_sprite;
	cocos2d::CCPoint m_spriteOffset;
	float m_spriteScale;
};

} // namespace amber
#include <amber/classes/TextboxObject.hpp>

using namespace amber;
using namespace geode::prelude;


TextboxObject* TextboxObject::create(
	std::string_view name, cocos2d::ccColor3B const& nameColor,
	std::string_view text, cocos2d::CCSprite* sprite,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	auto ret = new TextboxObject;

	if (ret->init(
		name, nameColor,
		text, sprite,
		textScale, spriteScale,
		spriteOffset, skippable
	)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool TextboxObject::init(
	std::string_view name, cocos2d::ccColor3B const& nameColor,
	std::string_view text, cocos2d::CCSprite* sprite,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	if (!DialogObject::init(
		{ name.data(), name.size() }, { text.data(), text.size() },
		1, textScale, skippable, nameColor
	)) return false;

	m_sprite = sprite;
	m_spriteScale = spriteScale;
	m_spriteOffset = spriteOffset;

	return true;
}
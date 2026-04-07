#include <amber/classes/TextboxObject.hpp>

using namespace amber;
using namespace geode::prelude;


TextboxObject* TextboxObject::create(
	std::string_view name, std::string_view text,
	cocos2d::CCSprite* sprite,
	cocos2d::ccColor3B const& nameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	auto ret = new TextboxObject;

	if (ret->init(
		name, text,
		sprite,
		nameColor,
		textScale, spriteScale,
		spriteOffset, skippable
	)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

TextboxObject* TextboxObject::create(
	std::string_view name, std::string_view text,
	ZStringView spriteFrameName,
	cocos2d::ccColor3B const& nameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	return create(
		name, text,
		CCSprite::createWithSpriteFrameName(spriteFrameName.c_str()),
		nameColor,
		textScale, spriteScale,
		spriteOffset, skippable
	);
}

TextboxObject* TextboxObject::create(
	std::string_view name, std::string_view text,
	DefaultSprite sprite,
	cocos2d::ccColor3B const& nameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	auto ret = new TextboxObject;

	if (ret->init(
		name, text,
		sprite,
		nameColor,
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
	std::string_view name, std::string_view text,
	cocos2d::CCSprite* sprite,
	cocos2d::ccColor3B const& nameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	if (!DialogObject::init(
		{ name.data(), name.size() }, { text.data(), text.size() },
		1, textScale, !skippable, nameColor
	)) return false;

	m_sprite = sprite;
	m_spriteOffset = spriteOffset;
	m_spriteScale = spriteScale;

	return true;
}

bool TextboxObject::init(
	std::string_view name, std::string_view text,
	DefaultSprite sprite,
	cocos2d::ccColor3B const& nameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	if (!DialogObject::init(
		{ name.data(), name.size() }, { text.data(), text.size() },
		static_cast<int>(sprite), textScale, !skippable, nameColor
	)) return false;

	m_sprite = nullptr;
	m_spriteOffset = spriteOffset;
	m_spriteScale = spriteScale;

	return true;
}

TextboxObject* TextboxObject::setOpenCallback(
	Function<void(TextboxChain*)> callback
) {
	m_callback = std::move(callback);

	return this;
}
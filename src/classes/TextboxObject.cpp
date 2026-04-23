#include "include/classes/TextboxObject.hpp"

using namespace amber;
using namespace geode::prelude;


TextboxObject* TextboxObject::create(
	std::string_view name, std::string_view text,
	cocos2d::CCSprite* sprite,
	cocos2d::ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	auto ret = new TextboxObject;

	if (ret->init(
		name, text,
		sprite,
		baseNameColor,
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
	cocos2d::ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	return create(
		name, text,
		CCSprite::createWithSpriteFrameName(spriteFrameName.c_str()),
		baseNameColor,
		textScale, spriteScale,
		spriteOffset, skippable
	);
}

TextboxObject* TextboxObject::create(
	std::string_view name, std::string_view text,
	DefaultSprite sprite,
	cocos2d::ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	auto ret = new TextboxObject;

	if (ret->init(
		name, text,
		sprite,
		baseNameColor,
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
	cocos2d::ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	if (!DialogObject::init(
		{ name.data(), name.size() }, { text.data(), text.size() },
		1, textScale, !skippable, baseNameColor
	)) return false;

	m_sprite = sprite;
	m_spriteOffset = spriteOffset;
	m_spriteScaleX = spriteScale;
	m_spriteScaleY = spriteScale;

	return true;
}

bool TextboxObject::init(
	std::string_view name, std::string_view text,
	DefaultSprite sprite,
	cocos2d::ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	cocos2d::CCPoint const& spriteOffset, bool skippable
) {
	if (!DialogObject::init(
		{ name.data(), name.size() }, { text.data(), text.size() },
		static_cast<int>(sprite), textScale, !skippable, baseNameColor
	)) return false;

	m_sprite = nullptr;
	m_spriteOffset = spriteOffset;
	m_spriteScaleX = spriteScale;
	m_spriteScaleY = spriteScale;

	return true;
}

TextboxObject* TextboxObject::setShowCallback(
	ShowCallback callback
) {
	m_callback = std::move(callback);

	return this;
}

TextboxObject* TextboxObject::setSkippable(bool skippable) {
	// robtop :troll:
	// (tbf this is bindings peoples not calling it correctly smh my head)
	m_skippable = !skippable;

	return this;
}

TextboxObject* TextboxObject::setSpriteScaleX(float scaleX) {
	m_spriteScaleX = scaleX;

	return this;
}

TextboxObject* TextboxObject::setSpriteScaleY(float scaleY) {
	m_spriteScaleY = scaleY;

	return this;
}

TextboxObject* TextboxObject::setSpriteScales(float scaleX, float scaleY) {
	m_spriteScaleX = scaleX;
	m_spriteScaleY = scaleY;

	return this;
}
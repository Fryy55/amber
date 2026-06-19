#include "include/classes/TextboxObject.hpp"

using namespace amber;
using namespace geode::prelude;


struct TextboxObject::Impl final {
	ShowCallback callback{};
	Ref<CCSprite> sprite;
	CCPoint spriteOffset;
	float spriteScaleX;
	float spriteScaleY;
};

TextboxObject::TextboxObject() : m_impl(std::make_unique<Impl>()) {}

TextboxObject::~TextboxObject() = default;


TextboxObject* TextboxObject::create(
	std::string_view name, std::string_view text,
	CCSprite* sprite,
	ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	CCPoint const& spriteOffset, bool skippable
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
	ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	CCPoint const& spriteOffset, bool skippable
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
	ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	CCPoint const& spriteOffset, bool skippable
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
	CCSprite* sprite,
	ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	CCPoint const& spriteOffset, bool skippable
) {
	if (!DialogObject::init(
		{ name.data(), name.size() }, { text.data(), text.size() },
		1, textScale, !skippable, baseNameColor
	)) return false;

	m_impl->sprite = sprite;
	m_impl->spriteOffset = spriteOffset;
	m_impl->spriteScaleX = spriteScale;
	m_impl->spriteScaleY = spriteScale;

	return true;
}

bool TextboxObject::init(
	std::string_view name, std::string_view text,
	DefaultSprite sprite,
	ccColor3B const& baseNameColor,
	float textScale, float spriteScale,
	CCPoint const& spriteOffset, bool skippable
) {
	if (!DialogObject::init(
		{ name.data(), name.size() }, { text.data(), text.size() },
		static_cast<int>(sprite), textScale, !skippable, baseNameColor
	)) return false;

	m_impl->sprite = nullptr;
	m_impl->spriteOffset = spriteOffset;
	m_impl->spriteScaleX = spriteScale;
	m_impl->spriteScaleY = spriteScale;

	return true;
}


TextboxObject* TextboxObject::setShowCallback(
	ShowCallback callback
) {
	m_impl->callback = std::move(callback);

	return this;
}

TextboxObject* TextboxObject::setSkippable(bool skippable) {
	// robtop :troll:
	// (tbf this is bindings peoples not calling it correctly smh my head)
	m_skippable = !skippable;

	return this;
}

TextboxObject* TextboxObject::setSpriteScaleX(float scaleX) {
	m_impl->spriteScaleX = scaleX;

	return this;
}

TextboxObject* TextboxObject::setSpriteScaleY(float scaleY) {
	m_impl->spriteScaleY = scaleY;

	return this;
}

TextboxObject* TextboxObject::setSpriteScales(float scaleX, float scaleY) {
	m_impl->spriteScaleX = scaleX;
	m_impl->spriteScaleY = scaleY;

	return this;
}


CCSprite* TextboxObject::_getSprite() const noexcept {
	return m_impl->sprite.data();
}

CCPoint const& TextboxObject::_getSpriteOffset() const noexcept {
	return m_impl->spriteOffset;
}

std::pair<float, float> TextboxObject::_getSpriteScales() const noexcept {
	return { m_impl->spriteScaleX, m_impl->spriteScaleY };
}

TextboxObject::ShowCallback& TextboxObject::_getShowCallback() noexcept {
	return m_impl->callback;
}
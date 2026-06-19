#pragma once

#include "../_internal/common.hpp"

#include <Geode/binding/DialogLayer.hpp>

#include "TextboxObject.hpp"


namespace amber {

class AMBER_DLL TextboxChain : public DialogLayer {
public:
	enum class Background : std::uint8_t {
		Brown = 1u,
		Blue,
		Green,
		Purple,
		Gray,
		White,
		Transparent
	};

	enum class StartAnimation : std::uint8_t {
		NoAnimation,
		FromCenter,
		FromLeft,
		FromRight,
		FromTop,
		Random
	};

	enum class TextboxPosition : std::uint8_t {
		Center,
		Top,
		Bottom
	};

public:
	template <typename ...TextboxObjects>
		requires (std::same_as<TextboxObject*, TextboxObjects> && ...)
	static TextboxChain* create(
		Background background,
		TextboxObject* object,
		TextboxObjects... objects
	) {
		auto ret = new TextboxChain;

		if (ret->init(background, object, objects...)) {
			ret->autorelease();
			return ret;
		}

		delete ret;
		return nullptr;
	}

protected:
	template <typename ...TextboxObjects>
	bool init(
		Background background,
		TextboxObject* object,
		TextboxObjects... objects
	) {
		if constexpr (sizeof...(objects) == 0u) {
			if (!DialogLayer::init(object, nullptr, static_cast<int>(background)))
				return false;
		} else {
			auto objectsArr = cocos2d::CCArray::create();
			objectsArr->addObject(object);
			(objectsArr->addObject(objects), ...);

			if (!DialogLayer::init(nullptr, objectsArr, static_cast<int>(background)))
				return false;
		}

		return true;
	}

public:
	void show(
		StartAnimation startAnimation = StartAnimation::Random,
		TextboxPosition position = TextboxPosition::Center
	);

	void setTextboxPosition(TextboxPosition position);
};

} // namespace amber
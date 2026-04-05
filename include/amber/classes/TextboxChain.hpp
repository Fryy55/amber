#pragma once

#include <Geode/binding/DialogLayer.hpp>

#include "TextboxObject.hpp"


namespace amber {

class TextboxChain final : public DialogLayer {
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

	template <typename ...Objects>
		requires (std::same_as<TextboxObject*, Objects> && ...)
	static TextboxChain* create(
		Background background,
		TextboxObject* object,
		Objects... objects
	) {
		auto ret = new TextboxChain;

		if (ret->init(background, object, objects...)) {
			ret->autorelease();
			return ret;
		}

		delete ret;
		return nullptr;
	}

private:
	template <typename ...Objects>
	bool init(
		Background background,
		TextboxObject* object,
		Objects... objects
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
	void displayDialogObject(DialogObject* object);
};

} // namespace amber
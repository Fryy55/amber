#include <amber/classes/TextboxChain.hpp>

using namespace amber;
using namespace geode::prelude;


void TextboxChain::displayDialogObject(DialogObject* object) {
	DialogLayer::displayDialogObject(object);

	auto sprite = static_cast<TextboxObject*>(object)->m_sprite.data();
	

	return;
}
#include <amber/classes/TextboxChain.hpp>

#include <Geode/modify/DialogLayer.hpp>

using namespace amber;
using namespace geode::prelude;


void TextboxChain::show(
	StartAnimation startAnimation,
	TextboxPosition position
) {
	this->setTextboxPosition(position);

	if (startAnimation == StartAnimation::Random)
		this->animateInRandomSide();
	else
		this->animateIn(static_cast<DialogAnimationType>(startAnimation));

	OverlayManager::get()->addChild(this, 5555);

	return;
}

void TextboxChain::setTextboxPosition(TextboxPosition position) {
	this->updateChatPlacement(static_cast<DialogChatPlacement>(position));

	return;
}


namespace amber::internal {

struct HDialogLayer final : Modify<HDialogLayer, DialogLayer> {
	$override
	void displayDialogObject(DialogObject* object) {
		DialogLayer::displayDialogObject(object);

		if (!this->getUserFlag("amber-instance"_spr))
			return;


		log::debug("amber::TextboxObject shown (from {})", Mod::get()->getID());

		auto obj = static_cast<TextboxObject*>(object);
		auto sprite = obj->m_sprite.data();

		if (!sprite) {
			m_characterSprite->setPosition(
				m_characterSprite->getPosition() + obj->m_spriteOffset
			);
			m_characterSprite->setScale(
				m_characterSprite->getScale() * obj->m_spriteScale
			);

			return;
		}

		sprite->setPosition(
			m_characterSprite->getPosition() + obj->m_spriteOffset
		);
		auto scaledCS = m_characterSprite->getScaledContentSize();
		sprite->setScaleX(
			scaledCS.width / sprite->getContentWidth() * obj->m_spriteScale
		);
		sprite->setScaleY(
			scaledCS.height / sprite->getContentHeight() * obj->m_spriteScale
		);
		sprite->setID("amber/custom-sprite");

		m_mainLayer->addChild(sprite, m_characterSprite->getZOrder());
		m_characterSprite->removeFromParent();
		m_characterSprite = sprite;

		if (auto& callback = obj->m_callback)
			callback(reinterpret_cast<TextboxChain*>(this));

		return;
	}
};

} // namespace amber::internal
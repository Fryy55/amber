#include "include/classes/TextboxChain.hpp"

#include "include/classes/ColoredLabel.hpp"

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

	OverlayManager::get()->addChild(this, CCScene::get()->getHighestChildZ());

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

		if (!typeinfo_cast<TextboxChain*>(this))
			return;


		log::info("amber::TextboxObject shown");

		auto obj = static_cast<TextboxObject*>(object);

		auto label = ColoredLabel::create("");
		auto pos = m_characterLabel->getPosition();
		label->setPosition(pos.x, pos.y);
		label->setScale(m_characterLabel->getScale());
		label->setColor(obj->m_color);
		label->setText(obj->m_character);
		label->setAnchorPoint(m_characterLabel->getAnchorPoint());
		label->setID("custom-label"_spr);

		m_mainLayer->addChild(label, m_characterLabel->getZOrder());
		m_characterLabel->removeFromParent();
		m_characterLabel = label;

		if (auto sprite = obj->m_sprite.data(); !sprite) { // if default sprite
			m_characterSprite->setPosition(
				m_characterSprite->getPosition() + obj->m_spriteOffset
			);
			m_characterSprite->setScaleX(
				m_characterSprite->getScaleX() * obj->m_spriteScaleX
			);
			m_characterSprite->setScaleY(
				m_characterSprite->getScaleY() * obj->m_spriteScaleY
			);
		} else {
			sprite->setPosition(
				m_characterSprite->getPosition() + obj->m_spriteOffset
			);
			auto scaledCS = m_characterSprite->getScaledContentSize();
			sprite->setScaleX(
				scaledCS.width / sprite->getContentWidth() * obj->m_spriteScaleX
			);
			sprite->setScaleY(
				scaledCS.height / sprite->getContentHeight() * obj->m_spriteScaleY
			);
			sprite->setID("custom-sprite"_spr);

			m_mainLayer->addChild(sprite, m_characterSprite->getZOrder());
			m_characterSprite->removeFromParent();
			m_characterSprite = sprite;
		}

		if (auto& callback = obj->m_callback)
			callback(reinterpret_cast<TextboxChain*>(this));

		return;
	}
};

} // namespace amber::internal
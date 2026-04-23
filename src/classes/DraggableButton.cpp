#include "include/classes/DraggableButton.hpp"

#include "include/utils/geometry.hpp"

using namespace amber;
using namespace geode::prelude;


DraggableButton* DraggableButton::create(
	CCSprite* sprite,
	ActivateCallback callback
) {
	auto ret = new DraggableButton;

	if (ret->init(sprite, callback)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

DraggableButton* DraggableButton::create(
	ZStringView spriteFrameName,
	ActivateCallback callback
) {
	auto ret = new DraggableButton;

	if (ret->init(spriteFrameName, callback)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

DraggableButton* DraggableButton::create(
	ZStringView labelText,
	ZStringView labelFont,
	ActivateCallback callback
) {
	auto ret = new DraggableButton;

	if (ret->init(labelText, labelFont, callback)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool DraggableButton::init(
	CCSprite* sprite,
	ActivateCallback& callback
) {
	if (!Button::initWithNode(
		sprite,
		[cb = std::move(callback)](Button* sender) mutable {
			cb(static_cast<DraggableButton*>(sender));
		}) || !this->commonInit()
	) return false;

	return true;
}

bool DraggableButton::init(
	ZStringView spriteFrameName,
	ActivateCallback& callback
) {
	if (!Button::initWithSpriteFrameName(
		spriteFrameName,
		[cb = std::move(callback)](Button* sender) mutable {
			cb(static_cast<DraggableButton*>(sender));
		}) || !this->commonInit()
	) return false;

	return true;
}

bool DraggableButton::init(
	ZStringView labelText,
	ZStringView labelFont,
	ActivateCallback& callback
) {
	if (!Button::initWithLabel(
		labelText,
		labelFont,
		[cb = std::move(callback)](Button* sender) mutable {
			cb(static_cast<DraggableButton*>(sender));
		}) || !this->commonInit()
	) return false;

	return true;
}

bool DraggableButton::commonInit() {
	if (!this->setArea(Area::Screen))
		return false;

	return true;
}

bool DraggableButton::setArea(Area area) {
	switch (area) {
		case Area::NoLimit:
			m_area = s_noLimitRect;
			return true;

		case Area::Screen:
			m_area = { { 0.f, 0.f }, CCDirector::get()->getWinSize() };
			return true;

		case Area::Parent:
			return this->setArea(this->getParent());

		default:
			return false;
	}
}

bool DraggableButton::setArea(CCNode* node) {
	if (!node)
		return false;

	m_area = utils::convertBoxToWorldSpace(node);

	return true;
}

void DraggableButton::activate() {
	// gode::Button resets pos on activate for some reason
	auto pos = this->getPosition();

	Button::activate();

	this->setPosition(pos.x, pos.y);

	return;
}

void DraggableButton::selected() {
	Button::selected();

	this->scheduleOnce(schedule_selector(DraggableButton::startDrag), m_delay);

	return;
}

void DraggableButton::unselected() {
	Button::unselected();

	this->unschedule(schedule_selector(DraggableButton::startDrag));

	return;
}

bool DraggableButton::ccTouchBegan(CCTouch* touch, CCEvent* event) {
	s_lastTouch = touch;

	return Button::ccTouchBegan(touch, event);
}

void DraggableButton::startDrag(float) {
	s_draggedButton = this;

	if (auto parent = this->getParent(); m_snap && parent)
		this->setPosition(parent->convertTouchToNodeSpace(s_lastTouch));

	if (m_dragStartedCallback)
		m_dragStartedCallback(this);

	return;
}

void DraggableButton::ccTouchMoved(CCTouch* touch, CCEvent* event) {
	s_lastTouch = touch;

	Button::ccTouchMoved(touch, event);

	auto btn = s_draggedButton;
	if (!btn)
		return;

	auto pos = btn->getPosition();
	if (utils::rectContains(btn->m_area, utils::convertBoxToWorldSpace(btn)))
		btn->m_lastValidPoint = pos;
	if (auto parent = btn->getParent()) {
		btn->setPosition(
			parent->convertToNodeSpace(
				parent->convertToWorldSpace(pos)
				+
				touch->getDelta()
			)
		);
	}

	if (btn->m_dragCallback)
		btn->m_dragCallback(btn, touch);

	return;
}

void DraggableButton::ccTouchEnded(CCTouch* touch, CCEvent* event) {
	if (auto btn = s_draggedButton) {
		btn->Button::ccTouchCancelled(touch, event);
		btn->dragReleased();

		return;
	}

	Button::ccTouchEnded(touch, event);

	return;
}

void DraggableButton::ccTouchCancelled(CCTouch* touch, CCEvent* event) {
	Button::ccTouchCancelled(touch, event);

	if (auto btn = s_draggedButton)
		btn->dragReleased();

	return;
}

void DraggableButton::dragReleased() {
	s_draggedButton = nullptr;

	if (
		m_area != s_noLimitRect
		&&
		!utils::rectContains(m_area, utils::convertBoxToWorldSpace(this))
	) this->setPosition(m_lastValidPoint);

	if (m_releaseCallback)
		m_releaseCallback(this);

	return;
}
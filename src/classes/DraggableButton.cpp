#include "include/classes/DraggableButton.hpp"

#include "include/utils/geometry.hpp"

using namespace amber;
using namespace geode::prelude;


static constexpr CCRect s_noLimitRect{ -1.f, -1.f, 0.f, 0.f };
static DraggableButton* s_draggedButton = nullptr;
static CCTouch* s_lastTouch = nullptr;

struct DraggableButton::Impl final {
	DragStartedCallback dragStartedCallback{};
	DragCallback dragCallback{};
	ReleaseCallback releaseCallback{};
	CCRect area;
	CCPoint lastValidPoint{ 0.f, 0.f };
	float delay = 0.5f;
	bool snap = true;
};

DraggableButton::DraggableButton() : m_impl(std::make_unique<Impl>()) {}

DraggableButton::~DraggableButton() = default;


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


float DraggableButton::getDelay() const noexcept {
	return m_impl->delay;
}

void DraggableButton::setDelay(float delay) noexcept {
	m_impl->delay = delay;

	return;
}

bool DraggableButton::getSnap() const noexcept {
	return m_impl->snap;
}

void DraggableButton::setSnap(bool snap) noexcept {
	m_impl->snap = snap;

	return;
}

CCRect DraggableButton::getArea() const noexcept {
	return m_impl->area;
}

bool DraggableButton::setArea(Area area) {
	switch (area) {
		case Area::NoLimit:
			m_impl->area = s_noLimitRect;
			return true;

		case Area::Screen:
			m_impl->area = { { 0.f, 0.f }, CCDirector::get()->getWinSize() };
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

	m_impl->area = utils::convertBoxToWorldSpace(node);

	return true;
}

void DraggableButton::setAreaRaw(CCRect const& area) noexcept {
	m_impl->area = area;

	return;
}

void DraggableButton::setDragStartedCallback(DragStartedCallback callback) {
	m_impl->dragStartedCallback = std::move(callback);

	return;
}

void DraggableButton::setDragCallback(DragCallback callback) {
	m_impl->dragCallback = std::move(callback);

	return;
}

void DraggableButton::setReleaseCallback(ReleaseCallback callback) {
	m_impl->releaseCallback = std::move(callback);

	return;
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

	this->scheduleOnce(schedule_selector(DraggableButton::startDrag), m_impl->delay);

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

	if (auto parent = this->getParent(); m_impl->snap && parent)
		this->setPosition(parent->convertTouchToNodeSpace(s_lastTouch));

	if (m_impl->dragStartedCallback)
		m_impl->dragStartedCallback(this);

	return;
}

void DraggableButton::ccTouchMoved(CCTouch* touch, CCEvent* event) {
	s_lastTouch = touch;

	Button::ccTouchMoved(touch, event);

	auto btn = s_draggedButton;
	if (!btn)
		return;

	auto pos = btn->getPosition();
	if (utils::rectContains(btn->m_impl->area, utils::convertBoxToWorldSpace(btn)))
		btn->m_impl->lastValidPoint = pos;
	if (auto parent = btn->getParent()) {
		btn->setPosition(
			parent->convertToNodeSpace(
				parent->convertToWorldSpace(pos)
				+
				touch->getDelta()
			)
		);
	}

	if (btn->m_impl->dragCallback)
		btn->m_impl->dragCallback(btn, touch);

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
		m_impl->area != s_noLimitRect
		&&
		!utils::rectContains(m_impl->area, utils::convertBoxToWorldSpace(this))
	) this->setPosition(m_impl->lastValidPoint);

	if (m_impl->releaseCallback)
		m_impl->releaseCallback(this);

	return;
}
#pragma once

#include "../_internal/common.hpp"

#include <Geode/ui/Button.hpp>


namespace amber {

class AMBER_DLL DraggableButton : public geode::Button {
	struct Impl;
	std::unique_ptr<Impl> m_impl;

protected:
	DraggableButton();
	~DraggableButton() override;

public:
	using ActivateCallback = geode::Function<void(DraggableButton* sender)>;
	using DragStartedCallback = geode::Function<void(DraggableButton* self)>;
	using DragCallback = geode::Function<void(DraggableButton* self, cocos2d::CCTouch* touch)>;
	using ReleaseCallback = DragStartedCallback;

	enum class Area : std::uint8_t {
		NoLimit,
		Screen,
		Parent
	};

public:
	static DraggableButton* create(
		cocos2d::CCSprite* sprite,
		ActivateCallback callback
	);
	static DraggableButton* create(
		geode::ZStringView spriteFrameName,
		ActivateCallback callback
	);
	static DraggableButton* create(
		geode::ZStringView labelText,
		geode::ZStringView labelFont,
		ActivateCallback callback
	);

protected:
	bool init(cocos2d::CCSprite*, ActivateCallback&);
	bool init(geode::ZStringView, ActivateCallback&);
	bool init(geode::ZStringView, geode::ZStringView, ActivateCallback&);

	bool commonInit();

public:
	[[nodiscard]] float getDelay() const noexcept;
	void setDelay(float delay) noexcept;
	[[nodiscard]] bool getSnap() const noexcept;
	void setSnap(bool snap) noexcept;
	[[nodiscard]] cocos2d::CCRect getArea() const noexcept;
	[[nodiscard]] bool setArea(Area area);
	[[nodiscard]] bool setArea(cocos2d::CCNode* node);
	void setAreaRaw(cocos2d::CCRect const& area) noexcept;

	void setDragStartedCallback(DragStartedCallback callback);
	void setDragCallback(DragCallback callback);
	void setReleaseCallback(ReleaseCallback callback);

	void activate() override;
	void selected() override;
	void unselected() override;

protected:
	bool ccTouchBegan(cocos2d::CCTouch*, cocos2d::CCEvent*) override;
	void startDrag(float);

	void ccTouchMoved(cocos2d::CCTouch*, cocos2d::CCEvent*) override;

	void ccTouchEnded(cocos2d::CCTouch*, cocos2d::CCEvent*) override;
	void ccTouchCancelled(cocos2d::CCTouch*, cocos2d::CCEvent*) override;
	void dragReleased();
};

} // namespace amber
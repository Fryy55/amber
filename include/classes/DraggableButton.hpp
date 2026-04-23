#pragma once

#include <Geode/ui/Button.hpp>


namespace amber {

class DraggableButton final : public geode::Button {
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

private:
	bool init(cocos2d::CCSprite*, ActivateCallback&);
	bool init(geode::ZStringView, ActivateCallback&);
	bool init(geode::ZStringView, geode::ZStringView, ActivateCallback&);

	bool commonInit();

public:
	[[nodiscard]] float getDelay() const noexcept { return m_delay; }
	void setDelay(float delay) noexcept { m_delay = delay; }
	[[nodiscard]] bool getSnap() const noexcept { return m_snap; }
	void setSnap(bool snap) noexcept { m_snap = snap; }
	[[nodiscard]] cocos2d::CCRect getArea() const noexcept { return m_area; }
	[[nodiscard]] bool setArea(Area area);
	[[nodiscard]] bool setArea(cocos2d::CCNode* node);
	void setAreaRaw(cocos2d::CCRect const& area) noexcept { m_area = area; }

	void setDragStartedCallback(DragStartedCallback callback) { m_dragStartedCallback = std::move(callback); }
	void setDragCallback(DragCallback callback) { m_dragCallback = std::move(callback); }
	void setReleaseCallback(ReleaseCallback callback) { m_releaseCallback = std::move(callback); }

	void activate() override;
	void selected() override;
	void unselected() override;

private:
	bool ccTouchBegan(cocos2d::CCTouch*, cocos2d::CCEvent*) override;
	void startDrag(float);

	void ccTouchMoved(cocos2d::CCTouch*, cocos2d::CCEvent*) override;

	void ccTouchEnded(cocos2d::CCTouch*, cocos2d::CCEvent*) override;
	void ccTouchCancelled(cocos2d::CCTouch*, cocos2d::CCEvent*) override;
	void dragReleased();

// Fields
private:
	static constexpr cocos2d::CCRect s_noLimitRect{ -1.f, -1.f, 0.f, 0.f };
	static inline DraggableButton* s_draggedButton = nullptr;
	static inline cocos2d::CCTouch* s_lastTouch = nullptr;

	DragStartedCallback m_dragStartedCallback{};
	DragCallback m_dragCallback{};
	ReleaseCallback m_releaseCallback{};
	cocos2d::CCRect m_area;
	cocos2d::CCPoint m_lastValidPoint{ 0.f, 0.f };
	float m_delay = 0.5f;
	bool m_snap = true;
};

} // namespace amber
#pragma once

#include <amber/prelude.hpp> // IWYU pragma: keep

#include <Geode/cocos/actions/CCActionInterval.h>


namespace amber::actions {

class ContentTo final : public cocos2d::CCActionInterval {
public:
	static ContentTo* create(float duration, float x = 0.f, float y = 0.f);

private:
	bool initWithDuration(float, float, float);
	void startWithTarget(cocos2d::CCNode*) override;
	void update(float) override;

	// Fields
	float m_startX;
	float m_startY;
	float m_deltaX;
	float m_deltaY;
	float m_endX;
	float m_endY;
};

} // namespace amber::actions
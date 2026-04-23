#pragma once

#include "../_internal/common.hpp"

#include <Geode/cocos/actions/CCActionInterval.h>


namespace amber::actions {

class AMBER_DLL ContentTo : public cocos2d::CCActionInterval {
public:
	static ContentTo* create(float duration, float width = 0.f, float height = 0.f);
	static ContentTo* create(float duration, cocos2d::CCSize const& size);

protected:
	bool initWithDuration(float, float, float);
	void startWithTarget(cocos2d::CCNode*) override;
	void update(float) override;

// Fields
protected:
	float m_startW;
	float m_startH;
	float m_deltaW;
	float m_deltaH;
	float m_endW;
	float m_endH;
};

} // namespace amber::actions
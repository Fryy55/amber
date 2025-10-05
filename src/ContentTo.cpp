#include <amber/actions/ContentTo.hpp>

using namespace geode::prelude;


ContentTo* ContentTo::create(float duration, float x, float y) {
	auto ret = new ContentTo;
	if (ret -> initWithDuration(duration, x, y)) {
		ret -> autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ContentTo::initWithDuration(float duration, float x, float y) {
	if (!CCActionInterval::initWithDuration(duration))
		return false;
	
	m_endX = x;
	m_endY = y;

	return true;
}

void ContentTo::startWithTarget(CCNode* target) {
	CCActionInterval::startWithTarget(target);

	m_startX = target -> getContentWidth();
	m_startY = target -> getContentHeight();

	if (!m_endX)
		m_endX = m_startX;
	if (!m_endY)
		m_endY = m_startY;

	m_deltaX = m_endX - m_startX;
	m_deltaY = m_endY - m_startY;

	return;
}

void ContentTo::update(float dt) {
	if (m_pTarget) {
		m_pTarget -> setContentWidth(m_startX + m_deltaX * dt);
		m_pTarget -> setContentWidth(m_startX + m_deltaX * dt);
	}

	return;
}
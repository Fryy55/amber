#include <amber/actions/ContentTo.hpp>

using namespace amber::actions;
using namespace geode::prelude;


ContentTo* ContentTo::create(float duration, float width, float height) {
	auto ret = new ContentTo;
	if (ret->initWithDuration(duration, width, height)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

ContentTo* ContentTo::create(float duration, CCSize const& size) {
	return create(duration, size.width, size.height);
}

bool ContentTo::initWithDuration(float duration, float width, float height) {
	if (!CCActionInterval::initWithDuration(duration))
		return false;
	
	m_endW = width;
	m_endH = height;

	return true;
}

void ContentTo::startWithTarget(CCNode* target) {
	CCActionInterval::startWithTarget(target);

	m_startW = target->getContentWidth();
	m_startH = target->getContentHeight();

	if (!m_endW)
		m_endW = m_startW;
	if (!m_endH)
		m_endH = m_startH;

	m_deltaW = m_endW - m_startW;
	m_deltaH = m_endH - m_startH;

	return;
}

void ContentTo::update(float dt) {
	if (m_pTarget) {
		m_pTarget->setContentWidth(m_startW + m_deltaW * dt);
		m_pTarget->setContentHeight(m_startH + m_deltaH * dt);
	}

	return;
}
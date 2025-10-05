#pragma once

#include <prelude/prelude.hpp> // IWYU pragma: keep

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>


namespace amber {

class Separator final : public cocos2d::CCNode {
public:
	static Separator* create(cocos2d::ccColor3B const& color, float fadeLength = 50.f, float totalLength = 160.f, float width = 2.f);

	void resize(float newLength);
	void setColor(cocos2d::ccColor3B const& color);
	void setOpacity(GLubyte opacity);

	void setContentWidth(float) = delete;
	void setContentHeight(float) = delete;
	void setContentSize(float) = delete;
	void setScaledContentSize(cocos2d::CCSize) = delete;

private:
	bool init(cocos2d::ccColor3B const&, float, float, float);

	// Fields
	cocos2d::CCLayerGradient* m_leftGradient;
	cocos2d::CCLayerColor* m_middle;
	cocos2d::CCLayerGradient* m_rightGradient;
	float m_fadeLength;
};

}
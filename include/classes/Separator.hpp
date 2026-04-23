#pragma once

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>


namespace amber {

class Separator final : public cocos2d::CCNodeRGBA {
public:
	static Separator* create(
		cocos2d::ccColor3B const& color = { .r=255u, .g=255u, .b=255u },
		float fadeLength = 50.f,
		float totalLength = 160.f,
		float width = 2.f
	);

private:
	bool init(cocos2d::ccColor3B const&, float, float, float);

public:
	void setContentSize(cocos2d::CCSize const& size) override;

	[[nodiscard]] float getFadeLength() const noexcept { return m_fadeLength; }
	void setFadeLength(float fadeLength);

	[[nodiscard]] cocos2d::ccColor3B const& getColor() noexcept override { return m_color; }
	void setColor(cocos2d::ccColor3B const& color) override;
	[[nodiscard]] GLubyte getOpacity() noexcept override { return m_opacity; }
	void setOpacity(GLubyte opacity) override;

// Fields
private:
	cocos2d::CCLayerGradient* m_leftGradient;
	cocos2d::CCLayerColor* m_middle;
	cocos2d::CCLayerGradient* m_rightGradient;
	float m_fadeLength;
	cocos2d::ccColor3B m_color;
	GLubyte m_opacity = 255u;
};

} // namespace amber
#pragma once

#include "../_internal/common.hpp"

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>


namespace amber {

class AMBER_DLL Separator : public cocos2d::CCNodeRGBA {
	struct Impl;
	std::unique_ptr<Impl> m_impl;

protected:
	Separator();
	~Separator() override;

public:
	static Separator* create(
		cocos2d::ccColor3B const& color = { .r=255u, .g=255u, .b=255u },
		float fadeLength = 50.f,
		float totalLength = 160.f,
		float width = 2.f
	);

protected:
	bool init(cocos2d::ccColor3B const&, float, float, float);

public:
	void setContentSize(cocos2d::CCSize const& size) override;

	[[nodiscard]] float getFadeLength() const noexcept;
	void setFadeLength(float fadeLength);

	[[nodiscard]] cocos2d::ccColor3B const& getColor() noexcept override;
	void setColor(cocos2d::ccColor3B const& color) override;
	[[nodiscard]] GLubyte getOpacity() noexcept override;
	void setOpacity(GLubyte opacity) override;
};

} // namespace amber
#pragma once

#include <prelude/prelude.hpp> // IWYU pragma: keep

#include <Geode/cocos/base_nodes/CCNode.h>


namespace amber {

class Padding final : public cocos2d::CCNode {
public:
	static Padding* create(float side);
	static Padding* create(float width, float height);

private:
	bool init(float, float);
};

} // namespace amber
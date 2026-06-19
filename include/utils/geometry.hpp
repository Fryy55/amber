#pragma once

#include "../_internal/common.hpp"

#include <Geode/cocos/cocoa/CCGeometry.h>


namespace amber::utils {

[[nodiscard]] AMBER_DLL cocos2d::CCRect convertBoxToWorldSpace(
	cocos2d::CCNode* node
) noexcept;

[[nodiscard]] AMBER_DLL bool rectContains(
	cocos2d::CCRect const& outer, cocos2d::CCRect const& inner
) noexcept;

} // namespace amber::utils
#pragma once

#include <Geode/cocos/cocoa/CCGeometry.h>


namespace amber::utils {

cocos2d::CCRect convertBoxToWorldSpace(cocos2d::CCNode* node) noexcept;

bool rectContains(cocos2d::CCRect const& outer, cocos2d::CCRect const& inner) noexcept;

} // namespace amber::utils
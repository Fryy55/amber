#include <amber/utils/geometry.hpp>

using namespace geode::prelude;


CCRect amber::utils::convertBoxToWorldSpace(CCNode* node) noexcept {
	auto area = node->boundingBox();
	if (auto parent = node->getParent())
		area.origin = parent->convertToWorldSpace(area.origin);

	return area;
}

bool amber::utils::rectContains(CCRect const& outer, CCRect const& inner) noexcept {
	return (
		outer.getMinX() <= inner.getMinX() // left
		&&
		inner.getMaxX() <= outer.getMaxX() // right
		&&
		outer.getMinY() <= inner.getMinY() // down
		&&
		inner.getMaxY() <= outer.getMaxY() // up
	);
}
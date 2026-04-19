#pragma once

#include <Geode/ui/Layout.hpp>


namespace amber::layouts {

class ListLayout final : public geode::AxisLayout {
private:
	ListLayout();

public:
	static ListLayout* create(float scrollLayerHeight, float gap = 0.f);

private:
	bool init(float, float);
};

} // namespace amber::layouts
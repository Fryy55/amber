#pragma once

#include "../_internal/common.hpp"

#include <Geode/ui/Layout.hpp>


namespace amber::layouts {

class AMBER_DLL ListLayout : public geode::AxisLayout {
protected:
	ListLayout();

public:
	static ListLayout* create(float scrollLayerHeight, float gap = 0.f);

protected:
	bool init(float, float);
};

} // namespace amber::layouts
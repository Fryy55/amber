#pragma once

#include <amber/prelude.hpp>

#include <Geode/ui/Layout.hpp>


namespace amber::layouts::ListLayout {

geode::AxisLayout* create(float scrollLayerHeight, float gap = 0.f);

} // namespace amber::layouts::ListLayout
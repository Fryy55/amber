#pragma once

#include <amber/prelude.hpp>

#include <Geode/ui/Layout.hpp>


namespace amber::layouts {

class ListLayout final : public geode::ColumnLayout {
public:
	static ListLayout* create(float scrollLayerHeight, float gap = 0.f);

private:
	ListLayout(float scrollLayerHeight, float gap);
};

} // namespace amber::layouts
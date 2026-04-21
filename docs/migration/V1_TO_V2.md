<!-- omit from toc -->
# amber v1 to v2 Migration Guide
amber v2.0.0 introduced a lot of new utilities and classes, but it also _broke_ a lot of existing APIs for the sake of better future experience and due to some breaking changes introduced in Geode v5. This documents aims to be the main migration guide to help ease the transition for your mods, in case you by some miracle were using amber before


<!-- omit from toc -->
# Table of Contents
- [Structure Changes](#structure-changes)
  - [`geode::prelude`](#geodeprelude)
  - [`<amber/classes/...>`](#amberclasses)
- [Removals](#removals)
- [API Changes](#api-changes)
  - [`WideTitleV3`](#widetitlev3)
  - [`ScrollBorders`](#scrollborders)
  - [`Separator`](#separator)
  - [`LimitedTextArea` and `ScrollTextArea`](#limitedtextarea-and-scrolltextarea)
  - [More on `ScrollTextArea`](#more-on-scrolltextarea)
- [Fixes and Improvements](#fixes-and-improvements)
  - [`ContentTo`](#contentto)
  - [`QuickNotification` and `ScrollTextArea`](#quicknotification-and-scrolltextarea)
  - [`WideTitleV3`](#widetitlev3-1)
- [Additions](#additions)


# Structure Changes
## `geode::prelude`
Prior to v2, amber added all its namespaces into `geode::prelude`. This was handy in case you are fine with having amber entities everywhere, but ultimately was removed. Due to the dynamic nature of amber v2, _there is currently no way to automatically use amber's namespace_

## `<amber/classes/...>`
Previously all _classes_ were accessible directly at the root of the amber include directory (e.g. `<amber/QuickNotification.hpp>`). Now all classes have their own subdirectory `classes/`, so the example include will become `<amber/classes/QuickNotification.hpp>`. Classes, of course, have their own "include everything header" at `<amber/classes/classes.hpp>`


# Removals
Random utilities (`random.hpp`) and `Padding` classes have been removed entirely due to Geode counterparts existing in v5. You can find them in `geode::utils` and `geode::Layout` scopes respectively


# API Changes
## `WideTitleV3`
Now registers itself automatically, as all (potential) settings + slightly revamped. See [WideTitleV3.md](../reference/settingsV3/WideTitleV3.md) for the current API

## `ScrollBorders`
An API got completely revamped. You can read more about it at [ScrollBorders.md](../reference/classes/ScrollBorders.md), but in short this class now can be created directly from a `geode::ScrollLayer` and will add it as its child. Its title now supports color tags, you can add a background to it and it was optimized with `geode::ZStringView` parameters and `geode::NineSlice` parts. Its content size now also perfectly matches its boundaries

## `Separator`
An API got completely revamped. Conventional "width" is now content height, `resize` was replaced with dynamic content size editing methods which are now the way to resize the separator. See [Separator.md](../reference/classes/Separator.md) for more info

## `LimitedTextArea` and `ScrollTextArea`
A lot of string function parameters have been replaced with views. This is unlikely to break something, but is still worth knowing

## More on `ScrollTextArea`
All setters now have a `bool updateLabel` parameter, which tells if the label should be updated after setting the value. By default it's `true` on all setters, meaning old code shouldn't break due to missing parameters/misbehaving, but it's worth looking into setting some of them to `false` whenever an update isn't needed to help performance


# Fixes and Improvements
## `ContentTo`
`ContentTo` action now has a new `create` function that takes a `CCSize const&`, has different parameter names and correctly scales content height (finally)

## `QuickNotification` and `ScrollTextArea`
Color tag parsing now handles more edge cases without failing

## `WideTitleV3`
`WideTitleV3` now fully supports descriptions, adding an `i` button at the top right of the node


# Additions
4 new classes ([ColoredLabel](../reference/classes/ColoredLabel.md), [DraggableButton](../reference/classes/DraggableButton.md), [TextboxObject](../reference/classes/TextboxObject.md) and [TextboxChain](../reference/classes/TextboxChain.md)) and new utilities ([geometry.hpp](../reference/utils/geometry.md)) have been added. You can read their short descriptions in the README.md and their detailed API by in the links above
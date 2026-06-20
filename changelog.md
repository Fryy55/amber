# 2.0.1
- Updated `[[nodiscard]]` attribution in `geometry.hpp` docs

# 2.0.0
- amber is now a _dynamic library_
- `geode::prelude` behavior moved to `amber::prelude`
- Removed `final` from classes
- Removed `random.hpp` and `Padding` due to Geode implementing these utilities
- Removed amber entities from `geode::prelude`
- Moved classes to `classes/` instead of raw root at `amber/`
- Revamped `ScrollBorders`
- Revamped `Separator`
- Fixed and revamped `ContentTo`
- `WideTitleV3` now registers itself and has been improved at handling different keys
- Changed string parameters in `QuickNotification`, `LimitedTextArea` and `ScrollTextArea` to views
- Added `bool updateLabel` parameters to `ScrollTextArea` setters
- Added:
    - `ColoredLabel`
    - `DraggableButton`
    - `TextboxObject`
    - `TextboxChain`
    - `geometry.hpp`
- Added amber documentation at `docs/`

For a more detailed changelog and migration guide see [V1_TO_V2.md](https://github.com/Fryy55/amber/blob/main/docs/migration/V1_TO_V2.md)

# 1.1.0
- Added a new class - `ListLayout`
- Fixed `random.hpp` erroring
- Removed Doxygen comments from `ContentTo.hpp`

# 1.0.1
- [CMakeLists.txt] Renamed `INCLUDE` to `INCLUDE_DIR` for clarity
- Moved `prelude.hpp` to `include/amber` for consistency

# 1.0.0
- Initial release
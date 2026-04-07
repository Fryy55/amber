# amber
Finally, a repo name that isn't an acronym, waow.

Offers general purpose classes/utilities I made for using in my Geode mods!

Check out [cue](https://github.com/dankmeme01/cue), another Geode library!

# Features
- Actions
    - `ContentTo`
- Layouts
    - `ListLayout` - a layout you can quickly apply to, for example, a `geode::ScrollLayer::m_contentLayer` for a nice, scrollable list
- Custom settings
    - `WideTitleV3` - info titles in settings
- General classes
    - `ColoredLabel` - a `cocos2d::CCLabelBMFont` that supports color tags (including custom ones like `<c-ff00ff>`)
    - `LimitedTextArea` - a text **display** node that is similar to a `geode::TextInput` in appearance, but is not intended for text input; setting its string to a string longer than its maximum configured length will add ellipsis at the end, massively helping render times of `cocos2d::CCLabelBMFont` used in it
    - `Padding` for `geode::Layout`s
    - `QuickNotification`, a `geode::Notification` derivative that has _no_ queue, allowing them to quickly fade away without stacking + a color tags integration
    - `ScrollBorders` - an accurately positioned border for lists, similar to level lists
    - `ScrollTextArea` - an `MDTextArea`-like display with no Markdown support and a color tags integration
    - `Separator` - a visual separator; similar to `edit_vLine_001.png`, but with customizable length, width, fade length, color and dynamic resizing
    - `TextboxObject` and `TextboxChain` - classes that extend `DialogObject` and `DialogLayer` to have better API and work great with custom portraits

# Usage
## Installing
Add the following lines to your `CMakeLists.txt`:

```cmake
CPMAddPackage("gh:Fryy55/amber@2.0.0")
target_link_libraries(${PROJECT_NAME} amber)
```
Replace `2.0.0` with the version you want to use.

You can also use a specific tag/branch/commit of amber like this:

`CPMAddPackage("gh:Fryy55/amber#b492c63")` - tag/branch/commit hash

## Using
Simply include headers (e.g. `#include <amber/classes/QuickNotification.hpp>`) and use them in your mods!

There is also a general "include everything" header (`<amber/amber.hpp>`), as well as grouped headers (e.g. `<amber/classes/classes.hpp>`).

> [!TIP]
> Normally, every utility/class/etc. is located in the `amber::*` namespace, however, if you are fine with leaking amber to every TU, you can add `set(AMBER_USE_NAMESPACE TRUE)` to your `CMakeLists.txt`. This will precompile the header that solely uses the namespace, thus enabling you to use features directly without explicitly using the namespace everywhere.

# License
This project is distributed under the **Apache-2.0 License**.

See `LICENSE` for permissions, conditions and limitations.

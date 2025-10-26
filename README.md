# amber
Finally, a repo name that isn't an acronym, waow.

Offers general purpose classes/utilities I made for using in my Geode mods!

`CMakeLists.txt` shamelessly taken and modified from [cue](https://github.com/dankmeme01/cue), another Geode library.

# Features
- Actions
    - `ContentTo`
- Custom settings
    - `WideTitleV3` - info titles in settings
- Utilities
    - `random.hpp`
- Convenience classes
    - `LimitedTextArea` - a text **display** node that is similar to a `geode::TextInput` in appearance, but is not intended for text input; setting its string to a string longer than its maximum configured length will add ellipsis at the end, massively helping render times of `cocos2d::CCLabelBMFont` used in it
    - `Padding` for `geode::Layout`s
    - `QuickNotification`, a `geode::Notification` derivative that has _no_ queue, allowing them to quickly fade away without stacking + a color tags integration
    - `ScrollBorders` - an accurately positioned border for lists, similar to level lists
    - `ScrollTextArea` - an `MDTextArea`-like display with no Markdown support and a color tags integration
    - `Separator` - a visual separator; similar to `edit_vLine_001.png`, but with customizable length, width, fade length and color

# Usage
## Installing
Add the following lines to your `CMakeLists.txt`:

```cmake
CPMAddPackage("gh:Fryy55/amber@1.0.0")
target_link_libraries(${PROJECT_NAME} amber)
```
Replace `1.0.0` with the version you want to use.

You can also use a specific tag/branch/commit of amber like this:

`CPMAddPackage("gh:Fryy55/amber#b492c63")` - tag/branch/commit hash

## Using
Simply include headers (e.g. `#include <amber/QuickNotification.hpp>`) and use them in your mods!

There is also a general "include everything" header (`<amber/amber.hpp>`), as well as grouped headers (e.g. `<amber/utils/utils.hpp>`).

> [!TIP]
> Normally, every utility/class/etc. is located in the `amber::*` namespace, however, `using namespace geode::prelude` also uses amber's namespace, so you can use these classes directly if you're used to `geode::prelude`.

# License
This project is distributed under the **Apache-2.0 License**.

See `LICENSE` for permissions, conditions and limitations.

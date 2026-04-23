# amber
Finally, a repo name that isn't an acronym, waow.

Offers general purpose classes/utilities I made for using in my Geode mods!

# Features
- Actions
    - `ContentTo`
- General classes
    - `ColoredLabel` - a `cocos2d::CCLabelBMFont` that supports color tags (including custom ones like `<c-ff00ff>`)
    - `DraggableButton` - a draggable button with customizable behavior and no `cocos2d::CCMenu` requirements
    - `LimitedTextArea` - a text **display** node that is similar to a `geode::TextInput` in appearance, but is not intended for text input; setting its string to a string longer than its maximum configured length will add ellipsis at the end, massively helping render times of `cocos2d::CCLabelBMFont` used in it
    - `QuickNotification` - a `geode::Notification` that has _no_ queue, allowing them to quickly fade away without stacking and a color tags integration
    - `ScrollBorders` - an accurately positioned border for lists, similar to level lists
    - `ScrollTextArea` - a `geode::MDTextArea`-like display with no Markdown support and a color tags integration
    - `Separator` - a visual separator; similar to `edit_vLine_001.png`, but with customizable length, width, fade length, color and dynamic resizing
    - `TextboxObject` and `TextboxChain` - classes that extend `DialogObject` and `DialogLayer` to have better API and work great with custom portraits
- Layouts
    - `ListLayout` - a layout you can quickly apply to, for example, a `geode::ScrollLayer::m_contentLayer` for a nice, scrollable list
- Custom settings
    - `WideTitleV3` - info titles in settings
- Utilities
    - `geometry.hpp` - geometry-related helper functions (mainly related to `cocos2d::CCRect`)

See [amber documentation](docs/reference) for full reference and examples

# Usage
Add amber as a dependency in your `mod.json`
```json
"dependencies": {
    "fryy_55.amber": {
        "version": ">=2.0.0",
        "required": true
    }
}
```

After that simply include headers (e.g. `#include <fryy_55.amber/include/classes/QuickNotification.hpp>`) and use them in your mods!

There is also a general "include everything" header (`<fryy_55.amber/include/amber.hpp>`), as well as grouped headers (e.g. `<fryy_55.amber/include/classes/classes.hpp>`)

> [!TIP]
> If you want to bring all amber entities to the global namespace you can use a `using namespace amber::prelude;` directive

# Migration
To help you migrate between major amber versions (e.g. from v1.x.x to v2.0.0) there is special [documentation](docs/migration). All relevant information is contained in files there (e.g. `V1_TO_V2.md` for v1 to v2 migration)

# License
This project is distributed under the **Apache-2.0 License**.

See `LICENSE` for permissions, conditions and limitations.

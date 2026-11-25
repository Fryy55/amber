# amber v2 to v3 Migration Guide
Compared to v2, amber v3 doesn't introduce much, and instead mainly focuses on tidying up whatever it can based on Geode v6 additions

## Removals
`ColoredLabel` is completely removed due to `geode::Label` providing similar functionality way better. See [v6 migration docs](https://docs.geode-sdk.org/tutorials/migrate-v6#geodelabel) for more information on that class

## API Changes
### Labels
Following this, classes that internally relied on `ColoredLabel` are switching to `geode::Label`, and a couple more `cocos2d::CCLabelBMFont`-reliant classes are doing the same. Most of the changes are pimpl-protected, but this concerns the following APIs:
- `QuickNotification`'s underlying label (following `geode::Notification` changes); keep in mind that it still has rich-text-enabled setters by default!
- `LimitedTextArea`'s underlying label
- `ScrollBorders`' underlying label
- `TextboxChain`'s and `TextboxObject`'s underlying name label
- `WideTitleV3`'s underlying label

### Include paths
Just like with most API mods in Geode v6, amber include paths change from `<fryy_55.amber/include/**/*.hpp>` to `<fryy_55.amber/**/*.hpp`, dropping `include`. Thus, to use `LimitedTextArea`, for example, in amber v3 you need to include `<fryy_55.amber/classes/LimitedTextArea.hpp>`. General header structure remains the same

### `LimitedTextArea`
`LimitedTextArea` gets a new parameter as a part of its `create` function - `bool rich = false`, which enables/disables color tag parsing. Old code might need to rearrange parameters to compile and, possibly, explicitly pass `true` to mimic old `ColoredLabel` behavior

### `WideTitleV3`
`WideTitleV3`'s padding now defaults to `15.0` instead of `10.0`. The setting itself also got a new key (`"offset"`) which defaults to `0.0` and dictates vertical offset of the label (see [WideTitleV3.md](../reference/settingsV3/WideTitleV3.md))

That's it, go enjoy this small but meaningful update!
# amber v2 to v3 Migration Guide
Compared to v2, amber v3 doesn't introduce much, and instead mainly focuses on tidying up whatever it can based on Geode v6 additions

## Removals
`ColoredLabel` is completely removed, due to `geode::Label` providing similar functionality way better. See [v6 migration docs](https://docs.geode-sdk.org/tutorials/migrate-v6#geodelabel) for more information on that class

## API Changes
Following this, classes that internally relied on `ColoredLabel` are switching to `geode::Label`, and a couple more `cocos2d::CCLabelBMFont`-reliant classes are doing the same. Most of the changes are pimpl-protected, but this concerns the following APIs:
- `QuickNotification`'s underlying label (following `geode::Notification` changes); keep in mind that it still has rich-text-enabled setters by default!
- `LimitedTextArea`'s underlying label

`LimitedTextArea` also gets a new parameter as a part of its string setter - `bool rich = false`. Old code might need to explicitly pass `true` to mimic old `ColoredLabel` behavior
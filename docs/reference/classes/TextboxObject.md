# TextboxObject
An object that describes a single textbox for display in [TextboxChain](TextboxChain.md)


# Useful in
[`amber::TextboxChain` applications](TextboxChain.md#useful-in)


# Key Methods
## Static
```c++
TextboxObject* create(
    std::string_view name, std::string_view text,
    cocos2d::CCSprite* sprite,
    cocos2d::ccColor3B const& baseNameColor = { .r=255u, .g=255u, .b=255u },
    float textScale = 1.f, float spriteScale = 1.f,
    cocos2d::CCPoint const& spriteOffset = { 0.f, 0.f }, bool skippable = true
);
TextboxObject* create(
    std::string_view name, std::string_view text,
    geode::ZStringView spriteFrameName,
    cocos2d::ccColor3B const& baseNameColor = { .r=255u, .g=255u, .b=255u },
    float textScale = 1.f, float spriteScale = 1.f,
    cocos2d::CCPoint const& spriteOffset = { 0.f, 0.f }, bool skippable = true
);
TextboxObject* create(
    std::string_view name, std::string_view text,
    DefaultSprite sprite,
    cocos2d::ccColor3B const& baseNameColor = { .r=255u, .g=255u, .b=255u },
    float textScale = 1.f, float spriteScale = 1.f,
    cocos2d::CCPoint const& spriteOffset = { 0.f, 0.f }, bool skippable = true
);
```
`create` functions. The only difference between them is what you pass - a ready `cocos2d::CCSprite`, a sprite frame name that will be used to create a sprite from a spritesheet or a default sprite from the enum. Default sprites are named like `CharacterExpression_Num`, where `Num` is the number of the sprite in the files (e.g. `ScratchTalking_10`)

The name in the created `amber::TextboxChain` is an `amber::ColoredLabel`, meaning _color tags works just fine with names_. Moreover, the `baseNameColor` parameter defines the _base color_, meaning setting it to green and setting the name to `"Example <cr>colored</c> name"` will color both `Example` and `name` green, while `colored` will be red

By default, all custom sprites are resized to fit the chat box, however you may pass custom scale as `spriteScale` and custom offset as `spriteOffset` to change its default properties

The `skippable` parameter defines if you can skip the text appearance animation by clicking before it finishes

## Member
All member functions return a `TextboxObject*` to self, meaning you can easily chain them inside a single, global `amber::TextboxChain::create` call to not create a lot of temporary variables

```c++
TextboxObject* setShowCallback(ShowCallback callback);
```
Sets a callback to run when this `TextboxObject` is _shown_. The callback signature is `void callback(TextboxChain* chain)`

```c++
TextboxObject* setSkippable(bool skippable);
```
Sets the skippable flag for the `TextboxObject`. This is provided as a separate method alongside passing the flag as a part of `create` because of how deep the `skippable` parameter is there, so you don't need to fill in 4 default parameters just to set it

```c++
TextboxObject* setSpriteScaleX(float scaleX);
TextboxObject* setSpriteScaleY(float scaleY);
TextboxObject* setSpriteScales(float scaleX, float scaleY);
```
Sets the sprite's scale in a more precise way. In case standard scaling from `create` isn't enough you can configure it per-dimension with these methods


# Usage
See [TextboxChain.md#Usage](TextboxChain.md#usage)
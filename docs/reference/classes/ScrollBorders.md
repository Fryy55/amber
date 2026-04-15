# ScrollBorders
Borders for lists, similar to in-game level lists. Has accurate content size, automatically scales with it, supports a title and/or background addition


# Useful in
Scrollable lists


# Key Methods
## Static
```c++
ScrollBorders* create(cocos2d::CCSize const& size);
ScrollBorders* create(
    cocos2d::CCSize const& size,
    geode::ZStringView title,
    geode::ZStringView font = "bigFont.fnt"
);
ScrollBorders* create(geode::ScrollLayer* childScrollLayer);
```
`create` functions. You can create borders with a specific size or with a size and a title string that will appear on top. You can also create borders that will _add an existing `geode::ScrollLayer` as a child_. In that case the size will be automatically set to match that of the passed scroll layer

## Member
```c++
void addBackground(Background background = Background::Brown);
void addBackground(geode::ZStringView sprite);
```
Functions to add a background to the borders. You can select from default backgrounds or add a _sprite_ (not a spritesheet frame) as a background

```c++
void setTitle(geode::ZStringView title);
void setString(geode::ZStringView title);
```
Title setters. Since `amber::ColoredLabel` is used for title, `setTitle` _parses color tags_, while `setString` just sets the raw string as title


# Usage
```c++
auto scrollLayer = ScrollLayer::create({ 340.f, 190.f });
auto borders = amber::ScrollBorders::create(scrollLayer);
borders->setTitle("Title <cg>example</c>");
borders->addBackground(amber::ScrollBorders::Background::Blue);
m_mainLayer->addChildAtPosition(borders, Anchor::Center);
```


# Notes
Changing content size dynamically repositions everything, so you can update everything in real time, _unless you've created borders with a `geode::ScrollLayer`_. In that case, you should move/resize these separately
# DraggableButton
A draggable, `cocos2d::CCMenu`-independent button


# Useful in
Global buttons for mobile devices (e.g. DevTools, Prism, etc.); extra customizable UI elements; joysticks; nodes, that can be resized via UI


# Key Methods
## Static
```c++
DraggableButton* create(
    cocos2d::CCSprite* sprite,
    ActivateCallback callback
);
DraggableButton* create(
    geode::ZStringView spriteFrameName,
    ActivateCallback callback
);
DraggableButton* create(
    geode::ZStringView labelText,
    geode::ZStringView labelFont,
    ActivateCallback callback
);
```
`create` function. Used to create a button with an existing sprite, a sprite frame name and a `cocos2d::CCLabelBMFont` as button sprite respectively

`ActivateCallback`'s signature is `void callback(DraggableButton* sender)`

## Member
```c++
[[nodiscard]] float getDelay() const noexcept;
void setDelay(float delay) noexcept;
```
Getters/setters for the delay until the button becomes draggable after beginning holding it (in seconds); default - `0.5f`

```c++
[[nodiscard]] bool getSnap() const noexcept;
void setSnap(bool snap) noexcept;
```
Getters/setters for the snap variable. If `true`, the button will automatically snap to the touch upon starting drag; default - `true`

```c++
[[nodiscard]] cocos2d::CCRect getArea() const noexcept;
[[nodiscard]] bool setArea(Area area);
[[nodiscard]] bool setArea(cocos2d::CCNode* node);
void setAreaRaw(cocos2d::CCRect const& area) noexcept;
```
Getters/setters for the _area_ within which the button can be dragged. Attempting to drag the button outside that area snaps the button back into the last valid position within the area; default - `Area::Screen`

`DraggableButton::Area` is an enum consisting of `NoLimit`, `Screen` and `Parent` values
- `NoLimit` disables the area system for the button entirely
- `Screen` makes the button draggable anywhere within the screen (default)
- `Parent` makes the button draggable within the _current_ parent's bounding box (see [Notes](#notes))

`cocos2d::CCNode*`-taking setter sets the area to the passed node's current bounding box. Called internally when setting `Area::Parent` as area

`bool` return from some setters indicates successful setting

`setAreaRaw` directly sets the passed `cocos2d::CCRect` as the button's area.

_The area rect is absolute (aka relative to the world), meaning 0.f, 0.f position is always the bottom left corner of the screen and no scale is considered_

```c++
void setDragStartedCallback(DragStartedCallback callback);
void setDragCallback(DragCallback callback);
void setReleaseCallback(ReleaseCallback callback);
```
Setters for callbacks that are called when dragging starts, when the button is dragged (each drag frame) and when the drag ends (button is released) respectively

Callback signatures are as follows:
| Callback Type         | Signature                                                       |
| --------------------- | --------------------------------------------------------------- |
| `DragStartedCallback` | `void callback(DraggableButton* self)`                          |
| `DragCallback`        | `void callback(DraggableButton* self, cocos2d::CCTouch* touch)` |
| `ReleaseCallback`     | `void callback(DraggableButton* self)`                          |

`cocos2d::CCTouch*` parameter in the `DragCallback` is the touch that triggered the callback

You can still freely use other base methods like ones for customizing selection animation that are provided by `geode::Button`


# Usage
```c++
auto btn = amber::DraggableButton::create( // create a button from a circle sprite
    CircleButtonSprite::createWithSpriteFrameName(
        "GJ_deleteIcon_001.png", 0.8f
    ),
    [](amber::DraggableButton* sender) static {
        amber::QuickNotification::create("<cf>Clicked</c>")->show();
    }
);

btn->setDelay(0.3f); // lower the delay before drag starts
btn->setSnap(false); // disable snapping on drag beginning

// set different callbacks
btn->setDragStartedCallback([](amber::DraggableButton* self) static {
    amber::QuickNotification::create("<cj>Started dragging</c>")->show();
});
btn->setDragCallback([](amber::DraggableButton* self, CCTouch* touch) static {
    log::debug("Button dragged to {}", touch->getLocation());
});
btn->setReleaseCallback([](amber::DraggableButton* self) static {
    amber::QuickNotification::create("<ca>Drag ended</c>")->show();
});

node->addChildAtPosition(btn, Anchor::Center)
// try setting area *after setting a parent*
if (!btn->setArea(amber::DraggableButton::Area::Parent))
    log::warn("Failed to set area for a button!");
```


# Notes
`Area::Parent` sets the _current_ parent's bounding box as the area for the button. This is important because it can easily lead to 2 common pitfalls:
1. Calling `setArea(amber::DraggableButton::Area::Parent)` on a button that is not yet added to a parent. This will simply not do anything as the parent doesn't exist for the button at the moment of the call, so _make sure to always check `bool` results from setters_ to avoid these
2. The area _isn't dynamic after setting_. This means that if your button's parent frequently changes its properties (position, scale, content size, etc.) it might be a good idea to set `self->setArea(amber::DraggableButton::Area::Parent);` as your button's _drag started_ callback to always update it on drag beginning
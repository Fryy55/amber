# QuickNotification
A queue-less notification with color tags support


# Useful in
Notifications that can be spammed; more visually appealing notifications


# Key Methods
Same API as `geode::Notification`, except strings support color tags (e.g. `"<cr>Error!</c>"`). Color tags specifics are exactly the same as in [ColoredLabel](ColoredLabel.md), as it is used internally

`void setString(geode::ZStringView)` works with color tags as expected


# Usage
```c++
auto btn = CCMenuItemExt::createSpriteExtra(
    sprite,
    [](CCMenuItemSpriteExtra*) static {
        amber::QuickNotification::create("Hello <cj>world</c>")->show();
    }
);
```


# Notes
Just as with regular notifications, remember to call `show` to actually display the notification!
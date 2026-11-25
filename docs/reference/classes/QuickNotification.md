# QuickNotification
A queue-less notification with color tags support


# Useful in
Notifications that can be spammed; more visually appealing notifications


# Key Methods
Same API as `geode::Notification`, except by default it sets _rich text_ for the underlying `geode::Label` on creation/`void setString(geode::ZStringView)`, which is mainly useful for color tags (e.g. `"<cr>Error!</c>"`)


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
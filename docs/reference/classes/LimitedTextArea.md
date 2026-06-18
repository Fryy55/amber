# LimitedTextArea
A read-only (from the end user perspective) text area that truncates its content


# Useful in
Nodes that need to truncate text to align it nicely; displaying the beginning of long, unreadable data data like Base64-encoded strings without rendering the entirety of it


# Key Methods
## Static
```c++
LimitedTextArea* create(
    cocos2d::CCSize const& size,
    geode::ZStringView text,
    std::size_t charLimit = 16z,
    geode::ZStringView font = "bigFont.fnt",
    cocos2d::CCPoint const& textOffset = { 0.f, 2.f },
    cocos2d::ccColor4B const& bgColor = { 0u, 0u, 0u, 90u }
);
```
`create` function

## Member
```c++
[[nodiscard]] geode::ZStringView getText() const noexcept;
void setText(geode::ZStringView text);
```
Getters/setters for the displayed string. String received via the getter is **not** truncated - it's the exact string passed via `create`/`setText`. The display string is automatically truncated after calling `setText`

```c++
[[nodiscard]] cocos2d::CCLabelBMFont* getLabel() const noexcept;
```
Getter for the `cocos2d::CCLabelBMFont` that is used for display


# Usage
```c++
auto area = amber::LimitedTextArea::create(
    { 150.f, 30.f },
    "Data", 20z, "goldFont.fnt",
    { 0.f, 2.f }, { .r=0u, .g=0u, .b=0u, .a=40u }
);
node->addChildAtPosition(area, Anchor::Center);

// in some function
area->setText(base64Data);
```
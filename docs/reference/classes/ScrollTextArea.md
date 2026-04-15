# ScrollTextArea
`geode::MDTextArea`, but with _only_ color tags support


# Useful in
Displaying arbitrary data (player input, web request responses, etc.) without worrying about contents messing up Markdown


# Key Methods
## Static
```c++
ScrollTextArea* create(
    std::string_view text,
    cocos2d::CCSize const& size,
    float fontScale = 0.75f,
    std::string_view bmFont = "chatFont.fnt",
    cocos2d::ccColor4B const& bgColor = { .r=0u, .g=0u, .b=0u, .a=75u }
);
```
`create` function. All parameters are self-explanatory; `size` is the size of the area to be created

## Member
```c++
[[nodiscard]] geode::ZStringView getFont() const;
void setFont(std::string_view bmFont, bool updateLabel = true);
[[nodiscard]] float getFontScale() const;
void setFontScale(float fontScale, bool updateLabel = true);
[[nodiscard]] geode::ZStringView getText() const;
void setText(std::string_view text, bool updateLabel = true);
```
Getters/setters for font, font scale and displayed text. Set `updateLabel` to `false` if you're updating multiple different values to not re-render every time!

```c++
void updateLabel();
```
Explicitly re-renders the text


# Usage
```c++
auto scrollArea = amber::ScrollTextArea::create(
    "<c-235ba6>Hello <cj>world</c>!</c>\nNew <ca>line</c> example",
    { 200.f, 260.f },
    1.2f, "bigFont.fnt",
    { .r=0u, .g=35u, .b=200u, .a=230u }
);

// in some callback
scrollArea->setText(text, false);
scrollArea->setFont("goldFont.fnt", false);
scrollArea->setFontScale(2.f); // re-renders
```


# Notes
Color tag parsing is the same as it is in [ColoredLabel](ColoredLabel.md)
# Separator
A dynamic visual separator with appearance similar to `edit_vLine_001.png`


# Useful in
Separating different UI parts in a texture pack-agnostic way and with more control


# Key Methods
## Static
```c++
Separator* create(
    cocos2d::ccColor3B const& color = { .r=255u, .g=255u, .b=255u },
    float fadeLength = 50.f,
    float totalLength = 160.f,
    float width = 2.f
);
```
`create` function. Parameters are pretty self-explanatory. _Width is content height, total length is content width_

## Member
```c++
[[nodiscard]] float getFadeLength() const noexcept;
void setFadeLength(float fadeLength);
```
Getters/setters for fade length

```c++
[[nodiscard]] cocos2d::ccColor3B const& getColor() noexcept;
void setColor(cocos2d::ccColor3B const& color);
[[nodiscard]] GLubyte getOpacity() noexcept;
void setOpacity(GLubyte opacity);
```
Getters/setters for color and opacity; default opacity - `255u`


# Usage
```c++
auto sep = amber::Separator::create(
    { .r=255u, .g=36u, .b=164u },
    70.f, 200.f, 5.f
);
sep->setOpacity(180u);
node->addChildAtPosition(sep, Anchor::Center);

// in some callback
sep->setColor({ .r=255u, .g=255u, .b=255u });
sep->setOpacity(200u);
sep->setContentSize({ 60.f, 3.f });
sep->setFadeLength(25.f);
```


# Notes
Change the separator's _content size_ in order to dynamically resize it. If the content width is _less than the fade length_, the _displayed_ fade length will be adjusted accordingly
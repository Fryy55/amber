# ColoredLabel
A `cocos2d::CCLabelBMFont`-like label that fully supports color tags


# Useful in
Any application `cocos2d::CCLabelBMFont` would be useful in


# Key Methods
## Static
```c++
ColoredLabel* create(
    geode::ZStringView text,
    geode::ZStringView font = "bigFont.fnt",
    bool nullptrOnFail = false
);
```
`create` function. Setting the `nullptrOnFail` parameter to `true` returns `nullptr` if color tag parsing critically failed; by default/with `false` it returns a valid label with a red `Failed to parse text.` message

## Member
```c++
void setText(geode::ZStringView text);
```
Sets colored text to display


# Usage
```c++
if (auto label = amber::ColoredLabel::create("Hello <cj>world</c>", "gjFont55.fnt", true))
    this->addChildAtPosition(label, geode::Anchor::Center);
```


# Notes
You don't have to use lowercase letters in custom tags. Uppercase and mixed tags equally work (e.g. `<c-Ff0EEa>` will be a valid starting tag)

You can fallback to `cocos2d::CCLabelBMFont`'s `setString` methods if you wish to bypass color tag parsing

Color tags can be nested (e.g. `<cf>This is an <cg>example</c> with nested colors</c>` will produce a light blue string with a green word `example` in the middle)
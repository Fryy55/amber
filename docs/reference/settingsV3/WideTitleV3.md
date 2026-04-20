# WideTitleV3
A wide title for the settings menu. Looks like a `cocos2d::CCLabelBMFont` that takes up the entire setting field (node)


# Useful in
Attention-grabbing labels in settings


# Key Fields
## Default
`"name"` - the actual string displayed as a title. [Supports color tags](../classes/ColoredLabel.md)

`"description"` - creates a description button (like on most settings)

`"enable-if"` - makes the title look grayed-out and shows an enable hint if false

## Custom
`"font"` (string) - sets the font of the label

`"padding"` (float) - adds padding to the sides of the label


# Usage
```json
"wide-title-setting-example": {
    "type": "custom:fryy_55.amber/wide-title",
    "name": "Custom <cs>Wide</c> Title",
    "description": "Example <cj>description</c>",
    "font": "bigFont.fnt",
    "padding": 100.0,
    "enable-if": "example-toggle",
    "enable-if-description": "\"Enable if\" desc"
}
```
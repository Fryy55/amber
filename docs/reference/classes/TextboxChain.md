# TextboxChain
A `DialogLayer`-like class for displaying dialogs with better API and full custom portraits support. See [TextboxObject](TextboxObject.md) for a textbox "blueprint" object


# Useful in
Any dialogs, and particularly dialogs with custom portraits


# Key Methods
## Static
```c++
TextboxChain* create(
    Background background,
    TextboxObject* object,
    TextboxObjects... objects
);
```
`create` function. `Background` enum has all default colors. [TextboxObject](TextboxObject.md)s passed will be the ones used for the chain; you can pass however many you want from 1 to [very big number]

## Member
```c++
void show(
    StartAnimation startAnimation = StartAnimation::Random,
    TextboxPosition position = TextboxPosition::Center
);
```
A convenience method to quickly add the chain at the `position` with a `startAnimation`. Check the enums for possible options

```c++
void setTextboxPosition(TextboxPosition position);
```
Sets the position of the textbox. _Can be used dynamically in `TextboxObject` callbacks_


# Usage
```c++
amber::TextboxChain::create(
    amber::TextboxChain::Background::Purple,
    amber::TextboxObject::create(
        "Colo<c-F5A9B8>red <c-ffffff>title</c> exa</c>mple",
        "This is an example with shakes<s010>!</s>",
        amber::TextboxObject::DefaultSprite::PotborTalking_21,
        { .r=91u, .g=206u, .b=250u },
        1.2f, 0.85f, { -7.f, 5.f }, false
    ),
    amber::TextboxObject::create(
        "A sprite frame example",
        "<cl>This text has a delay,<d050> however</c>\n"
        "<cl>nothing stops you from <i150>skipping</i></c>\n"
        "<cl>it <s050>altogether</s></c>",
        "GJ_coinsIcon2_001.png"
    ),
    amber::TextboxObject::create(
        "A sprite example",
        "This passes a <cf>raw sprite</c>,<d025> that is then <cg>resized</c> automatically",
        CCSprite::create("GJ_square01.png")
    )->setOpenCallback([](amber::TextboxChain* chain) static {
        chain->setTextboxPosition(amber::TextboxChain::TextboxPosition::Bottom);
    })->setSkippable(false)
)->show(amber::TextboxChain::StartAnimation::FromCenter);
```
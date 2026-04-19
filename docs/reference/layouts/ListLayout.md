# ListLayout
A layout that sets a list-like behavior


# Useful in
Any scrollable lists


# Key Methods
## Static
```c++
ListLayout* create(float scrollLayerHeight, float gap = 0.f);
```
`create` function. `scrollLayerHeight` is the _minimum height at which scrolling begins_ (usually the height of a `geode::ScrollLayer` you're adding a layout to)

## Member
This class inherits from `geode::AxisLayout`, which means you can easily customize all properties in-place using its methods


# Usage
```c++
auto scrollLayer = ScrollLayer::create({ 340.f, 190.f });
auto contentLayer = scrollLayer->m_contentLayer;
contentLayer->setLayout(
    amber::layouts::ListLayout::create(scrollLayer->getContentHeight())
);
```
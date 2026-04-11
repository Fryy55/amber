# ContentTo
An action that changes node's content size to a certain value


# Useful in
Dynamic animations with content size-responsive nodes like `geode::NineSlice`


# Key Methods
## Static
```c++
ContentTo* create(float duration, float width = 0.f, float height = 0.f);
ContentTo* create(float duration, cocos2d::CCSize const& size);
```
`create` functions. Doesn't change content size by default (see [Notes](#notes))

## Member
None


# Usage
Use it as any other action
```c++
node->runAction(
    amber::actions::ContentTo::create(0.3f, { 60.f, 70.f }) // create the action
);
```


# Notes
Leaving `0.f` on any of the parameters doesn't change it. Useful for only altering one dimension
```c++
amber::actions::ContentTo::create(0.5f, 0.f, 35.f) // doesn't change content width
```

Easing actions work exactly as you would expect
```c++
CCEaseInOut::create(amber::actions::ContentTo::create(1.f, 50.f), 2.f)
```
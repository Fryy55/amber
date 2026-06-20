# geometry.hpp
Geometry-related functions, particularly focusing on `cocos2d::CCRect`


# Useful in
`cocos2d::CCRect`-focused work, especially involving global (world-relative) rectangles


# Functions
```c++
[[nodiscard]] cocos2d::CCRect convertBoxToWorldSpace(cocos2d::CCNode* node) noexcept;
```
Converts `node`'s bounding box to a world-relative `cocos2d::CCRect`

```c++
[[nodiscard]] bool rectContains(cocos2d::CCRect const& outer, cocos2d::CCRect const& inner) noexcept;
```
Checks if one rectangle contains another


# Usage
`convertBoxToWorldSpace`, `rectContains`
```c++
auto pos = btn->getPosition();
if (amber::utils::rectContains(
    btn->m_area, amber::utils::convertBoxToWorldSpace(btn)
)) btn->m_lastValidPoint = pos;
```
#pragma once

#include "../_internal/common.hpp"

#include <Geode/cocos/label_nodes/CCLabelBMFont.h>


namespace amber {

class AMBER_DLL ColoredLabel : public cocos2d::CCLabelBMFont {
public:
	static ColoredLabel* create(geode::ZStringView text, geode::ZStringView font = "bigFont.fnt", bool nullptrOnFail = false);

protected:
	bool init(geode::ZStringView, geode::ZStringView, bool);

public:
	void setText(geode::ZStringView text);

protected:
	bool renderText(geode::ZStringView);
	std::optional<std::string> collectTag(std::size_t curPos, std::string_view string);
	cocos2d::ccColor3B colorForTag(std::string_view tag);

// Fields
protected:
	static constexpr char const* s_errorText = "<cr>Failed to parse text.</c>";
};

} // namespace amber
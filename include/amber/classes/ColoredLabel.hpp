#pragma once


#include <Geode/cocos/label_nodes/CCLabelBMFont.h>


namespace amber {

class ColoredLabel final : public cocos2d::CCLabelBMFont {
public:
	static ColoredLabel* create(geode::ZStringView text, geode::ZStringView font, bool nullptrOnFail = false);

private:
	bool init(geode::ZStringView, geode::ZStringView, bool);

public:
	void setText(geode::ZStringView text);

private:
	bool renderText(geode::ZStringView);
	std::optional<std::string> collectTag(std::size_t curPos, std::string_view string);
	cocos2d::ccColor3B colorForTag(std::string_view tag);

private:
	void setCString(char const*) override {}
	void setString(char const*) override {}
	void setString(char const*, bool) override {}
	void setString(unsigned short*, bool) override {}

// Fields
private:
	static constexpr char const* s_errorText = "<cr>Failed to parse text.</c>";
};

} // namespace amber
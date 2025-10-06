#pragma once

#include <amber/prelude.hpp> // IWYU pragma: keep

#include <Geode/loader/SettingV3.hpp>


namespace amber::settingsV3 {

class WideTitleV3 : public geode::SettingV3 {
public:
	static geode::Result<std::shared_ptr<geode::SettingV3>> parse(
		std::string const&,
		std::string const&,
		matjson::Value const&
	);

	bool load(matjson::Value const&) override { return true; }
	bool save(matjson::Value&) const override { return true; }

	bool isDefaultValue() const override { return true; }
	void reset() override {}

	geode::SettingNodeV3* createNode(float) override;

protected:
	// Fields
	float m_padding = 10.f;
	std::string m_font = "goldFont.fnt";
};


class WideTitleNodeV3 : public geode::SettingNodeV3 {
public:
	static WideTitleNodeV3* create(std::shared_ptr<WideTitleV3> const&, float, float, char const*);

protected:
	bool init(std::shared_ptr<WideTitleV3> const&, float, float, char const*);

	void updateState(cocos2d::CCNode*) override;

public:
	void onCommit() override {}
	void onResetToDefault() override {};

	[[nodiscard]] bool hasUncommittedChanges() const override { return false; }
	[[nodiscard]] bool hasNonDefaultValue() const override { return false; }

protected:
	// Fields
	cocos2d::CCLabelBMFont* m_label;
};

} // namespace amber
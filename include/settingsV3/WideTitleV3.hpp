#pragma once

#include "../_internal/common.hpp"

#include <Geode/loader/SettingV3.hpp>


namespace amber::settingsV3 {

class AMBER_DLL WideTitleV3 : public geode::SettingV3 {
	struct Impl;
	std::unique_ptr<Impl> m_impl;

public:
	WideTitleV3();
	~WideTitleV3() override;

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
};



class AMBER_DLL WideTitleNodeV3 : public geode::SettingNodeV3 {
	struct Impl;
	std::unique_ptr<Impl> m_impl;

protected:
	WideTitleNodeV3();
	~WideTitleNodeV3() override;

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
};

} // namespace amber::settingsV3
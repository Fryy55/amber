#include "WideTitleV3.hpp"

using namespace geode::prelude;


//* Setting
Result<std::shared_ptr<SettingV3>> WideTitleV3::parse(
	std::string const& key,
	std::string const& modID,
	matjson::Value const& json
) {
	auto ret = std::make_shared<WideTitleV3>();
	auto root = checkJson(json, "WideTitleV3");

	ret->init(key, modID);
	ret->parseNameAndDescription(root);
	ret->parseEnableIf(root);
	root.has("padding").into(ret->m_padding);
	root.has("font").into(ret->m_font);

	return root.ok(std::static_pointer_cast<SettingV3>(ret));
}

SettingNodeV3* WideTitleV3::createNode(float width) {
	return WideTitleNodeV3::create(
		std::static_pointer_cast<WideTitleV3>(shared_from_this()),
		width,
		m_padding,
		m_font.c_str()
	);
}

//* SettingNode
WideTitleNodeV3* WideTitleNodeV3::create(
	std::shared_ptr<WideTitleV3> const& setting,
	float width,
	float padding,
	char const* font
) {
	auto ret = new WideTitleNodeV3;

	if (ret->init(setting, width, padding, font)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool WideTitleNodeV3::init(
	std::shared_ptr<WideTitleV3> const& setting,
	float width,
	float padding,
	char const* font
) {
	if (!SettingNodeV3::init(setting, width))
		return false;

	auto menu = this->getButtonMenu();
	this->getNameLabel()->setVisible(false);

	auto const menuCW = this->getContentWidth() - padding * 2.f;

	m_label = CCLabelBMFont::create(this->getSetting()->getDisplayName().c_str(), font);
	m_label->limitLabelWidth(menuCW, 5.f, 0.1f);

	menu->setPositionX(padding);
	menu->setAnchorPoint({ 0.f, 0.5f });
	menu->setContentWidth(menuCW);

	menu->addChildAtPosition(m_label, Anchor::Center);

	this->updateState(nullptr);

	return true;
}

void WideTitleNodeV3::updateState(CCNode* invoker) {
	SettingNodeV3::updateState(invoker);

	m_label->setColor(
		this->getSetting()->shouldEnable() ? ccc3(255, 255, 255) : ccc3(166, 166, 166)
	);

	return;
}
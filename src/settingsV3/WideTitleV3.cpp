#include "include/settingsV3/WideTitleV3.hpp"

#include "../../include/classes/ColoredLabel.hpp"

using namespace amber::settingsV3;
using namespace geode::prelude;


//* Setting
struct WideTitleV3::Impl final {
	std::string font{ "goldFont.fnt" };
	float padding = 10.f;
};

WideTitleV3::WideTitleV3() : m_impl(std::make_unique<Impl>()) {}

WideTitleV3::~WideTitleV3() = default;


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
	root.has("padding").into(ret->m_impl->padding);
	root.has("font").into(ret->m_impl->font);

	return root.ok(std::static_pointer_cast<SettingV3>(ret));
}

SettingNodeV3* WideTitleV3::createNode(float width) {
	return WideTitleNodeV3::create(
		std::static_pointer_cast<WideTitleV3>(shared_from_this()),
		width,
		m_impl->padding,
		m_impl->font.c_str()
	);
}



//* SettingNode
static constexpr float s_statusBGPaddingWidth = 10.f;

struct WideTitleNodeV3::Impl final {
	amber::ColoredLabel* label;
	geode::NineSlice* statusBG;
};

WideTitleNodeV3::WideTitleNodeV3() : m_impl(std::make_unique<Impl>()) {}

WideTitleNodeV3::~WideTitleNodeV3() = default;

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

	float menuCW = this->getContentWidth() - padding * 2.f;

	auto label = m_impl->label = ColoredLabel::create(this->getSetting()->getDisplayName(), font);
	label->limitLabelWidth(menuCW, 5.f, 0.1f);

	menu->setPositionX(padding);
	menu->setAnchorPoint({ 0.f, 0.5f });
	menu->setContentWidth(menuCW);

	menu->addChildAtPosition(label, Anchor::Center);

	if (auto descBtn = this->getDescriptionButton()) {
		descBtn->removeFromParent();
		menu->addChildAtPosition(descBtn, Anchor::TopRight, { 0.f, -8.f });
	}

	auto statusLabel = this->getStatusLabel();
	statusLabel->setPositionY(7.f);
	statusLabel->setZOrder(7);

	auto statusBG = m_impl->statusBG = NineSlice::create("square02b_small.png");
	statusBG->setPosition(
		statusLabel->getPosition()
		-
		CCPoint{ s_statusBGPaddingWidth / 2.f, 0.f }
	);
	statusBG->setAnchorPoint({ 0.f, 0.5f });
	statusBG->setColor({ .r=0u, .g=0u, .b=0u });
	statusBG->setOpacity(120u);
	this->addChild(statusBG, 6);

	this->updateState(nullptr);

	return true;
}

void WideTitleNodeV3::updateState(CCNode* invoker) {
	SettingNodeV3::updateState(invoker);

	bool shouldEnable = this->getSetting()->shouldEnable();

	m_impl->label->setColor(
		shouldEnable ? ccc3(255, 255, 255) : ccc3(166, 166, 166)
	);

	m_impl->statusBG->setVisible(!shouldEnable);
	m_impl->statusBG->setContentSize(
		this->getStatusLabel()->getScaledContentSize()
		+
		CCSize{ s_statusBGPaddingWidth, 5.f }
	);

	return;
}


$on_mod(Loaded) {
	if (!Mod::get()->registerCustomSettingType("wide-title", &WideTitleV3::parse))
		log::error("Failed to register 'wide-title' setting");
}
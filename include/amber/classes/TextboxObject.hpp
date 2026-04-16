#pragma once

#include <Geode/binding/DialogObject.hpp>


namespace amber {

namespace internal {

struct HDialogLayer;

} // namespace internal


class TextboxChain;

class TextboxObject final : public DialogObject {
	friend struct internal::HDialogLayer;

public:
	enum class DefaultSprite : std::uint8_t {
		Spooky_1 = 1u,
		Glubfub_2,
		Gatekeeper_3,
		GlubfubConcerned_4,
		ShopkeeperTalking_5,
		ShopkeeperAnnoyed_6,
		GatekeeperDarkness_7,
		ScratchLookingLeft_8,
		ScratchLookingRight_9,
		ScratchTalking_10,
		ScratchRedEyes_11,
		ScratchAnnoyed_12,
		ScratchSuspiciousLookingRight_13,
		ScratchAngry_14,
		DemonGuardianEyes_15,
		DemonGuardianSmile_16,
		GlubfubShocked_17,
		GlubfubPanicking_18,
		PotborLookingLeft_19,
		PotborLookingRight_20,
		PotborTalking_21,
		PotborRedEyes_22,
		PotborAnnoyed_23,
		PotborSuspicious_24,
		PotborAngry_25,
		ScratchShrug_26,
		ScratchSuspiciousLookingDown_27,
		RobTop_28,
		ShopkeeperSuspicious_29,
		ShopkeeperAngry_30,
		ShopkeeperAngryLookingRight_31,
		ShopkeeperPossessed_32,
		Zolguroth_33,
		ShopkeeperShocked_34,
		ShopkeeperTwitching_35,
		ShopkeeperEmbarrassed_36,
		MechanicIdle_37,
		MechanicTalking_38,
		MechanicTalkingTiltedHead_39,
		DiamondShopkeeperIdle_40,
		DiamondShopkeeperTalking_41,
		DiamondShopkeeperTalkingWiderMouth_42,
		DiamondShopkeeperTalkingTiltedHead_43,
		MechanicBlackEyes_44,
		MechanicIdleTiltedHead_45,
		MechanicAngry_46,
		DiamondShopkeeperTalkingLookingBottomLeft_47,
		DiamondShopkeeperIdleTiltedHead_48,
		MechanicGreenEyes_49,
		MechanicPinkEyes_50,
		MechanicOpenMouth_51,
		ScratchChopper_52,
		WraithIdle_53,
		WraithTiltedHead_54,
		WraithAngry_55,
		WraithQuarterFace_56
	};

	using OpenCallback = geode::Function<void(TextboxChain* chain)>;

public:
	static TextboxObject* create(
		std::string_view name, std::string_view text,
		cocos2d::CCSprite* sprite,
		cocos2d::ccColor3B const& baseNameColor = { .r=255u, .g=255u, .b=255u },
		float textScale = 1.f, float spriteScale = 1.f,
		cocos2d::CCPoint const& spriteOffset = { 0.f, 0.f }, bool skippable = true
	);
	static TextboxObject* create(
		std::string_view name, std::string_view text,
		geode::ZStringView spriteFrameName,
		cocos2d::ccColor3B const& baseNameColor = { .r=255u, .g=255u, .b=255u },
		float textScale = 1.f, float spriteScale = 1.f,
		cocos2d::CCPoint const& spriteOffset = { 0.f, 0.f }, bool skippable = true
	);
	static TextboxObject* create(
		std::string_view name, std::string_view text,
		DefaultSprite sprite,
		cocos2d::ccColor3B const& baseNameColor = { .r=255u, .g=255u, .b=255u },
		float textScale = 1.f, float spriteScale = 1.f,
		cocos2d::CCPoint const& spriteOffset = { 0.f, 0.f }, bool skippable = true
	);

private:
	bool init(
		std::string_view name, std::string_view text,
		cocos2d::CCSprite* sprite,
		cocos2d::ccColor3B const& baseNameColor,
		float textScale, float spriteScale,
		cocos2d::CCPoint const& spriteOffset, bool skippable
	);
	bool init(
		std::string_view name, std::string_view text,
		DefaultSprite sprite,
		cocos2d::ccColor3B const& baseNameColor,
		float textScale, float spriteScale,
		cocos2d::CCPoint const& spriteOffset, bool skippable
	);

public:
	TextboxObject* setOpenCallback(OpenCallback callback);
	TextboxObject* setSkippable(bool skippable);

// Fields
private:
	OpenCallback m_callback{};
	geode::Ref<cocos2d::CCSprite> m_sprite;
	cocos2d::CCPoint m_spriteOffset;
	float m_spriteScale;
};

} // namespace amber
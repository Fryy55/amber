#include "QuickNotification.hpp"

#include <stack>

using namespace geode::prelude;


QuickNotification* QuickNotification::create(
	std::string const& text, NotificationIcon icon, float time
) {
	return create(text, createIcon(icon), time);
}

QuickNotification* QuickNotification::create(
	std::string const& text, CCSprite* icon, float time
) {
	auto ret = new QuickNotification;

	if (ret->init(text, icon, time)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

// NOOOO, my DRY collection :WHY:
bool QuickNotification::init(std::string const& text, CCSprite* icon, float time) {
	if (!CCNodeRGBA::init())
		return false;

	m_time = time;

	m_bg = CCScale9Sprite::create("square02b_small.png", { 0, 0, 40, 40 });
	m_bg->setColor({ 0, 0, 0 });
	this->addChild(m_bg);

	m_icon = icon;

	m_label = parseText(text);
	if (!m_label) {
		m_label = parseText("<cr>Failed to parse text.</c>"); // this won't nullptr TRUST :pray:
		m_icon = createIcon(NotificationIcon::Error);
	}

	m_label->setScale(0.6f);
	m_bg->addChild(m_label);

	if (m_icon) {
		m_bg->addChild(m_icon);
	}

	this->setScale(0.75f);
	this->updateLayout();

	return true;
}

CCLabelBMFont* QuickNotification::parseText(std::string const& string) {
	std::string resultStr = "";
	std::size_t labelSize = 0u;
	std::size_t stringSize = string.size();

	std::deque<std::tuple<std::size_t, std::size_t, ccColor3B>> colors{};
	std::stack<std::pair<std::size_t, ccColor3B>> colorsStack{};

	auto pushColor = [&colorsStack, &labelSize](ccColor3B const& color) {
		colorsStack.emplace(labelSize, color);
	};

	//! before calling check if stack is empty
	auto popColor = [&colorsStack, &labelSize, &colors]() {
		colors.emplace_front(colorsStack.top().first, labelSize, colorsStack.top().second);
		colorsStack.pop();
	};

	for (std::size_t i = 0u; i < stringSize; ++i) {
		char c = string[i];
		if (c == '<') {
			if (i + 1 >= stringSize)
				return nullptr;

			if (char c1 = string[i + 1]; c1 == 'c') {
				auto tagOpt = collectTag(i, string);
				if (!tagOpt)
					return nullptr;
				auto const& tag = tagOpt.value();

				pushColor(colorForTag(tag));

				// v
				// <cg>
				// 01234
				// tag - "g"
				// 0 + 1 + *2* = 3 ('>'), 4 on next iteration
				i += tag.size() + 2;

				continue; // skip adding anything to the result
			} else if (auto tagOpt = collectTag(i, string); c1 == '/') {
				if (!tagOpt)
					return nullptr;

				auto const& tag = tagOpt.value();

				if (tag != "c")
					goto skip; // safe equivalent of `c1 == '/' && tag == "c"` in `if`

				if (!colorsStack.empty())
					popColor();

				// v
				// </c>
				// 01234
				// tag - "c"
				// 0 + 1 + *2* = 3 ('>'), 4 on next iteration
				i += tag.size() + 2;

				continue; // skip adding anything to the result
			}
		}
		skip:

		// only executes when tag isn't a color tag or when there's no tag things in general i think
		if (c != '\n')
			++labelSize;
		resultStr.append(1, c);
	}

	auto label = CCLabelBMFont::create(resultStr.c_str(), "bigFont.fnt");
	auto letters = CCArrayExt<CCFontSprite*>(label->getChildren());

	// color the thing
	for (auto& [begin, end, color] : colors) {
		for (; begin < end; ++begin) {
			if (begin < labelSize)
				letters[begin]->setColor(color);
		}
	}

	return label;
}

std::optional<std::string> QuickNotification::collectTag(std::size_t curPos, std::string const& string) {
	std::string colorTag = "";
	auto stringSize = string.size();

	for (std::size_t offset = 2u;; ++offset) {
		if (curPos + offset >= stringSize)
			return std::nullopt;

		// replace the `for` condition
		if (auto c = string[curPos + offset]; c == '>')
			break;
		else
			colorTag.append(1, c);
	};

	return colorTag;
}

ccColor3B QuickNotification::colorForTag(std::string const& tag) {
	// tags are passed like "l", "f", "-ff00ff" etc

	// substr will throw otherwise
	if (!tag.size())
		return { 255, 255, 255 };

	// check for base tags
	if (tag == "b")
		return { 74, 82, 225 };
	else if (tag == "g")
		return { 64, 227, 72 };
	else if (tag == "l")
		return { 96, 171, 239 };
	else if (tag == "j")
		return { 50, 200, 255 };
	else if (tag == "y")
		return { 255, 255, 0 };
	else if (tag == "o")
		return { 255, 165, 75 };
	else if (tag == "r")
		return { 255, 90, 90 };
	else if (tag == "p")
		return { 255, 0, 255 };
	else if (tag == "a")
		return { 150, 50, 255 };
	else if (tag == "d")
		return { 255, 150, 255 };
	else if (tag == "c")
		return { 255, 255, 150 };
	else if (tag == "f")
		return { 150, 255, 255 };
	else if (tag == "s")
		return { 255, 220, 65 };

	// parse the "-ff00ff" things
	return cc3bFromHexString(tag.substr(1, tag.size() - 1)).unwrapOr(ccColor3B(255, 255, 255));
}

void QuickNotification::show() {
	if (!m_showing) {
		if (!this->getParent()) {
			auto winSize = CCDirector::get()->getWinSize();
			this->setPosition(winSize.width / 2, winSize.height / 4);
			this->setZOrder(CCScene::get()->getChildrenCount() > 0 ? CCScene::get()->getHighestChildZ() + 2 : 10);
		}
		SceneManager::get()->keepAcrossScenes(this);
		m_showing = true;
	}
	this->runAction(CCSequence::create(
		CCCallFunc::create(this, callfunc_selector(QuickNotification::animateIn)),
		// wait for fade-in to finish
		CCDelayTime::create(0.3f),
		CCCallFunc::create(this, callfunc_selector(QuickNotification::wait)),
		nullptr
	));

	return;
}

void QuickNotification::hide() {
	this->stopAllActions();
	this->runAction(CCSequence::create(
		CCCallFunc::create(this, callfunc_selector(QuickNotification::animateOut)),
		// wait for fade-out to finish
		CCDelayTime::create(1.f),
		CCCallFunc::create(this, callfunc_selector(QuickNotification::kill)),
		nullptr
	));

	return;
}

void QuickNotification::wait() {
	this->stopAllActions();
	if (m_time) {
		this->runAction(CCSequence::create(
			CCDelayTime::create(m_time),
			CCCallFunc::create(this, callfunc_selector(QuickNotification::hide)),
			nullptr
		));
	}

	return;
}

void QuickNotification::kill() {
	m_showing = false;

	SceneManager::get()->forget(this);

	this->removeFromParent();

	return;
}
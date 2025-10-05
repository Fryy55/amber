#include "ScrollTextArea.hpp"

using namespace geode::prelude;


ScrollTextArea* ScrollTextArea::create(
	std::string const& text,
	cocos2d::CCSize const& size,
	float fontScale,
	char const* font,
	cocos2d::ccColor4B const& bgColor
) {
	auto ret = new ScrollTextArea;

	if (ret->init(text, size, fontScale, font, bgColor)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ScrollTextArea::init(
	std::string const& text,
	cocos2d::CCSize const& size,
	float fontScale,
	char const* font,
	cocos2d::ccColor4B const& bgColor
) {
	if (!CCNode::init())
		return false;

	m_fontScale = fontScale;
	m_font = font;
	m_text = text;
	m_size = size - CCSize(s_totalScrollLayerOffset, 0.f);
	m_textRenderer = TextRenderer::create();
	m_textRenderer->retain();


	this->setContentSize(size);
	this->setAnchorPoint({ 0.5f, 0.5f });



	auto bg = CCScale9Sprite::create("square02b_001.png");
	bg->setContentSize(size);
	bg->setColor(to3B(bgColor));
	bg->setOpacity(bgColor.a);
	bg->setID("background");
	this->addChildAtPosition(bg, Anchor::Center);


	m_scrollLayer = ScrollLayer::create(m_size);

	m_contentMenu = CCMenu::create();
	m_contentMenu->setID("scroll-menu");

	m_scrollLayer->m_contentLayer->addChild(m_contentMenu);

	m_scrollLayer->setID("scroll-layer");
	this->addChildAtPosition(m_scrollLayer, Anchor::Center);
	m_scrollLayer->setPosition(s_totalScrollLayerOffset / 2.f, 0.f);



	this->updateLabel();

	return true;
}

ScrollTextArea::~ScrollTextArea() {
	m_textRenderer->release();
}

void ScrollTextArea::setText(std::string const& text) {
	m_text = text;
	this->updateLabel();

	return;
}

void ScrollTextArea::updateLabel() {
	m_textRenderer->begin(m_contentMenu, { 0.f, 0.f }, m_size);

	m_textRenderer->pushBMFont(m_font);
	m_textRenderer->pushScale(m_fontScale);

	if (!this->parseAndRenderText()) {
		m_textRenderer->end();

		this->setText("<cr>Failed to parse text.</c>"); // it will not recurse trust :pray:
		return;
	}

	m_textRenderer->end();


	// this is just straight up stolen impl but it works flawlessly so yeah
	if (m_contentMenu->getContentSize().height > m_size.height) {
		m_scrollLayer->m_contentLayer->setContentSize(
			m_contentMenu->getContentSize() + CCSize(0.f, 12.5f)
		);
		m_contentMenu->setPositionY(10.f);
	} else {
		m_scrollLayer->m_contentLayer->setContentSize(m_contentMenu->getContentSize());
		m_contentMenu->setPositionY(-2.5f);
	}

	m_scrollLayer->scrollToTop();

	return;
}

bool ScrollTextArea::parseAndRenderText() {
	std::string buffer = "";
	std::size_t textSize = m_text.size();

	for (std::size_t i = 0u; i < textSize; ++i) {
		char c = m_text[i];
		if (c == '<') {
			if (i + 1 >= textSize)
				return false;

			m_textRenderer->renderString(buffer);
			buffer.clear();

			if (char c1 = m_text[i + 1]; c1 == 'c') {
				auto tagOpt = collectTag(i);
				if (!tagOpt)
					return false;
				auto const& tag = tagOpt.value();

				m_textRenderer->pushColor(colorForTag(tag));

				// v
				// <cg>
				// 01234
				// tag - "g"
				// 0 + 1 + *2* = 3 ('>'), 4 on next iteration
				i += tag.size() + 2;

				continue; // skip adding anything to the buffer
			} else if (auto tagOpt = collectTag(i); c1 == '/') {
				if (!tagOpt)
					return false;

				auto const& tag = tagOpt.value();

				if (tag != "c")
					goto skip; // safe equivalent of `c1 == '/' && tag == "c"` in `if`

				m_textRenderer->popColor();

				// v
				// </c>
				// 01234
				// tag - "c"
				// 0 + 1 + *2* = 3 ('>'), 4 on next iteration
				i += tag.size() + 2;

				continue; // skip adding anything to the buffer
			}
		}
		skip:

		// only executes when tag isn't a color tag or when there's no tag things in general i think
		buffer.append(1, c);
	}

	m_textRenderer->renderString(buffer);

	return true;
}

std::optional<std::string> ScrollTextArea::collectTag(std::size_t curPos) {
	std::string colorTag = "";
	auto textSize = m_text.size();

	for (std::size_t offset = 2u;; ++offset) {
		if (curPos + offset >= textSize)
			return std::nullopt;

		// replace the `for` condition
		if (auto c = m_text[curPos + offset]; c == '>')
			break;
		else
			colorTag.append(1, c);
	};

	return colorTag;
}

ccColor3B ScrollTextArea::colorForTag(std::string const& tag) {
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
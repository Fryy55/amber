#include "include/classes/ScrollTextArea.hpp"

using namespace amber;
using namespace geode::prelude;


static constexpr float s_totalScrollLayerOffset = 15.f;

struct ScrollTextArea::Impl final {
	std::string font;
	std::string text;
	geode::ScrollLayer* scrollLayer;
	cocos2d::CCMenu* contentMenu;
	geode::TextRenderer* textRenderer;
	cocos2d::CCSize size;
	float fontScale;
};

ScrollTextArea::ScrollTextArea() : m_impl(std::make_unique<Impl>()) {}

ScrollTextArea::~ScrollTextArea() {
	m_impl->textRenderer->release();
}


ScrollTextArea* ScrollTextArea::create(
	std::string_view text,
	cocos2d::CCSize const& size,
	float fontScale,
	std::string_view font,
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
	std::string_view text,
	cocos2d::CCSize const& size,
	float fontScale,
	std::string_view font,
	cocos2d::ccColor4B const& bgColor
) {
	if (!CCNode::init())
		return false;

	m_impl->fontScale = fontScale;
	m_impl->font = font;
	m_impl->text = text;
	m_impl->size = size - CCSize(s_totalScrollLayerOffset, 0.f);
	m_impl->textRenderer = TextRenderer::create();
	m_impl->textRenderer->retain();


	this->setContentSize(size);
	this->setAnchorPoint({ 0.5f, 0.5f });



	auto bg = NineSlice::create("square02b_001.png");
	bg->setContentSize(size);
	bg->setColor(to3B(bgColor));
	bg->setOpacity(bgColor.a);
	bg->setID("background");
	this->addChildAtPosition(bg, Anchor::Center);


	auto scrollLayer = m_impl->scrollLayer = ScrollLayer::create(m_impl->size);

	auto contentMenu = m_impl->contentMenu = CCMenu::create();
	contentMenu->setID("scroll-menu");

	scrollLayer->m_contentLayer->addChild(contentMenu);

	scrollLayer->setID("scroll-layer");
	this->addChildAtPosition(scrollLayer, Anchor::Center);
	scrollLayer->setPosition(s_totalScrollLayerOffset / 2.f, 0.f);



	this->updateLabel();

	return true;
}


ZStringView ScrollTextArea::getFont() const noexcept {
	return m_impl->font;
}

void ScrollTextArea::setFont(std::string_view bmFont, bool updateLabel) {
	m_impl->font = bmFont;

	if (updateLabel)
		this->updateLabel();

	return;
}

float ScrollTextArea::getFontScale() const noexcept {
	return m_impl->fontScale;
}

void ScrollTextArea::setFontScale(float fontScale, bool updateLabel) {
	m_impl->fontScale = fontScale;

	if (updateLabel)
		this->updateLabel();

	return;
}

ZStringView ScrollTextArea::getText() const noexcept {
	return m_impl->text;
}

void ScrollTextArea::setText(std::string_view text, bool updateLabel) {
	m_impl->text = text;

	if (updateLabel)
		this->updateLabel();

	return;
}


void ScrollTextArea::updateLabel() {
	auto textRenderer = m_impl->textRenderer;
	auto contentMenu = m_impl->contentMenu;
	auto scrollLayer = m_impl->scrollLayer;

	textRenderer->begin(contentMenu, { 0.f, 0.f }, m_impl->size);

	textRenderer->pushBMFont(m_impl->font.c_str());
	textRenderer->pushScale(m_impl->fontScale);

	if (!this->parseAndRenderText()) {
		textRenderer->end();

		this->setText("<cr>Failed to parse text.</c>"); // it will not recurse trust :pray:
		return;
	}

	textRenderer->end();


	// this is just straight up stolen impl but it works flawlessly so yeah
	if (contentMenu->getContentSize().height > m_impl->size.height) {
		scrollLayer->m_contentLayer->setContentSize(
			contentMenu->getContentSize() + CCSize(0.f, 12.5f)
		);
		contentMenu->setPositionY(10.f);
	} else {
		scrollLayer->m_contentLayer->setContentSize(contentMenu->getContentSize());
		contentMenu->setPositionY(-2.5f);
	}

	scrollLayer->scrollToTop();

	return;
}

bool ScrollTextArea::parseAndRenderText() {
	std::string buffer = "";
	auto const& text = m_impl->text;
	std::size_t textSize = text.size();
	auto textRenderer = m_impl->textRenderer;

	for (std::size_t i = 0u; i < textSize; ++i) {
		char c = text[i];
		if (c == '<') {
			if (i + 1 >= textSize)
				goto skip;

			textRenderer->renderString(buffer);
			buffer.clear();

			if (char c1 = text[i + 1]; c1 == 'c') {
				auto tagOpt = collectTag(i);
				if (!tagOpt)
					return false;
				auto const& tag = tagOpt.value();

				textRenderer->pushColor(colorForTag(tag));

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

				textRenderer->popColor();

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

	textRenderer->renderString(buffer);

	return true;
}

std::optional<std::string> ScrollTextArea::collectTag(std::size_t curPos) {
	std::string colorTag = "";
	auto textSize = m_impl->text.size();

	for (std::size_t offset = 2u;; ++offset) {
		if (curPos + offset >= textSize)
			return std::nullopt;

		// replace the `for` condition
		if (auto c = m_impl->text[curPos + offset]; c == '>')
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
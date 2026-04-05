#include <amber/classes/ColoredLabel.hpp>

#include <stack>

using namespace amber;
using namespace geode::prelude;


ColoredLabel* ColoredLabel::create(ZStringView text, ZStringView font, bool nullptrOnFail) {
	auto ret = new ColoredLabel;

	if (ret->init(text, font, nullptrOnFail)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ColoredLabel::init(ZStringView text, ZStringView font, bool nullptrOnFail) {
	if (!CCLabelBMFont::initWithString("", font.c_str()))
		return false;

	if (!this->renderText(text)) {
		if (nullptrOnFail)
			return false;
		else
			this->renderText(s_errorText);
	}

	return true;
}

void ColoredLabel::setText(ZStringView text) {
	if (!this->renderText(text))
		this->renderText(s_errorText);

	return;
}


bool ColoredLabel::renderText(ZStringView text) {
	std::string resultStr = "";
	std::size_t labelSize = 0u;
	auto textView = text.view();
	std::size_t stringSize = text.size();

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
		char c = textView[i];
		if (c == '<') {
			if (i + 1 >= stringSize)
				goto skip;

			if (char c1 = textView[i + 1]; c1 == 'c') {
				auto tagOpt = collectTag(i, text);
				if (!tagOpt)
					return false;
				auto const& tag = tagOpt.value();

				pushColor(colorForTag(tag));

				// v
				// <cg>
				// 01234
				// tag - "g"
				// 0 + 1 + *2* = 3 ('>'), 4 on next iteration
				i += tag.size() + 2;

				continue; // skip adding anything to the result
			} else if (auto tagOpt = collectTag(i, textView); c1 == '/') {
				if (!tagOpt)
					return false;

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

	CCLabelBMFont::setString(resultStr.c_str());
	auto letters = CCArrayExt<CCFontSprite*>(this->getChildren());

	// color the thing
	for (auto& [begin, end, color] : colors) {
		for (; begin < end; ++begin) {
			if (begin < labelSize)
				letters[begin]->setColor(color);
		}
	}

	return true;
}

std::optional<std::string> ColoredLabel::collectTag(
	std::size_t curPos,
	std::string_view string
) {
	std::string colorTag{};
	auto stringSize = string.size();

	for (std::size_t offset = 2u;; ++offset) {
		if (curPos + offset >= stringSize)
			return std::nullopt;

		// replace the `for` condition
		if (char c = string[curPos + offset]; c == '>')
			break;
		else
			colorTag.append(1, c);
	};

	return colorTag;
}

ccColor3B ColoredLabel::colorForTag(std::string_view tag) {
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
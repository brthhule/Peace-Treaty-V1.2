#include "..\..\..\Support\Paths.h"
#include SECTION_HEADER 



Section::Section(int sectionNumber, int sectionStart, int bodyLength, std::string title, Order order, int* width) {
	this->sectionNumber = sectionNumber;
	this->startIndex = 0;
	this->bodyLength = bodyLength;
	this->sectionStart = sectionStart;
	this->texts = {};
	// Plus 2 for the lines after the section header and after the body
	this->sectionEnd = sectionStart + bodyLength + 2;
	this->title = title;
	this->textsOrder = order;
	this->sectionCols = width;
	this->increment = 0;
}

void Section::resetStart() {
	startIndex = 0;
}

const std::vector<std::string>* Section::getTexts() {
	return &texts;
}

int Section::modifyStartIndex(int amount, Direction direction) {
	// Move up
	if (direction == UP) {
		startIndex -= amount;
		if (startIndex < 0) {
			startIndex = 0;
		}
	} else {
		startIndex += amount;
		if (startIndex >= texts.size()) {
			startIndex = (int)texts.size() - 1;
		}
	}

	return 0;
}

std::string Section::getText(int index) {
	if (index >= texts.size()) {
		return "";
	}
	return texts[index];
}

void Section::addText(std::string text) {
	if (text.length() <= *sectionCols) {
		texts.emplace_back(text);
		return;
	}

	std::string firstPortion = text.substr(0, *sectionCols - 2);
	texts.emplace_back(firstPortion);
	addText("   " + text.substr(*sectionCols - 2));
}

bool Section::withinSection(int row) const {
	bool frontBound = row >= sectionStart;
	bool backBound = row <= sectionEnd;
	return frontBound && backBound;
}

bool Section::withinBody(int row) const {
	int bodyStart = this->sectionStart + 2;
	bool frontBound = row >= bodyStart;
	bool backBound = row < bodyStart + bodyLength;
	return (frontBound && backBound);
}



Section::Section() : Section(0, 0, 0, "", Order::FRONT_TO_BACK, nullptr) {

}

void Section::clearTexts() {
	texts.clear();
}


void Section::detCurrentText(int row) {
	if (!withinBody(row)) {
		return;
	}
	if (texts.empty()) {
		currentText = "";
		increment++;
		return;
	}


	int index = this->increment;
	if (textsOrder == BACK_TO_FRONT) {
		index = (int)texts.size() - increment - 1;
	}

	if (index >= texts.size()) {
		currentText = "";
		increment++;
		return;
	}

	// -2 to account for numbers/list
	currentText = Section::substr(texts.at(index), *sectionCols - 2);
	increment++;
}

void Section::setCurrentText(std::string text) {
	this->currentText = text;
}

const std::string& Section::getCurrentText() const {
	return currentText;
}

std::string Section::substr(std::string text, int length) {
	if (length >= text.length()) {
		return text;
	}
	return text.substr(0, length);
}


//////////////////////////////////////////////////////////////////////////////

int DebugSection::currentStackFrame = 0;

DebugSection::DebugSection(int sectionNumber, int sectionStart, int bodyLength, std::string title, Order order, int* width) :
	Section(sectionNumber, sectionStart, bodyLength, title, order, width) {

}

void DebugSection::addText(std::string text) {
	/*if (text.length() <= *sectionCols) {
		std::cout << "Emplace back text\n";
		texts.emplace_back(text);
		std::cout << "Size: " << texts.size() << "\n";
		return;
	}

	std::string firstPortion = text.substr(0, *sectionCols - 2);
	texts.emplace_back(firstPortion);
	addText("   " + text.substr(*sectionCols - 2));
	*/
}
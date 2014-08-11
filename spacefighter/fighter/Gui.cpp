#include "Gui.h"
#include <algorithm>
using namespace gui;

void Gui::loadResources() {
	mFont.loadFromFile("../Media/Fonts/kenvector_future.ttf");
}

Gui Gui::sInstance;


Image::Image(const std::string& path) {
	mTexture.loadFromFile(path);
	mSprite.setTexture(mTexture);
}

TextBased::TextBased(const std::string& text) {
	mText.setString(text);
	mText.setFont(Gui::getInstance().getFont());
	mText.setColor(sf::Color(50, 50, 50, 255));
	mText.setCharacterSize(24);
}

Text::Text(const std::string& text) : TextBased(text) {
}

void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mText, states);
}

Button::Button(const std::string& text) : TextBased(text) {
	if (sTexture.getSize().x == 0) {
		sTexture.loadFromFile("../Media/Gui/buttonBlue.png");
	}

	mSprite.setTexture(sTexture);
	mText.setPosition({ 15.0f, 0.0f });
}

void Button::onPositionChanged(const sf::Vector2f& position) {
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
	target.draw(mText, states);
}

sf::Texture Button::sTexture;

Container::Container() : mLayout(FLOW), mPadding(5.0f, 5.0f), mSpacing(15.0f, 15.0f) {

}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform.translate(mPadding);

	for (int i = 0; i < mChildren.size(); ++i) {

		sf::Vector2f childSize = mChildren[i]->calculateSize();

		mChildren[i]->draw(target, states);

		switch (mLayout) {
		case FLOW:
			states.transform.translate({ childSize.x + mSpacing.x, 0.0f });
			break;

		case ROW:
			states.transform.translate({ 0.0f, childSize.y + mSpacing.y });
			break;
		}
	}
}

sf::Vector2f Container::calculateSize() const {

	sf::Vector2f size(mPadding);
	sf::Vector2f calcSize;

	for (int i = 0; i < mChildren.size(); ++i) {

		calcSize = mChildren[i]->calculateSize();

		switch (mLayout) {
		case FLOW:
			size.x += calcSize.x + mSpacing.x;
			size.y = std::max(size.y, calcSize.y + mSpacing.y);
			break;

		case ROW:
			size.x = std::max(size.x, calcSize.x + mSpacing.x);
			size.y += calcSize.y + mSpacing.y;
			break;
		}
	}

	return size - mSpacing;
}


// 0---1------------2---3
// | 0 |     1      | 2 |
// +---+------------+---+
// |   |            |   | 
// |   |            |   | 
// | 1 |            |   | 
// |   |            |   |
// |   |            |   |
// +---+------------+---+
// | 2 |            |   |
// +---+------------+---+

Frame::Frame() : mBorder(10, 15) {
	//	mTexture.loadFromFile("../Media/Gui/glassPanel_cornerBL.png");
	//mTexture.loadFromFile("../Media/Gui/metalPanel.png");
	mTexture.loadFromFile("../Media/Gui/glassPanel_projection.png");

	mTexture.setSmooth(true);
	mTexture.setRepeated(true);

	setPadding({ 2.0f, 2.0f });
	setSpacing({ 2.0f, 2.0f });
}

void Frame::prepare() {
	sf::Vector2f contentSize = Container::calculateSize();
	sf::Vector2f size;

	for (int y = 0; y < 3; ++y){

		for (int x = 0; x < 3; ++x) {
			sf::IntRect textureRect;
			if (x == 0) { textureRect.left = 0.0f; textureRect.width = mBorder.x; }
			if (x == 1) { textureRect.left = mBorder.x; textureRect.width = mTexture.getSize().x - 2 * mBorder.x; }
			if (x == 2) { textureRect.left = mTexture.getSize().x - mBorder.x; textureRect.width = mBorder.x; }
			if (y == 0) { textureRect.top = 0.0f; textureRect.height = mBorder.y; }
			if (y == 1) { textureRect.top = mBorder.y; textureRect.height = mTexture.getSize().y - 2 * mBorder.y; }
			if (y == 2) { textureRect.top = mTexture.getSize().y - mBorder.y; textureRect.height = mBorder.y; }
			mSprites[x][y].setTextureRect(textureRect);
			mSprites[x][y].setTexture(mTexture);

			sf::Vector2f position;
			if (x == 0) position.x = 0.0f;
			if (x == 1) position.x = mBorder.x;
			if (x == 2) position.x = mBorder.x + contentSize.x;
			if (y == 0) position.y = 0.0f;
			if (y == 1) position.y = mBorder.y;
			if (y == 2) position.y = mBorder.y + contentSize.y;
			mSprites[x][y].setPosition(position);

			sf::Vector2f scale(1.0f, 1.0f);
			if (x == 1) scale.x = contentSize.x / textureRect.width;
			if (y == 1) scale.y = contentSize.y / textureRect.height;
			mSprites[x][y].setScale(scale);
		}
	}
}

sf::Vector2f Frame::calculateSize() const {
	return Container::calculateSize() + mBorder * 2.0f;
}

void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	for (int y = 0; y < 3; ++y){
		for (int x = 0; x < 3; ++x) {
			target.draw(mSprites[x][y], states);
		}
	}

	states.transform.translate(mBorder);

	Container::draw(target, states);
}

Window::Window() {

	mCaption.setFont(Gui::getInstance().getFont());
	mCaption.setColor(sf::Color(255, 255, 255, 255));
	mCaption.setCharacterSize(16);
	mCaption.setPosition(15.0f, 5.0f);

	mTexture.loadFromFile("../Media/Gui/metalPanel_blue.png");
	mTexture.setSmooth(true);
	mTexture.setRepeated(true);

	setBorder({ 15.0f, 35.0f });
	setPadding({ 2.0f, 2.0f });

}

void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	Frame::draw(target, states);

	if (mCaption.getString().getSize() > 0)
		target.draw(mCaption, states);
}
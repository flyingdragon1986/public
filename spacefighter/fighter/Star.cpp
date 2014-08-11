#include "Star.h"
#include "Game.h"
using namespace game;

const char* STAR_TEXTURE_PATH[] = {
	"../Media/Effects/star1.png",
	"../Media/Effects/star2.png",
	"../Media/Effects/star3.png"
};

Star::Star(const sf::Vector2f& position) : GameObject(EFFECT), mLife(1.0f) {
	mSprite.setPosition(position);
	mSprite.setTexture(sTexture[0]);
	mSprite.setOrigin(getSize() * 0.5f);

	mCollisionable = false;
}

void Star::update(const sf::Time& delta) {

	mLife -= delta.asSeconds();

	if (mLife > 0.6f)
		mSprite.setTexture(sTexture[0]);
	else if (mLife > 0.3f)
		mSprite.setTexture(sTexture[1]);
	else if (mLife > 0.0f)
		mSprite.setTexture(sTexture[2]);
	else
		Game::getInstance().remove(this);
}

void Star::loadResources() {
	for (int i = 0; i < 3; ++i) {
		sTexture[i].loadFromFile(STAR_TEXTURE_PATH[i]);
		sTexture[i].setSmooth(true);
	}
}

sf::Texture Star::sTexture[3];
#include "Laser.h"
#include "Game.h"
#include "Star.h"
#include "Math.h"
using namespace game;

sf::Texture Laser::sTexture[4];

const char* LASER_TEXTURE_FILES[] = {
	"../Media/Lasers/laserBlue01.png",
	"../Media/Lasers/laserBlue02.png",
	"../Media/Lasers/laserBlue03.png",
	"../Media/Lasers/laserBlue04.png"
};

void Laser::loadResources() {
	for (int i = 0; i < 4; ++i) {
		sTexture[i].loadFromFile(LASER_TEXTURE_FILES[i]);
		sTexture[i].setSmooth(true);
	}
}

Laser::Laser(const sf::Vector2f& position, float rotation) : GameObject(LASER), mSpeed(250.0f), mLife(5.0f){

	mSprite.setTexture(sTexture[0]);
	mSprite.setPosition(position);
	mSprite.setRotation(rotation);
	mSprite.setOrigin({
		(float)mSprite.getTexture()->getSize().x * 0.5f,
		(float)mSprite.getTexture()->getSize().y * 0.1f
	});

	mRadius = 3.0f;
}

void Laser::damage() {
	Game::getInstance().add(new Star(getPosition()));
	Game::getInstance().remove(this);
}

void Laser::update(const sf::Time& delta) {

	mSprite.move(
		sinf(mSprite.getRotation() * math::DEG2RAD) * delta.asSeconds() * mSpeed,
		-cosf(mSprite.getRotation() * math::DEG2RAD) * delta.asSeconds() * mSpeed
		);

	mLife -= delta.asSeconds();

	if (mLife < 0.0f)
		game::Game::getInstance().remove(this);
}
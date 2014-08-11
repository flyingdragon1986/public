#include "Asteroid.h"
#include "Game.h"
#include <random>

using namespace game;

std::default_random_engine random;
std::uniform_real_distribution<float> width(0, 800);
std::uniform_real_distribution<float> height(0, 400);
std::uniform_real_distribution<float> angle(0, 314);
std::uniform_real_distribution<float> rotation_speed_range(-50, 50);
std::uniform_real_distribution<float> spread(-30, 30);

const char* ASTEROID_TEXTURE_PATH[] = {
	"../Media/Meteors/meteorGrey_big1.png",
	"../Media/Meteors/meteorGrey_med1.png",
	"../Media/Meteors/meteorGrey_small1.png",
	"../Media/Meteors/meteorGrey_tiny1.png"
};

Asteroid::Asteroid(AsteroidType type, const sf::Vector2f& position) : GameObject(ENEMY), mRotationSpeed(5), mVelocity(10), mAsteroidType(type), mHitPoints(1){

	switch (type) {
	case BIG:
		mRadius = 35.0f;
		mHitPoints = 7;
		mSprite.setTexture(sTexture[0]);
		mSprite.setPosition({ width(random), height(random) });
		break;

	case MEDIUM:
		mSprite.setTexture(sTexture[1]);
		mSprite.setPosition(position + sf::Vector2f(spread(random), spread(random)));
		mHitPoints = 4;
		mRadius = 25.0f;
		break;

	case SMALL:
		mSprite.setTexture(sTexture[2]);
		mSprite.setPosition(position + sf::Vector2f(spread(random), spread(random)));
		mHitPoints = 2;
		mRadius = 15.0f;
		break;

	case TINY:
		mHitPoints = 1;
		mSprite.setTexture(sTexture[3]);
		mSprite.setPosition(position + sf::Vector2f(spread(random), spread(random)));
		mRadius = 5.0f;
		break;
	}

	mSprite.setRotation(angle(random));
	mSprite.setOrigin(getSize() * 0.5f);
	mRotationSpeed = rotation_speed_range(random);
}

void Asteroid::damage() {

	--mHitPoints;

	if (mHitPoints <= 0) {
		if (mAsteroidType == BIG) {
			Game::getInstance().add(new Asteroid(MEDIUM, this->getPosition()));
			Game::getInstance().add(new Asteroid(MEDIUM, this->getPosition()));
			Game::getInstance().add(new Asteroid(MEDIUM, this->getPosition()));
		}
		else if (mAsteroidType == MEDIUM) {
			Game::getInstance().add(new Asteroid(SMALL, this->getPosition()));
			Game::getInstance().add(new Asteroid(SMALL, this->getPosition()));
		}
		else if (mAsteroidType == SMALL) {
			Game::getInstance().add(new Asteroid(TINY, this->getPosition()));
			Game::getInstance().add(new Asteroid(TINY, this->getPosition()));
		}

		Game::getInstance().remove(this);
	}

}

void Asteroid::update(const sf::Time& delta) {
	mSprite.rotate(delta.asSeconds() * mRotationSpeed);
}

void Asteroid::loadResources() {
	for (int i = 0; i < 4; ++i) {
		sTexture[i].loadFromFile(ASTEROID_TEXTURE_PATH[i]);
		sTexture[i].setSmooth(true);
	}
}

sf::Texture Asteroid::sTexture[4];
#include "Enemy.h"
#include "Game.h"
using namespace game;

const char* ENEMY_TEXTURE_PATH[] = {
	"../Media/Enemies/enemyBlack1.png",
	"../Media/Enemies/enemyBlue1.png",
	"../Media/Enemies/enemyGreen1.png",
	"../Media/Enemies/enemyRed1.png",
	"../Media/Enemies/enemyBlack2.png",
	"../Media/Enemies/enemyBlue2.png",
	"../Media/Enemies/enemyGreen2.png",
	"../Media/Enemies/enemyRed2.png",
	"../Media/Enemies/enemyBlack3.png",
	"../Media/Enemies/enemyBlue3.png",
	"../Media/Enemies/enemyGreen3.png",
	"../Media/Enemies/enemyRed3.png",
	"../Media/Enemies/enemyBlack4.png",
	"../Media/Enemies/enemyBlue4.png",
	"../Media/Enemies/enemyGreen4.png",
	"../Media/Enemies/enemyRed4.png",
	"../Media/Enemies/enemyBlack5.png",
	"../Media/Enemies/enemyBlue5.png",
	"../Media/Enemies/enemyGreen5.png",
	"../Media/Enemies/enemyRed5.png"
};

Enemy::Enemy(const sf::Vector2f& position) : GameObject(ENEMY), mVelocity(0.0f, 5.0f) {
	mSprite.setTexture(sTexture[rand()%20]);
	mSprite.setPosition(position);
	mSprite.setOrigin(getSize() * 0.5f);

	mRadius = 30;
}

Enemy::~Enemy() {
}

void Enemy::damage() {
	Game::getInstance().remove(this);
}

void Enemy::update(const sf::Time& delta) {
	mSprite.move(mVelocity * delta.asSeconds());
}

void Enemy::loadResources() {
	for (int i = 0; i < 20; ++i) {
		sTexture[i].loadFromFile(ENEMY_TEXTURE_PATH[i]);
		sTexture[i].setSmooth(true);
	}
}

sf::Texture Enemy::sTexture[20];
#include "Fighter.h"
#include "Game.h"
#include "Laser.h"
#include "Math.h"
#include <random>

using namespace game;

Fighter::Fighter() : GameObject(PLAYER), mReloading(0.0f), mSpeed(150.0f) {
	mSprite.setTexture(sTexture);
	mSprite.setPosition({ 400, 500 });
	mSprite.setOrigin({ sTexture.getSize().x / 2.0f, sTexture.getSize().y / 2.0f });

	mLaserSound.setBuffer(sBuffer);
	mRadius = 30;
}

void Fighter::update(const sf::Time& delta) {

	if (mReloading > 0.0f) {
		mReloading -= delta.asSeconds();
	}

	sf::Vector2f movement;

	//mSprite.rotate(delta.asSeconds() * 30.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x = -mSpeed * delta.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x = mSpeed * delta.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.y = -mSpeed * delta.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.y = mSpeed * delta.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		fire();

	if (sf::Joystick::isConnected(0)) {
		sf::Vector2f joystick_axis(
			sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X),
			sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));

		if (joystick_axis.x < -30.0f || joystick_axis.x > 30.0f) {
			movement.x = joystick_axis.x / 100.0f * delta.asSeconds() * mSpeed;
		}

		if (sf::Joystick::isButtonPressed(0, 0)) {
			fire();
		}
	}

	mSprite.move({
		-sinf(mSprite.getRotation() * math::DEG2RAD) * movement.y,
		cosf(mSprite.getRotation() * math::DEG2RAD) * movement.y
	});
	mSprite.rotate(movement.x);
}

void Fighter::fire() {
	if (mReloading <= 0.0f) {
		sf::Transform t;
		t.translate(mSprite.getPosition());
		t.rotate(mSprite.getRotation());
		t.translate({ 0.0f, -mSprite.getOrigin().y*2.5f });
		//t.translate(mSprite.getOrigin());

		//sf::Vector2f position = mSprite.getPosition();
		//position.y -= mSprite.getOrigin().x;

		Game::getInstance().add(new Laser(t.transformPoint(sf::Vector2f(0, 0)), mSprite.getRotation()));
		mReloading = 0.1f;

		mLaserSound.play();
	}
}

void Fighter::loadResources() {
	sTexture.loadFromFile("../Media/playerShip2_blue.png");
	sTexture.setSmooth(false);

	sBuffer.loadFromFile("../Media/Sounds/laser4.ogg");
}

sf::SoundBuffer Fighter::sBuffer;
sf::Texture		Fighter::sTexture;
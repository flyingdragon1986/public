#include "Game.h"
#include "Laser.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Star.h"
#include "Asteroid.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace game;

inline float pow2(float n) {
	return n*n;
}

Game::Game() : mBackgroundQuad(sf::Quads, 4), mLoading(false) {
}

void Game::init() {

	if (mBackgroundTexture.loadFromFile("../Media/Backgrounds/blue.png")) {
		mBackgroundTexture.setRepeated(true);
		mBackgroundTexture.setSmooth(true);
	}

	mBackgroundQuad.append(sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
	mBackgroundQuad.append(sf::Vertex(sf::Vector2f(800, 0), sf::Vector2f(800, 0)));
	mBackgroundQuad.append(sf::Vertex(sf::Vector2f(800, 640), sf::Vector2f(800, 640)));
	mBackgroundQuad.append(sf::Vertex(sf::Vector2f(0, 640), sf::Vector2f(0, 640)));

	mFont.loadFromFile("../Media/Fonts/kenvector_future.ttf");
	mText.setFont(mFont);
	mText.setCharacterSize(10);

	Fighter::loadResources();
	Enemy::loadResources();
	Laser::loadResources();
	Star::loadResources();
	Asteroid::loadResources();

	add(new game::Fighter);
	add(new game::Asteroid());
	add(new game::Asteroid);
	add(new game::Asteroid);
	add(new game::Asteroid);
	add(new game::Asteroid);
	add(new game::Asteroid);

	add(new game::Enemy(sf::Vector2f(100.0f, 10.0f)));
	add(new game::Enemy(sf::Vector2f(200.0f, 100.0f)));
	add(new game::Enemy(sf::Vector2f(400.0f, 150.0f)));
	add(new game::Enemy(sf::Vector2f(600.0f, 100.0f)));
	add(new game::Enemy(sf::Vector2f(700.0f, 10.0f)));

	mClock.restart();
}

void Game::collide(GameObject* o1, GameObject* o2) {
	if (o1->getType() == o2->getType())
		return;

	if (o1->getType() == GameObject::PLAYER && o2->getType() == GameObject::LASER);

	o1->damage();
	o2->damage();
}

void Game::update() {

	sf::Time delta = mClock.restart();

	// copy
	GameObjects objects = mObjects;

	for (GameObjects::iterator it = objects.begin(); it != objects.end(); ++it) {
		// update object
		(*it)->update(delta);

		if ((*it)->isCollisionable()) {

			// check collisition
			GameObjects::iterator next = it;
			next++;

			for (GameObjects::iterator it2 = next; it2 != objects.end(); ++it2) {

				if ((*it2)->isCollisionable()) {

					GameObject* o1 = (*it);
					GameObject* o2 = (*it2);

					sf::Vector2f distance = o1->getPosition() - o2->getPosition();
					float nq = pow2(distance.x) + pow2(distance.y);
					float rq = pow2(o1->getRadius()) + pow2(o2->getRadius());

					if (rq > nq)
						collide(o1, o2);
				}

			}


		}

	}

	// delete old objects

	for (std::set<GameObject*>::iterator it = mGarbage.begin(); it != mGarbage.end(); ++it) {
		delete (*it);
	}

	mGarbage.clear();
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	sf::CircleShape circle;
	std::stringstream text;
	bool debug = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	target.draw(mBackgroundQuad, &mBackgroundTexture);

	for (GameObjects::const_iterator it = mObjects.begin(); it != mObjects.end(); ++it) {
		(*it)->draw(target);

		if (debug)	{
			circle.setRadius((*it)->getRadius());
			circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()) );
			circle.setPosition((*it)->getPosition());
			circle.setOutlineColor(sf::Color(255, 255, 255, 255));

			target.draw(circle);

			// text.precision(2);
			text << (unsigned long)(*it)->getType() 
				<< " Position=" <<  std::setw(5) << (*it)->getPosition().x 
				<< ":" << (*it)->getPosition().y 
				<< " Rotation: " << (*it)->getRotation() << "°"
				<< std::endl;
		}

	}

	//if (debug) {
	//	mText.setCharacterSize(10);
	//	mText.setString(text.str());
	//	target.draw(mText);
	//}
}

void Game::findAll(GameObject::GameObjectType type, Game::GameObjects &objects) {
	objects.clear();

	for (GameObjects::iterator it = mObjects.begin(); it != mObjects.end(); ++it) {
		if ((*it)->getType() == type)
			objects.push_back(*it);
	}
}

Game Game::sInstance;
#include "Gameobject.h"
using namespace game;

GameObject::GameObject(GameObjectType type) : mType(type), mRadius(0.0f), mCollisionable(true) {

}

void GameObject::draw(sf::RenderTarget& target) {
	target.draw(mSprite);
}

void GameObject::update(const sf::Time& delta) {
}

void GameObject::damage() {

}
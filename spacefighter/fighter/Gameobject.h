// GameObject.h
#pragma once
#include <SFML\Graphics.hpp>

namespace game {

	class GameObject {
	public:
		enum GameObjectType {
			PLAYER,
			ENEMY,
			LASER,
			EFFECT,
			ITEM
		};

		enum GameObjectLayer{ FOREGROUND, MIDDLE, BACKGROUND };

		GameObject(GameObjectType type);

		virtual void draw(sf::RenderTarget&);
		virtual void update(const sf::Time& delta);
		virtual void damage();

		inline bool isCollisionable()const { return mCollisionable; }

		inline const sf::Vector2f& getPosition() const { return mSprite.getPosition(); }
		inline const float getRotation() const { return mSprite.getRotation(); }
		inline const float getRadius() const { return mRadius; }
		inline const sf::Vector2f& getOrigin() const { return mSprite.getOrigin(); }
		inline const sf::Vector2f getSize() const { return sf::Vector2f(mSprite.getTexture()->getSize()); }

		inline GameObjectType getType() const { return mType; }

	protected:
		sf::Sprite mSprite;
		float mRadius;
		bool mCollisionable;
		GameObjectType mType;

	};

}

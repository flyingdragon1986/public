#pragma once

#include "Gameobject.h"

namespace game {

	class Asteroid : public GameObject {
	public:
		enum AsteroidType {BIG, MEDIUM, SMALL, TINY};

		Asteroid(AsteroidType type = BIG, const sf::Vector2f& position = sf::Vector2f());
		void update(const sf::Time&);
		void damage();

		static void		loadResources();

	protected:
		static sf::Texture sTexture[4];

		AsteroidType	mAsteroidType;
		float			mRotationSpeed;
		float			mVelocity;
		int				mHitPoints;
	};
}
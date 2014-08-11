#pragma once
#include "Gameobject.h"

namespace game {

	class Enemy :
		public GameObject
	{
	protected:
		static sf::Texture sTexture[20];
		sf::Vector2f mVelocity;
		int mShield;
	public:
		Enemy(const sf::Vector2f& position);
		~Enemy();

		void update(const sf::Time& delta);
		void damage();

		static void loadResources();
	};
}


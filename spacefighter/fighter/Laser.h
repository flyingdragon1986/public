#pragma once
#include "Gameobject.h"

namespace game {
	class Laser : public GameObject {
	protected:
		static sf::Texture sTexture[4];
		float mSpeed;
		float mLife;
	public:
		Laser(const sf::Vector2f& position, float rotation);
		void update(const sf::Time& delta);
		void damage();

		static void loadResources();
	};
}
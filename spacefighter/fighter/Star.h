// star.h
#pragma once

#include "Gameobject.h"

namespace game {
	class Star : public GameObject {
	protected:
		static sf::Texture sTexture[3];
		float mLife;
	public:
		Star(const sf::Vector2f& position);
		void update(const sf::Time& delta);

		static void loadResources();
	};
}
// fighter.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gameobject.h"
#include <string>

namespace game {

	struct FighterTemplate {
		std::string texture;
		float max_speed;
		float velocity;
	};

	class Fighter : public GameObject{
	private:
		static sf::Texture sTexture;
		static sf::SoundBuffer sBuffer;

		sf::Sound	mLaserSound;
		float		mReloading;
		float		mSpeed;
	public:
		Fighter();
		void update(const sf::Time& delta);
		void fire();

		static void loadResources();
	};
}


#pragma once
#include "Gameobject.h"

namespace game {
	class Weapon {
	protected:
		float mReloading;
	public:
		void fire();
		inline bool isReloading() const { return mReloading; }
	};

	class Ship : public GameObject {
	protected:
		Weapon mWeapon;
	public:
		virtual void update(const sf::Time& delta);
		void fire();
		void damage();
	};
}


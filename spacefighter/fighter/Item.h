#pragma once
#include "Gameobject.h"

namespace game {
	class Item : public GameObject {
	public:
		void activate(Fighter);
		void onDamage();
	};
}
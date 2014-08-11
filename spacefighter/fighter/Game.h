// game.h
#pragma once

#include "Gameobject.h"
#include <list>
#include <set>
#include <SFML/Graphics.hpp>

namespace game {
	class Game : public sf::Drawable {
	protected:
		typedef std::list<GameObject*> GameObjects;

		static Game		sInstance;
		GameObjects		mObjects;
		std::set<GameObject*> mGarbage;
		sf::Clock		mClock;
		sf::Texture		mBackgroundTexture;
		sf::VertexArray mBackgroundQuad;
		sf::Font		mFont;
		sf::Text		mText;
		bool			mLoading;

	public:
		Game();

		inline static Game& getInstance() {
			return sInstance;
		}
		inline void add(GameObject* gameObject) { mObjects.push_back(gameObject); }
		inline void remove(GameObject* gameObject) { mObjects.remove(gameObject); mGarbage.insert(gameObject); }
		const GameObjects& getAll() const { return mObjects; }
		void findAll(GameObject::GameObjectType type, GameObjects& objects);

		void init();
		void update();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void collide(GameObject*, GameObject*);
	};
}


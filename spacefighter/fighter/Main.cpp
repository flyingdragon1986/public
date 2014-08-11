#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Fighter.h"
#include "Asteroid.h"
#include "Laser.h"
#include <list>
#include <algorithm>
#include "Game.h"
#include "Gui.h"

#pragma comment (lib, "sfml-main-d.lib")

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Fighter!");


	gui::Gui::getInstance().loadResources();

	gui::Frame container;// ({ 400.0f, 300.0f });
	gui::Button button;
	gui::Text text;
	text.setText("Missiles");
	button.setText("Press Me!");
//	button.setPosition({ 50.0f, 500.0f });
	//container.add(button);
	//container.add(text);
	container.setLayout(gui::Container::FLOW);

	gui::Image s1("../Media/Gui/squareBlue.png");
	gui::Image s2("../Media/Gui/square_shadow.png");

	container.add(text);
	container.add(s1);
	container.add(s1);
	container.add(s1);
	container.add(s2);
	container.add(s2);
	container.prepare();

	gui::Window wc;
	wc.setCaption("Window");
	wc.setLayout(gui::Container::ROW);
	wc.add(container);
	wc.add(container);
	wc.add(button);
	wc.prepare();

	game::Game& game = game::Game::getInstance();

	game.init();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		game.update();

		window.clear();
		window.draw(game);
		window.draw(wc);
		window.display();
	}

	return 0;
}


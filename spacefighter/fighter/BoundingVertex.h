#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct BoundingSphere {
	sf::Vector2f center;
	float radius;
};

struct BoundingBox {
	sf::Vector2f a;
	sf::Vector2f b;
};

struct BoundingShape {
	std::vector<sf::Vector2f> points;
};






class BoundingVertex {
protected:
	std::vector<sf::Vector2f> mVertex;
public:
	bool intersects(sf::Vector2f& point);
	bool intersects(sf::Vector2f& point, float radius);
	bool intersects(sf::Vector2f& start, sf::Vector2f& end);
};
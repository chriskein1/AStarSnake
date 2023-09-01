#ifndef FRUIT_H
#define FRUIT_H

#include "SFML/Graphics.hpp"
#include "Snake.h"

class Snake;

class Fruit {
private:
	sf::RectangleShape fruit;

public:
	Fruit();
	void PlaceFruit(Snake& snake);
	void Render(sf::RenderWindow& window);
	sf::Vector2f GetLocation();
};

#endif
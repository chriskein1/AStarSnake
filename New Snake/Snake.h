#ifndef SNAKE_H
#define SNAKE_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "Fruit.h"
#include <queue>

class Fruit;


class Snake {
private:
	sf::RectangleShape head;
	sf::RectangleShape body_tile;
	std::vector<sf::RectangleShape> snake_body;
	short int movement_direction; // 1 - up, 2 - down, 3 - left, 4 - right
	std::queue<short int> movement_queue;
	sf::Vector2f movement;
	bool dead = false;

public:
	Snake();
	void Render(sf::RenderWindow& window);
	void Move();
	bool Eat(Fruit& fruit);
	bool IsDead();
	void Reset();
	int GetSize();
	sf::Vector2f GetHeadLocation();
	sf::Vector2f GetBodyLocation(int index);
	sf::Vector2f GetTailLocation();
	void Pathfind(std::queue<int> &shortest_path);

};

#endif
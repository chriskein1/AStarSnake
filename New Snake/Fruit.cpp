#include "Fruit.h"
#include "Global.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


// Fruit constructor
Fruit::Fruit() {
	fruit.setSize(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
	fruit.setFillColor(sf::Color::Red);

	// seed random number generator
	srand(time(NULL));

}

// Fruit placement based on the Snake's location
void Fruit::PlaceFruit(Snake& snake) {
	int random_x;
	int random_y;
	
	// flag set to true to loop to see if there is actually collision
	bool collision = true;

	while (collision) {
		// if there is no collision, it will stay false
		collision = false;
		// set spawn location based on time elapsed (cheap way to make random numbers)
		random_x = rand() % BOARD_SIZE;
		random_y = rand() % BOARD_SIZE + 1;

		// make sure x and y isn't the same as the snake's current x and y
		if (random_x == snake.GetHeadLocation().x && random_y == snake.GetHeadLocation().y) {
			collision = true;
			continue;
		}

		// make sure x and y isn't the same as snake body's current x and y
		for (size_t i = 0; i < snake.GetSize() - 1; i++) {
			if ((snake.GetBodyLocation(i).x / TILE_SIZE) == random_x && (snake.GetBodyLocation(i).y / TILE_SIZE) == random_y) {
				collision = true;
				break;
			}
		}
	}
	fruit.setPosition(random_x * TILE_SIZE, random_y * TILE_SIZE);
}

void Fruit::Render(sf::RenderWindow& window) {
	window.draw(fruit);
}

sf::Vector2f Fruit::GetLocation() {
	return fruit.getPosition();
}
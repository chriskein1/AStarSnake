#include "SFML/Graphics.hpp"
#include "Snake.h"
#include "Global.h"
#include "Fruit.h"
#include "Graph.h"
#include "Menu.h"
#include <queue>

void ChangeSpeed(int& speed);
int GameSpeed(int& speed);
int main() {
	int speed = 1;
	// Create window object
	sf::RenderWindow window(sf::VideoMode(TILE_SIZE * BOARD_SIZE, TILE_SIZE * BOARD_SIZE + TILE_SIZE), "Snake");
	sf::Event event;

	// Clock object to keep track of time elapsed
	sf::Clock clock;
	sf::Time elapsed;

	Menu menu;

	Snake snake;
	Fruit fruit;
	
	fruit.PlaceFruit(snake);

	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	bar.setFillColor(sf::Color{ 27, 27, 27 });

	// text and font variables to display the length and high score
	int high_score = 0;
	sf::Text display_length;
	sf::Font display_font;

	sf::Text display_high_score;

	// set the text to a font
	display_font.loadFromFile("arcade_font.ttf");
	display_length.setFont(display_font);

	display_high_score.setFont(display_font);
	display_high_score.setPosition(TILE_SIZE * BOARD_SIZE * 2 / 3, 0);

	Graph game_state;
	std::queue<int> shortest_path;

	// Game loop
	while (window.isOpen()) {

		sf::Vector2u old_size = window.getSize();
		while (window.pollEvent(event)) {
			if (event.type == event.Closed)
				window.close();
		}

		// Adjust window based on resizing
		if (event.type == event.Resized) {
			float aspect_ratio = 26 / 25;
			if (old_size.x != event.size.width)
				window.setSize(sf::Vector2u(event.size.width, event.size.width / aspect_ratio));
			if (old_size.y != event.size.height)
				window.setSize(sf::Vector2u(event.size.height / aspect_ratio, event.size.height));

		}

		if (!menu.StartGame()) {
			menu.GetInput();
			menu.Render(window);
			if (menu.StartGame()) {
				if (menu.IsAI()) {
					game_state.ClearNodes();
					game_state.SetGraph(snake, fruit);
					shortest_path = game_state.GetShortestPath();
				}
			}
			continue;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			snake.Reset();
			menu.Reset();
			speed = 1;
			continue;
		}

		ChangeSpeed(speed);

		// Keep track of elapsed time
		elapsed += clock.restart();

		// Update score
		display_length.setString("LENGTH: " + std::to_string(snake.GetSize()));

		window.clear();
		fruit.Render(window);
		snake.Render(window);
		for (int i = 0; i < BOARD_SIZE; i++) {
			bar.setPosition(TILE_SIZE * i, 0);
			window.draw(bar);
		}
		window.draw(display_length);
		if (high_score > 0) {
			display_high_score.setString("HIGH: " + std::to_string(high_score));
		//	window.draw(display_high_score);
		}
		window.display();

		
		// Reset game
		if (snake.IsDead()) {
			window.clear();
			if (snake.GetSize() > high_score) high_score = snake.GetSize();
			snake.Reset();
			fruit.PlaceFruit(snake);
			if (menu.IsAI())
			game_state.ClearNodes();
		}

		// Handle movement
		if (elapsed >= sf::milliseconds(GameSpeed(speed))) {
			elapsed -= sf::milliseconds(GameSpeed(speed));  // Subtract the elapsed time
			if (menu.IsAI()) {
				snake.Pathfind(shortest_path);
				if (snake.Eat(fruit) || shortest_path.empty() || snake.IsDead()) {
					game_state.ClearNodes();
					game_state.SetGraph(snake, fruit);
					shortest_path = game_state.GetShortestPath();

				}
			}

			else {
				snake.Move();
				snake.Eat(fruit);
			}
		}		
	}
	return 0;
}

void ChangeSpeed(int& speed) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) speed = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) speed = 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) speed = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) speed = 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) speed = 5;

}

int GameSpeed(int& speed) {
	if (speed == 1) return 100;
	if (speed == 2) return 50;
	if (speed == 3) return 25;
	if (speed == 4) return 15;
	else return 1;
}
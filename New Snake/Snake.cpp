#include "Snake.h"
#include "Global.h"

// Constructor to initialize the Snake object
Snake::Snake() {
	head.setSize(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
	head.setFillColor(sf::Color::Blue);

	body_tile.setSize(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
	body_tile.setFillColor(sf::Color::Green);

	movement = { BOARD_SIZE / 2 , BOARD_SIZE / 2 };

	head.setPosition(movement.x * TILE_SIZE, movement.y * TILE_SIZE);

	// Direction set to 0 (nothing)
	movement_direction = 0;
}

void Snake::Render(sf::RenderWindow &window) {
	
	// Loop through snake body container to render each body tile
	for (int i = 0; i < snake_body.size(); i++) {
		window.draw(snake_body[i]);
	}
	window.draw(head);
}

// Function to handle movement of the entire Snake
void Snake::Move() {
	
	// Keep track if a key has already been pressed
	// This is to prevent simultaneous key presses
	static bool key_pressed = false;

	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && movement_direction != 2 && !key_pressed) {
		movement_direction = 1;
		key_pressed = true;
	}
	// Down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && movement_direction != 1 && !key_pressed) {
		movement_direction = 2;
		key_pressed = true;
	}
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && movement_direction != 4 && !key_pressed) {
		movement_direction = 3;
		key_pressed = true;
	}
	// Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && movement_direction != 3 && !key_pressed) {
		movement_direction = 4;
		key_pressed = true;
	}

	// Add to the queue
	movement_queue.push(movement_direction);

	// Move based on first input in queue
	if (movement_queue.front() == 1) movement.y -= 1;
	if (movement_queue.front() == 2) movement.y += 1;
	if (movement_queue.front() == 3) movement.x -= 1;
	if (movement_queue.front() == 4) movement.x += 1;

	// Remove first direction from queue
	if (movement_queue.size() > 0) movement_queue.pop();

	// Check bounds
	if (movement.x < 0 || movement.y < 1 || movement.x > BOARD_SIZE - 1 || movement.y > BOARD_SIZE) dead = true;

	if (snake_body.size() > 0) {
		for (size_t i = snake_body.size() - 1; i > 0; i--) {
			// Set the current body tile to the body tile in front of it
			snake_body[i].setPosition(snake_body[i - 1].getPosition());
			// Kill the player and end loop if there is collision between any body tile and the head
			if (snake_body[i].getPosition() == head.getPosition()) {
				dead = true;
				break;
			}
		}
		snake_body[0].setPosition(head.getPosition());
	}

	head.setPosition(movement.x * TILE_SIZE, movement.y * TILE_SIZE);


	if (sf::Event::KeyReleased) key_pressed = false;

}

void Snake::Pathfind(std::queue<int> &shortest_path) {

	// Move based on first input in queue
	if (!shortest_path.empty()) {
		if (shortest_path.front() == 1) movement.y -= 1;
		if (shortest_path.front() == 2) movement.y += 1;
		if (shortest_path.front() == 3) movement.x -= 1;
		if (shortest_path.front() == 4) movement.x += 1;

		// Remove first direction from queue
		if (shortest_path.size() > 0) shortest_path.pop();

		// Check bounds
		if (movement.x < 0 || movement.y < 1 || movement.x > BOARD_SIZE - 1 || movement.y > BOARD_SIZE) dead = true;

		if (snake_body.size() > 0) {
			for (size_t i = snake_body.size() - 1; i >= 1; i--) {
				// Set the current body tile to the body tile in front of it
				snake_body[i].setPosition(snake_body[i - 1].getPosition());
				// Kill the player and end loop if there is a collision between any body tile and the head
			//	if (snake_body[i].getPosition() == head.getPosition()) {
			//		dead = true;
			//		break;
			//	}
			}
			snake_body[0].setPosition(head.getPosition());
		}

		head.setPosition(movement.x * TILE_SIZE, movement.y * TILE_SIZE);
	}
}


// Collision between Snake and Fruit
bool Snake::Eat(Fruit& fruit) {
	if (head.getPosition().x == fruit.GetLocation().x && head.getPosition().y == fruit.GetLocation().y) {
		snake_body.push_back(body_tile);
		fruit.PlaceFruit(*this);
		return true;
	}
	return false;
 }

void Snake::Reset() {
	movement = { BOARD_SIZE / 2 , BOARD_SIZE / 2 };

	head.setPosition(movement.x * TILE_SIZE, movement.y * TILE_SIZE);

	// Direction set to 0 (nothing)
	movement_direction = 0;

	// Empty the Snake's body
	snake_body.clear();

	dead = false;
}

int Snake::GetSize() {
	return snake_body.size() + 1;
}

sf::Vector2f Snake::GetHeadLocation() {
	return head.getPosition();
}

sf::Vector2f Snake::GetBodyLocation(int index) {
	return snake_body[index].getPosition();
}

sf::Vector2f Snake::GetTailLocation() {
	if (snake_body.empty()) {
		return head.getPosition();
	}
	return snake_body.back().getPosition();
}

bool Snake::IsDead() {
	return dead;
}
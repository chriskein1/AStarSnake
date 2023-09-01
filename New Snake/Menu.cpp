#include "Menu.h"
#include "Global.h"

Menu::Menu() {
	Setup();
}

void Menu::Setup() {
	start = false;
	AI = false;
	cursor_location = 0;

	arcade_font.loadFromFile("arcade_font.ttf");
	menu_screen.setFont(arcade_font);
	menu_screen.setString("SNAKE");
	menu_screen.setCharacterSize(TILE_SIZE * 2);
	menu_screen.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 5, TILE_SIZE * 2);

	name.setFont(arcade_font);
	name.setString("CHRIS KEININGHAM");
	name.setCharacterSize(TILE_SIZE);
	name.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 2, TILE_SIZE * 2 + TILE_SIZE * 2.75);


	play.setFont(arcade_font);
	play.setString("PLAY");
	play.setCharacterSize(TILE_SIZE);
	play.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 5, BOARD_SIZE / 2 + TILE_SIZE * 10);

	AI_text.setFont(arcade_font);
	AI_text.setString("AI");
	AI_text.setCharacterSize(TILE_SIZE);
	AI_text.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 5, BOARD_SIZE / 2 + TILE_SIZE * 11.5);

	cursor.loadFromFile("selected.png");
	selected.setTexture(cursor);
	selected.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 3.75, BOARD_SIZE / 2 + TILE_SIZE * 10);
}

bool Menu::IsAI() { return AI; }

bool Menu::StartGame() { return start;  }

void Menu::GetInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		selected.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 3.75, BOARD_SIZE / 2 + TILE_SIZE * 10);
		cursor_location = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		selected.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 3.75, BOARD_SIZE / 2 + TILE_SIZE * 11.5);
		cursor_location = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (cursor_location == 0) {
			start = true;
			AI = false;
		}
		else {
			start = true;
			AI = true;
		}
	}
}

void Menu::Reset() {
	start = false;
	AI = false;
	cursor_location = 0;
	selected.setPosition(BOARD_SIZE / 2 + TILE_SIZE * 3.75, BOARD_SIZE / 2 + TILE_SIZE * 10);
}

void Menu::Render(sf::RenderWindow& window) {
	window.clear();
	window.draw(menu_screen);
	window.draw(play);
	window.draw(AI_text);
	window.draw(name);
	window.draw(selected);
	window.display();
}
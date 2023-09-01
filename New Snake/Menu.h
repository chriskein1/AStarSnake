#pragma once
#include "SFML/Graphics.hpp"

class Menu {
private:
	sf::Text menu_screen;
	sf::Text play;
	sf::Text AI_text;
	sf::Text name;

	sf::Font arcade_font;
	sf::Texture cursor;
	sf::Sprite selected;

	int cursor_location;

	bool AI;
	bool start;

public:
	Menu();
	bool IsAI();
	bool StartGame();
	void GetInput();
	void Setup();
	void Reset();
	void Render(sf::RenderWindow& window);
};
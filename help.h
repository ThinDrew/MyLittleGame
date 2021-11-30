#pragma once
#include <SFML/Graphics.hpp>

class Interface {
private:
	int scale;

	sf::Texture texture;
	sf::Sprite obj;
	sf::Vector2f spriteSize = { 60, 15 };
	sf::Vector2f tempSpriteSize = { 4, 5 };

	sf::Texture tempTexture;
	sf::Sprite tempObj;
	//sf::Text textHP;
	//sf::Text textMoney;
	//sf::Text textSteps;
	//sf::Font font;
public:
	Interface() {}

	Interface(int valueScale) : scale(valueScale) {
		texture.loadFromFile("sprites/interface.png");
		tempTexture.loadFromFile("sprites/costyl.png");

		//font.loadFromFile("fonts/font.ttf");
		//textMoney.setFont(font);
		//textHP.setFont(font);
		//textSteps.setFont(font);

		//textHP.setCharacterSize(5 * scale);
		//textMoney.setCharacterSize(4 * scale);
		//textSteps.setCharacterSize(4 * scale);

		//textHP.setPosition(10 * scale, 115 * scale);
		//textMoney.setPosition(28 * scale, 113 * scale);
		//textSteps.setPosition(44 * scale, 115 * scale);
	}

	void drawInterface(sf::RenderWindow& window, Player hero);
	void drawHP(sf::RenderWindow& window, int value);
};

bool chance(int value);
int random(int a, int b);
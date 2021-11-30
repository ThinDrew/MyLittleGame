#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

#include "map.h"

bool chance(int value) {
	int check = rand() % 1000;
	if (check > value) return false;
	else return true;
}

int random(int a, int b) {
	return (rand() % (b - a + 1)) + a;
}

void Interface::drawHP(sf::RenderWindow& window, int value) {
	tempObj.setTexture(tempTexture);
	tempObj.setTextureRect(sf::IntRect(value * 4, 0, 4, 5));
	tempObj.setScale(scale, scale);
	tempObj.setPosition(28 * scale, 113 * scale);

	window.draw(tempObj);
}

void Interface::drawInterface(sf::RenderWindow& window, Player hero) {
	obj.setTexture(texture);
	obj.setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
	obj.setScale(scale, scale);
	obj.setPosition(0, 105 * scale);

	//textMoney.setString(std::to_string(hero.getMoney()));
	//textHP.setString(std::to_string(hero.getHP()));

	window.draw(obj);
	drawHP(window, hero.getHP());
	//window.draw(textMoney);
	//window.draw(textHP);
	//window.draw(textSteps);
}
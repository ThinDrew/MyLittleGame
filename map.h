#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <iterator>

#include "color.h"
#include "entity.h"
#include "help.h"

enum Direction {
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DASH
};

struct Map {
	const sf::Vector2i startSizeMap{ 0, 0 };
	sf::Vector2i endSizeMap{ 8, 3 };

	unsigned int stepCount;
	static short count_f;

	char field[7][3];

	sf::Texture texture;
	sf::Sprite obj;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	sf::Music music;

	int spriteSize = 20;
	int scale;
	Player hero;
	Interface myInterface;

	std::list <Enemy*> enemy;

	Map(int scaleValue) : scale(scaleValue), stepCount(0) {

		music.openFromFile("sounds/music.wav");
		music.setVolume(60);
		music.play();
		music.setLoop(true);

		count_f = 1;
		stepCount = 0;
		hero = Player(endSizeMap.y, endSizeMap.x);
		myInterface = Interface(scale);
		texture.loadFromFile("sprites/tileset.png");

		create();
	}

	//создание и пересоздание	
	void create();
	void restart();
	
	//обновление карты
	void update(int move);
	void heroMove(int move);
	void mapMove();
	void generate();
	void shiftEnemies(int value);
	
	void enemyBehavior();

	//Вывод карты
	void print();
	void show(sf::RenderWindow& window);

	Player getHero() {
		return hero;
	}
};
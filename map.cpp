#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

#include "entity.h"
#include "map.h"
#include "help.h"

//#, %, o, O - тайлы пола, которые ни на что не влияют
// # - обычный пол
//^ - шипы
//v - окрававленные шипы
//m - монеты

void Map::create() {
	for (int i = startSizeMap.x; i < endSizeMap.x; i++) {
		for (int j = startSizeMap.y; j < endSizeMap.y; j++) {
			field[i][j] = '#';
			if (chance(30)) {
				switch (rand() % 3) {
				case 0:
					field[i][j] = '%';
					break;

				case 1:
					field[i][j] = 'o';
					break;

				case 2:
					if (chance(20))
						field[i][j] = 'O';

					else
						field[i][j] = '#';
					break;
				}
			}
		}
	}
}

void Map::restart() {
	enemy.clear();
	hero = Player(endSizeMap.y, endSizeMap.x);
	texture.loadFromFile("sprites/tileset.png");

	sound.stop();
	music.play();

	create();
}

void Map::print() {
	for (int i = startSizeMap.x; i < endSizeMap.x; i++) {
		for (int j = startSizeMap.y; j < endSizeMap.y; j++) {
			switch (field[i][j]) {
				case '#':
					if (i == startSizeMap.x) color(l_blue);
					else color(gray);
					break;

				case '%':
					if (i == startSizeMap.x) color(l_blue);
					else color(gray);
					break;

				case 'o':
					if (i == startSizeMap.x) color(l_blue);
					else color(gray);
					break;

				case 'O':
					if (i == startSizeMap.x) color(l_blue);
					else color(gray);
					break;

				case 'm':
					if (i == startSizeMap.x) color(l_green);
					else color(yellow);
					break;

				case '^':
					if (i == startSizeMap.x) color(purple);
					else color(l_red);
					break;
			}

			std::cout << field[i][j];
			color(white);
		}
		std::cout << '\n';
	}
	color(l_red);
	std::cout << "HP: " << hero.getHP();
	color(white);
	std::cout << "\nDamage: " << hero.getDMG();
	color(yellow);
	std::cout << "\nCoins: " << hero.getMoney() << '\n';
	color(white);

	std::cout << "Number of enemies: ";
	std::cout << enemy.size() << '\n';
	
	if (!hero.isAlive()) {
		color(red);
		std::cout << "\n\n-----------\n";
		std::cout << "You died...\n";
		std::cout << "-----------\n\n";
		color(white);
	}
}

void Map::generate() {
	int randomTile = rand() % 3;
	//Разнообразный пол
	while (true) {
		switch (rand() % 2) {
		case 0:
			field[startSizeMap.x][randomTile] = '%';
			break;

		case 1:
			field[startSizeMap.x][randomTile] = 'o';
			break;
		}
		if (chance(1))
			field[startSizeMap.x][randomTile] = 'O';
		break;
	}
	
	//40% шанса появления шипов
	if (chance(40)) {
		// 30% шанса появления вторых шипов (на той же линии)
		if (chance(30)) {
			field[startSizeMap.x][randomTile] = '^';
			int randomTile = rand() % 3;
			field[startSizeMap.x][randomTile] = '^';
			return;
		}
		else
			field[startSizeMap.x][randomTile] = '^';
		return;
	}

	//10% шанса появления скелета
	if (chance(10)) {
		Skeleton skeleton;
		enemy.push_back(skeleton);
		return;
	}

	//5% шанса появление монет
	if (chance(5)) {
		field[startSizeMap.x][randomTile] = 'm';
		return;
	}

	//если ничего не сработало
	return;
}

void Map::update(int move) {
	// Движение карты
	for (int i = endSizeMap.x - 1; i >= startSizeMap.x; i--) {
		for (int j = endSizeMap.y - 1; j >= startSizeMap.y; j--) {
			if (i == endSizeMap.x - 1) {
				field[i][j] = '#';
			}

			else {
				field[i+1][j] = field[i][j];
				field[i][j] = '#';
			}
		}
	}

	generate();

	sf::Vector2i temp = hero.getCord();
	switch (move) {
		case DIR_LEFT:
			temp.x--;
			if (temp.x < startSizeMap.y) temp.x = startSizeMap.y;
			break;
		case DIR_RIGHT:
			temp.x++;
			if (temp.x > endSizeMap.y - 1) temp.x = endSizeMap.y - 1;
			break;
	}
	hero.setCord(temp);

	switch (field[hero.getCord().y][hero.getCord().x]) {
		case 'm':
			hero.addMoney(10);
			field[hero.getCord().y][hero.getCord().x] = '#';

			buffer.loadFromFile("sounds/coin.wav");
			sound.setBuffer(buffer);
			sound.play();

			break;

		case '^':
			hero.hit(3);
			field[hero.getCord().y][hero.getCord().x] = 'v';

			buffer.loadFromFile("sounds/hit.wav");
			sound.setBuffer(buffer);
			sound.play();
			if (!hero.isAlive()) {
				music.stop();
				buffer.loadFromFile("sounds/death.wav");
				sound.setBuffer(buffer);
				sound.play();
			}

			break;
	}

	//поведение врагов
	if (enemy.size() > 0) {
		std::list <Enemy>::iterator it = enemy.begin();
		for (it; it != enemy.end(); it++) {
			if ((*it).getID() == ID_SKELETON) {
				if ((*it).getCord().x + (*it).getDir() < 0 or (*it).getCord().x + (*it).getDir() > 2) {
					(*it).changeDir();
				}
				(*it).plusCord();
			}

			//если игрок на клетке с врагом
			if ((*it).getCord() == hero.getCord()) {
				hero.hit((*it).getDMG());

				if (!hero.isAlive()) {
					buffer.loadFromFile("sounds/death.wav");
					sound.setBuffer(buffer);
					sound.play();
				}
				else {
					buffer.loadFromFile("sounds/hit.wav");
					sound.setBuffer(buffer);
					sound.play();
				}
			}
		}
		it = enemy.begin();
		if ((*it).getCord().y > endSizeMap.x - 1)
			enemy.pop_front();
	}
}

void Map::show(sf::RenderWindow& window) {
	for (int i = startSizeMap.x; i < endSizeMap.x; i++) {
		for (int j = startSizeMap.y; j < endSizeMap.y; j++) {
			obj.setTexture(texture);
			switch (field[i][j]) {
				case '#':
					obj.setTextureRect(sf::IntRect(0, 0, spriteSize, spriteSize));
					break;

				case '%':
					obj.setTextureRect(sf::IntRect(spriteSize, 0, spriteSize, spriteSize));
					break;

				case 'o':
					obj.setTextureRect(sf::IntRect(2 * spriteSize, 0, spriteSize, spriteSize));
					break;

				case 'O':
					obj.setTextureRect(sf::IntRect(3 * spriteSize, 0, spriteSize, spriteSize));
					break;

				case 'm':
					obj.setTextureRect(sf::IntRect(4 * spriteSize, 0, spriteSize, spriteSize));
					break;

				case '^':
					obj.setTextureRect(sf::IntRect(5 * spriteSize, 0, spriteSize, spriteSize));
					break;

				case 'v':
					obj.setTextureRect(sf::IntRect(6 * spriteSize, 0, spriteSize, spriteSize));
					break;
			}

			obj.setScale(scale, scale);
			//i-1 потому что сдвигаем от глаз ненужную строчку
			obj.setPosition((j) * spriteSize * scale, (i-1) * spriteSize * scale);
			window.draw(obj);
		}
	}
	//отрисовка врагов:
	
	if (enemy.size() > 0) {
		for (std::list <Enemy>::iterator it = enemy.begin(); it != enemy.end(); it++) {
			if ((*it).getID() == ID_SKELETON) {
				(*it).obj.setScale(scale, scale);
				(*it).obj.setTexture(texture);
				(*it).obj.setPosition((*it).getCord().x * spriteSize * scale, ((*it).getCord().y - 1) * spriteSize * scale);
				window.draw((*it).obj);
			}
		}
	}
	
	//отрисовка героя:
		//проверка на смерть:
	hero.die();

	hero.obj.setScale(scale, scale);
	hero.obj.setTexture(texture);
	hero.obj.setPosition(hero.getCord().x * spriteSize * scale, (hero.getCord().y - 1) * spriteSize * scale);
	window.draw(hero.obj);
}
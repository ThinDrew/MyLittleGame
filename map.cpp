#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "entity.h"
 
#include "map.h"
#include "help.h"

// —прайты пола:
// # - обычный пол
// % - трещины в полу
// о - камушки
// ќ - череп

// ƒругие спрайты:
//^ - шипы
//v - окрававленные шипы
//m - монеты
//? - рандомна€ коробочка
short Map::count_f = 1;

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
					if (chance(10))
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

	stepCount = 0;
	count_f = 1;
	sound.stop();
	music.play();

	create();
}

void Map::print() {
	system("CLS");

	for (int i = startSizeMap.x; i < endSizeMap.x; i++) {
		for (int j = startSizeMap.y; j < endSizeMap.y; j++) {
			switch (field[i][j]) {
				case '#':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(l_blue);
					else color(gray);
					break;

				case '%':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(l_blue);
					else color(gray);
					break;

				case 'o':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(l_blue);
					else color(gray);
					break;

				case 'O':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(l_blue);
					else color(gray);
					break;

				case 'm':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(l_green);
					else color(yellow);
					break;

				case '^':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(purple);
					else color(l_red);
					break;
				
				case 'a':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(green);
					else color(l_green);
					break;

				case '-':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(purple);
					else color(l_red);
					break;

				case '?':
					if (i == startSizeMap.x or i == endSizeMap.x - 1) color(l_cyan);
					else color(cyan);
					break;
			}

			std::cout << field[i][j];
			color(white);
		}
		std::cout << '\n';
	}
	color(l_red);
	std::cout << "HP: " << hero.getHP();
	color(yellow);
	std::cout << "\nCoins: " << hero.getMoney() << '\n';
	color(white);

	std::cout << "Number of enemies: ";
	std::cout << enemy.size() << '\n';

	std::cout << "Steps: " << stepCount << '\n';
	
	if (!hero.isAlive()) {
		color(red);
		std::cout << "\n\n-----------\n";
		std::cout << "You died...\n";
		std::cout << "-----------\n\n";
		color(white);
	}

	std::cout << "Dash info: " << hero.getDash() << "\n";
}

void Map::generate() {
	int randomTile = rand() % 3;
	//–азнообразный пол
	while (true) {
		switch (rand() % 2) {
		case 0:
			field[startSizeMap.x][randomTile] = '%';
			break;

		case 1:
			field[startSizeMap.x][randomTile] = 'o';
			break;
		}
		if (chance(10))
			field[startSizeMap.x][randomTile] = 'O';
		break;
	}

	//2% шанса по€влени€ €блока
	if (chance(20)) {
		field[startSizeMap.x][randomTile] = 'a';
		return;
	}

	//5% шанса по€влени€ монет
	if (chance(50)) {
		field[startSizeMap.x][randomTile] = 'm';
		return;
	}

	//7% шанса по€влени€ пилы
	if (chance(70)) {
		field[startSizeMap.x][0] = '-';
		field[startSizeMap.x][1] = '-';
		field[startSizeMap.x][2] = '-';
		MovingSaw* saw = new MovingSaw;
		enemy.push_back(saw);
		return;
	}

	//10% шанса по€влени€ скелета
	if (chance(100)) {
		Skeleton* skeleton = new Skeleton;
		enemy.push_back(skeleton);
		return;
	}

	//40% шанса по€влени€ шипов
	if (chance(400)) {
		// 30% шанса по€влени€ вторых шипов (на той же линии)
		if (chance(300)) {
			field[startSizeMap.x][randomTile] = '^';
			int randomTile = rand() % 3;
			field[startSizeMap.x][randomTile] = '^';
			return;
		}
		else
			field[startSizeMap.x][randomTile] = '^';
		return;
	}

	//1% шанса по€влени€ рандомной коробочки
	if (chance(10)) {
		field[startSizeMap.x][randomTile] = '?';
		return;
	}

	//если ничего не сработало
	return;
}

void Map::mapMove() {
	for (int i = endSizeMap.x - 1; i >= startSizeMap.x; i--) {
		for (int j = endSizeMap.y - 1; j >= startSizeMap.y; j--) {
			if (i == endSizeMap.x - 1) {
				field[i][j] = '#';
			}

			else {
				field[i + 1][j] = field[i][j];
				field[i][j] = '#';
			}
		}
	}
}

void Map::shiftEnemies(int value) {
	if (enemy.size() > 0) {
		std::list <Enemy*>::iterator it = enemy.begin();
		for (it; it != enemy.end(); it++) {
			(*it)->setDirY(value);
		}
	}
}

//void Map::update(int move) {
//	// ƒвижение карты
//	mapMove();
//
//	generate();
//
//	shiftEnemies(1);
//}

	//ƒвижение игрока
void Map::heroMove(int move) {
	sf::Vector2i temp = hero.getCord();
	switch (move) {
		case DIR_LEFT:
			temp.x--;
			hero = -1;
			if (temp.x < startSizeMap.y) {
				temp.x = startSizeMap.y;
				hero = 0;
			}
			break;
		case DIR_RIGHT:
			temp.x++;
			hero = 1;
			if (temp.x > endSizeMap.y - 1) {
				temp.x = endSizeMap.y - 1;
				hero = 0;
			}
			break;

		case DIR_UP:
			hero = 0;
			break;

		case DIR_DASH:
			hero = 0;
			mapMove();
			hero.dashHero();
			shiftEnemies(2);
	}
	hero.setCord(temp);
}

void Map::enemyBehavior() {
	if (enemy.size() > 0) {
		std::list <Enemy*>::iterator it = enemy.begin();
		for (it; it != enemy.end(); it++) {
			if ((*it)->getID() == ID_SKELETON or (*it)->getID() == ID_SAW) {
				if ((*it)->getCord().x + (*it)->getDir().x < 0 or (*it)->getCord().x + (*it)->getDir().x > 2) {
					(*it)->changeDir();
				}
				if ((*it)->getCord().x + 2 * (*it)->getDir().x < 0 or (*it)->getCord().x + 2 * (*it)->getDir().x > 2)
					(*it)->changeSpriteDir();
				(*it)->plusDir();
			}

			//если игрок на клетке с врагом
			if ((*it)->getCord() == hero.getCord()) {
				hero.hit((*it)->getDMG());

				if (!hero.isAlive()) {
					music.stop();
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
		if ((*it)->getCord().y > endSizeMap.x - 1)
			enemy.pop_front();
	}
}

void Map::update(int move) {
	// ƒвижение карты
	mapMove();

	generate();

	//ƒвижение игрока
	heroMove(move);

	//¬заимодействие с объектами
	switch (field[hero.getCord().y][hero.getCord().x]) {
		case 'm':
			hero.addMoney(random(1, 3));
			field[hero.getCord().y][hero.getCord().x] = '#';

			buffer.loadFromFile("sounds/coin.wav");
			sound.setBuffer(buffer);
			sound.play();
			break;

		case '^':
			hero.hit(1);
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

		case 'a':
			hero.heal(1);
			field[hero.getCord().y][hero.getCord().x] = '#';

			buffer.loadFromFile("sounds/eat.wav");
			sound.setBuffer(buffer);
			sound.play();
			break;

		case '?':
			field[hero.getCord().y][hero.getCord().x] = '#';

			switch (rand() % 3) {
				case 0:
					hero.heal(hero.getMaxHP());
					buffer.loadFromFile("sounds/accept.wav");
					sound.setBuffer(buffer);
					sound.play();
					break;
				case 1:
					hero.hit(1);
					buffer.loadFromFile("sounds/decline.wav");
					sound.setBuffer(buffer);
					sound.play();
					if (!hero.isAlive()) {
						music.stop();
						buffer.loadFromFile("sounds/death.wav");
						sound.setBuffer(buffer);
						sound.play();
					}
					break;
				case 2:
					hero.addMoney(random(2, 5));
					buffer.loadFromFile("sounds/coin.wav");
					sound.setBuffer(buffer);
					sound.play();
					break;
			}
			break;
	}

	//поведение врагов
	enemyBehavior();
	count_f = 1;
	stepCount++;
}

void Map::show(sf::RenderWindow& window) {
	for (int i = startSizeMap.x ; i < endSizeMap.x; i++) {
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

				case 'a':
					obj.setTextureRect(sf::IntRect(7 * spriteSize, 0, spriteSize, spriteSize));
					break;

				case '-':
					obj.setTextureRect(sf::IntRect(8 * spriteSize, 0, spriteSize, spriteSize));
					break;
				case '?':
					obj.setTextureRect(sf::IntRect(9 * spriteSize, 0, spriteSize, spriteSize));
					break;
			}

			obj.setScale(scale, scale);
			sf::Vector2f start_place((j)*spriteSize * scale, (i-2) * spriteSize * scale);
			sf::Vector2f offset(0, (stepCount > 0) * spriteSize * scale / 60.0 * count_f);
			obj.setPosition(start_place + offset);
			window.draw(obj);
		}
	}
	//отрисовка врагов:
	
	if (enemy.size() > 0) {
		for (std::list <Enemy*>::iterator it = enemy.begin(); it != enemy.end(); it++) {
				(*it)->obj.setScale(scale, scale);
				(*it)->obj.setTexture(texture);
				sf::Vector2f start_place(((*it)->getCord().x - (*it)->getDir().x) * spriteSize * scale, ((*it)->getCord().y-2) * spriteSize * scale);
				sf::Vector2f offset(((*it)->getDir().x)* spriteSize * scale / 60.0 * count_f, spriteSize * scale / 60.0 * count_f);
	
				(*it)->obj.setPosition(start_place + offset);
				window.draw((*it)->obj);
		}
	}
	
	//отрисовка геро€:
		//проверка на смерть:
	hero.die();

	hero.obj.setScale(scale, scale);
	hero.obj.setTexture(texture);
	
	sf::Vector2f start_place((hero.getCord().x - hero.getDir())* spriteSize * scale, (hero.getCord().y-1) * spriteSize * scale);
	sf::Vector2f offset((hero.getDir() * spriteSize * scale) / 60.0 * count_f, 0);
	hero.obj.setPosition(start_place + offset);
	window.draw(hero.obj);
}
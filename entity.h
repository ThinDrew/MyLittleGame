#pragma once

#include <cstdlib>

enum Enemies
{
	ID_PLAYER,
	ID_SKELETON,
	ID_GOBLIN,
	ID_SPIKES
};

class Entity {
protected:
	int m_id;
	int m_hp;
	int m_maxhp;
	int m_dmg;
	sf::Vector2i m_dir;
	int spriteSize = 20;

	sf::Vector2i m_cord;
public:
	sf::Texture texture;
	sf::Sprite obj;

	Entity() {}

	Entity(int x, int y, int hp, int dmg) : m_cord(x, y), m_hp(hp), m_maxhp(hp), m_dmg(dmg) {}

	Entity(sf::Vector2i cord, int hp, int dmg) : m_cord(cord), m_hp(hp), m_dmg(dmg) {}

	//get
	int getHP() {
		return m_hp;
	}
	int getDMG() {
		return m_dmg;
	}
	sf::Vector2i getCord() {
		return m_cord;
	}
	int getID() {
		return m_id;
	}

	//set
	void setCord(int xValue, int yValue) {
		m_cord.x = xValue;
		m_cord.y = yValue;
	}

	void setCord(sf::Vector2i value) {
		m_cord = value;
	}

	//plus or minus
	void hit(int value) {
		m_hp -= value;
	}


	////other
	//virtual void die() = 0;
};

class Player : public Entity{
private:
	int money;
	bool dash;
public:
	Player() {}

	Player(int valueX, int valueY) :Entity(valueX/2, valueY - 3, 10, 1) , money(0), dash(false) {
		obj.setTextureRect(sf::IntRect(0, spriteSize, spriteSize, spriteSize));
		m_id = ID_PLAYER;
	}

	//get
	int getMoney() {
		return money;
	}

	void dashHero() {
		dash =  (dash == false) ? true : false;
	}
		
	bool getDash() {
		return dash;
	}
	
	void operator =(int value) {
		m_dir.x = value;
	}

	int getDir() {
		return m_dir.x;
	}

	bool isAlive() {
		return m_hp > 0;
	}

	//plus or minus
	void addMoney(int value) {
		money += value;
	}
	void heal(int value) {
		m_hp += value;
		if (m_hp > m_maxhp) m_hp = m_maxhp;
	}

	//other
	void die() {
		if (m_hp <= 0) {
			obj.setTextureRect(sf::IntRect(4 * spriteSize, spriteSize, spriteSize, spriteSize));
			m_hp = 0;
		}
	}

	//void operator +=(int value) {
	//	money += value;
	//}
};

class Enemy : public Entity {
public:
	Enemy (int damage, int health, int id): Entity(rand()% 3, -1, health, damage){
		m_id = id;
		int dir;
		switch (rand() % 2) {
			case 0:
				dir = -1;
				break;
			case 1:
				dir = 1;
				break;
		}
		m_dir.x = dir;
		m_dir.y = 1;
	}

	//get
	sf::Vector2i getDir() {
		return m_dir;
	}

	//set
	void setDirY(int value) {
		m_dir.y = value;
	}

	//plus or minus
	void plusDir() {
		m_cord += m_dir;
	}

	void plusCord(sf::Vector2i& a) {
		m_cord += a;
	}

	void minusCord() {
		m_cord -= m_dir;
	}

	//other
	void changeDir() {
		m_dir.x *= -1;
	}

	virtual void changeSpriteDir() {}
};

class MovingSpikes : public Enemy {
public:
	MovingSpikes() : Enemy(2, 0, ID_SPIKES) {
		if (getDir().x < 0)
			obj.setTextureRect(sf::IntRect(0, 3 * spriteSize, spriteSize, spriteSize));
		else
			obj.setTextureRect(sf::IntRect(spriteSize, 3 * spriteSize, spriteSize, spriteSize));
	}

	virtual void changeSpriteDir() {
		if (getDir().x > 0)
			obj.setTextureRect(sf::IntRect(0, 3 * spriteSize, spriteSize, spriteSize));
		else
			obj.setTextureRect(sf::IntRect(spriteSize, 3 * spriteSize, spriteSize, spriteSize));
	}
};

class Skeleton : public Enemy {
public:
	/////////////////dmg/hp//
	Skeleton() :Enemy(1, 10, ID_SKELETON){
		if (getDir().x < 0)
			obj.setTextureRect(sf::IntRect(5 * spriteSize, 2 * spriteSize, spriteSize, spriteSize));
		else
			obj.setTextureRect(sf::IntRect(6 * spriteSize, 2 * spriteSize, spriteSize, spriteSize));
	}
	Skeleton(const Skeleton &another): Enemy(another.m_dmg, another.m_hp, ID_SKELETON) {
		
	}

	//other
	virtual void changeSpriteDir() {
		if (getDir().x > 0)
			obj.setTextureRect(sf::IntRect(5 * spriteSize, 2 * spriteSize, spriteSize, spriteSize));
		else
			obj.setTextureRect(sf::IntRect(6 * spriteSize, 2 * spriteSize, spriteSize, spriteSize));
	}
};
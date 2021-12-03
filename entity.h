#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>

enum Enemies
{
	ID_PLAYER,
	ID_SKELETON,
	ID_GOBLIN,
	ID_SAW
};

class Entity {
protected:
	sf::Vector2i m_dir;
	int spriteSize = 20;

	sf::Vector2i m_cord;
public:
	sf::Texture texture;
	sf::Sprite obj;

	Entity() {}

	Entity(int x, int y) : m_cord(x, y) {}

	Entity(sf::Vector2i cord, int hp, int dmg) : m_cord(cord) {}

	//get
	sf::Vector2i getCord() {
		return m_cord;
	}

	//set
	void setCord(int xValue, int yValue) {
		m_cord.x = xValue;
		m_cord.y = yValue;
	}
	void setCord(sf::Vector2i value) {
		m_cord = value;
	}

	virtual int getID() = 0;

	////other
	//virtual void die() = 0;
};

class Player : public Entity{
private:
	int m_hp;
	int m_maxhp;
	int money;
	bool dash;
	static int idPlayer;
public:
	Player() {}

	Player(int valueX, int valueY) :Entity(valueX/2, valueY - 3), money(0), dash(false), m_maxhp(5), m_hp(5) {
		obj.setTextureRect(sf::IntRect(0, spriteSize, spriteSize, spriteSize));
		idPlayer = ID_PLAYER;
	}

	//get
	int getMoney() {
		return money;
	}
	int getHP() {
		return m_hp;
	}
	int getMaxHP() {
		return m_maxhp;
	}
	void dashHero() {
		dash =  (dash == false) ? true : false;
	}		
	bool getDash() {
		return dash;
	}	
	int getDir() {
		return m_dir.x;
	}

	//plus or minus
	void addMoney(int value) {
		money += value;
	}
	void heal(int value) {
		m_hp += value;
		if (m_hp > m_maxhp) m_hp = m_maxhp;
	}
	void hit(int value) {
		m_hp -= value;
	}

	//other
	void die() {
		if (m_hp <= 0) {
			obj.setTextureRect(sf::IntRect(spriteSize, spriteSize, spriteSize, spriteSize));
			m_hp = 0;
		}
	}
	void operator =(int value) {
		m_dir.x = value;
	}
	bool isAlive() {
		return m_hp > 0;
	}

	virtual int getID() {
		return idPlayer;
	}

	//void operator +=(int value) {
	//	money += value;
	//}
};

class Enemy : public Entity {
private:
	int m_dmg;
public:
	Enemy (int damage): Entity(rand()% 3, -1), m_dmg(damage){
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
	int getDMG() {
		return m_dmg;
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

	virtual int getID() {
		throw "EXCEPTION WAS THROWN: ruterned ID from parent class ";
	}

	virtual void changeSpriteDir() {}
};



class MovingSaw : public Enemy {
private:
	static int idSaw;
public:
	MovingSaw() : Enemy(1) {
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
	virtual int getID() {
		return idSaw;
	}

};


class Skeleton : public Enemy {
private:
	static int idSkeleton;
public:
	/////////////////dmg/hp/m_id//
	Skeleton() :Enemy(1){
		if (getDir().x < 0)
			obj.setTextureRect(sf::IntRect(0, 2 * spriteSize, spriteSize, spriteSize));
		else
			obj.setTextureRect(sf::IntRect(spriteSize, 2 * spriteSize, spriteSize, spriteSize));
	}

	//other
	virtual void changeSpriteDir() {
		if (getDir().x > 0)
			obj.setTextureRect(sf::IntRect(0, 2 * spriteSize, spriteSize, spriteSize));
		else
			obj.setTextureRect(sf::IntRect(spriteSize, 2 * spriteSize, spriteSize, spriteSize));
	}
	
	virtual int getID() {
		return idSkeleton;
	}
};


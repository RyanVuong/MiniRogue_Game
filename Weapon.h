#ifndef WEAPON_INCLUDED
#define WEAPON_INCLUDED
#include <string>
#include <iostream>
#include "GameObject.h"
using namespace std;

class Weapon : public GameObject{
public:
	virtual ~Weapon() {}
	Weapon(int bonus, int dmg, int r, int c, string n, string action) : GameObject(r, c, n) { m_bonus = bonus, m_damage = dmg, m_action = action; }
	virtual int dext() { return m_bonus; }
	virtual int damage() { return m_damage; }
	virtual bool isWeapon() const { return true; }
	virtual string action() { return m_action; }
	//implementing these because they were made pure virtual before
	virtual bool isTpScroll() const { return false; }
	virtual bool isHpScroll() const { return false; }
	virtual bool isArmorScroll() const { return false; }
	virtual bool isDextScroll() const { return false; }
	virtual bool isStrengthScroll() const { return false; }
private:
	string m_action;
	int m_bonus;
	int m_damage;
};

// classes for each weapon and constructors to give each one their traits
class Mace : public Weapon {
public:
	Mace(int r, int c) : Weapon(0,2, r, c, "mace", "swings mace at") {}
private:
	
};

class ShortSword : public Weapon {
public:
	ShortSword(int r, int c): Weapon(0, 2, r, c, "short sword", "slashes short sword at"){}
};

class LongSword : public Weapon {
public:
	LongSword(int r, int c) : Weapon(2, 4, r, c, "long sword", "swings long sword at") {}
};

class MagicFangs : public Weapon {
public:
	MagicFangs(int r, int c) : Weapon(3, 2, r, c, "magic fangs of sleep", "strikes magic fangs at") {}
};

class MagicAxe : public Weapon {
public:
	MagicAxe(int r, int c) : Weapon(5, 5, r, c, "magic axe", "chops magic axe at") {}
};

#endif
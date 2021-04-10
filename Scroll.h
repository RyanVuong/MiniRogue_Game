#ifndef SCROLL_INCLUDED
#define SCROLL_INCLUDED
#include <string>
#include <iostream>

using namespace std;

class Scroll : public GameObject{
public:
	Scroll(int r, int c, string n): GameObject(r,c,n){}
	virtual int getRow() { return 0; }
	virtual int getCol() { return 0; }
	virtual bool isWeapon() const { return false; }

	virtual bool isTpScroll() const = 0;
	virtual bool isHpScroll() const = 0;
	virtual bool isArmorScroll() const = 0;
	virtual bool isDextScroll() const = 0;
	virtual bool isStrengthScroll() const = 0;
private:
};

class tpScroll : public Scroll {
public:
	virtual bool isTpScroll() const { return true; }
	virtual bool isHpScroll() const { return false; }
	virtual bool isArmorScroll() const { return false; }
	virtual bool isDextScroll() const { return false; }
	virtual bool isStrengthScroll() const { return false; }
	tpScroll(int r, int c) : Scroll(r, c, "scroll of teleportation") {}
};

class armorScroll : public Scroll {
public:
	virtual bool isTpScroll() const { return false; }
	virtual bool isHpScroll() const { return false; }
	virtual bool isArmorScroll() const { return true; }
	virtual bool isDextScroll() const { return false; }
	virtual bool isStrengthScroll() const { return false; }
	armorScroll(int r, int c) : Scroll(r, c, "scroll of enhance armor") {}
};

class healthScroll : public Scroll {
public:
	virtual bool isTpScroll() const { return false; }
	virtual bool isHpScroll() const { return true; }
	virtual bool isArmorScroll() const { return false; }
	virtual bool isDextScroll() const { return false; }
	virtual bool isStrengthScroll() const { return false; }
	healthScroll(int r, int c) : Scroll(r, c, "scroll of enhance health") {}
};

class strengthScroll : public Scroll {
public:
	virtual bool isTpScroll() const { return false; }
	virtual bool isHpScroll() const { return false; }
	virtual bool isArmorScroll() const { return false; }
	virtual bool isDextScroll() const { return false; }
	virtual bool isStrengthScroll() const { return true; }
	strengthScroll(int r, int c) : Scroll(r, c, "scroll of strength") {}
};

class dextScroll : public Scroll {
public:
	virtual bool isTpScroll() const { return false; }
	virtual bool isHpScroll() const { return false; }
	virtual bool isArmorScroll() const { return false; }
	virtual bool isDextScroll() const { return true; }
	virtual bool isStrengthScroll() const { return false; }
	dextScroll(int r, int c) : Scroll(r, c, "scroll of enhance dexterity") {}
};

#endif
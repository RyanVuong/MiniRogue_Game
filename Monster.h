#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED
#include "Actor.h"
#include "GameObject.h"
#include "utilities.h"
using namespace std;

class Monster : public Actor {
public:
    Monster(int r, int c, int h, int a, int s, int d, int slp, GameObject* o) : Actor(r, c, h, a, s, d, slp, o) {}
    string name() { return m_name; }
    void setName(string n) { m_name = n; }
    // helper functions for arena
    virtual bool isGoblin() const = 0;
    virtual bool isSnakewoman() const = 0;
    virtual bool isBogeyman() const = 0;
    virtual bool isDragon() const = 0;
    virtual int maxHealth() { return 0; }
private:
    string m_name;
};

class Goblin : public Monster {
public:
    // constructs a goblin with the stats given in the spec, a short sword, and a name

    Goblin(int r, int c) : Monster(r, c, randInt(15, 20), 1, 3, 1, 0, new ShortSword(r, c)) { setWeapon(new ShortSword(r, c)); setName("Goblin"); }
    // write goblin move function!

    virtual bool isGoblin() const { return true; }
    virtual bool isSnakewoman() const { return false; }
    virtual bool isBogeyman() const { return false; }
    virtual bool isDragon() const { return false; }

};

class Snakewoman : public Monster {
public:
    // constructs a snakewoman with the stats given in the spec, magic fangs, and a name

    Snakewoman(int r, int c) : Monster(r, c, randInt(3, 6), 3, 2, 3, 0, new MagicFangs(r, c)) { setWeapon(new MagicFangs(r, c)); setName("Snakewoman"); }

    virtual bool isGoblin() const { return false; }
    virtual bool isSnakewoman() const { return true; }
    virtual bool isBogeyman() const { return false; }
    virtual bool isDragon() const { return false; }

};
class Bogeyman : public Monster {
public:
    // constructs a bogeyman with the stats given in the spec, a short sword, and a name

    Bogeyman(int r, int c) : Monster(r, c, randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), 0, new ShortSword(r, c)) { setWeapon(new ShortSword(r, c)); setName("Bogeyman"); }

    virtual bool isGoblin() const { return false; }
    virtual bool isSnakewoman() const { return false; }
    virtual bool isBogeyman() const { return true; }
    virtual bool isDragon() const { return false; }

};

class Dragon : public Monster {
public:
    // constructs a dragon with the stats given in the spec, a long sword, and a name
    int maxHealth() { return randInt(20, 25); } //random int for dragon's initial and max health
    Dragon(int r, int c) : Monster(r, c, maxHealth(), 4, 4, 4, 0, new LongSword(r, c)) { setWeapon(new LongSword(r, c)); setName("Dragon"); }


    virtual bool isGoblin() const { return false; }
    virtual bool isSnakewoman() const { return false; }
    virtual bool isBogeyman() const { return false; }
    virtual bool isDragon() const { return true; }

};


#endif
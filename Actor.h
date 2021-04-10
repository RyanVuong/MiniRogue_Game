#ifndef ACTOR_INCLUDED
#define ACTOR_INCLUDED
#include "GameObject.h"
#include "utilities.h"

class Actor {
public:
    Actor(int r, int c, int h, int a, int s, int d, int slp, GameObject* o) { m_r = r, m_c = c, m_health = h; m_armor = a, m_strength = s, m_dexterity = d, m_sleep = slp, m_object = o; m_putToSleep = false; }
    
    // getters
    int health() { return m_health; }
    int a_row() { return m_r; }
    int a_col() { return m_c; }
    int armor() { return m_armor; }
    int sleep() { return m_sleep; }
    int strength() { return m_strength; }
    int dexterity() { return m_dexterity; }
    // bools to see if actor is killed or sleeping or put to sleep
    bool isKilled() { return (health() <= 0); }
    bool isAsleep() { return (sleep() > 0); }
    bool putToSleep() { return m_putToSleep; }
    // sets actor to sleep when the actor is actually put to sleep to display putting to sleep message
    void setPutToSleep(bool b) { m_putToSleep = b; }
    // points for attacking
    int attackerPoints() { return dexterity() + m_object->dext(); }
    int defenderPoints() { return dexterity() + armor(); }
    int damagePoints() { return randInt(0, strength() + m_object->damage() - 1); }
    GameObject* getObject() { return m_object; }  // gets the object player is holding
    // setters
    void setWeapon(GameObject* o) { m_object = o; } 
    void setDext(int d) { m_dexterity = d; }
    void setStrength(int s) { m_strength = s; }
    void setSleep(int slp) { m_sleep = slp; }
    void setArmor(int a) { m_armor = a; }
    void setRow(int r) { m_r = r; }
    void setCol(int c) { m_c = c; }
    void setHealth(int h) { m_health = h; }

private:
	int m_health;
	int m_r;
    int m_c;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleep;
    bool m_putToSleep;
    GameObject* m_object;
};




#endif
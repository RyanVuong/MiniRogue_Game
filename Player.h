#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED
#include "utilities.h"
#include "Arena.h"
#include "GameObject.h"
#include <vector>
using namespace std;

class Player : public Actor {
public:
	//giving the player a short sword and placing it into the inventory
	// change magic fangs later
	Player(Arena* ap, int r, int c) : Actor(r, c, 20, 2, 2, 2, 0, new ShortSword(r, c)) { m_arena = ap; m_inventory.push_back(new ShortSword(r, c)); setWeapon(m_inventory[0]); m_maxHP = 20; }
	// functions for playing the game
	void move(char d);
	void accessInventory();  // accesses inventory
	int grab(Arena* ap);	// grabs item on the ground
	int wield();  //wields weapon
	int read();	// reads scroll and returns corresponding scroll
	int useScroll(GameObject* o);	// activates ability of scroll
	virtual ~Player() {}
	void setMax(int m) { m_maxHP = m; }
	// getters
	int maxHP() { return m_maxHP; }
	GameObject* topItem() { return m_inventory[m_inventory.size() - 1]; } // gets top item of inventory for printing when picked up
	vector<GameObject*> getInventory() { return m_inventory; }
private:
	Arena* m_arena;
	vector<GameObject*> m_inventory;
	int m_maxHP;

};

#endif
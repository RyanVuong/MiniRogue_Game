#include <string>
#include <iostream>
#include "Weapon.h"
#include "Scroll.h"
#include <vector>
#include "Monster.h"
#ifndef ARENA_INCLUDED
#define ARENA_INCLUDED

using namespace std;

class Player;
class Arena {

public:
	Arena(int nRows, int nCols);
	Arena(int nRows, int nCols, Player* p, int lvl);
	int level() { return m_level; }
	int rows() const { return m_rows; }
	int cols() const { return m_cols; }
	int getCellStatus(int r, int c) const { return m_grid[r - 1][c - 1]; }
	void setCellStatus(int r, int c, int status) { m_grid[r - 1][c - 1] = status; }
	Player* player() { return m_player; }

	void display();
	// adding things to arena
	void addPlayer(int r, int c);
	void addObjects(int r, int c);
	void addMonsters(int r, int c);
	void addStaircase(int r, int c);
	void addIdol(int r, int c);
	// staircase functions
	void setStaircaseRow(int r) { m_staircaseRow = r; }
	void setStaircaseCol(int c) { m_staircaseCol = c; }
	void setidolRow(int r) { m_idolRow = r; }
	void setidolCol(int c) { m_idolCol = c; }
	// level functions
	int getLevel() { return m_level; } 
	void setLevel(int i) { m_level = i; }
	// player and monster functions
	bool isValid(int r, int c); // sees if the player's move is valid
	bool attack(int e); // player attack function
	bool monstersAttack(int e); // monsters' attack function
	bool inRange(int e); // returns true if player can be attacked by monster
	bool moveMonsters(int e, int smell, char c); // function for moving monsters, returns true if monster is moved
	bool moveSnakewomen(int e, char c); //function for moving snakewomen, returns true if it's moved
	bool moveBogeyman(int e, char c); // function for moving bogeymen, same as snakewomen but with different smell
	bool goblinMove(int e, int s, char c);
	bool pathExists(int maze[18][70], int sr, int sc, int er, int ec);
	bool drop(int e);
	vector<GameObject*> objVector() { return m_objVector; }
	vector<Monster*> monsterVector() { return m_monsterVector; }
private:
	int m_level;
	int m_rows;
	int m_cols;
	int m_grid[18][70];
	Player* m_player;
	int m_staircaseRow;
	int m_staircaseCol;
	int m_idolRow;
	int m_idolCol;
	vector<GameObject*> m_objVector;
	vector<Monster*> m_monsterVector;
};

#endif
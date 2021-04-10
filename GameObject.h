#ifndef GAMEOBJECT_INCLUDED
#define GAMEOBJECT_INCLUDED
#include <string>
using namespace std;

class GameObject {
public:
	GameObject(int r, int c, string name): m_row(r), m_col(c), m_name(name){} 
	// all game objects have a location and name
	string name() const { return m_name; }
	int row() const { return m_row; }
	int col() const { return m_col; }
	void setRow(int r) { m_row = r; }
	void setColumn(int c) { m_col = c; }
	virtual ~GameObject() {}
	// virtual functions for accessing weapon traits 
	virtual bool isWeapon() const = 0;
	virtual int dext() { return 0; }
	virtual int damage() { return 0; }
	virtual string action() { return " "; }
	// functions to help figure out which effects to apply
	virtual bool isTpScroll() const = 0;
	virtual bool isHpScroll() const = 0;
	virtual bool isArmorScroll() const = 0;
	virtual bool isDextScroll() const = 0;
	virtual bool isStrengthScroll() const = 0;
private:
	string m_name;
	int m_row;
	int m_col;
};

#endif
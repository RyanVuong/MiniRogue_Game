#include "Arena.h"
#include "utilities.h"
#include "Player.h"
#include "Monster.h"
Arena::Arena(int nRows, int nCols) {

	// creates empty arena
	m_level = 0;
	m_rows = nRows;
	m_cols = nCols;
	

	for (int r = 1; r <= m_rows; r++) {
		for (int c = 1; c <= m_cols; c++) {
			setCellStatus(r, c, 1);
		}
	}
	for (int r = 2; r < m_rows; r++) {
		for (int c = 2; c < m_cols; c++) {
			setCellStatus(r, c, 0);
		}
	}
}
Arena::Arena(int nRows, int nCols, Player* p, int lvl) {
	m_rows = nRows;
	m_cols = nCols;
	m_player = p;
	m_level = lvl;
	for (int r = 1; r <= m_rows; r++) {
		for (int c = 1; c <= m_cols; c++) {
			setCellStatus(r, c, 1);
		}
	}
	for (int r = 2; r < m_rows; r++) {
		for (int c = 2; c < m_cols; c++) {
			setCellStatus(r, c, 0);
		}
	}
}

bool Arena::attack(int e) {
	int a = randInt(1, 5); // rand int for sleep probability
	int b = randInt(2, 6); // rand int for sleep setting
	if (randInt(1, m_player->attackerPoints()) >= randInt(1, monsterVector()[e]->defenderPoints())) { // if attack is successful...
		monsterVector()[e]->setHealth(monsterVector()[e]->health() - m_player->damagePoints()); // reduce monster's health
		if (monsterVector()[e]->health() < 1) { // if monster is killed in the attack
			drop(e);
			monsterVector()[e]->setRow(0);
			monsterVector()[e]->setCol(0);
		}
		if (m_player->getObject()->dext() == 3 && monsterVector()[e]->isAsleep() == false && a == 1) {  // if the player is wielding magic fangs of sleep then there's a 1 in 5 chance of sleeping the defender
			monsterVector()[e]->setSleep(randInt(2, 6));
			monsterVector()[e]->setPutToSleep(true); // setting put to sleep to be true to display putting to sleep action
		}
		else if (m_player->getObject()->dext() == 3 && monsterVector()[e]->isAsleep() && a == 1) { // if player is already sleeping, setSleep to be greater if randInt(2,6) is greater
			if (b > monsterVector()[e]->sleep()) {
				monsterVector()[e]->setSleep(b);
			}
		}
		return true;
	}
	return false;
}

bool Arena::inRange(int e) {
	if ((monsterVector()[e]->a_row() == m_player->a_row() - 1 && monsterVector()[e]->a_col() == m_player->a_col()) || (monsterVector()[e]->a_row() == m_player->a_row() + 1 && monsterVector()[e]->a_col() == m_player->a_col()) || (monsterVector()[e]->a_row() == m_player->a_row() && monsterVector()[e]->a_col() == m_player->a_col() + 1) || (monsterVector()[e]->a_row() == m_player->a_row() && monsterVector()[e]->a_col() == m_player->a_col() - 1)) {
		return true;
	}
	else return false;
}

bool Arena::monstersAttack(int e) {
	int a = randInt(1, 5); // rand int for sleep probability
	int b = randInt(2, 6); // rand int for sleep setting
	if (inRange(e)) {
		if (randInt(1, monsterVector()[e]->attackerPoints()) >= randInt(1, m_player->defenderPoints())) { // if attack is successful...
			m_player->setHealth(m_player->health() - monsterVector()[e]->damagePoints()); // reduce player's health
			if (monsterVector()[e]->isSnakewoman() && m_player->isAsleep() == false && a == 1) {  
				m_player->setSleep(randInt(2, 6));
				m_player->setPutToSleep(true);
			}
			else if (monsterVector()[e]->isSnakewoman() && m_player->isAsleep() == true && a == 1) {
				if (b > m_player->sleep()) {
					m_player->setSleep(b);
				}
			}
			return true;
		}
	}
	return false;
}

bool Arena::drop(int e) {
	// if a monster is killed, randomizes its drop if it does drop something
	int a = randInt(1, 10); // 1 in 10 chance of dropping magic axe
	int b = randInt(1, 3); // 1 in 3 chance
	int f = randInt(1, 5); // 1 in 5 chance to get each scroll
	int d = randInt(1, 2); // 1 in 2 chance
	int r = m_monsterVector[e]->a_row();
	int c = m_monsterVector[e]->a_col();
	if (getCellStatus(monsterVector()[e]->a_row(), monsterVector()[e]->a_col()) != 3) {
		if (monsterVector()[e]->isBogeyman()) {
			if (a == 1) {
				m_objVector.push_back(new MagicAxe(r, c));
				setCellStatus(r, c, 3);
				return true;
			}
		}
		if (monsterVector()[e]->isGoblin()) {
			if (b == 1) {
				if (d == 1) {
					m_objVector.push_back(new MagicFangs(r, c));
					setCellStatus(r, c, 3);
					return true;
				}
				if (d == 2) {
					m_objVector.push_back(new MagicAxe(r, c));
					setCellStatus(r, c, 3);
					return true;
				}
			}
		}
		if (monsterVector()[e]->isSnakewoman()) {
			if (b == 1) {
				m_objVector.push_back(new MagicFangs(r, c));
				setCellStatus(r, c, 3);
				return true;
			}
		}
		if (monsterVector()[e]->isDragon()) {
			if (f == 1) {
				m_objVector.push_back(new tpScroll(r, c));
				setCellStatus(r, c, 3);
			}
			if (f == 2) {
				m_objVector.push_back(new healthScroll(r, c));
				setCellStatus(r, c, 3);
			}
			if (f == 3) {
				m_objVector.push_back(new dextScroll(r, c));
				setCellStatus(r, c, 3);
			}
			if (f == 4) {
				m_objVector.push_back(new strengthScroll(r, c));
				setCellStatus(r, c, 3);
			}
			if (f == 5) {
				m_objVector.push_back(new armorScroll(r, c));
				setCellStatus(r, c, 3);
			}
			return true;
		}
		
	}
	return false;

}

bool Arena::isValid(int r, int c) {
	for (size_t i = 0; i < monsterVector().size(); i++) {
		if (monsterVector()[i]->a_row() == r && monsterVector()[i]->a_col() == c) {
			return false;
		}
	}
	if (getCellStatus(r, c) == 0 || getCellStatus(r, c) == 3 || getCellStatus(r, c) == 4 || getCellStatus(r, c) == 5) {
		return true;
	}
	return false;
}

void Arena::display()
{
	char displayGrid[18][70];
	int r, c;

	for (r = 1; r <= rows(); r++) {
		for (c = 1; c <= cols(); c++) {
			if (getCellStatus(r, c) == 1) {
				displayGrid[r - 1][c - 1] = '#';
			}
			else if (getCellStatus(r, c) == 0) {
				displayGrid[r - 1][c - 1] = ' ';
			}
		}
	}
	
	// displays each object at their respective position
	// if the object is a weapon, display ')', if the object is a scroll, display '?'
	for (size_t i = 0; i < m_objVector.size(); i++) {
		displayGrid[m_objVector[i]->row() - 1][m_objVector[i]->col() - 1] = (m_objVector[i]->isWeapon() ? ')' : '?');
	}
	// displays each monster as their respective type
	for (size_t i = 0; i < m_monsterVector.size(); i++) {
		if (m_monsterVector[i]->isGoblin() && m_monsterVector[i]->a_col() != 0) {
			displayGrid[m_monsterVector[i]->a_row() - 1][m_monsterVector[i]->a_col() - 1] = 'G';
		}
		if (m_monsterVector[i]->isSnakewoman() && m_monsterVector[i]->a_col() != 0) {
			displayGrid[m_monsterVector[i]->a_row() - 1][m_monsterVector[i]->a_col() - 1] = 'S';
		}
		if (m_monsterVector[i]->isBogeyman() && m_monsterVector[i]->a_col() != 0) {
			displayGrid[m_monsterVector[i]->a_row() - 1][m_monsterVector[i]->a_col() - 1] = 'B';
		}
		if (m_monsterVector[i]->isDragon() && m_monsterVector[i]->a_col() != 0) {
			displayGrid[m_monsterVector[i]->a_row() - 1][m_monsterVector[i]->a_col() - 1] = 'D';
		}
		//cout << displayGrid[m_monsterVector[i]->a_row() - 1][m_monsterVector[i]->a_col() - 1] << endl;
	}
	displayGrid[m_staircaseRow - 1][m_staircaseCol - 1] = '>'; // displays staircase
	displayGrid[m_idolRow - 1][m_idolCol - 1] = '&'; // displays idol
	displayGrid[m_player->a_row() - 1][m_player->a_col() - 1] = '@';
	
	clearScreen();

	for (r = 1; r <= rows(); r++)
	{
		for (c = 1; c <= cols(); c++)
			cout << displayGrid[r - 1][c - 1];
		cout << endl;
	}
	cout << endl;
}

void Arena::addPlayer(int r, int c) {
	// adds player with initial stats and weapon
	m_player = new Player(this, r, c);
}

void Arena::addObjects(int r, int c) {

	// makes it a 50-50 whether a weapon or scroll is generated
	int random = randInt(1, 2);
	// if a weapon is generated, makes the chance to get each weapon 1/3
	int a = randInt(1, 3);
	// if a scroll is generated, makes the chance to get each one 1/5
	int b = randInt(1, 5);
	//adds a random object
	if (random == 1) {
		if (a == 1) {
			m_objVector.push_back(new Mace(r, c));
		}
		if (a == 2) {
			m_objVector.push_back(new ShortSword(r, c));
		}
		if (a == 3) {
			m_objVector.push_back(new LongSword(r, c));
		}
	}
	else {
		if (b == 1) {
			m_objVector.push_back(new dextScroll(r, c));
		}
		if (b == 2) {
			m_objVector.push_back(new healthScroll(r, c));
		}
		if (b == 3) {
			m_objVector.push_back(new tpScroll(r, c));
		}
		if (b == 4) {
			m_objVector.push_back(new strengthScroll(r, c));
		}
		if (b == 5) {
			m_objVector.push_back(new armorScroll(r, c));
		}
	}
	setCellStatus(r, c, 3);
}

void Arena::addMonsters(int r, int c) {
	// adds a random monster based on the level and probability in the spec
	int a = randInt(1, 2);
	int b = randInt(1, 3);
	int d = randInt(1, 4);
	if (level() < 2) {
		if (a == 1) {
			m_monsterVector.push_back(new Goblin(r, c));
		}
		if (a == 2) {
			m_monsterVector.push_back(new Snakewoman(r, c));
		}
	}
	if (level() == 2) {
		if (b == 1) {
			m_monsterVector.push_back(new Goblin(r, c));
		}
		if (b == 2) {
			m_monsterVector.push_back(new Snakewoman(r, c));
		}
		if (b == 3) {
			m_monsterVector.push_back(new Bogeyman(r, c));
		}
	}
	if (level() > 2) {
		if (d == 1) {
			m_monsterVector.push_back(new Goblin(r, c));
		}
		if (d == 2) {
			m_monsterVector.push_back(new Snakewoman(r, c));
		}
		if (d == 3) {
			m_monsterVector.push_back(new Bogeyman(r, c));
		}
		if (d == 4) {
			m_monsterVector.push_back(new Dragon(r, c));
		}
	}
}
// adds the staircase to the floor
void Arena::addStaircase(int r, int c) {
	setStaircaseRow(r);
	setStaircaseCol(c);
	setCellStatus(r, c, 4);
}
// adds the idol to the fourth floor
void Arena::addIdol(int r, int c) {
	setidolRow(r);
	setidolCol(c);
	setCellStatus(r, c, 5);
}

bool Arena::moveSnakewomen(int e, char c) {
	int monstRow = monsterVector()[e]->a_row();
	int monstCol = monsterVector()[e]->a_col();
	int playerRow = m_player->a_row();
	int playerCol = m_player->a_col();
	int rowDistance = abs(monstRow - playerRow); // row distance between player and monster
	int colDistance = abs(monstCol - playerCol); // column distance between player and monster
	int totalDistance = rowDistance + colDistance;
	int rowDistanceDown = abs(monstRow - playerRow - 1); // row distance between player and monster for proposed move down
	int colDistanceLeft = abs(monstCol - playerCol - 1); // column distance between player and monster for proposed move left
	int rowDistanceUp = abs(monstRow - playerRow + 1); // row distance between player and monster for proposed move up
	int colDistanceRight = abs(monstCol - playerCol + 1); // column distance between player and monster for proposed move right
	int totalDistanceDown = rowDistanceDown + colDistance;
	int totalDistanceLeft = rowDistance + colDistanceLeft;
	int totalDistanceUp = rowDistanceUp + colDistance;
	int totalDistanceRight = rowDistance + colDistanceRight;
	if (inRange(e)) {
		return false;
	}
	// if total distance is less than 4 and greater than zero, move in the direction of the player
	if (totalDistance < 4 && totalDistance > 0) {
		if (totalDistance == 2) {
			if (c == 'h') {
				if (totalDistanceRight < totalDistance - 1) {
					monsterVector()[e]->setCol(monstCol - 1);
					return true;
				}
				else return false;
			}
			if (c == 'l') {
				if (totalDistanceLeft < totalDistance - 1) {
					monsterVector()[e]->setCol(monstCol + 1);
					return true;
				}
				else return false;
			}
			if (c == 'j') {
				if (totalDistanceUp < totalDistance - 1) {
					monsterVector()[e]->setRow(monstRow - 1);
					return true;
				}
				else return false;
			}
			if (c == 'k') {
				if (totalDistanceDown < totalDistance- 1) {
					monsterVector()[e]->setRow(monstRow + 1);
					return true;
				}
				else return false;
			}
		}
		if (totalDistanceDown < totalDistance) {
			monsterVector()[e]->setRow(monstRow - 1);
			return true;
		}
		if (totalDistanceUp < totalDistance) {
			monsterVector()[e]->setRow(monstRow + 1);
			return true;
		}
		if (totalDistanceRight < totalDistance) {
			monsterVector()[e]->setCol(monstCol + 1);
			return true;
		}
		if (totalDistanceLeft < totalDistance) {
			monsterVector()[e]->setCol(monstCol - 1);
			return true;
		}
		return false;
		
	}
	return false;
}

bool Arena::moveBogeyman(int e, char c) {
	int monstRow = monsterVector()[e]->a_row();
	int monstCol = monsterVector()[e]->a_col();
	int playerRow = m_player->a_row();
	int playerCol = m_player->a_col();
	int rowDistance = abs(monstRow - playerRow); // row distance between player and monster
	int colDistance = abs(monstCol - playerCol); // column distance between player and monster
	int totalDistance = rowDistance + colDistance;
	int rowDistanceDown = abs(monstRow - playerRow - 1); // row distance between player and monster for proposed move down
	int colDistanceLeft = abs(monstCol - playerCol - 1); // column distance between player and monster for proposed move left
	int rowDistanceUp = abs(monstRow - playerRow + 1); // row distance between player and monster for proposed move up
	int colDistanceRight = abs(monstCol - playerCol + 1); // column distance between player and monster for proposed move right
	int totalDistanceDown = rowDistanceDown + colDistance;
	int totalDistanceLeft = rowDistance + colDistanceLeft;
	int totalDistanceUp = rowDistanceUp + colDistance;
	int totalDistanceRight = rowDistance + colDistanceRight;
	if (inRange(e)) {
		return false;
	}
	if (totalDistance < 6 && totalDistance > 0) {
		if (totalDistance == 2) {
			if (c == 'h') {
				if (totalDistanceDown < totalDistance - 1) {
					monsterVector()[e]->setCol(monstCol - 1);
					return true;
				}
				else return false;
			}
			if (c == 'l') {
				if (totalDistanceUp < totalDistance - 1) {
					monsterVector()[e]->setCol(monstCol + 1);
					return true;
				}
				else return false;
			}
			if (c == 'j') {
				if (totalDistanceRight < totalDistance - 1) {
					monsterVector()[e]->setRow(monstRow - 1);
					return true;
				}
				else return false;
			}
			if (c == 'k') {
				if (totalDistanceLeft < totalDistance - 1) {
					monsterVector()[e]->setRow(monstRow + 1);
					return true;
				}
				else return false;
			}
		}
		if (totalDistanceDown < totalDistance) {
			monsterVector()[e]->setRow(monstRow - 1);
			return true;
		}
		if (totalDistanceUp < totalDistance) {
			monsterVector()[e]->setRow(monstRow + 1);
			return true;
		}
		if (totalDistanceRight < totalDistance) {
			monsterVector()[e]->setCol(monstCol + 1);
			return true;
		}
		if (totalDistanceLeft < totalDistance) {
			monsterVector()[e]->setCol(monstCol - 1);
			return true;
		}
		return false;

	}
	return false;
}

bool Arena::moveMonsters(int e, int smell, char c) {
	
	if (monsterVector()[e]->isSnakewoman()) {
		if (moveSnakewomen(e, c)) {
			return true;
		}
	}
	if (monsterVector()[e]->isBogeyman()) {
		if (moveBogeyman(e, c)) {
			return true;
		}
	}
	if (monsterVector()[e]->isGoblin()) {
		if (goblinMove(e, smell, c)) {
			return true;
		}
	}
	return false;
}

bool Arena::goblinMove(int e, int s, char c) {
	int tempGrid[18][70];
	for (int x = 1; x < 18; x++)
	{
		for (int y = 1; y < 70; y++)
		{
			tempGrid[x][y] = m_grid[x][y];
		}
	}
	if (pathExists(tempGrid, monsterVector()[e]->a_row(), monsterVector()[e]->a_col(), m_player->a_row(), m_player->a_col())) {
		// same move function as other monsters if a path exists
		int monstRow = monsterVector()[e]->a_row();
		int monstCol = monsterVector()[e]->a_col();
		int playerRow = m_player->a_row();
		int playerCol = m_player->a_col();
		int rowDistance = abs(monstRow - playerRow); // row distance between player and monster
		int colDistance = abs(monstCol - playerCol); // column distance between player and monster
		int totalDistance = rowDistance + colDistance;
		int rowDistanceDown = abs(monstRow - playerRow - 1); // row distance between player and monster for proposed move down
		int colDistanceLeft = abs(monstCol - playerCol - 1); // column distance between player and monster for proposed move left
		int rowDistanceUp = abs(monstRow - playerRow + 1); // row distance between player and monster for proposed move up
		int colDistanceRight = abs(monstCol - playerCol + 1); // column distance between player and monster for proposed move right
		int totalDistanceDown = rowDistanceDown + colDistance;
		int totalDistanceLeft = rowDistance + colDistanceLeft;
		int totalDistanceUp = rowDistanceUp + colDistance;
		int totalDistanceRight = rowDistance + colDistanceRight;
		if (inRange(e)) {
			return false;
		}
		if (totalDistance < s && totalDistance > 0) {
			if (totalDistance == 2) {
				if (c == 'h') {
					if (totalDistanceDown < totalDistance - 1) {
						monsterVector()[e]->setCol(monstCol - 1);
						return true;
					}
					else return false;
				}
				if (c == 'l') {
					if (totalDistanceUp < totalDistance - 1) {
						monsterVector()[e]->setCol(monstCol + 1);
						return true;
					}
					else return false;
				}
				if (c == 'j') {
					if (totalDistanceRight < totalDistance - 1) {
						monsterVector()[e]->setRow(monstRow - 1);
						return true;
					}
					else return false;
				}
				if (c == 'k') {
					if (totalDistanceLeft < totalDistance - 1) {
						monsterVector()[e]->setRow(monstRow + 1);
						return true;
					}
					else return false;
				}
			}
			if (totalDistanceDown < totalDistance) {
				monsterVector()[e]->setRow(monstRow - 1);
				return true;
			}
			if (totalDistanceUp < totalDistance) {
				monsterVector()[e]->setRow(monstRow + 1);
				return true;
			}
			if (totalDistanceRight < totalDistance) {
				monsterVector()[e]->setCol(monstCol + 1);
				return true;
			}
			if (totalDistanceLeft < totalDistance) {
				monsterVector()[e]->setCol(monstCol - 1);
				return true;
			}
			return false;

		}
		return true;
	}
	return false;
}

bool Arena::pathExists(int maze[18][70], int sr, int sc, int er, int ec) {

	if ((sr == er + 1 && sc == ec ) || (sr == er - 1 && sc == ec) || (sr == er && sc == ec + 1) || (sr == er && sc == ec - 1)) {
		return true;
	}
	maze[sr][sc] = 2;
	if (maze[sr + 1][sc] == 0) {
		if (pathExists(maze, sr + 1, sc, er, ec)) {
			return true;
		}
	}
	if (maze[sr][sc - 1] == 0) {
		if (pathExists(maze, sr, sc - 1, er, ec)) {
			return true;
		}
	}
	if (maze[sr - 1][sc] == 0) {
		if (pathExists(maze, sr - 1, sc, er, ec)) {
			return true;
		}
	}
	if (maze[sr][sc + 1] == 0) {
		if (pathExists(maze, sr, sc + 1, er, ec)) {
			return true;
		}
	}
	return false;
}
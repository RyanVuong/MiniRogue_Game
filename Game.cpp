// Game.cpp

#include "Game.h"
#include "Player.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    
    m_arena = new Arena(18, 70);    // creates a new arena
    int rPlayer;
    int cPlayer;
    
    do
    {
        rPlayer = randInt(2, 17);
        cPlayer = randInt(2, 69);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != 0);    // randomizes player's location
    //creates a player
    m_arena->addPlayer(rPlayer, cPlayer);
    // creating objects with the nonoverlapping coordinates
    m_arena->addStaircase(randInt(2, 17), randInt(2, 69));
    for (int i = 0; i < randInt(2, 3); i++) {
        m_arena->addObjects(randInt(2, 17), randInt(2, 69));
    }
    for (int i = 0; i < randInt(2, 5 * (m_arena->level() + 1) + 1); i++) {
        int r = randInt(2, 17);
        int c = randInt(2, 69);
        m_arena->addMonsters(r, c);
    }
}


void Game::play()
{
    // helper variables for printing
    int grabber = 0; // to be stored in grab int value
    int read = 0; // to be stored in read int value
    int att = 100; // to be stored in attack int value 
    bool isAttacked = false;
    int level = 0;
    Player* player = m_arena->player();
    //displays initial screen with stats
    m_arena->display();
    cout << "Dungeon Level: " << m_arena->level() << ", Hit Points: " << player->health() << ", Armor: " << player->armor() << ", Strength: " << player->strength() << ", Dexterity: " << player->dexterity() << endl;
    char character = getCharacter();
    while (character != 'q' || player->isAsleep()) {
        att = 100;
        grabber = 50;
        bool gameWon = false;
        bool test = false;
        int wield = 30;
        int regen = randInt(1, 10);
        char move = 'a';
        bool arr[26] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
        bool isAttacked[26] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
        // only moves the character if a move character is chosen and that move is valid and attack if attacking is valid
        for (size_t i = 0; i < m_arena->monsterVector().size(); i++) {
            if (m_arena->moveMonsters(i, 15, move) && isAttacked[i] == false) {
                arr[i] = true;
            }
        }
        if (player->isAsleep() == false) {
            
            if (character == 'h' || character == 'j' || character == 'k' || character == 'l') {
                if (character == 'h' && m_arena->isValid(player->a_row(), player->a_col() - 1))
                    player->move(character); 
                else if (character == 'l' && m_arena->isValid(player->a_row(), player->a_col() + 1))
                    player->move(character);
                else if (character == 'j' && m_arena->isValid(player->a_row() + 1, player->a_col()))
                    player->move(character);
                else if (character == 'k' && m_arena->isValid(player->a_row() - 1, player->a_col()))
                    player->move(character);

                else {
                    for (size_t i = 0; i < m_arena->monsterVector().size(); i++) { // checks if player can attack a monster and if so attacks monster accordingly
                        if (character == 'h' && (m_arena->monsterVector()[i]->a_row() == player->a_row()) && (m_arena->monsterVector()[i]->a_col() == player->a_col() - 1)) {
                            if (m_arena->attack(i)) {
                                isAttacked[i] = true;
                            }
                            att = i;
                        }
                        if (character == 'l' && (m_arena->monsterVector()[i]->a_row() == player->a_row()) && (m_arena->monsterVector()[i]->a_col() == player->a_col() + 1)) {
                            if (m_arena->attack(i)) {
                                isAttacked[i] = true;
                            }
                            att = i;
                        }
                        if (character == 'j' && (m_arena->monsterVector()[i]->a_row() - 1 == player->a_row()) && (m_arena->monsterVector()[i]->a_col() == player->a_col())) {
                            if (m_arena->attack(i)) {
                                isAttacked[i] = true;
                            }
                            att = i;
                        }
                        if (character == 'k' && (m_arena->monsterVector()[i]->a_row() + 1 == player->a_row()) && (m_arena->monsterVector()[i]->a_col() == player->a_col())) {
                            if (m_arena->attack(i)) {
                                isAttacked[i] = true;
                            }
                            att = i;
                        }
                    }
                }
            }
            if (character == 'c') {
                player->setHealth(50);
                player->setStrength(9);
            }

            if (character == 'i') {
                player->accessInventory();
                getCharacter();
            }
            if (character == 'g') {
                int g = player->grab(m_arena);
                grabber = g;
                // if the player actually grabbed an item, move the item off the board
                if (grabber != 50) {
                    m_arena->setCellStatus(m_arena->objVector()[grabber]->row(), m_arena->objVector()[grabber]->col(), 0);
                    m_arena->objVector()[grabber]->setColumn(0);
                    m_arena->objVector()[grabber]->setRow(0);
                }
                // if player picks up the idol, end the game with winning text
                else if (m_arena->getCellStatus(player->a_row(), player->a_col()) == 5) {
                    gameWon = true;
                }
            }
            if (character == 'w') {
                int w = player->wield();
                wield = w;
            }
            if (character == 'r') {
                int r = player->read();
                read = r;
            }
            if (character == '>' && m_arena->getCellStatus(player->a_row(), player->a_col()) == 4) {
                level++;
                m_arena = new Arena(18, 70, player, level);
                int rPlayer;
                int cPlayer;

                do
                {
                    rPlayer = randInt(2, 17);
                    cPlayer = randInt(2, 69);
                } while (m_arena->getCellStatus(rPlayer, cPlayer) != 0);    // randomizes player's location
                // creating objects with the nonoverlapping coordinates
                if (level < 5) {
                    m_arena->addStaircase(randInt(2, 17), randInt(2, 69)); // adding staircase
                }
                if (level == 4) {
                    m_arena->addIdol(randInt(2, 17), randInt(2, 69));
                }
                for (int i = 0; i < randInt(2, 3); i++) {
                    m_arena->addObjects(randInt(2, 17), randInt(2, 69));
                }
                for (int i = 0; i < randInt(2, 5 * (m_arena->level() + 1) + 1); i++) {
                    int r = randInt(2, 17);
                    int c = randInt(2, 69);
                    m_arena->addMonsters(r, c);
                }
            }
        }
        

        m_arena->display();
        
        cout << "Dungeon Level: " << m_arena->level() << ", Hit Points: " << player->health() << ", Armor: " << player->armor() << ", Strength: " << player->strength() << ", Dexterity: " << player->dexterity() << endl;
        
        if (gameWon == true) {
            cout << "You pick up the golden idol" << endl;
            cout << "Congratulations, you won!" << endl;
            break;
        }

      
        if (character == 'h' && m_arena->isValid(player->a_row(), player->a_col() - 1))
            char move = 'h';
        else if (character == 'l' && m_arena->isValid(player->a_row(), player->a_col() + 1))
            char move = 'l';
        else if (character == 'j' && m_arena->isValid(player->a_row() + 1, player->a_col()))
            char move = 'j';
        else if (character == 'k' && m_arena->isValid(player->a_row() - 1, player->a_col()))
            char move = 'k';
       
        if (grabber != 50 && character == 'g') { // if player actually grabbed an object, display the grab message
            if (player->topItem()->isWeapon())
                cout << "You pick up " << player->topItem()->name() << endl;
            else
                cout << "You pick up a scroll called " << player->topItem()->name() << endl;
        }
        if (character == 'r') {
            if (read > 50) {
                if (read == 51) {
                    cout << "You read the scroll called scroll of enhance armor." << endl;
                    cout << "Your armor glows blue." << endl;
                }
                if (read == 52) {
                    cout << "You read the scroll called scroll of strength." << endl;
                    cout << "Your muscles bulge." << endl;
                }
                if (read == 53) {
                    cout << "You read the scroll called scroll of enhance dexterity." << endl;
                    cout << "You feel like less of a klutz." << endl;
                }
                if (read == 54) {
                    cout << "You read the scroll called scroll of enhance health." << endl;
                    cout << "You feel your heart beating stronger." << endl;
                }
                if (read == 55) {
                    cout << "You read the scroll called scroll of teleportation." << endl;
                    cout << "You feel your body wrenched in space and time." << endl;
                }
            }
            else {
                cout << "You can't read a " << player->getInventory()[read]->name() << endl;
            }
        }

        if (character == 'w') {
            if (player->getInventory()[wield]->isWeapon()) {
                cout << "You are wielding " << player->getObject()->name() << endl;
            }
            else cout << "You can't wield " << player->getInventory()[wield]->name() << endl;
        }

        // if player attempts to attack, display the according message for what ensues
        if (att != 100) {
            if (isAttacked[att] == true) {
                if (m_arena->monsterVector()[att]->isKilled()) {
                    cout << "Player " << player->getObject()->action() << " the " << m_arena->monsterVector()[att]->name() << " dealing a final blow." << endl;
                }
                else if (m_arena->monsterVector()[att]->putToSleep() == true) {
                    cout << "Player " << player->getObject()->action() << " the " << m_arena->monsterVector()[att]->name() << " and hits, putting " << m_arena->monsterVector()[att]->name() << " to sleep." << endl;
                    m_arena->monsterVector()[att]->setPutToSleep(false);
                }
                else
                    cout << "Player " << player->getObject()->action() << " the " << m_arena->monsterVector()[att]->name() << " and hits." << endl;
            }
            else {
                cout << "Player " << player->getObject()->action() << " the " << m_arena->monsterVector()[att]->name() << " and misses." << endl;
            }
        }
        // if a monster attacks, display the according message for what ensues and carry out the attack
        for (size_t i = 0; i < m_arena->monsterVector().size(); i++) {
            if (m_arena->monsterVector()[i]->isAsleep() == false && arr[i] == false) {
                if (m_arena->monstersAttack(i)) {
                    if (player->isKilled()) {
                        cout << m_arena->monsterVector()[i]->name() << " " << m_arena->monsterVector()[i]->getObject()->action() << " Player dealing a final blow." << endl;
                    }
                    else if (player->putToSleep() == true) {
                        cout << m_arena->monsterVector()[i]->name() << " " << m_arena->monsterVector()[i]->getObject()->action() << " Player and hits, putting Player to sleep." << endl;
                        player->setPutToSleep(false);
                    }
                    else {
                        cout << m_arena->monsterVector()[i]->name() << " " << m_arena->monsterVector()[i]->getObject()->action() << " Player and hits." << endl;
                    }
                }
                else if (m_arena->inRange(i)) {
                    cout << m_arena->monsterVector()[i]->name() << " " << m_arena->monsterVector()[i]->getObject()->action() << " Player and misses." << endl;
                }
                //else {
                    //m_arena->moveMonsters(i, 15);
               // }
            }
            else if(m_arena->monsterVector()[i]->isAsleep() == true){
                m_arena->monsterVector()[i]->setSleep(m_arena->monsterVector()[i]->sleep() - 1);
            }
        }
        if (player->isKilled()) {
            break;
        }
        if (player->isAsleep()) {
            player->setSleep(player->sleep() - 1);
        }
        // 1 in 10 chance to regen player's hp
        if (regen == 1 && player->health() < player->maxHP()) {
            player->setHealth(player->health() + 1);
        }
        // 1 in 10 chance to regen dragon's hp
        for (size_t i = 0; i < m_arena->monsterVector().size(); i++) {
            if (m_arena->monsterVector()[i]->isDragon() && (randInt(1, 10) == 1) && m_arena->monsterVector()[i]->health() < m_arena->monsterVector()[i]->maxHealth()) {
                m_arena->monsterVector()[i]->setHealth(m_arena->monsterVector()[i]->health() + 1);
            }
        }
        character = getCharacter();
    }
    cout << "Press q to exit game." << endl;
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

#include "Player.h"
#include "utilities.h"

void Player::move(char d) {

    // changes players coordinate according to the arrow key chosen
    if (d == 'h') {
        setCol(a_col() - 1);
    }
    if (d == 'l') {
        setCol(a_col() + 1);
    }
    if (d == 'k') {
        setRow(a_row() - 1);
    }
    if (d == 'j') {
        setRow(a_row() + 1);
	}

}

void Player::accessInventory() {
    clearScreen();
    // loops for every item in the player's inventory and lists them.
    string arr[26] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
    for (size_t i = 0; i < m_inventory.size(); i++) {
        cout << arr[i] << ". " << m_inventory[i]->name() << endl;
    }
}

int Player::grab(Arena* ap) {
    // if the player actually grabs an item this function returns which item
    for (size_t i = 0; i < ap->objVector().size(); i++) {
        if (a_row() == ap->objVector()[i]->row() && a_col() == ap->objVector()[i]->col()) {
            m_inventory.push_back(ap->objVector()[i]);
            return i;
        }
    }
    return 50; // return this number because inventory slots can't reach 50
}

int Player::wield() {
    
    char arr[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    accessInventory();
    char toWield = getCharacter();  // reads the character of the inventory slot the character wants to equip a weapon from and equips the weapon if the inventory slot is a weapon

    for (size_t i = 0; i < m_inventory.size(); i++) {
        if (toWield == arr[i]) {
            Weapon* wp = dynamic_cast<Weapon*>(m_inventory[i]);
            if (wp != nullptr) {
                setWeapon(m_inventory[i]);
            }
            return i;
        }
    }
    return 30;
}

int Player::read() {

    accessInventory();
    int value = 0;
    char arr[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    char toRead = getCharacter();
    for (size_t i = 0; i < m_inventory.size(); i++) {  // iterate through each item of the inventory to find the letter the user chose
        if (toRead == arr[i]) {
            Scroll* sp = dynamic_cast<Scroll*>(m_inventory[i]);
            if (sp != nullptr) { // if the letter the user chose is a scroll, use the scroll
                value = useScroll(m_inventory[i]);
                if (i == m_inventory.size() - 1) { 
                    m_inventory.pop_back();
                }
                else {
                    for (size_t j = i + 1; j < m_inventory.size(); j++) { // shifts the vector so that it deletes the scroll that was used if it isn't at the end of the vector
                        m_inventory[i] = m_inventory[j];
                    }
                    m_inventory.pop_back();
                }
            }
            else {
                value = i;
            }
            return value;
            break;
        }
    }
    return 0;
}

int Player::useScroll(GameObject* o) {
    if (o->isArmorScroll()) {
        setArmor(armor() + randInt(1, 3));  // if scroll being used is an armor one, add 1-3 armor points
        return 51;
    }
    if (o->isStrengthScroll()) {
        setStrength(strength() + randInt(1, 3)); // if scroll is a strength one, add 1-3 strength points
        return 52;
    }
    if (o->isDextScroll()) {
        setDext(dexterity() + 1); // if scroll is a dexterity one, add 1 dexterity point
        return 53;
    }
    if (o->isHpScroll()) {
        setMax(maxHP() + randInt(3, 8)); // if scroll is an hp one, add 3-8 max health points
        return 54;
    }
    if (o->isTpScroll()) {
        setRow(randInt(2, 17)); // tp player to random position
        setCol(randInt(2, 69));
        return 55;
    }
    return 0;
}
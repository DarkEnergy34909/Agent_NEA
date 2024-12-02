#include "Character.h"

Character::Character(Texture* texture, int posX, int posY, int width, int height) : Entity(texture, posX, posY, width, height) {
	// Initialise hp
	hp = hpMax;

	// Initialise alive variable
	alive = true;
}

Character::~Character() {
	// Do nothing
}

void Character::takeDamage(int damage) {
	// Reduce the character's hp by the given amount
	hp -= damage;

	// If hp is less than or equal to 0, the character is dead
	if (hp <= 0) {
		alive = false;
	}
}
#include "Character.h"

Character::Character(Texture* texture, int posX, int posY, int width, int height) : Entity(texture, posX, posY, width, height) {
	// Initialise hp
	hp = hpMax;

	// Initialise alive variable
	alive = true;

	// Character has no weapon by default
	weapon = NULL;
}

Character::~Character() {
	// Delete the weapon
	if (weapon != NULL) {
		delete weapon;
		weapon = NULL;
	}
}

void Character::takeDamage(int damage) {
	// Reduce the character's hp by the given amount
	hp -= damage;

	// If hp is less than or equal to 0, the character is dead
	if (hp <= 0) {
		alive = false;
	}
}

void Character::render() {
	// Render the character itself
	Entity::render();

	// Render the weapon if the character has one
	if (weapon != NULL) {
		switch (weapon->getWeaponType()) {
			case PISTOL:
				// Check the angle of the weapon
				// If the weapon is pointed to the right, render the gun to the right of the character
				if (weapon->getAngle() > -90.0 && weapon->getAngle() < 90.0) {
					weapon->render(posX + (3 * width / 4), posY + (height / 2));
				}
				// If the weapon is pointed to the left, render the gun to the left of the character
				else {
					weapon->render(posX + (width / 4) - weapon->getTexture()->getWidth(), posY + (height / 2));
				}
				break;
			default:
				// If the weapon type is invalid, print an error message
				std::cout << "Invalid weapon type" << std::endl;
				break;
		}
	}
}

void Character::setWeapon(Weapon* weapon) {
	// Delete the current weapon if the Character has one
	if (this->weapon != NULL) {
		delete this->weapon;
		this->weapon = NULL;
	}

	// Set the new weapon
	this->weapon = weapon;
}

// X and Y default values are set to -999 so that the default values can be checked in the function
Bullet* Character::shoot(int x, int y) {
	// If the character has a weapon and the weapon has ammo, then the character can shoot
	if (weapon != NULL) {
		// Create a new bullet with position at the edge of the character's gun, taking into account the angle of the weapon
		// If the weapon is pointed to the right, the bullet is fired to the right of the character
		if (weapon->getAngle() > -90.0 && weapon->getAngle() < 90.0) {

			// Calculate x position of the bullet
			//double bulletX = posX + (3 * width / 4) + (weapon->getTexture()->getWidth() * cos(weapon->getAngle() * M_PI / 180));
			double bulletX = posX + (3 * width / 4) + (weapon->getTexture()->getWidth());
			bulletX = int(bulletX);

			// Calculate y position of the bullet
			//double bulletY = posY + (height / 2) - (weapon->getTexture()->getHeight() * sin(weapon->getAngle() * M_PI / 180));
			double bulletY = posY + (height / 2);
			bulletY = int(bulletY);

			// If a position is given, set the angle of the weapon to point towards that position
			if (x != -999 && y != -999) {
				// Calculate the angle of the weapon
				double angle = atan2(y - bulletY, x - bulletX) * 180 / M_PI;
				// Set the angle of the weapon
				weapon->setAngle(angle);

			}

			return weapon->fire(bulletX, bulletY);
		}
		// If the weapon is pointed to the left, the bullet is fired to the left of the character
		else {

			// Calculate x position of the bullet
			double bulletX = posX + (width / 4) - weapon->getTexture()->getWidth() - weapon->getBulletTexture()->getWidth();
			bulletX = int(bulletX);

			// Calculate y position of the bullet
			//double bulletY = posY + (height / 2) - (weapon->getTexture()->getHeight() * sin(weapon->getAngle() * M_PI / 180));
			double bulletY = posY + (height / 2);
			bulletY = int(bulletY);

			// If a position is given, set the angle of the weapon to point towards that position
			if (x != -999 && y != -999) {
				// Calculate the angle of the weapon
				double angle = atan2(y - bulletY, x - bulletX) * 180 / M_PI;
				// Set the angle of the weapon
				weapon->setAngle(angle);
			}

			std::cout << "posX: " << posX << "width: " << width << "bullet width: " << weapon->getBulletTexture()->getWidth() << "bulletX: " << bulletX << std::endl;

			return weapon->fire(bulletX, bulletY);
		}
	}
	else {
		// If the character has no weapon, return NULL
		return NULL;
	}
}

bool Character::isAlive() {
	// Return whether the character is alive
	return hp > 0;
}

int Character::getHp() {
	// Return the current hp of the character
	return hp;
}
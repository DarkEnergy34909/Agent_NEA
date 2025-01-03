#pragma once
#include "Entity.h"
#include "Weapon.h"
#include "Bullet.h"

class Character : public Entity {
	public:
		// Constructor
		Character(Texture* texture, int posX, int posY, int width, int height);

		// Destructor
		~Character();

		// Reduces the character's hp by a given amount
		void takeDamage(int damage);

		// Adds a weapon to the character
		void setWeapon(Weapon* weapon);

		// Renders the character and the weapon (if the character has one)
		virtual void render() override; 

		// Returns a bullet fired by the character
		Bullet* shoot();

	protected:
		// Maximum hp of the character
		int hpMax = 100;

		// Current hp of the character
		int hp;

		// Whether the character is alive
		bool alive;

		// The character's weapon
		Weapon* weapon;
};
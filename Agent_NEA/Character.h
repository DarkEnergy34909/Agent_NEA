#pragma once
#include "Entity.h"

class Character : public Entity {
	public:
		// Constructor
		Character(Texture* texture, int posX, int posY, int width, int height);

		// Destructor
		~Character();

		// Reduces the character's hp by a given amount
		void takeDamage(int damage);

		// TODO: shoot method
		// void shoot();

	private:
		// Maximum hp of the character
		int hpMax = 100;

		// Current hp of the character
		int hp;

		// Whether the character is alive
		bool alive;

		// TODO: weapon attribute
		// Weapon weapon;
};
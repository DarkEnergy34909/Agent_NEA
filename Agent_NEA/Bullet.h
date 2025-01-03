#pragma once
#include "Entity.h"
#include "Texture.h"

class Bullet : public Entity {
	public:
		// Constructor
		Bullet(Texture* texture, int posX, int posY, double angle, int damage);

		// Destructor
		~Bullet();

		// Calculates the x and y velocities of the bullet based on the angle
		void calculateVelocities();

		// Renders the bullet
		void render() override;

		// Getters 
		int getDamage();

	private:
		// The dimensions of the bullet
		static const int BULLET_WIDTH = 14;
		static const int BULLET_HEIGHT = 5;

		// Maximum velocity of the bullet
		int velMax = 10;

		// Damage dealt by the bullet
		int damage;

		// The angle the bullet is fired at
		double angle;
};
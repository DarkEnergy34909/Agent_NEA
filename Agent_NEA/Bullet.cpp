#include "Bullet.h"

Bullet::Bullet(Texture* texture, int posX, int posY, double angle, int damage) : Entity(texture, posX, posY, BULLET_WIDTH, BULLET_HEIGHT) {
	// Set the object type
	objectType = BULLET;

	// Set the angle of the bullet
	this->angle = angle;

	// Set the damage of the bullet
	this->damage = damage;

	// Calculate and set the x and y velocities of the bullet based on the angle
	calculateVelocities();
}

Bullet::~Bullet() {
	// Do not free the texture as other Bullet instances may be using it
}

void Bullet::calculateVelocities() {
	// Convert the angle to radians
	double radianAngle = angle * (M_PI / 180);

	// Calculate and set x velocity
	velX = velMax * cos(radianAngle);

	// Calculate and set y velocity
	velY = velMax * sin(radianAngle);
}

void Bullet::render() {
	// Copied from Entity::render() - renders the bullet at its current position
	// If not moving , render the Bullet normally
	if ((velX == 0 && velY == 0) || animationTextures.empty()) {
		// Render the bullet at the given position with the given angle
		//SDL_Point point = { 0,0 };
		texture->render(posX, posY, NULL, angle, NULL);

		// Reset the animation
		currentFrame = 0;
	}
	else {
		// Render the Entity with the current animation texture
		animationTextures[currentFrame]->render(posX, posY, NULL, angle);

		// Increment frame delay counter
		frameDelayCounter++;

		// If frame delay is reached, increment the current frame
		if (frameDelayCounter == frameDelay) {
			// Reset frame delay
			frameDelayCounter = 0;

			// Move onto the next texture
			currentFrame++;
		}

		// If the end of the animation is reached, reset the animation
		if (currentFrame == animationTextures.size()) {
			currentFrame = 0;
		}
	}
}

int Bullet::getDamage() {
	// Return the damage dealt by the bullet
	return damage;
}
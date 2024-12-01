#include "Entity.h"

Entity::Entity(Texture& texture, int posX, int posY, int width, int height) : GameObject(texture, posX, posY, width, height) {
	// Initialise velocities
	velX = 0;
	velY = 0;

	// Initialise the animation vector
	animationTextures = std::vector<Texture*>();
}

Entity::~Entity() {
	// Do nothing
}

void Entity::moveX() {
	// Move the entity in the x-direction
	posX += velX;

	// Update collider
	collider.x = posX;
}

void Entity::moveY() {
	// Move the entity in the y-direction
	posY += velY;

	// Update collider
	collider.y = posY;
}

void Entity::addAnimationTexture(Texture& texture) {
	// Modify the texture's dimensions to match that of the Entity
	texture.setWidth(width);
	texture.setHeight(height);

	// Add a texture to the animationTextures vector
	animationTextures.push_back(&texture);
}

void Entity::render() {
	// If not moving , render the entity normally
	if ((velX == 0 && velY == 0) || animationTextures.empty()) {
		texture->render(posX, posY);

		// Reset the animation
		currentFrame = 0;
	}
	else {
		// Render the Entity with the current animation texture
		animationTextures[currentFrame]->render(posX, posY);

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

void Entity::setVelX(int velX) {
	// Set the x velocity of the entity
	this->velX = velX;
}

void Entity::setVelY(int velY) {
	// Set the y velocity of the entity
	this->velY = velY;
}
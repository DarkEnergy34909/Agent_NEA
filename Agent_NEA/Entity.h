#pragma once
#include "GameObject.h"
#include <vector>

class Entity : public GameObject {
	public:
		// Constructor
		Entity(Texture* texture, int posX, int posY, int width, int height);
		
		// Destructor
		virtual ~Entity();

		// Moves the entity in the x-direction
		void moveX();

		// Moves the entity in the y-direction
		void moveY();

		// Adds a texture to the animationTextures vector
		void addAnimationTexture(Texture* texture);

		// Renders the entity (overridden from GameObject)
		virtual void render(int camX = 0, int camY = 0) override;

		// Setters (for testing)
		void setVelX(int velX);

		void setVelY(int velY);

		// Getters 
		int getVelX();

		int getVelY();

	protected:
		// Maximum velocity of the entity
		int velMax = 1;

		// Current x/y velocities of the entity
		int velX, velY;

		// Textures used for animation of the entity (when moving)
		std::vector<Texture*> animationTextures;

		// Current frame of the animation
		int currentFrame = 0;

		// How many frames to wait before moving onto the next texture
		int frameDelay = 15;

		// Frame delay counter
		int frameDelayCounter = 0;
};
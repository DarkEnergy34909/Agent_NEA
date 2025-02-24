#include "Player.h"

Player::Player(Texture* texture, int posX, int posY, int width, int height) : Character(texture, posX, posY, width, height) {
	// Set the object type
	objectType = PLAYER;
}

Player::~Player() {
	// Do nothing
}

void Player::handleInput(SDL_Event& e, int camX, int camY) {
	// If a key is pressed, adjust velocity
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			// Move up if W is pressed
			case SDLK_w:
				velY -= velMax;
				break;

			// Move down if S is pressed
			case SDLK_s:
				velY += velMax;
				break;

			// Move left if A is pressed
			case SDLK_a:
				velX -= velMax;
				break;

			// Move right if D is pressed
			case SDLK_d:
				velX += velMax;
				break;

		}
	}

	// If a key is released, cancel out previous velocity
	else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
			// Stop moving up if W is released
			case SDLK_w:
				velY += velMax;
				break;

			// Stop moving down if S is released
			case SDLK_s:
				velY -= velMax;
				break;

			// Stop moving left if A is released
			case SDLK_a:
				velX += velMax;
				break;

			// Stop moving right if D is released
			case SDLK_d:
				velX -= velMax;
				break;
		}
	}

	// If the mouse is moved adjust the angle of the weapon
	else if (e.type == SDL_MOUSEMOTION) {
		
		// Get the position of the cursor
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		// Calculate the angle between the player's weapon and the cursor
		double angle = 0; 

		// Check the weapon type and calculate the angle accordingly
		switch (weapon->getWeaponType()) {
			case PISTOL:
				// Calculate the angle between the player and the cursor
				//angle = atan2(mouseY - (posY + (height / 2)), mouseX - (posX + (3 * width / 4)));
				angle = atan2(mouseY - (posY + (height / 2) - camY), mouseX - (posX + (width / 2) - camX));

				// Convert the angle from radians to degrees
				angle = angle * 180 / M_PI;

				// Subtract the angle from 360 degrees as weapon rotation is clockwise
				//angle = 360 - angle; COMMENTING THIS OUT TO SEE IF IT FIXES THE ISSUE
				break;

			default:
				// If the weapon type is invalid, print an error message
				std::cout << "Invalid weapon type" << std::endl;
				break;
		}
		// Set the angle of the weapon
		weapon->setAngle(angle);

	}
}
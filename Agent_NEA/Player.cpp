#include "Player.h"

Player::Player(Texture& texture, int posX, int posY, int width, int height) : Character(texture, posX, posY, width, height) {
	// Do nothing
}

Player::~Player() {
	// Do nothing
}

void Player::handleInput(SDL_Event& e) {
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
}
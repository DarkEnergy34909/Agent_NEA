#pragma once
#include "Character.h"

class Player : public Character {
	public:
		// Constructor
		Player(Texture* texture, int posX, int posY, int width, int height);

		// Destructor
		~Player();

		// Handles keyboard input for the player
		void handleInput(SDL_Event& e);
};
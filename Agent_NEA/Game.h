#pragma once

// Include SDL2 libraries
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Game {
	public:
		// Constructor
		Game();
			
		// Destructor
		~Game();

		// Initialises SDL and creates a window for the game
		bool init();

		// Loads textures/sounds for the game
		bool loadMedia();

		// Closes the game and quits SDL
		void close(); 

		// Main window loop
		void mainLoop();

	private:
		// Screen dimensions
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;


		// The window the game is rendered to 
		SDL_Window* window; 

		// The renderer that renders the game
		SDL_Renderer* renderer; 


};

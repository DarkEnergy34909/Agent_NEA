#pragma once
#include "Texture.h"

enum MenuOption {
	PLAY, INSTRUCTIONS, SETTINGS, QUIT
};

class MainMenu {
	public:
		// Constructor
		MainMenu(SDL_Window* window, SDL_Renderer* renderer);

		// Destructor 
		~MainMenu();

		// Initialises the main menu
		bool loadMenu();

		// Updates the main menu
		void update();

		// Handles input
		void handleInput(SDL_Event& e);

		// Renders the main menu
		void render();

		// Completes the appropriate action for the current menu option
		void selectOption();

		// Returns whether the game has started
		bool isGameStarted();

		// Returns whether the user has quit the game
		bool hasQuit();

		// Closes the main menu
		void close();


	private:
		// File path
		const std::string PATH = "C:/Users/Sebastian Kember/OneDrive - King Edward VI Grammar School/CS A-Level/NEA/Media/";

		// The window
		SDL_Window* window;

		// The renderer
		SDL_Renderer* renderer;

		// Screen constants
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

		// The font
		TTF_Font* font;

		// The background texture
		Texture* background;

		// The title texture
		Texture* title;

		// The play texture
		Texture* play;

		// The instructions texture
		Texture* instructions;

		// The settings texture
		Texture* settings;

		// The quit texture
		Texture* quit;

		// The current menu option selected
		int currentOption;

		// Whether the game has started
		bool gameStarted;

		// Whether the user has quit the game
		bool gameQuit;
};

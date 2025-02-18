#pragma once
#include "Texture.h"
#include "Constants.h"

enum MenuOption {
	PLAY, INSTRUCTIONS, SETTINGS, QUIT
};

enum MenuScreen {
	MAIN_MENU, INSTRUCTIONS_MENU, SETTINGS_MENU, GAME_OVER_MENU
};

enum SettingsOption {
	VOLUME, FPS, BACK
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

		// Returns the volume level
		int getVolume();

		// Returns the FPS
		int getFPS();

		// Sets the game screen
		void setScreen(int screen);

		// Sets whether the game has started
		void setGameStarted(bool gameStarted);

		// Closes the main menu
		void close();

		// Sets the score
		void setScore(int score);


	private:
		// File path
		const std::string PATH = "C:/Users/Sebastian Kember/OneDrive - King Edward VI Grammar School/CS A-Level/NEA/Media/";

		// The window
		SDL_Window* window;

		// The renderer
		SDL_Renderer* renderer;

		// Screen constants
		//const int SCREEN_WIDTH = 640;
		//const int SCREEN_HEIGHT = 480;
		//const int SCREEN_WIDTH = 800;
		//const int SCREEN_HEIGHT = 640;

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

		// The back texture
		Texture* back;

		// The instructions screen texture
		Texture* instructionsText;

		// The settings screen texture
		Texture* settingsText;

		// The volume texture
		Texture* volumeSetting;

		// The FPS texture
		Texture* fpsSetting;

		// The game over texture
		Texture* gameOver;

		// The current menu option selected
		int currentOption;

		// The current settings option selected
		int currentSettingsOption;

		// The current menu screen
		int currentScreen;

		// Whether the game has started
		bool gameStarted;

		// Whether the user has quit the game
		bool gameQuit;

		// The volume level
		int volume;

		// The FPS
		int fps;

		// The score displayed on the game over screen
		int score;
};

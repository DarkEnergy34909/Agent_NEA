#include "Game.h"
#include <iostream>



Game::Game() {
	renderer = NULL;
	window = NULL;

	level = NULL;
	mainMenu = NULL;
}

Game::~Game() {
	// Close the game
	close();
}

bool Game::init() {
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error initialising SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initialise window
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cout << "Error enabling scaling: " << SDL_GetError() << std::endl;
		return false; 
	}

	window = SDL_CreateWindow("Agent", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cout << "Error creating window: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initialise renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	// Set renderer colour to white
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Initialise SDL_image to load iamge textures
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "Error initialising SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

	// Initialise SDL_ttf to load text
	if (TTF_Init() == -1) {
		std::cout << "Error initialising SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}

	// Initialise SDL_mixer (with 6 channels) to play sounds
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudioDevice(44100, MIX_DEFAULT_FORMAT, 8, 2048, NULL, 0) < 0) {
		std::cout << "Error initialising SDL_mixer: " << Mix_GetError() << std::endl;
		return false;
	}
	// Set volume to half initially
	Mix_Volume(-1, 64);

	// Initialise the game level
	level = new Level(window, renderer);

	// Initialise the main menu
	mainMenu = new MainMenu(window, renderer);

	return true; 

}

bool Game::loadMedia() {

	// Load level media
	if (!level->init()) {
		std::cout << "Error loading level" << std::endl;
		return false;
	}

	return true;
}

bool Game::loadMenu() {
	// Load main menu
	if (!mainMenu->loadMenu()) {
		std::cout << "Error loading main menu" << std::endl;
		return false;
	}
	return true;
}

void Game::close() {
	// Delete the level
	delete level;
	level = NULL;

	// Delete the main menu
	delete mainMenu;
	mainMenu = NULL;

	// Close the renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Close the window
	SDL_DestroyWindow(window);
	window = NULL;

	// Close SDL subsystems
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}


void Game::mainLoop() {
	// Initialise quit flag
	bool quit = false;

	// Input event
	SDL_Event e;

	// Main loop for both the main menu and the game
	while (!quit) {

		// Test loop for the main menu
		while (!quit) {
			// When an event is detected
			while (SDL_PollEvent(&e) != 0) {

				// Quit the game if the user closes the window
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				else {
					// Handle input
					mainMenu->handleInput(e);

					// Update game settings
					if (mainMenu->getVolume() != volume) {
						volume = mainMenu->getVolume();
						int mixVolume = volume * (128.0 / 100.0);
						Mix_Volume(-1, (volume * (128 / 100)));
					}
				}

			}

			// Clear previous frame
			SDL_RenderClear(renderer);

			// Update the main menu
			mainMenu->update();

			// Render everything to the screen
			SDL_RenderPresent(renderer);

			// If the game has started, break the loop
			if (mainMenu->isGameStarted()) {
				// Reset the game started flag (so that the game does not start again when the main menu is reloaded)
				mainMenu->setGameStarted(false);
				break;
			}

			// If the user has quit, quit the game
			if (mainMenu->hasQuit()) {
				quit = true;
			}
		}


		// Main loop
		while (!quit) {

			// When an event is detected
			while (SDL_PollEvent(&e) != 0) {

				// Quit the game if the user closes the window
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				else {
					// Handle input
					level->handleInput(e);
				}
			}

			// Clear previous frame
			SDL_RenderClear(renderer);

			// Update the level
			level->update();

			// Render everything to the screen
			SDL_RenderPresent(renderer);

			// If the level is not running, quit the game
			if (!level->isRunning()) {
				// Get the score from the level and add it to the main menu
				int score = level->getScore();
				mainMenu->setScore(score);

				// Set the screen to the game over menu
				mainMenu->setScreen(GAME_OVER_MENU);

				// Close the level and reload it
				delete level;
				level = NULL;

				level = new Level(window, renderer);
				loadMedia();

				break;
			}
		}
	}
}



/*
void Game::mainLoop() {
	// Initialise quit flag
	bool quit = false;

	// Input event
	SDL_Event e;

	// Test texture
	Texture testTexture = Texture(renderer);
	if (!testTexture.loadFromFile(PATH + "car_test_image.png")) {
		std::cout << "Error loading test texture" << std::endl;
	}

	// Test texture 2
	Texture testTexture2 = Texture(renderer);
	if (!testTexture2.loadFromFile(PATH + "car_test_image2.png")) {
		std::cout << "Error loading test texture" << std::endl;
	}

	// Test entity
	Entity testEntity = Entity(&testTexture, 0, 0, 100, 100);
	testEntity.setVelX(1);
	testEntity.setVelY(0);
	testEntity.addAnimationTexture(&testTexture);
	testEntity.addAnimationTexture(&testTexture2);


	// Main loop
	while (!quit) {

		// When an event is detected
		while (SDL_PollEvent(&e) != 0) {
			// Quit the game if the user closes the window
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			else {
				// Handle input
			}
		}

		// Clear the previous frame
		SDL_RenderClear(renderer);

		// Move and render the test entity
		testEntity.moveX();
		testEntity.moveY();
		testEntity.render();

		// Render updated screen
		SDL_RenderPresent(renderer);
		
	}
}
*/


bool Game::start() {
	// Start the game
	if (!init()) {
		std::cout << "Error initialising game" << std::endl;
		return false;
	}
	if (!loadMedia()) {
		std::cout << "Error loading media" << std::endl;
		return false;
	}
	if (!loadMenu()) {
		std::cout << "Error loading menu" << std::endl;
		return false;
	}
	mainLoop();
	return true;
}

int main(int argc, char* args[]) {
	// Initialise a new Game 
	Game game = Game();
	game.start();

	return 0;
}
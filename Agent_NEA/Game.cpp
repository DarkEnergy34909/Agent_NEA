#include "Game.h"
#include <iostream>



Game::Game() {
	renderer = NULL;
	window = NULL;
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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 2048) < 0) {
		std::cout << "Error initialising SDL_mixer: " << Mix_GetError() << std::endl;
		return false;
	}

	return true; 

}

bool Game::loadMedia() {
	// Load media

	// Load test texture

	return true;
}

void Game::close() {

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

	// Texture for testing 
	Texture testTexture = Texture(renderer);

	if (!testTexture.loadFromFile(PATH + "car_test_image.png")) {
		std::cout << "Error loading test texture" << std::endl;
	}

	Texture testTexture2 = Texture(renderer);
	if (!testTexture2.loadFromFile(PATH + "car_test_image2.png")) {
		std::cout << "Error loading test texture" << std::endl;
	}

	// First GameObject for testing
	//GameObject object1 = GameObject(testTexture, 0, 0, 300, 300);

	// Second GameObject for testing
	//GameObject object2 = GameObject(testTexture2, 300, 300, 100, 100);

	// First Entity for testing
	//Entity entity1 = Entity(testTexture, 0, 0, 200, 200);
	//entity1.setVelX(1);
	//entity1.setVelY(1);
	
	//entity1.addAnimationTexture(testTexture);
	//entity1.addAnimationTexture(testTexture2);

	// Player character for testing
	Player player1 = Player(testTexture, 0, 0, 200, 200);


	// Main loop
	while (!quit) {

		// When an event is detected
		while (SDL_PollEvent(&e) != 0) {

			// Quit the game if the user closes the window
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
				player1.handleInput(e);
			}
		}

		SDL_RenderClear(renderer);

		// Render test objects
		//object1.render();
		//object2.render();

		// Move and render test entity
		//entity1.moveX();
		//entity1.moveY();
		//entity1.render();

		// Move and render player
		player1.moveX();
		player1.moveY();
		player1.render();

		SDL_RenderPresent(renderer);
	}

	close();
}

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
	mainLoop();
	return true;
}

int main(int argc, char* args[]) {
	// Initialise a new Game 
	Game game = Game();
	game.start();

	return 0;
}
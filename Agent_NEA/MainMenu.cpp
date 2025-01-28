#include "MainMenu.h"

MainMenu::MainMenu(SDL_Window* window, SDL_Renderer* renderer) {
	// Set the window and renderer
	this->window = window;
	this->renderer = renderer;

	// Set textures to null initially
	background = NULL;
	title = NULL;
	play = NULL;
	settings = NULL;
	quit = NULL;

	// Set font to null initially
	font = NULL;

	// Set the current menu option to play
	currentOption = PLAY;

	// Set game started to false
	gameStarted = false;

	// Set game quit to false
	gameQuit = false;
	
}

MainMenu::~MainMenu() {
	// Free the textures
	close();
}

bool MainMenu::loadMenu() {
	// Load the font
	font = TTF_OpenFont((PATH + "OpenSans-Regular.ttf").c_str(), 28);

	// Check if the font loaded
	if (font == NULL) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	// Load the background texture
	background = new Texture(renderer);
	if (!background->loadFromFile(PATH + "dark.png")) {
		std::cout << "Error loading background texture" << std::endl;
		return false;
	}
	background->setWidth(SCREEN_WIDTH);
	background->setHeight(SCREEN_HEIGHT);

	// Load the title texture
	title = new Texture(renderer);
	if (!title->loadFromText("The Game", font, { 255,255,255 })) {
		std::cout << "Error loading title texture" << std::endl;
		return false;
	}

	// Load the play texture
	play = new Texture(renderer);
	if (!play->loadFromText("Play", font, { 255,255,255 })) {
		std::cout << "Error loading play texture" << std::endl;
		return false;
	}

	// Load the settings texture
	settings = new Texture(renderer);
	if (!settings->loadFromText("Settings", font, { 255,255,255 })) {
		std::cout << "Error loading settings texture" << std::endl;
		return false;
	}

	// Load the quit texture
	quit = new Texture(renderer);
	if (!quit->loadFromText("Quit", font, { 255,255,255 })) {
		std::cout << "Error loading quit texture" << std::endl;
		return false;
	}

	return true;
}

void MainMenu::update() {
	// Render the main menu
	render();
}

void MainMenu::render() {

	// Render the background
	background->render(0, 0);

	// Render the title
	title->render((SCREEN_WIDTH - title->getWidth()) / 2, 50);

	// Render the play option
	if (currentOption == PLAY) {
		play->setColor(255, 0, 0);
	}
	else {
		play->setColor(255, 255, 255);
	}
	play->render((SCREEN_WIDTH - play->getWidth()) / 2, 200);

	// Render the settings option
	if (currentOption == SETTINGS) {
		settings->setColor(255, 0, 0);
	}
	else {
		settings->setColor(255, 255, 255);
	}
	settings->render((SCREEN_WIDTH - settings->getWidth()) / 2, 250);

	// Render the quit option
	if (currentOption == QUIT) {
		quit->setColor(255, 0, 0);
	}
	else {
		quit->setColor(255, 255, 255);
	}
	quit->render((SCREEN_WIDTH - quit->getWidth()) / 2, 300);

}

void MainMenu::handleInput(SDL_Event& e) {
	// If a key is pressed
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			// If the up arrow is pressed, move the current option up
			case SDLK_UP:
				currentOption = (currentOption + 2) % 3;
				break;

			// If the down arrow is pressed, move the current option down
			case SDLK_DOWN:
				currentOption = (currentOption + 1) % 3;
				break;

			// If the enter key is pressed, select the current option
			case SDLK_RETURN:
				selectOption();
				break;

		}
	}
}

void MainMenu::selectOption() {
	// If the current option is play, start the game
	switch (currentOption) {
	case PLAY:
		gameStarted = true;
		break;

		// If the current option is settings, open the settings menu
	case SETTINGS:
		// TODO
		break;

		// If the current option is quit, quit the game
	case QUIT:
		gameQuit = true;
		break;
	}
}

bool MainMenu::isGameStarted() {
	return gameStarted;
}

bool MainMenu::hasQuit() {
	return gameQuit;
}

void MainMenu::close() {
		// Free the textures
	delete background;
	background = NULL;

	delete title;
	title = NULL;

	delete play;
	play = NULL;

	delete settings;
	settings = NULL;

	delete quit;
	quit = NULL;

	// Close the font
	TTF_CloseFont(font);
	font = NULL;
}
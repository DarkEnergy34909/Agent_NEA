#include "MainMenu.h"

MainMenu::MainMenu(SDL_Window* window, SDL_Renderer* renderer) {
	// Set the window and renderer
	this->window = window;
	this->renderer = renderer;

	// Set textures to null initially
	background = NULL;
	title = NULL;
	play = NULL;
	instructions = NULL;
	settings = NULL;
	quit = NULL;
	back = NULL;
	instructionsText = NULL;

	// Set font to null initially
	font = NULL;

	// Set the current menu option to play
	currentOption = PLAY;

	// Set the current menu screen to main menu
	currentScreen = MAIN_MENU;

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
	if (!title->loadFromText("Agent", font, { 255,255,255 })) {
		std::cout << "Error loading title texture" << std::endl;
		return false;
	}

	// Load the play texture
	play = new Texture(renderer);
	if (!play->loadFromText("Play", font, { 255,255,255 })) {
		std::cout << "Error loading play texture" << std::endl;
		return false;
	}

	// Load the instructions texture
	instructions = new Texture(renderer);
	if (!instructions->loadFromText("Instructions", font, { 255,255,255 })) {
		std::cout << "Error loading instructions texture" << std::endl;
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

	// Load the back texture
	back = new Texture(renderer);
	if (!back->loadFromText("Back", font, { 255,255,255 })) {
		std::cout << "Error loading back texture" << std::endl;
		return false;
	}

	// Load the instructions texture
	instructionsText = new Texture(renderer);
	std::string instructionsString = "Instructions: \n\n"
		"Use the WASD keys to move the player\n"
		"Use the cursor to aim your weapon\n"
		"Press the left mouse button to shoot\n"
		"Collect cash to increase your score\n"
		"Avoid the enemies\n"
		"Unalerted enemies will have a white vision circle\n"
		"Alerted enemies will have a red vision circle\n";
	if (!instructionsText->loadFromText(instructionsString, font, { 255,255,255 })) {
		std::cout << "Error loading instructions texture" << std::endl;
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

	// If the current screen is the main menu, render the main menu
	if (currentScreen == MAIN_MENU) {
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

		// Render the instructions option
		if (currentOption == INSTRUCTIONS) {
			instructions->setColor(255, 0, 0);
		}
		else {
			instructions->setColor(255, 255, 255);
		}
		instructions->render((SCREEN_WIDTH - instructions->getWidth()) / 2, 250);

		// Render the settings option
		if (currentOption == SETTINGS) {
			settings->setColor(255, 0, 0);
		}
		else {
			settings->setColor(255, 255, 255);
		}
		settings->render((SCREEN_WIDTH - settings->getWidth()) / 2, 300);

		// Render the quit option
		if (currentOption == QUIT) {
			quit->setColor(255, 0, 0);
		}
		else {
			quit->setColor(255, 255, 255);
		}
		quit->render((SCREEN_WIDTH - quit->getWidth()) / 2, 350);
	}

	// If the current screen is the instructions menu, render the instructions menu
	else if (currentScreen == INSTRUCTIONS_MENU) {
		// Render instructions
		instructionsText->render(25, 25);

		// Render the back option
		back->setColor(255, 0, 0);
		back->render((SCREEN_WIDTH - back->getWidth()) / 2, 400);
	}

	// If the current screen is the settings menu, render the settings menu
	else if (currentScreen == SETTINGS_MENU) {
		// TODO
	}

}

void MainMenu::handleInput(SDL_Event& e) {
	// If a key is pressed
	if (e.type == SDL_KEYDOWN) {
		// If the user is on the main menu screen
		if (currentScreen == MAIN_MENU) {
			switch (e.key.keysym.sym) {
				// If the up arrow is pressed, move the current option up
				case SDLK_UP:
					currentOption = (currentOption + 3) % 4;
					break;

				// If the down arrow is pressed, move the current option down
				case SDLK_DOWN:
					currentOption = (currentOption + 1) % 4;
					break;

				// If the enter key is pressed, select the current option
				case SDLK_RETURN:
					selectOption();
					break;

			}
		}
		// If the user is on the instructions screen
		else if (currentScreen == INSTRUCTIONS_MENU) {
			// If the enter key is pressed, go back to the main menu
			if (e.key.keysym.sym == SDLK_RETURN) {
				currentScreen = MAIN_MENU;
			}
		}

		// If the user is on the settings screen
		else if (currentScreen == SETTINGS_MENU) {
			// TODO
		}
	}
}

void MainMenu::selectOption() {
	switch (currentOption) {
		// If the current option is play, start the game
		case PLAY:
			gameStarted = true;
			break;

		// If the current option is instructions, open the instructions menu
		case INSTRUCTIONS:
			// Set the current screen to the instructions menu
			currentScreen = INSTRUCTIONS_MENU;
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

	delete instructions;
	instructions = NULL;

	delete settings;
	settings = NULL;

	delete quit;
	quit = NULL;

	delete back;
	back = NULL;

	delete instructionsText;
	instructionsText = NULL;

	// Close the font
	TTF_CloseFont(font);
	font = NULL;
}
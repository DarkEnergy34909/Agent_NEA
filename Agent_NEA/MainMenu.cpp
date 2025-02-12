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
	settingsText = NULL;
	volumeSetting = NULL;
	fpsSetting = NULL;
	gameOver = NULL;

	// Set font to null initially
	font = NULL;

	// Set the current menu option to play
	currentOption = PLAY;

	// Set the current menu screen to main menu
	currentScreen = MAIN_MENU;

	// Set the current settings option to volume
	currentSettingsOption = VOLUME;
	
	// Set game started to false
	gameStarted = false;

	// Set game quit to false
	gameQuit = false;

	// Set the volume to 50
	volume = 50;

	// Set the FPS to 60
	fps = 60;

	// Set the score to 0
	score = 0;
	
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
	std::string instructionsString = "Instructions:\n\n"
		"Use the WASD keys to move the player\n"
		"Use the cursor to aim your weapon\n"
		"Press the left mouse button to shoot\n"
		"Collect cash to increase your score\n"
		"Avoid or silently kill enemies\n"
		"Unalerted enemies will have a white vision circle\n"
		"Alerted enemies will have a red vision circle\n"
		"If you alert 2 or more enemies, an alarm sounds\n"
		"and all enemies will be alerted\n";
	if (!instructionsText->loadFromText(instructionsString, font, { 255,255,255 })) {
		std::cout << "Error loading instructions texture" << std::endl;
		return false;
	}

	// Load the settings text texture
	settingsText = new Texture(renderer);
	if (!settingsText->loadFromText("Settings:", font, { 255,255,255 })) {
		std::cout << "Error loading settings text texture" << std::endl;
		return false;
	}

	// Load the volume setting texture
	volumeSetting = new Texture(renderer);
	if (!volumeSetting->loadFromText("Volume: " + std::to_string(volume), font, { 255,255,255 })) {
		std::cout << "Error loading volume setting texture" << std::endl;
		return false;
	}

	// Load the FPS setting texture
	fpsSetting = new Texture(renderer);
	if (!fpsSetting->loadFromText("FPS: " + std::to_string(fps), font, { 255,255,255 })) {
		std::cout << "Error loading FPS setting texture" << std::endl;
		return false;
	}

	// Load the game over texture
	gameOver = new Texture(renderer);
	if (!gameOver->loadFromText("Game Over!\n\nScore: " + std::to_string(score), font, {255,255,255})) {
		std::cout << "Error loading game over texture" << std::endl;
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
		instructionsText->render(10, 10);

		// Render the back option
		back->setColor(255, 0, 0);
		back->render((SCREEN_WIDTH - back->getWidth()) / 2, 435);
	}

	// If the current screen is the settings menu, render the settings menudddd
	else if (currentScreen == SETTINGS_MENU) {
		// Render the settings title
		settingsText->render((SCREEN_WIDTH - settings->getWidth()) / 2, 50);

		// Render the volume setting
		if (currentSettingsOption == VOLUME) {
			volumeSetting->setColor(255, 0, 0);
		}
		else {
			volumeSetting->setColor(255, 255, 255);
		}
		volumeSetting->render((SCREEN_WIDTH - volumeSetting->getWidth()) / 2, 200);

		// Render the FPS setting
		if (currentSettingsOption == FPS) {
			fpsSetting->setColor(255, 0, 0);
		}
		else {
			fpsSetting->setColor(255, 255, 255);
		}
		fpsSetting->render((SCREEN_WIDTH - fpsSetting->getWidth()) / 2, 250);

		// Render the back option
		if (currentSettingsOption == BACK) {
			back->setColor(255, 0, 0);
		}
		else {
			back->setColor(255, 255, 255);
		}
		back->render((SCREEN_WIDTH - back->getWidth()) / 2, 300);
	}

	// If the game is over, render the game over screen
	else if (currentScreen == GAME_OVER_MENU) {
		gameOver->render((SCREEN_WIDTH - gameOver->getWidth()) / 2, (SCREEN_HEIGHT - gameOver->getHeight()) / 2);

		// Render the back option
		back->setColor(255, 0, 0);
		back->render((SCREEN_WIDTH - back->getWidth()) / 2, 400);
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
			switch (e.key.keysym.sym) {
				// If the up arrow is pressed, move the current option up
				case SDLK_UP:
					currentSettingsOption = (currentSettingsOption + 2) % 3;
					break;

				// If the down arrow is pressed, move the current option down
				case SDLK_DOWN:
					currentSettingsOption = (currentSettingsOption + 1) % 3;
					break;

				// If the left arrow is pressed, decrease the current setting
				case SDLK_LEFT:
					// If the current setting is volume, decrease the volume
					if (currentSettingsOption == VOLUME) {
						volume -= 1;
						if (volume < 0) {
							volume = 0;
						}

						// Update the volume setting texture
						volumeSetting->loadFromText("Volume: " + std::to_string(volume), font, { 255,255,255 });
					}

					// If the current setting is FPS, decrease the FPS
					else if (currentSettingsOption == FPS) {
						fps -= 1;
						if (fps < 20) {
							fps = 20;
						}

						// Update the FPS setting texture
						fpsSetting->loadFromText("FPS: " + std::to_string(fps), font, { 255,255,255 });
					}
					break;

				// If the right arrow is pressed, increase the current setting
				case SDLK_RIGHT:
					// If the current setting is volume, increase the volume
					if (currentSettingsOption == VOLUME) {
						volume += 1;
						if (volume > 100) {
							volume = 100;
						}

						// Update the volume setting texture
						volumeSetting->loadFromText("Volume: " + std::to_string(volume), font, { 255,255,255 });
					}

					// If the current setting is FPS, increase the FPS
					else if (currentSettingsOption == FPS) {
						fps += 1;
						if (fps > 60) {
							fps = 60;
						}

						// Update the FPS setting texture
						fpsSetting->loadFromText("FPS: " + std::to_string(fps), font, { 255,255,255 });
					}
					break;

				case SDLK_RETURN:
					// If the current option is back, go back to the main menu
					if (currentSettingsOption == BACK) {
						currentScreen = MAIN_MENU;
					}
					break;
			}
		}
		else if (currentScreen == GAME_OVER_MENU) {
			// If the enter key is pressed, go back to the main menu
			if (e.key.keysym.sym == SDLK_RETURN) {
				currentScreen = MAIN_MENU;
			}
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
			// Set the current screen to the settings menu
			currentScreen = SETTINGS_MENU;
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

int MainMenu::getVolume() {
	return volume;
}

int MainMenu::getFPS() {
	return fps;
}

void MainMenu::setScreen(int screen) {
	currentScreen = screen;
}

void MainMenu::setGameStarted(bool gameStarted) {
	this->gameStarted = gameStarted;
}

void MainMenu::setScore(int score) {
	this->score = score;

	// Update the game over texture
	gameOver->loadFromText("Game Over!\n\nScore: " + std::to_string(score), font, { 255,255,255 });
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

	delete settingsText;
	settingsText = NULL;

	delete volumeSetting;
	volumeSetting = NULL;

	delete fpsSetting;
	fpsSetting = NULL;	

	delete gameOver;
	gameOver = NULL;

	// Close the font
	TTF_CloseFont(font);
	font = NULL;
}
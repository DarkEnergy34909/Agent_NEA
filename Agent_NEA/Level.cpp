#include "Level.h"

enum TileTypes {
	TILE_RED,
	TILE_GREEN,
	TILE_BLUE,
	TILE_CENTRE,
	TILE_TOP,
	TILE_TOP_RIGHT,
	TILE_RIGHT,
	TILE_BOTTOM_RIGHT,
	TILE_BOTTOM,
	TILE_BOTTOM_LEFT,
	TILE_LEFT,
	TILE_TOP_LEFT
};

Level::Level(SDL_Window* window, SDL_Renderer* renderer) {
	// Set window
	this->window = window;

	// Set renderer
	this->renderer = renderer;

	// Set text textures to null initially
	scoreTexture = NULL;
	healthTexture = NULL;

	// Set font to null initially
	font = NULL;

	// Initialise containers
	gameObjects = std::vector<GameObject*>();
	entities = std::vector<Entity*>();
	characters = std::vector<Character*>();

	// Set player to null initially
	player = NULL;

	// Set item to null initially
	item = NULL;

	// Initialise tiles to null initially
	for (int i = 0; i < TOTAL_TILES; i++) {
		tiles[i] = NULL;
	}

	// Initialise levelGrid to 0s
	for (int i = 0; i < VERTICAL_TILES; i++) {
		for (int j = 0; j < HORIZONTAL_TILES; j++) {
			levelGrid[i][j] = 0;
		}
	}

	// Initialise clips to default values
	for (int i = 0; i < TOTAL_TILE_TYPES; i++) {
		SDL_Rect defaultRect = { 0, 0, TILE_WIDTH, TILE_HEIGHT };
		
		tileClips[i] = defaultRect;
	}

	// Level is not paused initially
	paused = false;

	// Level is running initially
	running = true;

	// Alarm is not triggered initially
	alarmTriggered = false;

	// Set level timer to 0
	levelTimer = 0;

	// Set frame counter to 0
	frameCounter = 0;

	// Set score to 0
	score = 0;

	// Set shoot sound to null initially
	shootSound = NULL;

	// Set cash sound to null initially
	cashSound = NULL;

	// Set alarm sound to null initially
	alarmSound = NULL;


}

Level::~Level() {
	// Close the level
	close();
}

bool Level::init() {
	// TODO
	return false;
}

void Level::close() {
	// Delete all game objects
	for (auto& gameObject : gameObjects) {
		delete gameObject;
		gameObject = NULL;
	}

	// All entities/characters/player have already been deleted in the gameObjects vector
	// So no need to delete them again

	// Delete all tiles
	for (auto& tile : tiles) {
		delete tile;
		tile = NULL;
	}

	// Delete all textures
	for (auto& texture : textures) {
		delete texture;
		texture = NULL;
	}

	// Clear all vector containers
	gameObjects.clear();
	entities.clear();
	characters.clear();
	textures.clear();

	// Stop all audio from playing
	Mix_HaltChannel(-1);

	// Delete sounds
	Mix_FreeChunk(shootSound);
	shootSound = NULL;

	Mix_FreeChunk(cashSound);
	cashSound = NULL;

	Mix_FreeChunk(alarmSound);
	alarmSound = NULL;


}

bool Level::loadObjects() {
	// Load default player texture
	Texture* playerDefaultTexture = new Texture(renderer);
	if (!playerDefaultTexture->loadFromFile(PATH + "player_test_1.png")) {
		std::cout << "Error loading player texture" << std::endl;
		return false;
	}

	// Load player animation texture 1
	Texture* playerWalkTexture1 = new Texture(renderer);
	if (!playerWalkTexture1->loadFromFile(PATH + "player_test_2.png")) {
		std::cout << "Error loading player texture" << std::endl;
		return false;
	}

	// Load player animation texture 2
	Texture* playerWalkTexture2 = new Texture(renderer);
	if (!playerWalkTexture2->loadFromFile(PATH + "player_test_3.png")) {
		std::cout << "Error loading player texture" << std::endl;
		return false;
	}

	// Load pistol texture
	Texture* pistolTexture = new Texture(renderer);
	if (!pistolTexture->loadFromFile(PATH + "pistol.png")) {
		std::cout << "Error loading pistol texture" << std::endl;
		return false;
	}
	pistolTexture->setWidth(28);
	pistolTexture->setHeight(19);

	// Load bullet texture
	Texture* bulletTexture = new Texture(renderer);
	if (!bulletTexture->loadFromFile(PATH + "bullet.png")) {
		std::cout << "Error loading bullet texture" << std::endl;
		return false;
	}

	// Load item texture
	Texture* itemTexture = new Texture(renderer);
	if (!itemTexture->loadFromFile(PATH + "cash.png")) {
		std::cout << "Error loading item texture" << std::endl;
		return false;
	}

	// Load vision textures
	Texture* visionTexture1 = new Texture(renderer);
	if (!visionTexture1->loadFromFile(PATH + "vision_circle.png")) {
		std::cout << "Error loading vision texture" << std::endl;
		return false;
	}
	// Vision radius must be transparent
	visionTexture1->setAlpha(96);

	Texture* visionTexture2 = new Texture(renderer);
	if (!visionTexture2->loadFromFile(PATH + "vision_circle.png")) {
		std::cout << "Error loading vision texture" << std::endl;
		return false;
	}
	// Vision radius must be transparent
	visionTexture2->setAlpha(96);

	Texture* visionTexture3 = new Texture(renderer);
	if (!visionTexture3->loadFromFile(PATH + "vision_circle.png")) {
		std::cout << "Error loading vision texture" << std::endl;
		return false;
	}
	// Vision radius must be transparent
	visionTexture3->setAlpha(96);

	// Add textures to textures vector
	textures.push_back(playerDefaultTexture);
	textures.push_back(playerWalkTexture1);
	textures.push_back(playerWalkTexture2);
	textures.push_back(pistolTexture);
	textures.push_back(bulletTexture);
	textures.push_back(visionTexture1);
	textures.push_back(visionTexture2);
	textures.push_back(visionTexture3);
	textures.push_back(itemTexture);


	// Load the item
	GameObject* cash = new GameObject(itemTexture, 600, 440, 25, 15);
	if (cash == NULL) {
		std::cout << "Error loading item" << std::endl;
		return false;
	}

	// Set the item
	this->item = cash;

	// Add item to containers
	gameObjects.push_back(cash);

	// Load test enemy
	Enemy* enemy1 = new Enemy(playerDefaultTexture, 500, 500, 40, 70, BASIC);
	if (enemy1 == NULL) {
		std::cout << "Error loading enemy" << std::endl;
		return false;
	}

	// Add animations
	enemy1->addAnimationTexture(playerDefaultTexture);
	enemy1->addAnimationTexture(playerWalkTexture1);
	enemy1->addAnimationTexture(playerDefaultTexture);
	enemy1->addAnimationTexture(playerWalkTexture2);

	// Set the enemy's weapon
	enemy1->setWeapon(new Weapon(PISTOL, pistolTexture, bulletTexture));

	// Add the enemy's vision texture
	enemy1->setVisionTexture(visionTexture1);

	//this->enemy = enemy;

	// Add enemy to containers
	gameObjects.push_back(enemy1);
	entities.push_back(enemy1);
	characters.push_back(enemy1);
	enemies.push_back(enemy1);

	// Load another test enemy
	Enemy* enemy2 = new Enemy(playerDefaultTexture, 400, 0, 40, 70, BASIC);
	if (enemy2 == NULL) {
		std::cout << "Error loading enemy" << std::endl;
		return false;
	}

	// Add animations
	enemy2->addAnimationTexture(playerDefaultTexture);
	enemy2->addAnimationTexture(playerWalkTexture1);
	enemy2->addAnimationTexture(playerDefaultTexture);
	enemy2->addAnimationTexture(playerWalkTexture2);

	// Set the enemy's weapon
	enemy2->setWeapon(new Weapon(PISTOL, pistolTexture, bulletTexture));

	// Add the enemy's vision texture
	enemy2->setVisionTexture(visionTexture2);

	// Add enemy to containers
	gameObjects.push_back(enemy2);
	entities.push_back(enemy2);
	characters.push_back(enemy2);
	enemies.push_back(enemy2);

	// Load another test enemy
	Enemy* enemy3 = new Enemy(playerDefaultTexture, 0, 400, 40, 70, BASIC);
	if (enemy3 == NULL) {
		std::cout << "Error loading enemy" << std::endl;
		return false;
	}

	// Add animations
	enemy3->addAnimationTexture(playerDefaultTexture);
	enemy3->addAnimationTexture(playerWalkTexture1);
	enemy3->addAnimationTexture(playerDefaultTexture);
	enemy3->addAnimationTexture(playerWalkTexture2);

	// Set the enemy's weapon
	enemy3->setWeapon(new Weapon(PISTOL, pistolTexture, bulletTexture));

	// Add the enemy's vision texture
	enemy3->setVisionTexture(visionTexture3);

	// Add enemy to containers
	gameObjects.push_back(enemy3);
	entities.push_back(enemy3);
	characters.push_back(enemy3);
	enemies.push_back(enemy3);

	// Load the player
	//Player* player = new Player(playerDefaultTexture, 0, 0, 50, 87);
	Player* player = new Player(playerDefaultTexture, 0, 0, 40, 70);
	if (player == NULL) {
		std::cout << "Error loading player" << std::endl;
		return false;
	}

	// Add animations
	player->addAnimationTexture(playerDefaultTexture);
	player->addAnimationTexture(playerWalkTexture1);
	player->addAnimationTexture(playerDefaultTexture);
	player->addAnimationTexture(playerWalkTexture2);

	// Set the player's weapon
	player->setWeapon(new Weapon(PISTOL, pistolTexture, bulletTexture));

	// Set player
	this->player = player;

	// Add player to containers
	gameObjects.push_back(player);
	entities.push_back(player);
	characters.push_back(player);

	// Load the shot sound effect
	shootSound = Mix_LoadWAV((PATH + "shot3.wav").c_str());
	if (shootSound == NULL) {
		std::cout << "Error loading shoot sound" << std::endl;
		return false;
	}

	// Load the cash sound effect
	cashSound = Mix_LoadWAV((PATH + "cash.wav").c_str());
	if (cashSound == NULL) {
		std::cout << "Error loading cash sound" << std::endl;
		return false;
	}

	// Load the alarm sound effect
	alarmSound = Mix_LoadWAV((PATH + "alarm.wav").c_str());
	if (alarmSound == NULL) {
		std::cout << "Error loading alarm sound" << std::endl;
		return false;
	}


	return true;
}

bool Level::loadText() {
	// Load the font
	font = TTF_OpenFont((PATH + "OpenSans-Regular.ttf").c_str(), 28);

	// If the font is null, print an error message and return false
	if (font == NULL) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	// Load the score texture
	scoreTexture = new Texture(renderer);
	if (!scoreTexture->loadFromText("Score: 0", font, { 255, 0, 0 })) {
		std::cout << "Error loading score texture" << std::endl;
		return false;
	}

	// Load the health texture
	healthTexture = new Texture(renderer);
	if (!healthTexture->loadFromText("Health: 100", font, { 255, 0, 0 })) {
		std::cout << "Error loading health texture" << std::endl;
		return false;
	}
	
	// Add textures to textures vector
	textures.push_back(scoreTexture);
	textures.push_back(healthTexture);

	return true;

}

bool Level::loadLevel() {
	// The level will eventually be loaded from a file, but for now it is hardcoded
	int storedLevel[6][8] = {
		{TILE_RED, TILE_GREEN, TILE_BLUE, TILE_RED, TILE_GREEN, TILE_BLUE, TILE_RED, TILE_GREEN},
		{TILE_GREEN, TILE_TOP_LEFT, TILE_TOP_RIGHT, TILE_GREEN, TILE_BLUE, TILE_RED, TILE_GREEN, TILE_BLUE},
		{TILE_BLUE, TILE_BOTTOM_LEFT, TILE_BOTTOM_RIGHT, TILE_BLUE, TILE_RED, TILE_GREEN, TILE_BLUE, TILE_RED},
		{TILE_RED, TILE_GREEN, TILE_BLUE, TILE_RED, TILE_GREEN, TILE_TOP_LEFT, TILE_TOP_RIGHT, TILE_GREEN},
		{TILE_GREEN, TILE_BLUE, TILE_RED, TILE_GREEN, TILE_BLUE, TILE_BOTTOM_LEFT, TILE_BOTTOM_RIGHT, TILE_BLUE},
		{TILE_BLUE, TILE_RED, TILE_GREEN, TILE_BLUE, TILE_RED, TILE_GREEN, TILE_BLUE, TILE_RED}
	};

	// Initialise the tileset texture
	Texture* tileset = new Texture(renderer);
	if (!tileset->loadFromFile(PATH + "tileset.png")) {
		std::cout << "Error loading tileset" << std::endl;
		return false;
	}

	// The position of each tile
	int posX = 0;
	int posY = 0;

	// Counters for iteration over the 2D array
	int horizontalCounter = 0;
	int verticalCounter = 0;

	// Initialise each tile - iterate over tiles array to do this
	for (int i = 0; i < TOTAL_TILES; i++) {

		// Get tile type from the stored level
		int tileType = storedLevel[verticalCounter][horizontalCounter];

		// Initialise a new tile
		Tile* tile = new Tile(tileType, posX, posY);
		if (tile == NULL) {
			std::cout << "Error loading tile" << std::endl;
			return false;
		}

		// Set the texture of the tile
		tile->setTexture(tileset);

		// Update levelGrid
		// If the tile is not a wall (a coloured tile), set the corresponding element in levelGrid to 0
		if (tileType == TILE_RED || tileType == TILE_GREEN || tileType == TILE_BLUE) {
			levelGrid[verticalCounter][horizontalCounter] = 0;

			// Set wall to false
			tile->setWall(false);
		}
		// If it is a wall (a black tile), set the corresponding element in levelGrid to 1
		else {
			levelGrid[verticalCounter][horizontalCounter] = 1;

			// Set wall to true
			tile->setWall(true);
		}

		// Add this tile to the tiles array
		tiles[i] = tile;

		// Increment x counter
		posX += TILE_WIDTH;
		// If the x counter is at the end of the row, reset it and increment the y counter
		if (posX >= LEVEL_WIDTH) {
			posX = 0;
			posY += TILE_HEIGHT;
		}

		// Increment horizontal counter
		horizontalCounter++;
		// If the horizontal counter is at the end of the row, reset it and increment the vertical counter
		if (horizontalCounter >= HORIZONTAL_TILES) {
			horizontalCounter = 0;
			verticalCounter++;
		}
	}

	// Set the clips for each tile type

	tileClips[TILE_RED].x = 0;
	tileClips[TILE_RED].y = 0;

	tileClips[TILE_GREEN].x = 0;
	tileClips[TILE_GREEN].y = 80;

	tileClips[TILE_BLUE].x = 0;
	tileClips[TILE_BLUE].y = 160;

	tileClips[TILE_TOP_LEFT].x = 80;
	tileClips[TILE_TOP_LEFT].y = 0;

	tileClips[TILE_LEFT].x = 80;
	tileClips[TILE_LEFT].y = 80;

	tileClips[TILE_BOTTOM_LEFT].x = 80;
	tileClips[TILE_BOTTOM_LEFT].y = 160;

	tileClips[TILE_TOP].x = 160;
	tileClips[TILE_TOP].y = 0;

	tileClips[TILE_CENTRE].x = 160;
	tileClips[TILE_CENTRE].y = 80;

	tileClips[TILE_BOTTOM].x = 160;
	tileClips[TILE_BOTTOM].y = 160;

	tileClips[TILE_TOP_RIGHT].x = 240;
	tileClips[TILE_TOP_RIGHT].y = 0;

	tileClips[TILE_RIGHT].x = 240;
	tileClips[TILE_RIGHT].y = 80;

	tileClips[TILE_BOTTOM_RIGHT].x = 240;
	tileClips[TILE_BOTTOM_RIGHT].y = 160;

	return true;
}

void Level::render() {
	if (renderer == NULL) {
		std::cout << "Error rendering: " << SDL_GetError() << std::endl;
		return;
	}

	// Render the level itself (excluding walls)
	for (auto& tile : tiles) {
		if (!tile->isWall()) {
			tile->render(&tileClips[tile->getTileType()]);
		}
	}

	// Render vision circles under game objects
	for (auto& enemy : enemies) {
		if (enemy != NULL) {
			enemy->renderVision();
		}
	}

	// Render GameObjects
	for (auto& gameObject : gameObjects) {
		gameObject->render();
	}

	// Render the level walls on top of the level
	for (auto& tile : tiles) {
		if (tile->isWall()) {
			tile->render(&tileClips[tile->getTileType()]);
		}
	}

	// Render score
	scoreTexture->loadFromText("Score: " + std::to_string(score), font, { 255, 0, 0 });
	scoreTexture->render(SCREEN_WIDTH - scoreTexture->getWidth() - 10, 10);

	// Render health
	healthTexture->loadFromText("Health: " + std::to_string(player->getHp()), font, { 255, 0, 0 });
	healthTexture->render(10, 10);
}

void Level::update() {
	if (!paused) {
		// Update test enemy
		updateEnemies();

		// Update characters
		updateCharacters();

		//std::cout << "Player health: " << player->getHp() << "/100" << std::endl;

		// Move all entities
		moveEntities();

		// Render the level
		render();

		// Update the level timer
		levelTimer = SDL_GetTicks();

		// Update the frame counter
		frameCounter++;

		if (frameCounter % 100 == 0) {
			// Increase score by 10
			updateScore(1);
		}
	}
}

void Level::updateScore(int scoreDifference) {
	// Update the score
	score += scoreDifference;

	// If the score is less than 0, set it to 0
	if (score < 0) {
		score = 0;
	}

	// Print the score
	std::cout << "Score: " << score << std::endl;

}

int Level::getScore() {
	return score;
}

void Level::updateEnemies() {
	// Update each enemy in the game
	if (enemies.empty()) {
		return;
	}

	// Flag to check how many enemies are alerted
	int alertedEnemies = 0;

	for (auto& enemy : enemies) {

		if (enemy != NULL) {
			// Get the player's centre position
			int targetPosX = player->getPosX() + player->getWidth() / 2;
			int targetPosY = player->getPosY() + player->getHeight() / 2;

			// If the player is within the enemy's vision radius, set the enemy to alerted
			if (enemy->canSee(player->getCollider())) {
				enemy->setAwareness(ALERTED);

				// Decrease the player's score by 2 every 100 frames
				if (frameCounter % 100 == 0) {
					std::cout << "Player spotted by enemy" << std::endl;

					updateScore(-5);
				}
			}

			// If the enemy is passive, move to a random waypoint
			if (enemy->getAwareness() == PASSIVE) {
				// Set the enemy's initial waypoint if it is not set
				if (enemy->getCurrentWaypoint() == std::make_pair(-1, -1)) {
					enemy->setWaypoint(getWaypoint());
				}

				// Set a new waypoint every 300ms (or so)
				else if (levelTimer % 300 == 0) {
					enemy->setWaypoint(getWaypoint());
				}

				// Move the enemy to the current waypoint
				enemy->moveToCurrentWaypoint(levelGrid);
			}

			// If the enemy is alerted, move towards the player and shoot at them
			else if (enemy->getAwareness() == ALERTED) {
				// Increment the number of alerted enemies
				alertedEnemies++;

				// If enemy is further than 75 pixels from the player, calculate a path and move towards the player
				if (calculateDistance(targetPosX, targetPosY, enemy->getPosX() + enemy->getWidth() / 2, enemy->getPosY() + enemy->getHeight() / 2) > 75.0) {
					std::pair<int, int> nextPos = enemy->calculatePath(targetPosX, targetPosY, levelGrid);
					enemy->moveTo(nextPos.first, nextPos.second);
				}
				// Stop moving if the enemy is within 75 pixels of the player
				else {
					enemy->setVelX(0);
					enemy->setVelY(0);
				}

				// Iterate over all other enemies
				for (auto& otherEnemy : enemies) {
					if (otherEnemy != NULL) {

						// If the enemy is not the same as the current enemy and the enemy is within the vision radius of the current enemy, alert the enemy
						if (otherEnemy != enemy && enemy->canSee(otherEnemy->getCollider()) && otherEnemy->getAwareness() != ALERTED) {
							otherEnemy->setAwareness(ALERTED);

							std::cout << "Enemy alerted by another enemy" << std::endl;

							// If an enemy alerts another enemy, reduce the player's score by 10
							updateScore(-10);
						}
					}
				}

				// Shoot at the player every 100ms
				if (levelTimer % 75 == 0) {
					Bullet* bullet = enemy->shoot(targetPosX, targetPosY);

					// Play the shoot sound effect
					Mix_PlayChannel(-1, shootSound, 0);

					// Add the bullet to the game containers
					if (bullet != NULL) {
						gameObjects.push_back(bullet);
						entities.push_back(bullet);
						bullets.push_back(bullet);
					}
				}
			}
			else {
				std::cout << "Invalid awareness level" << std::endl;
			}
		}
	}

	// Every 2000 frames, if all enemies are passive, increase score by 30
	if (frameCounter % 2000 == 0 && alertedEnemies == 0) {
		std::cout << "Stealth bonus: " << std::endl;

		updateScore(30);
	}

	// If at least 3 enemies are alerted, set all enemies to alerted and play an alarm sound effect
	if (alertedEnemies >= 3 && !alarmTriggered) {
		// Trigger the alarm
		alarmTriggered = true;

		for (auto& enemy : enemies) {
			if (enemy != NULL) {
				enemy->setAwareness(ALERTED);
			}
		}

		// Play the alarm sound effect
		Mix_PlayChannel(0, alarmSound, -1);


		// Reduce the player's score by 100
		updateScore(-100);
	
	}

	// Every 1000 frames, add a new enemy
	if (frameCounter % 1000 == 0) {
		spawnEnemy();
	}
	
}

void Level::handleInput(SDL_Event& e) {
	// Handle keypresses
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP || e.type == SDL_MOUSEMOTION) {
		player->handleInput(e);
	}
	// Handle mouse clicks
	else if (e.type == SDL_MOUSEBUTTONDOWN) {
		// If the left mouse button is clicked, the player shoots their gun
		if (e.button.button == SDL_BUTTON_LEFT) {
			// Get the bullet fired by the player
			Bullet* bullet = player->shoot();

			// Play the shoot sound effect
			Mix_PlayChannel(-1, shootSound, 0);

			// If the bullet is not null, add it to game containers
			if (bullet != NULL) {
				gameObjects.push_back(bullet);
				entities.push_back(bullet);
				bullets.push_back(bullet);
			}
		}
	}

	// TODO: handle other inputs
}

void Level::moveEntities() {

	// Iterate over all entities
	for (auto& entity: entities) {
		//for (auto& e : entities) {
			//std::cout << e << ", ";
		//}
		//std::cout << std::endl;
		// Get the entity
		//Entity* entity = *entityIterator;

		bool isDeleted = false;

		// Move in the x direction
		entity->moveX();

		// Collision detection
		for (auto& tile : tiles) {
			if (isColliding(entity->getCollider(), tile->getTileCollider()) && tile->isWall()) {

				// Resolve collisions

				// If the entity is a bullet, remove it from the game
				if (entity->getObjectType() == BULLET) {
					// Mark the bullet to be deleted
					isDeleted = true;
				}
				
				// If the entity is moving right (hits the left side of a wall) set its x position so that its right side is touching the left side of the wall
				else if (entity->getVelX() > 0) {
					entity->setPosX(tile->getPosX() - entity->getWidth());
				}
				
				// If the entity is moving left (hits the right side of a wall) set its x position so that its left side is touching the right side of the wall
				else if (entity->getVelX() < 0) {
					entity->setPosX(tile->getPosX() + tile->getWidth());
				}
				
			}
		}

		if (!isDeleted) {
			if (entity->getPosX() < 0) {
				if (entity->getObjectType() == BULLET) {
					isDeleted = true;
				}
				else {
					entity->setPosX(0);
				}
			}
			else if (entity->getPosX() + entity->getWidth() > LEVEL_WIDTH) {
				if (entity->getObjectType() == BULLET) {
					isDeleted = true;
				}
				else {
					entity->setPosX(LEVEL_WIDTH - entity->getWidth());
				}
			}
		}

		// If the entity has not been deleted, move in the y direction
		if (!isDeleted) {
			// Move in the y direction
			entity->moveY();

			// Collision detection in the y direction
			for (auto& tile : tiles) {
				if (isColliding(entity->getCollider(), tile->getTileCollider()) && tile->isWall()) {

					// Resolve collisions

					// If the entity is a bullet, remove it from the game
					if (entity->getObjectType() == BULLET) {
						// Mark the bullet to be deleted
						isDeleted = true;

					}

					// If the entity is moving down (hits the top side of a wall) set its y position so that its bottom side is touching the top side of the wall
					else if (entity->getVelY() > 0) {
						entity->setPosY(tile->getPosY() - entity->getHeight());
					}

					// If the entity is moving up (hits the bottom side of a wall) set its y position so that its top side is touching the bottom side of the wall
					else if (entity->getVelY() < 0) {
						entity->setPosY(tile->getPosY() + tile->getHeight());
					}
				}
			}
		}

		if (!isDeleted) {
			if (entity->getPosY() < 0) {
				if (entity->getObjectType() == BULLET) {
					isDeleted = true;
				}
				else {
					entity->setPosY(0);
				}
			}
			else if (entity->getPosY() + entity->getHeight() > LEVEL_HEIGHT) {
				if (entity->getObjectType() == BULLET) {
					isDeleted = true;
				}
				else {
					entity->setPosY(LEVEL_HEIGHT - entity->getHeight());
				}
			}
		}

		// If entity has been deleted, delete it
		if (isDeleted) {
			// Set entity to null in gameObjects vector
			for (auto& gameObject : gameObjects) {
				if (gameObject == entity) {
					gameObject = NULL;
				}
			}

			// Delete the entity
			delete entity;

			// Set entity to null in entities vector
			entity = NULL;
		}
	}


	// Check if the player has collected the item
	if (item != NULL && isColliding(player->getCollider(), item->getCollider())) {
		std::cout << "Item collected" << std::endl;

		// Increase score by 100
		score += 100;

		// Play the cash pickup sound effect
		Mix_PlayChannel(-1, cashSound, 0);

		// Spawn the item elsewhere
		spawnObject(item);

		
	}

	// Remove all deleted entities from game containers
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), nullptr), gameObjects.end());
	entities.erase(std::remove(entities.begin(), entities.end(), nullptr), entities.end());
}

void Level::updateCharacters() {
	// Iterate through characters 
	for (auto& character : characters) {

		// Iterate through bullets to check for collisions
		for (auto& bullet : bullets) {

			// Check if the bullet is colliding with the character
			if (bullet != NULL && isColliding(bullet->getCollider(), character->getCollider())) {

				// If the bullet is colliding with the character, deal damage to the character
				character->takeDamage(bullet->getDamage());

				// If the character is an enemy, set its awareness to alerted
				for (auto& enemy: enemies) {
					if (enemy == character) {
						enemy->setAwareness(ALERTED);

						std::cout << "Enemy alerted" << std::endl;

						// Reduce the player's score by 5 when the player alerts an enemy by shooting it
						updateScore(-5);
					}
				}

				// Remove the bullet from the game
				// Set bullet to null in gameObjects vector
				for (auto& gameObject : gameObjects) {
					if (gameObject == bullet) {
						gameObject = NULL;
					}
				}

				// Set bullet to null in entities vector
				for (auto& entity : entities) {
					if (entity == bullet) {
						entity = NULL;
					}
				}

				// Delete the bullet
				delete bullet;

				// Set bullet to null in bullets vector
				bullet = NULL;

			}
		}


		// If the character is dead, remove it from the game
		if (!character->isAlive()) {
			// Set character to null in gameObjects vector
			for (auto& gameObject : gameObjects) {
				if (gameObject == character) {
					gameObject = NULL;
				}
			}

			// Set character to null in entities vector
			for (auto& entity : entities) {
				if (entity == character) {
					entity = NULL;
				}
			}

			// If the character is an enemy, set enemy to null
			for (auto& enemy: enemies) {
				if (enemy == character) {
					enemy = NULL;

					std::cout << "Enemy killed" << std::endl;

					// Increase the player's score by 20 when they kill an enemy
					updateScore(20);
				}
			}

			if (character == player) {
				// If the player is dead, end the game
				running = false;
			}

			// Delete the character
			delete character;

			// Set character to null in characters vector
			character = NULL;
		}
	}

	// Remove all deleted characters and bullets from game containers
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), nullptr), gameObjects.end());
	entities.erase(std::remove(entities.begin(), entities.end(), nullptr), entities.end());
	characters.erase(std::remove(characters.begin(), characters.end(), nullptr), characters.end());
	bullets.erase(std::remove(bullets.begin(), bullets.end(), nullptr), bullets.end());

}

bool Level::isColliding(SDL_Rect a, SDL_Rect b) {
	// Rectangles not colliding if the left edge of a is to the right of the right edge of b
	if (a.x >= b.x + b.w) {
		return false;
	}

	// Rectangles not colliding if the right edge of a is to the left of the left edge of b
	if (a.x + a.w <= b.x) {
		return false;
	}

	// Rectangles not colliding if the top edge of a is below the bottom edge of b
	if (a.y >= b.y + b.h) {
		return false;
	}

	// Rectangles not colliding if the bottom edge of a is above the top edge of b
	if (a.y + a.h <= b.y) {
		return false;
	}

	// If none of these are true, the rectangles are colliding
	return true; 
}

double Level::calculateDistance(int x1, int y1, int x2, int y2) {
	// Calculate the distance between two points using Pythagoras
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

std::pair<int, int> Level::getWaypoint() {
	// Get a random waypoint for the enemy to move to
	int x = rand() % LEVEL_WIDTH;
	int y = rand() % LEVEL_HEIGHT;

	// If the waypoint is within a wall, get a new waypoint
	while (levelGrid[y / TILE_HEIGHT][x / TILE_WIDTH] == 1) {
		x = rand() % LEVEL_WIDTH;
		y = rand() % LEVEL_HEIGHT;
	}

	return { x, y };
}

void Level::spawnObject(GameObject* object) {
	std::pair<int, int> randomPos = getWaypoint();

	object->setPosX(randomPos.first);
	object->setPosY(randomPos.second);

	for (auto& tile : tiles) {
		if (isColliding(object->getCollider(), tile->getTileCollider()) && tile->isWall()) {
			spawnObject(object);
		}
	}

}

void Level::spawnEnemy() {
	// Create a new enemy
	Enemy* enemy = new Enemy(textures[0], 0, 0, 40, 70, BASIC);
	if (enemy == NULL) {
		std::cout << "Error loading enemy" << std::endl;
		return;
	}

	// Add animations
	enemy->addAnimationTexture(textures[0]);
	enemy->addAnimationTexture(textures[1]);
	enemy->addAnimationTexture(textures[0]);
	enemy->addAnimationTexture(textures[2]);

	// Add the enemy's weapon
	enemy->setWeapon(new Weapon(PISTOL, textures[3], textures[4]));

	// Add the enemy's vision texture
	Texture* visionTexture = new Texture(renderer);
	if (!visionTexture->loadFromFile(PATH + "vision_circle.png")) {
		std::cout << "Error loading vision texture" << std::endl;
		return;
	}
	// Vision radius must be transparent
	visionTexture->setAlpha(96);
	enemy->setVisionTexture(visionTexture);

	// Add vision texture to textures vector
	textures.push_back(visionTexture);

	// Set the enemy's position
	std::pair<int, int> randomPos = getWaypoint();

	enemy->setPosX(randomPos.first);
	enemy->setPosY(randomPos.second);

	while (enemy->canSee(player->getCollider())) {
		randomPos = getWaypoint();
		enemy->setPosX(randomPos.first);
		enemy->setPosY(randomPos.second);
	}

	// If the alarm has been triggered, set the enemy to alerted
	if (alarmTriggered) {
		enemy->setAwareness(ALERTED);
	}

	// Add the enemy to the game
	gameObjects.push_back(enemy);
	entities.push_back(enemy);
	characters.push_back(enemy);
	enemies.push_back(enemy);


}

bool Level::isRunning() {
	return running;
}

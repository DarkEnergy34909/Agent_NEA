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

	// Initialise containers
	gameObjects = std::vector<GameObject*>();
	entities = std::vector<Entity*>();
	characters = std::vector<Character*>();

	// Set player to null initially
	player = NULL;

	// Set enemy to null initially
	enemy = NULL;

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

	// Set level timer to 0
	levelTimer = 0;
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

	// Add textures to textures vector
	textures.push_back(playerDefaultTexture);
	textures.push_back(playerWalkTexture1);
	textures.push_back(playerWalkTexture2);
	textures.push_back(pistolTexture);
	textures.push_back(bulletTexture);

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

	// Load test enemy
	Enemy* enemy = new Enemy(playerDefaultTexture, 500, 500, 40, 70, BASIC);
	if (enemy == NULL) {
		std::cout << "Error loading enemy" << std::endl;
		return false;
	}

	// Add animations
	enemy->addAnimationTexture(playerDefaultTexture);
	enemy->addAnimationTexture(playerWalkTexture1);
	enemy->addAnimationTexture(playerDefaultTexture);
	enemy->addAnimationTexture(playerWalkTexture2);

	// Set the enemy's weapon
	enemy->setWeapon(new Weapon(PISTOL, pistolTexture, bulletTexture));

	this->enemy = enemy;

	// Add enemy to containers
	gameObjects.push_back(enemy);
	entities.push_back(enemy);
	characters.push_back(enemy);

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
		std::cout << "Error rendering222: " << SDL_GetError() << std::endl;
		return;
	}

	// Render the level itself
	for (auto& tile : tiles) {
		tile->render(&tileClips[tile->getTileType()]);
	}

	// Render GameObjects
	for (auto& gameObject : gameObjects) {
		gameObject->render();
	}
}

void Level::update() {
	// Update test enemy
	if (enemy != NULL) {
		// Convert player position to centre of tile
		int targetPosX = player->getPosX() + player->getWidth() / 2;
		int targetPosY = player->getPosY() + player->getHeight() / 2;

		std::pair<int, int> nextPos = enemy->calculatePath(targetPosX, targetPosY, levelGrid);
		enemy->moveTo(nextPos.first, nextPos.second);

		// Make the enemy attack the player if they are in range

		// Get the Bullet shot by the Enemy
		if (levelTimer % 100 == 0) {
			Bullet* bullet = enemy->shoot(targetPosX, targetPosY);

			// Add the bullet to the game containers
			if (bullet != NULL) {
				gameObjects.push_back(bullet);
				entities.push_back(bullet);
				bullets.push_back(bullet);
			}
		}
	}

	// Update characters
	updateCharacters();

	std::cout << "Player health: " << player->getHp() << "/100" << std::endl;

	// Move all entities
	moveEntities();

	// Render the level
	render();

	// Update the level timer
	levelTimer = SDL_GetTicks();
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
				std::cout << "Collision detected" << std::endl;

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
					std::cout << "Collision detected" << std::endl;

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

			// If the character the enemy, set enemy to null
			if (character == enemy) {
				enemy = NULL;
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


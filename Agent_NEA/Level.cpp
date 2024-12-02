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
}

Level::~Level() {
	// TODO: close()
}

bool Level::init() {
	// TODO
	return false;
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

	// Load the player
	Player* player = new Player(playerDefaultTexture, 0, 0, 50, 87);
	if (player == NULL) {
		std::cout << "Error loading player" << std::endl;
		return false;
	}

	// Add animations
	player->addAnimationTexture(playerDefaultTexture);
	player->addAnimationTexture(playerWalkTexture1);
	player->addAnimationTexture(playerDefaultTexture);
	player->addAnimationTexture(playerWalkTexture2);

	// Set player
	this->player = player;

	// Add player to containers
	gameObjects.push_back(player);
	entities.push_back(player);
	characters.push_back(player);

	// TODO: Load enemies

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
	// Move all entities
	moveEntities();

	// Render the level
	render();
}

void Level::handleInput(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
		player->handleInput(e);
	}
}

void Level::moveEntities() {
	for (auto& entity : entities) {
		entity->moveX();

		entity->moveY();
		// TODO: resolve collisions
	}
}
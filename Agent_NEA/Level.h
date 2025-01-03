#pragma once
#include <vector>
#include <SDL.h>
#include "Tile.h"
#include "Texture.h"
#include "GameObject.h"
#include "Entity.h"
#include "Character.h"
#include "Player.h"

class Level {
	public: 
		// Constructor
		Level(SDL_Window* window, SDL_Renderer* renderer);

		// Destructor
		~Level();

		// Initialises the level and all objects/textures
		bool init();

		// Loads each game object and its textures
		bool loadObjects();

		// Loads the level
		bool loadLevel();

		// Spawns all characters
		void spawnCharacters();

		// Updates the level (called every frame)
		void update();

		// Renders the level and all objects
		void render();

		// Moves all entities and resolves collisions
		void moveEntities();

		// Detects a collision between two rectangles
		bool isColliding(SDL_Rect a, SDL_Rect b);

		// Handles input
		void handleInput(SDL_Event& e);

		// Closes the level
		void close();


	private:
		// File path
		const std::string PATH = "C:/Users/S_kem/OneDrive - King Edward VI Grammar School/CS A-Level/NEA/Media/";

		// The window the level is rendered to
		SDL_Window* window;

		// The renderer used to render the level
		SDL_Renderer* renderer;

		// Level constants
		const int LEVEL_WIDTH = 640;
		const int LEVEL_HEIGHT = 480;

		// Screen constants - for now the screen will be the same size as the level
		const int SCREEN_WIDTH = 640;
		const int SCREEN_HEIGHT = 480;

		// Tile constants
		const int TILE_WIDTH = 80;
		const int TILE_HEIGHT = 80;

		static const int TOTAL_TILES = 48;
		static const int TOTAL_TILE_TYPES = 12;

		static const int HORIZONTAL_TILES = 8;
		static const int VERTICAL_TILES = 6;


		// The tiles that make up the level
		Tile* tiles[TOTAL_TILES];

		// The grid of tiles that make up the level
		int levelGrid[VERTICAL_TILES][HORIZONTAL_TILES];

		// The clips of the tileset for each tile type
		SDL_Rect tileClips[TOTAL_TILE_TYPES];

		// Containers for game objects
		std::vector<GameObject*> gameObjects;
		std::vector<Entity*> entities;
		std::vector<Character*> characters;
		std::vector<Texture*> textures;

		// The player character
		Player* player; 

		// Whether the level is paused
		bool paused;



};
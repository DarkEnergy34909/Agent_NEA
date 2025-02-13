#pragma once
#include <vector>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Tile.h"
#include "Texture.h"
#include "GameObject.h"
#include "Entity.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"

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

		// Loads text and font
		bool loadText();

		// Spawns all characters
		void spawnCharacters();

		// Updates the level (called every frame)
		void update();

		// Renders the level and all objects
		void render();

		// Moves all entities and resolves collisions
		void moveEntities();

		// Updates the state of all characters
		void updateCharacters();

		// Updates behaviour of the enemy
		void updateEnemies();

		// Detects a collision between two rectangles
		bool isColliding(SDL_Rect a, SDL_Rect b);

		// Handles input
		void handleInput(SDL_Event& e);

		// Closes the level
		void close();

		// Calculates the distance between two points
		double calculateDistance(int x1, int y1, int x2, int y2);

		// Gets a random waypoint for the enemy to move to
		std::pair<int, int> getWaypoint();

		// Changes a GameObject's position to a random position, making sure it is not in a wall
		void spawnObject(GameObject* object);

		// Update the user's score
		void updateScore(int scoreDifference);

		// Get the user's score
		int getScore();

		// Spawn a new enemy at a random position
		void spawnEnemy();

		// Checks if the game is running
		bool isRunning();


	private:
		// File path
		const std::string PATH = "C:/Users/S_kem/OneDrive - King Edward VI Grammar School/CS A-Level/NEA/Media/";

		// The window the level is rendered to
		SDL_Window* window;

		// The renderer used to render the level
		SDL_Renderer* renderer;

		// The score texture
		Texture* scoreTexture;

		// The player's health texture
		Texture* healthTexture;

		// The stealth status texture
		Texture* statusTexture;

		// The text font
		TTF_Font* font;

		// Level constants
		//const int LEVEL_WIDTH = 640;
		//const int LEVEL_HEIGHT = 480;
		const int LEVEL_WIDTH = 800;
		const int LEVEL_HEIGHT = 640;

		// Screen constants - for now the screen will be the same size as the level
		//const int SCREEN_WIDTH = 640;
		//const int SCREEN_HEIGHT = 480;
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 640;

		// Tile constants
		const int TILE_WIDTH = 80;
		const int TILE_HEIGHT = 80;


		//static const int TOTAL_TILES = 48;
		static const int TOTAL_TILES = 80;
		static const int TOTAL_TILE_TYPES = 12;

		//static const int HORIZONTAL_TILES = 8;
		//static const int VERTICAL_TILES = 6;
		static const int HORIZONTAL_TILES = 10;
		static const int VERTICAL_TILES = 8;


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
		std::vector<Bullet*> bullets;
		std::vector<Texture*> textures;
		std::vector<Enemy*> enemies;

		// The player character
		Player* player; 

		// The item the player has to collect
		GameObject* item;

		// A test enemy
		//Enemy* enemy;

		// Whether the level is paused
		bool paused;

		// The level timer
		int levelTimer;

		// The frame counter
		int frameCounter;

		// Shoot sound effect
		Mix_Chunk* shootSound;

		// Cash pickup sound effect
		Mix_Chunk* cashSound;

		// Alarm sound effect
		Mix_Chunk* alarmSound;

		// Whether the game is running
		bool running;

		// The user's current score
		int score;

		// Whether the alarm has been triggered
		bool alarmTriggered;

};


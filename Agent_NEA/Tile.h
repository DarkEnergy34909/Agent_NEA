#pragma once
#include "Texture.h"

class Tile {
	public:
		// Constructor
		Tile(int tileType, int posX, int posY);

		// Destructor
		~Tile();

		// Renders the tile
		void render(SDL_Rect* clip, int camX = 0, int camY = 0);

		// Getters

		SDL_Rect getTileCollider();

		int getTileType();

		int getPosX();

		int getPosY();

		bool isWall();

		int getWidth();

		int getHeight();

		// Setters

		void setWall(bool wall);

		void setTexture(Texture* texture);

	private:
		// Tile dimensions
		const int TILE_WIDTH = 80;
		const int TILE_HEIGHT = 80;

		// Tile position
		int posX, posY;

		// Tile collider
		SDL_Rect tileCollider;

		// The texture of the tile
		Texture* texture;

		// The type of the tile
		int tileType;

		// Whether the tile is a wall
		bool wall;
};

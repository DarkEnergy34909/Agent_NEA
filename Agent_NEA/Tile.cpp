#include "Tile.h"

Tile::Tile(int tileType, int posX, int posY) {
	// Set the tile type
	this->tileType = tileType;

	// Set the position of the tile
	this->posX = posX;
	this->posY = posY;

	// Set the tile collider
	tileCollider.x = posX;
	tileCollider.y = posY;
	tileCollider.w = TILE_WIDTH;
	tileCollider.h = TILE_HEIGHT;

	// Tile isn't a wall by default
	wall = false;

	// Texture will be initialised later in the Level class
	texture = NULL;
}

Tile::~Tile() {
	// Free the tile texture (because if one tile is deleted, all tiles are deleted)
	texture->free();
}

void Tile::render(SDL_Rect* clip) {
	// Render the tile
	texture->render(posX, posY, clip);
}

SDL_Rect Tile::getTileCollider() {
	// Return the tile collider
	return tileCollider;
}

int Tile::getTileType() {
	// Return the tile type
	return tileType;
}

int Tile::getPosX() {
	// Return the x-position of the tile
	return posX;
}

int Tile::getPosY() {
	// Return the y-position of the tile
	return posY;
}

bool Tile::isWall() {
	// Return whether the tile is a wall
	return wall;
}

int Tile::getWidth() {
	// Return the width of the tile
	return TILE_WIDTH;
}

int Tile::getHeight() {
	// Return the height of the tile
	return TILE_HEIGHT;
}

void Tile::setWall(bool wall) {
	// Set whether the tile is a wall
	this->wall = wall;
}

void Tile::setTexture(Texture* texture) {
	// Set the texture of the tile
	this->texture = texture;

	// Set the dimensions of the texture
	texture->setWidth(TILE_WIDTH);
	texture->setHeight(TILE_HEIGHT);

}
#include "GameObject.h"

GameObject::GameObject(Texture& texture, int posX, int posY, int width, int height) {
	// Initialise position of the object
	this->posX = posX;
	this->posY = posY;

	// Initialise dimensions
	this->width = width;
	this->height = height;

	// Initialise collider
	collider.x = posX;
	collider.y = posY;
	collider.w = width;
	collider.h = height;

	// Initialise the texture 
	this->texture = &texture;
	this->texture->setWidth(width);
	this->texture->setHeight(height);
}

GameObject::~GameObject() {
	// Do nothing
}

void GameObject::render() {
	// Render the texture at the object's position
	texture->render(posX, posY);
}

int GameObject::getPosX() {
	return posX;
}

int GameObject::getPosY() {
	return posY;
}

int GameObject::getWidth() {
	return width;
}

int GameObject::getHeight() {
	return height;
}

SDL_Rect GameObject::getCollider() {
	return collider;
}

void GameObject::setPosX(int x) {
	// Update x position
	posX = x;

	// Update collider
	collider.x = x;
}

void GameObject::setPosY(int y) {
	// Update y position
	posY = y;

	// Update collider
	collider.y = y;
}

void GameObject::setWidth(int width) {
	// Update width
	this->width = width;

	// Update collider
	collider.w = width;

	// Update texture width
	texture->setWidth(width);
}

void GameObject::setHeight(int height) {
	// Update height
	this->height = height;

	// Update collider
	collider.h = height;

	// Update texture height
	texture->setHeight(height);
}




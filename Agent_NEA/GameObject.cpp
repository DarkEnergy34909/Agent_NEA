#include "GameObject.h"

GameObject::GameObject() {
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;

	collider = { 0, 0, 0, 0 };
}

GameObject::~GameObject() {
	texture.free();
}

void GameObject::render(bool isFlipped) {
	// TODO: Add flip functionality
	texture.render(posX, posY);
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
	texture.setWidth(width);
}

void GameObject::setHeight(int height) {
	// Update height
	this->height = height;

	// Update collider
	collider.h = height;

	// Update texture height
	texture.setHeight(height);
}




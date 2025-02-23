#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"

enum ObjectType {
	PLAYER,
	ENEMY,
	BULLET,
	OTHER
};

class GameObject {
	public:
		// Constructor
		GameObject(Texture* texture, int posX, int posY, int width, int height);

		// Destructor
		virtual ~GameObject();

		// Renders the GameObject
		virtual void render(int camX = 0, int camY = 0);

		// Getters
		int getPosX();

		int getPosY();

		int getWidth();

		int getHeight();

		SDL_Rect getCollider();

		int getObjectType();

		// Setters

		void setPosX(int x);

		void setPosY(int y);

		void setWidth(int width);

		void setHeight(int height);

	protected:
		// Position of the GameObject within the level
		int posX, posY;

		// Dimensions of the GameObject
		int width, height;

		// Sprite (texture) of the GameObject
		Texture* texture;

		// Collider of the GameObject (to be used in collision detection)
		SDL_Rect collider;

		// The type of the GameObject
		int objectType;
};
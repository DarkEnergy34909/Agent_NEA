#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"


class GameObject {
	public:
		// Constructor
		GameObject(Texture &texture, int posX, int posY, int width, int height);

		// Destructor
		~GameObject();

		// Renders the GameObject
		void render();

		// Getters
		int getPosX();

		int getPosY();

		int getWidth();

		int getHeight();

		SDL_Rect getCollider();

		// Setters

		void setPosX(int x);

		void setPosY(int y);

		void setWidth(int width);

		void setHeight(int height);



	private:
		// Position of the GameObject within the level
		int posX, posY;

		// Dimensions of the GameObject
		int width, height;

		// Sprite (texture) of the GameObject
		Texture* texture;

		// Collider of the GameObject (to be used in collision detection)
		SDL_Rect collider;
		

};
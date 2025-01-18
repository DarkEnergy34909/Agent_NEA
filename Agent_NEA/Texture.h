#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Texture {
	public:
		// Constructor
		Texture(SDL_Renderer* renderer);

		// Destructor
		~Texture();

		// Loads the texture from a png file
		bool loadFromFile(std::string filePath);

		// Loads the texture from a text string and font
		bool loadFromText(std::string text, TTF_Font* font, SDL_Color color);

		// Deletes the texture
		void free();

		// Sets the colour of the texture
		void setColor(int r, int g, int b);

		// Sets the alpha (transparency) of the texture
		void setAlpha(int alpha);

		// Sets the blend mode of the texture
		void setBlendMode(SDL_BlendMode blending);

		// Renders a part (clip) of the texture at a given position, with a given angle and flip
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		// Getters
		int getWidth();
		
		int getHeight();

		// Setters
		void setWidth(int width);

		void setHeight(int height);

	private:
		// The SDL texture
		SDL_Texture* texture; 

		// Texture dimensions
		int width;
		int height; 

		// Renderer
		SDL_Renderer* renderer;
};
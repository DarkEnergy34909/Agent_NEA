#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer) {
	// Set the renderer
	this->renderer = renderer;

	texture = NULL;

	width = 0;
	height = 0;

	// Load texture from file
	//loadFromFile(filePath);
}

Texture::~Texture() {
	// Free texture
	free();
}

bool Texture::loadFromFile(std::string filePath) {
	// Destroy the previous texture stored
	free();

	SDL_Texture* newTexture = NULL;

	// Load the image from the file path
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());

	if (loadedSurface == NULL) {
		std::cout << "Error loading image: " << IMG_GetError() << std::endl;
	}
	else {
		// Create a texture from the image surface
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
		}
		else {
			// Set the dimensions of the texture
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		// Destroy the temporary image surface
		SDL_FreeSurface(loadedSurface);
	}
	// Set the texture to the new texture
	texture = newTexture;

	// Return true if the texture was successfully loaded, false if not
	return (texture != NULL);
}

void Texture::free() {
	// Destroy the texture
	if (texture != NULL) {
		SDL_DestroyTexture(texture);

		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::setColor(int r, int g, int b) {
	// Set the colour of the texture
	SDL_SetTextureColorMod(texture, r, g, b);
}

void Texture::setAlpha(int alpha) {
	// Set the alpha of the texture
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	// Set the blend mode of the texture
	SDL_SetTextureBlendMode(texture, blending);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	// The rectangle on the screen the texture is rendered to
	SDL_Rect renderQuad = { x, y, width, height };

	// If a clip is given, set the dimensions of the renderQuad to the clip dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render the texture to the screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() {
	// Return the width of the texture
	return width;
}

int Texture::getHeight() {
	// Return the height of the texture
	return height;
}

void Texture::setWidth(int width) {
	// Set the width of the texture
	this->width = width;
}

void Texture::setHeight(int height) {
	// Set the height of the texture
	this->height = height;
}


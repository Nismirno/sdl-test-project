#include "LTexture.h"
#include <SDL.h>
#include <SDL_image.h>

LTexture::LTexture() {
	// Initialize
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
}


LTexture::~LTexture() {
	// Deallocate
	free();
}


bool LTexture::loadFromFile(std::string path) {
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specific path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	} 
	// Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	// Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (newTexture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s", path.c_str(), SDL_GetError());
		return false;
	}
	// Get image dimensions
	m_width = loadedSurface->w;
	m_height = loadedSurface->h;

	// Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	// Return success
	m_texture = newTexture;

	return m_texture != NULL;
}


void LTexture::free() {
	// Free texture if it exists
	if (m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}


void LTexture::render(int x, int y, const SDL_Rect* clip) const {
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_width, m_height };

	// Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, m_texture, clip, &renderQuad);
}


int LTexture::getWidth() const {
	return m_width;
}


int LTexture::getHeight() const {
	return m_height;
}

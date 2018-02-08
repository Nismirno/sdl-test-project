#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Globals.h"

struct SDL_Texture;
struct SDL_Rect;

class LTexture {
public:
	// Initialize variables
	LTexture();

	// Deallocate memory
	~LTexture();

	// Loads image at specific path
	bool loadFromFile(std::string path);

	// Deallocate texture
	void free();

	// Set color modulation
	void setColor(uint8_t red, uint8_t green, uint8_t blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(uint8_t alpha);

	// Renders texture at given point
	void render(int x, int y, const SDL_Rect* clip = NULL) const;

	// Gets image dimension
	int getWidth() const;
	int getHeight() const;

private:
	// The actual hardware texture
	SDL_Texture* m_texture;

	// Image dimensions
	int m_width;
	int m_height;
};
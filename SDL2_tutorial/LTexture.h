#pragma once
#include <string>
#include "Globals.h"

class SDL_Texture;

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

	// Renders texture at given point
	void render(int x, int y) const;

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
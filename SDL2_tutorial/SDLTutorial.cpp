// Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Globals.h"
#include "LTexture.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// <-- Global variables
// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;
// Global variables -->

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Scene Textures
bool init() {
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags)) & imgFlags) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	// Loading success flag
	bool success = true;

	// Load texture
	gTexture = loadTexture("media/viewport.png");
	if (gTexture == NULL) {
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}


void close() {
	// Free loaded texture
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destoy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	// Quit SDL subsystem
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path) {
	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int main(int argc, char* args[]) {

	if (!init()) {
		printf("Failed to initialize!\n");
	} else {
		// Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// While application is running
			while (!quit) {
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					// User requests quit
					if (e.type == SDL_QUIT) {
						quit = true;
					} 
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Top left viewport
				SDL_Rect topLeftViewport;
				topLeftViewport.x = 0;
				topLeftViewport.y = 0;
				topLeftViewport.w = SCREEN_WIDTH / 2;
				topLeftViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &topLeftViewport);

				// Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Top right viewport
				SDL_Rect topRightViewport;
				topRightViewport.x = SCREEN_WIDTH / 2;
				topRightViewport.y = 0;
				topRightViewport.w = SCREEN_WIDTH / 2;
				topRightViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &topRightViewport);

				// Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Bottom right viewport
				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT / 2;
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(gRenderer, &bottomViewport);

				// Render texture to screen
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Update scren
				SDL_RenderPresent(gRenderer);

			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}
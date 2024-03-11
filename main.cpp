#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// dependencies
// libsdl2-dev, libsdl2-image-dev

int SCREEN_WIDTH = 512;
int SCREEN_HEIGHT = 512;

SDL_Window *g_window;
SDL_Renderer *g_renderer;

SDL_Texture* g_image;

struct RGBA{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

struct RGB{
	Uint8 r;
	Uint8 g;
	Uint8 b;
};

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cout << "Failed to load image! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    texture = SDL_CreateTextureFromSurface(g_renderer, surface);
    if (!texture) {
        std::cout << "Failed to create texture! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}

int init(const char *name = ""){
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	g_window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!g_window){
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (!g_renderer){
		std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	return 0;
}

void clear(SDL_Renderer *renderer, RGB color = {255,255,255}){
	SDL_SetRenderDrawColor(g_renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_renderer);
}

void loop();
void setup();

void close(){
	SDL_DestroyTexture(g_image);
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

int main(){
	if (init("lsd2") != 0) return 1;
	int f = 0;
	setup();
	SDL_Event e;
	bool quit = false;
	while (quit == false){
		SDL_Delay(5);
		if(f%4==0) loop();
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT) quit = true;
		}
		f++;
	}
	return 0;
}



//! end of simulation setup
//! drawFrame is called repetetively
//! dont care about anything above

void renderTexture(SDL_Texture* texture, int x, int y, int width, int height) {
    SDL_Rect srcRect = {0, 0, 128, 128};
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(g_renderer, texture, &srcRect, &destRect);
}


void setup(){
	g_image = loadTexture("./assets/flag.png");
    if (!g_image) {
        close();
        return;
    }
}


void loop(){
	clear(g_renderer, {0,0,0});
	renderTexture(g_image, 0, 128, 512, 256);
	renderTexture(g_image, 512-128, 256, 64, 64);
	renderTexture(g_image, 64, 128, 64, 64);
	SDL_RenderPresent(g_renderer);
}
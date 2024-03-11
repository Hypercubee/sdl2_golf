#include <iostream>
#include "lib/renderlib.hpp"



int SCREEN_WIDTH = 512;
int SCREEN_HEIGHT = 512;

SDL_Window *g_window;
SDL_Renderer *g_renderer;
SDL_Texture* g_image;

void loop();
void setup();

int main(){
	if (rn::init("lsd2", g_window, g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT) != 0) return 1;
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

//! setup runs once and afterwards loop runs repeatedly

void setup(){
	g_image = rn::loadTexture(g_renderer, "./assets/flag.png");
    if (!g_image) {
        rn::close(g_window, g_renderer);
        return;
    }
}

void loop(){
	rn::clear(g_renderer, {0,0,0});
	rn::renderTexture(g_renderer, g_image, 0, 128, 512, 256);
	rn::renderTexture(g_renderer, g_image, 512-128, 256, 64, 64);
	rn::renderTexture(g_renderer, g_image, 64, 128, 64, 64);
	SDL_RenderPresent(g_renderer);
}
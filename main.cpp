#include <iostream>
#include "lib/renderlib.hpp"
#include <vector>
#include <array>


int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;

SDL_Window *g_window;
SDL_Renderer *g_renderer;



void loop();
void setup();

int main(){
	if (rn::init("golf", g_window, g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT) != 0) return -1;
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

std::vector<std::string> assetPaths = {
	"./assets/grass-floor.png",
	"./assets/flag.png",
	"./assets/wall.png",
	"./assets/grass-wall0.png",
	"./assets/grass-wall1.png",
	"./assets/grass-wall2.png",
	"./assets/grass-wall3.png",
};

std::vector<SDL_Texture*> g_textures;

std::vector<std::pair<int, std::vector<Cell>>> levels;

void setup(){
	rn::loadAssets(g_renderer, assetPaths, g_textures);
	levels.push_back(rn::readLevelFile("levels/level_02"));
}

void loop(){
	rn::clear(g_renderer, {0,0,0});
	rn::drawLevel(g_renderer, g_window, g_textures, levels[0]);
	SDL_RenderPresent(g_renderer);
}

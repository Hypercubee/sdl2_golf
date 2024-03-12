#include <iostream>
#include "lib/renderlib.hpp"
#include <vector>



//TODO make function to trash the textures before exit
void loadAssets(SDL_Renderer *renderer, const std::vector<std::string> paths, std::vector<SDL_Texture*>& textures){
	for(std::string path : paths){
		SDL_Texture *texture = rn::loadTexture(renderer, path);
		textures.push_back(texture);
	}
}




int SCREEN_WIDTH = 512;
int SCREEN_HEIGHT = 512;

SDL_Window *g_window;
SDL_Renderer *g_renderer;

std::vector<std::string> assetPaths = {
	"./assets/flag.png",
	"./assets/grass-floor.png",
	"./assets/grass-wall0.png",
	"./assets/grass-wall1.png",
	"./assets/grass-wall2.png",
	"./assets/grass-wall3.png",
};

std::vector<SDL_Texture*> textures;

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
	loadAssets(g_renderer, assetPaths, textures);
}

void loop(){
	rn::clear(g_renderer, {0,0,0});
	rn::renderTexture(g_renderer, textures.at(1), 0, 128, 512, 256);
	rn::renderTexture(g_renderer, textures.at(0), 512-128, 256, 64, 64);
	rn::renderTexture(g_renderer, textures.at(2), 64, 128, 64, 64);
	SDL_RenderPresent(g_renderer);
}
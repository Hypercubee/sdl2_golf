#include <iostream>
#include "lib/renderlib.hpp"
#include <vector>
#include <array>



//TODO make function to trash the textures before exit





int SCREEN_WIDTH = 512;
int SCREEN_HEIGHT = SCREEN_WIDTH;

SDL_Window *g_window;
SDL_Renderer *g_renderer;

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





std::pair<int, std::vector<Cell>> readLevelFile(const std::string& filename) {
    std::pair<int, std::vector<Cell>> vec;
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
		file.read(reinterpret_cast<char*>(&vec.first), sizeof(vec.first));
        vec.second.resize(size / sizeof(Cell));
        file.read(reinterpret_cast<char*>(vec.second.data()), size);
        file.close();
    } else {
        std::cout << "Unable to open file for reading: " << filename << std::endl;
    }
    return vec;
}



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

std::vector<std::pair<int, std::vector<Cell>>> levels;


void setup(){
	rn::loadAssets(g_renderer, assetPaths, g_textures);
	levels.push_back(readLevelFile("levels/level_02"));
}

void loop(){
	rn::clear(g_renderer, {0,0,0});
	rn::drawLevel(g_renderer, g_textures, levels[0]);
	SDL_RenderPresent(g_renderer);
}
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

std::vector<SDL_Texture*> textures;

struct Cell{
	int x;
	int y;
	int tex;
};



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

void drawLevel(SDL_Renderer *renderer, std::pair<int, std::vector<Cell>> level){
	int& size = level.first;
	std::vector<Cell>& lvl = level.second;
	int cellSize = SCREEN_WIDTH / size;

	for(int i = 0; i < size*size; i++){
		rn::renderTexture(renderer, textures.at(0), (i%size)*cellSize, (i/size)*cellSize, cellSize, cellSize);
	}

	for(Cell c : lvl){
		rn::renderTexture(renderer, textures.at(c.tex), c.x * cellSize, c.y * cellSize, cellSize, cellSize);
	}

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
	rn::loadAssets(g_renderer, assetPaths, textures);
	levels.push_back(readLevelFile("levels/level_02"));
}

void loop(){
	rn::clear(g_renderer, {0,0,0});
	drawLevel(g_renderer, levels[0]);
	SDL_RenderPresent(g_renderer);
}
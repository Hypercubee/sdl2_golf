#include "renderlib.hpp"


namespace rn{

    //! window management
    int init(const char *name, SDL_Window *&window, SDL_Renderer *&renderer, int width, int height){
        if (SDL_Init(SDL_INIT_VIDEO) < 0){
            std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        if (!window){
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer){
            std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return 1;
        }
        return 0;
    }

    void close(SDL_Window *window, SDL_Renderer *renderer){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }   



    //! renderer functions

    void clear(SDL_Renderer *renderer, RGB color){
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
    }

    // * loading resources

    SDL_Texture* loadTexture(SDL_Renderer *renderer, const std::string& path) {
        SDL_Texture* texture = nullptr;
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface) {
            std::cout << "Failed to load image! SDL_Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            std::cout << "Failed to create texture! SDL_Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(surface);
        return texture;
    }

    void loadAssets(SDL_Renderer *renderer, const std::vector<std::string> paths, std::vector<SDL_Texture*>& textures){
	    for(std::string path : paths){
		    SDL_Texture *texture = loadTexture(renderer, path);
		    textures.push_back(texture);
	    }
    }

    void renderTexture(SDL_Renderer *renderer, SDL_Texture* texture, int x, int y, int width, int height) {
        SDL_Rect srcRect = {0, 0, 128, 128};
        SDL_Rect destRect = {x, y, width, height};
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    }

}
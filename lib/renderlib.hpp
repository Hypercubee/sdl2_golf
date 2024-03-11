#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


namespace rn{
    struct RGBA{
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    struct RGB{
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    // * window management
    /**
     * @brief Initialize SDL and create a window with a renderer.
     * 
     * @param name The title of the window.
     * @param window A reference to a pointer to store the created SDL_Window.
     * @param renderer A reference to a pointer to store the created SDL_Renderer.
     * @param width The width of the window.
     * @param height The height of the window.
     * @return 0 on success, 1 on failure.
     */
    int init(const char *name, SDL_Window *&window, SDL_Renderer *&renderer, int width, int height);

    /**
     * @brief Close the window and renderer.
     * 
     * @param window pointer to window created by init
     * @param renderer pointer to renderer created by init
     */
    void close(SDL_Window *window, SDL_Renderer *renderer);

    //  * renderer functions
    /**
     * @brief clears whole screen with set color
     * 
     * @param renderer pointer to SDL renderer
     * @param color color to clear with
    */
    void clear(SDL_Renderer *renderer, RGB color = {255,255,255});

    /**
     * @brief clears whole screen with set color
     * 
     * @param renderer pointer to SDL renderer
     * @param path path to the image file
     * @return loaded texture
    */
    SDL_Texture* loadTexture(SDL_Renderer *renderer, const std::string& path);

    /**
     * @brief Renders a texture to the screen.
     * 
     * @param renderer pointer to SDL renderer
     * @param texture pointer to texture to render
     * @param x x coord of the texture on screen
     * @param y y coord of the texture on screen
     * @param w width of the texture on screen
     * @param h height of the texture on screen
     */
    void renderTexture(SDL_Renderer *renderer, SDL_Texture* texture, int x, int y, int width, int height);
}
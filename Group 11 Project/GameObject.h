#pragma once

#include "Game.h"
#include "TextureManager.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
class GameObject
{
public:
    GameObject(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols);
    GameObject(const char *texturesheet,int,string,SDL_Color,int,int,int,int);
    ~GameObject();

    void update();
    void Render(bool flipFlag = false); 
    void updateDestRect();

    // reset to spawning position
    void reset();

protected:
    int xpos, ypos;
    int start_x,start_y;
    TextureManager* Texture;
    int width , height;
    // is null if we don't clip, specifies the dest rect
    SDL_Rect destRect;
    // stepSize
    int stepSize = 8;
    // camera control
};
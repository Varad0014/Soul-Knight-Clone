#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "GameObject.h"

class Camera {
    public:
        // constructor
        Camera(int width, int height, int x, int y);
        
        // get the destination rectangle
        SDL_Rect GetSrcRect();

        // update the rectangle
        void UpdateCoords(int x, int y);

    private:
        int width;
        int height;
        int x = 0;
        int y = 0;
        SDL_Rect SrcRect;
};
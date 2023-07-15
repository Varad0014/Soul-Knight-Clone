#pragma once

#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <utility>
using namespace std;

class TextureManager
{
    private:
        // texture
        SDL_Texture* texture;

        // dimensions of the whole image
        int TextWidth;
        int TextHeight;
 
        // dimensions of the source
        int SrcWidth;
        int SrcHeight;

        // image rectangle
        SDL_Rect srcRect;

        // number of partitions of the texture
        int parts;

        // number of rows and cols of the grid of the texture
        int rows, cols;

    public:
        // sarthak start

        // renderer
        static SDL_Renderer* renderer;
        // Constructor
        TextureManager();

        // Destructor
        ~TextureManager();  

        // tries to load the texture and returns if it was successful or not
        bool loadTexture(string fName, int parts, int rows, int cols);

        // make grids out of the texture
        bool makeGrid(int noOfParts, int noOfRows, int noOfCols);

        // make the source rectangle
        bool makeSourceRectangle(int rowNumber, int colNumber);

        // renders text on screen
        bool renderText(const char*,int,string,SDL_Color);

        // destroy the texture
        void destroyTexture();

        // render the texture
        void render(SDL_Rect* destRect, bool flipFlag = false);
        void render(SDL_Rect* destRect, SDL_Rect* srcRect, bool flipFlag = false);

        // get rows and columns
        pair<int, int> getRowsAndCols();

        // set the renderer
        static void setRenderer(SDL_Renderer* rend);
};
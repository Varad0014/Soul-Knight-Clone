#include "TextureManager.h"
#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

// initialise renderer
SDL_Renderer* TextureManager::renderer = NULL;

TextureManager::TextureManager() {
    // initialise
    texture = NULL;
}

void TextureManager::destroyTexture() {
    if(texture != NULL) {
        SDL_DestroyTexture(texture); 
    }
}

// tries to load the texture and returns if it was successful or not
bool TextureManager::loadTexture(string fName, int parts, int rows, int cols) {
    // reset the texture if present
    destroyTexture();

    // final texture will be stored here
    SDL_Texture* finalTexture = NULL;
    
    // temporary surface stores the loaded file
    SDL_Surface* tempSurface = IMG_Load(fName.c_str());

    if(tempSurface == NULL) {
        cout << "Not able to load image" << fName << " SDL Error: " << SDL_GetError() << endl;
    }
    else {
        // color key
        SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

        // make texture from the surface
        finalTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if(finalTexture == NULL) {
            cout << "Unable to create texture from " << fName << " SDL Error: " << SDL_GetError() << endl;
        }
        else {
            TextWidth = tempSurface->w;
            TextHeight = tempSurface->h;
        }

        // destroy temp surface
        SDL_FreeSurface(tempSurface);
    }

    texture = finalTexture;
    return (texture != NULL && makeGrid(parts, rows, cols));
}

bool TextureManager :: renderText(const char* fname,int size,string text,SDL_Color color)
{
    destroyTexture();

    TTF_Font *gfont = TTF_OpenFont(fname,size);
    SDL_Texture* finalTexture = NULL;
    SDL_Surface* tempSurface = TTF_RenderText_Solid(gfont,text.c_str(),color);

    if(tempSurface == NULL)
        cout << "Not able to load image,"  << " SDL_ttf Error: " << TTF_GetError() << endl;
    else
    {
        finalTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if(finalTexture == NULL)
        {
            cout << "Unable to create texture from " << " SDL Error: " << SDL_GetError() << endl;
        }
        else
        {
            TextWidth = tempSurface->w;
            TextHeight = tempSurface->h;
        }
        SDL_FreeSurface(tempSurface);
    }

    TTF_CloseFont(gfont);

    texture = finalTexture;
    return (texture != NULL && makeGrid(1,1,1));
}

bool TextureManager::makeGrid(int noOfParts, int noOfRows, int noOfCols) {
    // initialise attributes
    parts = noOfParts;
    rows = noOfRows;
    cols = noOfCols;

    // calculate source width and height
    SrcWidth = TextWidth/cols;
    SrcHeight = TextHeight/rows;

    return makeSourceRectangle(0, 0);
}

// get row and col number given part number
bool TextureManager::makeSourceRectangle(int rowN, int colN) {
    // rowNumber of the grid
    int rowNumber = rowN;
    int colNumber = colN;

    // source rectangle
    srcRect = {colNumber*SrcWidth, rowNumber*SrcHeight, SrcWidth, SrcHeight};

    return true;
}

// destroy the texture
TextureManager::~TextureManager() {
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        TextWidth = 0;
        TextHeight = 0;
    }
}

// display the specified part of the texture
void TextureManager::render(SDL_Rect* destRect, bool flipFlag) {
    // render the rect
    if(flipFlag) {
        SDL_RenderCopyEx(renderer, texture, &srcRect, destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else {
        SDL_RenderCopy(renderer, texture, &srcRect, destRect);
    }
}

// display the specified part of the texture
void TextureManager::render(SDL_Rect* destRect, SDL_Rect* srcRect, bool flipFlag) {
    // render the rect
    if(flipFlag) {
        SDL_RenderCopyEx(renderer, texture, srcRect, destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else {
        SDL_RenderCopy(renderer, texture, srcRect, destRect);
    }
}

// return rows and cols
pair<int, int> TextureManager::getRowsAndCols() {
    return make_pair(rows, cols);
}

// set the renderer
void TextureManager::setRenderer(SDL_Renderer* rend) {
    renderer = rend;
}
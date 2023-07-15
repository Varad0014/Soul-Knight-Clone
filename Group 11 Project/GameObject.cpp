#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
using namespace std;

GameObject::GameObject(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols) 
{
    xpos = x;
    start_x = x;
    ypos = y;
    start_y = y;

    Texture = new TextureManager(); 
    Texture->loadTexture(texturesheet, parts, rows, cols);
    width = w;
    height = h;
    // make the destination rectangle
    destRect = {xpos, ypos, width, height};
}

GameObject :: GameObject(const char *texturesheet,int size,string text,SDL_Color color,int x,int y,int w,int h)
{
    xpos = x;
    start_x = x;
    ypos = y;
    start_y = y;

    Texture = new TextureManager();
    Texture->renderText(texturesheet,size,text,color);
    width = w;
    height = h;

    destRect = {xpos,ypos,width,height};

}

void GameObject::update()
{
    updateDestRect();
}

void GameObject::Render(bool flipFlag)
{
    Texture->render(&destRect, flipFlag);
}

void GameObject::updateDestRect() {
    destRect.x = xpos;
    destRect.y = ypos;
}

void GameObject :: reset()
{
    xpos = start_x;
    ypos = start_y;
}

GameObject::~GameObject()
{
    
}

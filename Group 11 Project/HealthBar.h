#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
#include <utility>
#include <vector>
using namespace std;

class HealthBar: public GameObject
{
    public:
        HealthBar(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols);
        virtual void update() = 0;
        void Render();
    protected:
        int maxHealth;

};
#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
#include "HealthBar.h"
#include <utility>
#include<vector>
using namespace std;

class EnemyHealth: public HealthBar
{
    public:
        EnemyHealth(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int max_health, Enemy* e);
        void update();
        void updateCoord();
    private:
        Enemy* enemy;
};

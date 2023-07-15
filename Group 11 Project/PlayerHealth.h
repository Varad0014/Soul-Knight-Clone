#pragma once 

#include "GameObject.h"
#include "Game.h"
#include "HealthBar.h"
#include "Player.h"
#include "TextureManager.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
#include <utility>
#include<vector>
using namespace std;


class PlayerHealth: public HealthBar
{
    public:
        PlayerHealth(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int max_health, Player* p);
        void update();
    private:
        Player* player;
        int rowNo = 5;
};

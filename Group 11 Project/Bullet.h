#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> 
#include <utility>
using namespace std;

class Bullet: public GameObject
{
    private:
        Enemy* targetEnemy;
        int xDiff, yDiff, enemyX, enemyY;
        double distance;
        int i =1;
        int counter = 0;
        bool reachedDest = false;
    public:
        Bullet(const char *, int x, int y, int w, int h, int parts, int rows, int cols, int eX, int eY, int xDiff, int yDiff, double distance);
        void update(int shiftX, int shiftY);
        void shotBulletMovement(int shiftX, int shiftY);
        void Render();
        bool reachDest();
        bool exceededMaxTime();
        void addRelX(int x);
        void addRelY(int x);
        SDL_Rect* getDestRect();
};
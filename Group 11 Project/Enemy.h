#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include "HealthBar.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
#include <utility>
#include <vector>
using namespace std;



class Enemy : public Player 
{
public:
    Enemy(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int mHealth, int sCount, Player *p); // last two args by sarthak
    static Enemy* generateEnemy(Player* p, int xBound, int yBound);
    void update();
    void setFlipFlag(bool flag);
    SDL_Rect* getDestRect();
    pair<int, int> GetCoords();
    pair<int, int> GetDims();
    void Render();
    void movement();
    void addRelX(int x);
    void addRelY(int x);
    void shootBullet();
    vector<Bullet*> &getBullets();
    void reduceHealth(vector<Enemy*> &enemies, int i);
    void setBullets(vector<Bullet*> enemyBullets);
    int getScaleCount();
    ~Enemy();
private:
    int colControl = 0, colNo = 0, animationControl = 4;
    bool flipFlag = false;
    int stepSize = 1;
    Player *player;
    int plyX, plyY;
    vector<Bullet*> bullets;
    int counter = 0;
    bool relUP, relDOWN, relLEFT, relRIGHT;
    int shiftX, shiftY;
    int scaleCount;

};
    
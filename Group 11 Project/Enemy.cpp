#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "Bullet.h"
#include "EnemyHealth.h"
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h>
using namespace std;

Enemy::Enemy(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int mHealth, int  sCount, Player *p)
:Player(texturesheet, x, y, w, h, parts, rows, cols, mHealth) { 
    player = p;
    healthBar = new EnemyHealth("Images/healthbarEnemy.png", x, y, 65, 9, 2, 2, 1, maxHealth, this);
    shiftX = shiftY = 0;
    scaleCount = sCount;
}

void Enemy::update()
{
    // updates column in every frame
    colControl = (colControl == (animationControl*4 - 1) ? 0 : colControl + 1);
    colNo = colControl/animationControl;
    movement();
    updateDestRect(); 
    Texture->makeSourceRectangle(0, colNo);
    healthBar -> update();
    if(counter >= 180)
    {
        cout << "enemy shoot" << endl;
        counter = 0;
        shootBullet();
    }
    
    for(int i=0 ; i<bullets.size() ; i++)
    {
        if(bullets[i])
            bullets[i] -> update(shiftX, shiftY);
    }  
    counter++;
    shiftX = 0;
    shiftY = 0;
    
}

void Enemy::movement()
{
    plyX = player -> GetCoords().first;
    plyY = player -> GetCoords().second;
    
    int xDiff = abs(plyX - xpos);
    int yDiff = abs(plyY - ypos);
    double distance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
    if(plyX > xpos)
    {
        xpos += ceil(stepSize*(xDiff/distance));
        setFlipFlag(false);
    }
    if(plyX < xpos)
    {
        xpos -= ceil(stepSize*(xDiff/distance));
        setFlipFlag(true);
    }

    if(plyY > ypos)
    {
        ypos += ceil(stepSize*(yDiff/distance));
    }
    if(plyY < ypos)
    {
        ypos -= ceil(stepSize*(yDiff/distance));
    }
}

void Enemy::addRelX(int x)
{
    if(x==1)
    {
        shiftX = 1;
    }
    else
    {
        shiftX = -1;
    }
    xpos += GameObject::stepSize*x;
    for(int i=0 ; i<bullets.size() ; i++)
    {
        if(bullets[i])
            bullets[i]->addRelX(x);
    }
}

void Enemy::addRelY(int x)
{
    if(x==1)
    {
        shiftY = 1;
    }
    else
    {
        shiftY = -1;
    }
    ypos += GameObject::stepSize*x;
    for(int i=0 ; i<bullets.size() ; i++)
    {
        if(bullets[i])
            bullets[i]->addRelY(x);
    }
}

// set flipflag
void Enemy::setFlipFlag(bool flag) {
    flipFlag = flag;
}

void Enemy::Render()
{
    GameObject::Render(flipFlag);
    for(int i=0 ; i<bullets.size() ; i++)
    {
        if(bullets[i])
            bullets[i] -> Render();
    }
    healthBar -> Render();
}

// get coords
pair<int, int> Enemy::GetCoords() {
    return (make_pair(xpos, ypos));
}

Enemy* Enemy::generateEnemy(Player* p, int xBound, int yBound)
{
    int x = rand()%xBound;
    int y = rand()%yBound;
    Enemy* newEnemy = new Enemy("Images/EnemySprite.png", x, y, 50, 46, 4, 1, 4, 2, 1, p);
    return(newEnemy);
}

SDL_Rect* Enemy::getDestRect()
{
    return(&destRect);
}

pair<int, int> Enemy::GetDims()
{
    return(make_pair(destRect.w, destRect.h));
}

void Enemy::shootBullet()
{
    pair<int, int> playerCoord = player -> GetCoords();
    int playerX = playerCoord.first;
    int playerY = playerCoord.second;
    
    int xDiff = abs(xpos - playerX);
    int yDiff = abs(ypos - playerY);
    double distance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
    Bullet* bullet = new Bullet("Images/fireball.png", xpos, ypos, 25, 20, 1, 1, 1, playerX, playerY, xDiff, yDiff, distance);
    bullets.push_back(bullet);
    Mix_Chunk* bul1= Mix_LoadWAV("Music/Enemyhit.wav");
    Mix_PlayChannel(1, bul1, 0);
}

void Enemy::reduceHealth(vector<Enemy*> &enemies, int i)
{
    health--;
}

vector<Bullet*>& Enemy::getBullets()
{
    return(bullets);
}

void Enemy::setBullets(vector<Bullet*> enemyBullets)
{
    bullets = enemyBullets;
}

int Enemy::getScaleCount()
{
    return(scaleCount);
}

Enemy::~Enemy()
{
    
}
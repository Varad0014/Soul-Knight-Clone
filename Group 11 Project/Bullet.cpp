#include "Bullet.h"
#include "Enemy.h"

Bullet::Bullet(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int eX, int eY, int xD, int yD, double dist)
: GameObject(texturesheet, x, y, w, h, parts, rows, cols)
{
    xDiff = xD;
    yDiff = yD;
    distance = dist;
    enemyX = eX;
    enemyY = eY;
    
}

void Bullet::shotBulletMovement(int shiftX, int shiftY)
{
    enemyX = enemyX + shiftX*GameObject::stepSize;
    enemyY = enemyY + shiftY*GameObject::stepSize;
    if(enemyX > xpos)
    {
        xpos += ceil(stepSize*(xDiff/distance));
    }
    if(enemyX < xpos)
    {
        xpos -= ceil(stepSize*(xDiff/distance));    
    }

    if(enemyY > ypos)
    {
        ypos += ceil(stepSize*(yDiff/distance));
    }
    if(enemyY < ypos)
    {
        ypos -= ceil(stepSize*(yDiff/distance));
    }
    if(xpos == enemyX && ypos == enemyY)
        reachedDest = true;
  
}


void Bullet::update(int shiftX, int shiftY)
{
    Texture->makeSourceRectangle(0, 0);
    updateDestRect();
    shotBulletMovement(shiftX, shiftY);
    counter++;
    
}

void Bullet::Render()
{
    GameObject::Render(false);
    
}

bool Bullet::reachDest()
{
    return(reachedDest);
}
bool Bullet::exceededMaxTime()
{
    if(counter >= 30)
        return(true);
}


void Bullet::addRelX(int x)
{
    xpos += GameObject::stepSize*x;
}

void Bullet::addRelY(int x)
{
    ypos += GameObject::stepSize*x;
}

SDL_Rect* Bullet::getDestRect()
{
    return(&destRect);
}
#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "HealthBar.h"
#include "PlayerHealth.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include<vector>
using namespace std;

Player::Player(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int mHealth)
:GameObject(texturesheet, x, y, w, h, parts, rows, cols) {
    maxHealth = mHealth;
    health = maxHealth;
    healthBar = new PlayerHealth("Images/healthbarPlayer.png", 10, 10, 129, 37, 6, 6, 1, maxHealth, this);
}

void Player::update() 
{
    // updates column in every frame
    colControl = (colControl == (animationControl*6 - 1) ? 0 : colControl + 1);
    colNo = colControl/animationControl;
    rowNo = 2*rowUpFlag + rowLeftFlag;
    updateDestRect(); 
    Texture->makeSourceRectangle(rowNo, colNo);
    for(int i=0 ; i<bullets.size() ; i++)
    {
        if(bullets[i])
            bullets[i] -> update(0, 0);
    }    
    healthBar -> update();
}

// set flipflag
void Player::setFlipFlag(bool flag) {
    flipFlag = flag;
}

// get flipFlag
bool Player::getFlipFlag() {
    return flipFlag;
}

SDL_Rect* Player::getDestRect()
{
    return(&destRect);
}

void Player::reduceHealth()
{
    health -= 1;
}

int Player::getHealth()
{
    return(health);
}
// set rowControl (left, up)
void Player::setRowControl(int leftFlag, int upFlag) {
    rowLeftFlag = leftFlag;
    rowUpFlag = upFlag;
}

// get flags
pair<int, int> Player::getFlags() {
    return make_pair(rowLeftFlag, rowUpFlag);
}

void Player::Render()
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
pair<int, int> Player::GetCoords() {
    return (make_pair(xpos, ypos));
}

void Player::shootBullet(vector<Enemy*> &enemies)
{

    
        Enemy *enemy = NULL, *targetEnemy = NULL;
        int targetXdist, targetYdist, enemyX, enemyY, yDiff, xDiff, eX, eY;
        double distance, minDist;
        if(enemies.size()>0)
        {
            int i=0;
            while(enemies[i] == NULL && i<enemies.size())
                i++;
            if(i<enemies.size())
                enemy = targetEnemy = enemies[i];
        }
        
        if(enemy)
        {
            pair<int, int> enemyCoord = enemy->GetCoords();
            enemyX = enemyCoord.first;
            enemyY = enemyCoord.second;
            
            yDiff = abs(ypos - enemyY);

            
            xDiff = abs(xpos - enemyX);
            
            targetXdist = xDiff;
            targetYdist = yDiff;
            distance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
            minDist = distance;
        }
        for(int i=1 ; i<enemies.size() ; i++)
        {
            enemy = enemies[i];
            if(enemy)
            {
                pair<int, int> enemyCoord = enemy->GetCoords();
                enemyX = enemyCoord.first;
                enemyY = enemyCoord.second;
                yDiff = abs(ypos - enemyY);
                xDiff = abs(xpos - enemyX);
                distance = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
                if(distance < minDist)
                {
                    minDist = distance;
                    targetEnemy = enemy;
                    targetXdist = xDiff;
                    targetYdist = yDiff;
                    
                }
            }
            
        }
        if(targetEnemy)
        {
            Bullet* bullet = new Bullet("Images/bullet.png", xpos, ypos, 15, 12, 1, 1, 1, targetEnemy -> GetCoords().first, targetEnemy -> GetCoords().second, targetXdist, targetYdist, minDist);
            bullets.push_back(bullet);
        }
}   

void Player :: reset()
{
    colControl = 0;
    colNo = 0;
    rowNo = 0;
    rowLeftFlag = 0;
    rowUpFlag = 0;
}

vector<Bullet*>& Player::getBullets()
{
    return(bullets);
}

Player::~Player()
{

}
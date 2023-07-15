#include "EnemyHealth.h"
#include "HealthBar.h"
#include "Enemy.h"
using namespace std;

EnemyHealth::EnemyHealth(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int max_health, Enemy* e)
: HealthBar(texturesheet, x, y, w, h, parts, rows, cols)
{
    enemy = e;
    maxHealth = max_health;
}

void EnemyHealth::update()
{
    int rowNo = 0;
    updateCoord();
    if(enemy -> getHealth() <= maxHealth/2)
        rowNo = 1;
    Texture -> makeSourceRectangle(rowNo, 0); //toggle first number to change health
    updateDestRect();
}

void EnemyHealth::updateCoord()
{
    pair<int, int> enemyCoord = enemy -> GetCoords();
    xpos = enemyCoord.first - 5;
    ypos = enemyCoord.second - 10;
}
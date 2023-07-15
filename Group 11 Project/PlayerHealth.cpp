#include "PlayerHealth.h"
#include "HealthBar.h"
#include "Player.h"

PlayerHealth::PlayerHealth(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols, int max_health, Player* p)
:HealthBar(texturesheet, x, y, w, h, parts, rows, cols)
{
    player = p;
    maxHealth = max_health;
}


void PlayerHealth::update()
{
    
    int health = player -> getHealth();
    if(health == 2)
        rowNo = 3;
    else if(health == 1)
        rowNo = 1;

    Texture -> makeSourceRectangle(rowNo, 0); // toggle first number to change health
    updateDestRect();
}
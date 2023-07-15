#include "HealthBar.h"
#include "Enemy.h"

HealthBar::HealthBar(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols)
: GameObject(texturesheet, x, y, w, h, parts, rows, cols) {}

void HealthBar::Render()
{
    GameObject::Render(false);
}
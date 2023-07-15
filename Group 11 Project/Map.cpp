#include "Map.h"

Map::Map(const char *texturesheet, int x, int y, int w, int h, int parts, int rows, int cols)
:GameObject(texturesheet, x, y, w, h, parts, rows, cols) {
    PX = x;
    PY = y;
    camera = new Camera(w/scale_factor, h/scale_factor, PX - w/(2*scale_factor), PY - h/(2*scale_factor));
    destRect = {0, 0, width, height};
}

// update the camera
void Map::UpdateCamera() {
    xpos = PX - width/(2*scale_factor);
    ypos = PY - height/(2*scale_factor);

    // update the coordinates of the camera
    camera->UpdateCoords(xpos, ypos); 
}

void Map::update() {
    UpdateCamera();
}

// render overload
void Map::Render(bool flipFlag) {
    SDL_Rect srcRect = camera->GetSrcRect();
    Texture->render(&destRect, &srcRect, flipFlag);
}

// get coords
pair<int, int> Map::getCoords() {
    return make_pair(PX, PY);
}

// detect collision
bool Map::detectCollision(int x, int y) {
    bool success = true;
    int rowNo = y/16;
    int colNo = x/16;

    if(CollisionArray[rowNo][colNo] != 0) {
        success = false;
        cout << success << endl;
    }

    return success;
}

// update PX and PY, -1 1
void Map::updatePX(int x) {
    if(detectCollision(PX + x*stepSize, PY))
        PX += x*stepSize;
}

void Map::updatePY(int x) {
    if(detectCollision(PX, PY + x*stepSize))
        PY += x*stepSize;
}

void Map :: reset() {
    PX = start_x;
    PY = start_y;
}
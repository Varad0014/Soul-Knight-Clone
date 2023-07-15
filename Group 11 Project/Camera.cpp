#include "Camera.h"

Camera::Camera(int width, int height, int x, int y) {
    // initialise all variables
    this->width = width;
    this->height = height;
    SrcRect.x = x;
    SrcRect.y = y;
    SrcRect.w = width;
    SrcRect.h = height;
}

// get the destination rectangle
SDL_Rect Camera::GetSrcRect() {
    return SrcRect;
}

// update the coords of the camera
void Camera::UpdateCoords(int x, int y) {
    SrcRect.x = x;
    SrcRect.y = y;
}
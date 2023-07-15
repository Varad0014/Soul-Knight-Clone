#pragma once

#include<string>
#include<SDL2/SDL_image.h>

class MenuObject : public GameObject
{
    private:
    int rowNo,colNo,noOfMenus,diff;
    SDL_Rect option;

    public:
    MenuObject(const char*,int,int,int,int,int,int,int,int);
    void Render();
    int mouse_check(int,int);           // returns menuoption which the mouse is present in
    int keyboard_check();               // returns menuoption which keyboard input has selected
    void move_option_down();            // switch menu option selected downwards
    void move_option_up();              // switch menu option selected upwards
    void mouse_motion_option(int,int);  // switch menu option based on mouse motion
    ~MenuObject();
};

// let's use enter/z to select menu option
// x for exit out of option in case
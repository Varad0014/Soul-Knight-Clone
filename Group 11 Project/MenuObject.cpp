#include"GameObject.h"
#include"MenuObject.h"
#include"TextureManager.h"
#include<SDL2/SDL.h>

MenuObject::MenuObject(const char* texturesheet,int pos_x,int pos_y,int width,int height,int parts,int rows,int cols,int menus)
: GameObject(texturesheet,pos_x,pos_y,width,height,parts,rows,cols) 
{
    noOfMenus = menus;
    rowNo = 0;
    colNo = 0;
    diff = 7;
    
    option = {destRect.x + diff,destRect.y + diff,destRect.w - 2*diff,(destRect.h/noOfMenus) - 2*diff};
}

// returns menuoption which the mouse is present in
int MenuObject :: mouse_check(int mouse_x,int mouse_y)
{   
    for(int counter = 0;counter < noOfMenus;counter++)
    {
        if((destRect.x <= mouse_x && destRect.x + destRect.w >= mouse_x) && (destRect.y + (destRect.h/noOfMenus*counter) <= mouse_y && destRect.y + (destRect.h/noOfMenus * (counter + 1)) >= mouse_y))
            return ++counter;
    }
    return 0;
}

// returns menuoption which keyboard input has selected
int MenuObject :: keyboard_check()
{
    for(int counter = 0;counter < noOfMenus;counter++)
    {
        if((destRect.x <= option.x && destRect.x + destRect.w >= option.x) && (destRect.y + (destRect.h/noOfMenus*counter) <= option.y && destRect.y + (destRect.h/noOfMenus * (counter + 1)) >= option.y))
            return ++counter;
    }
    return 0;
}

void MenuObject :: Render()
{
    GameObject :: Render(false);
    SDL_SetRenderDrawColor(TextureManager :: renderer,140,146,172,255);
    if(SDL_RenderDrawRect(TextureManager :: renderer,&option) != 0)
    {
        cout << "Not able to draw rectangle border " << SDL_GetError() << endl;
    }
}

// switch menu option selected downwards
void MenuObject :: move_option_down()
{
    if(keyboard_check() == noOfMenus)
        option.y = destRect.y + diff;
    else
        option.y += destRect.h/noOfMenus;
}

// switch menu option selected upwards
void MenuObject :: move_option_up()
{
    if(keyboard_check() == 1)
        option.y = destRect.y + (noOfMenus-1) * (destRect.h/noOfMenus) + diff;
    else
        option.y -= destRect.h/noOfMenus;
}

// switch menu option based on mouse motion
void MenuObject :: mouse_motion_option(int mouse_x,int mouse_y)
{
    int i = mouse_check(mouse_x,mouse_y);
    if(i != 0)
    {
        option.y = destRect.y + (i - 1) * (destRect.h/noOfMenus) + diff;
    }
}

MenuObject :: ~MenuObject()
{

}
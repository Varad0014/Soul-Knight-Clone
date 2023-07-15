#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "Game.h"
#include <iostream>
using namespace std; 

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *backgroundSound =Mix_LoadMUS("Music/bgm.mp3");
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    long long frameStart;
    int frameTime;
    Game *game = new Game(); //Game*game
    Mix_PlayMusic(backgroundSound,-1);
    // title, title_xcoord, title_ycoord, screenWidth, screenHeight, fullscreen
    game->init("Silent Assassin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, true);
    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }
    game->clean();
    Mix_FreeMusic(backgroundSound);
    Mix_CloseAudio();
    return 0;
}

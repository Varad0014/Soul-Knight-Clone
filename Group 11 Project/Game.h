#pragma once

#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

enum screen_state
{
    START_MENU,
    GAMEPLAY,
    INSTRUCTIONS,
    LEADERBOARD,
    PAUSE_MENU,
    GAME_OVER
};

class Game
{
    private:
    int scene_state;

    protected: 
        int cnt = 0, counter = 0, count = 0;
        bool isRunning;
        SDL_Window *window;
        int windowWidth;
        int windowHeight;

    public:
        SDL_Renderer *renderer;
        Game();
        ~Game();

        void init(const char *title, int x, int y, int width, int height, bool fullscreen);
        void handleEvents();
        void handleKeyDownEvents();
        void update();
        void render();
        void clean();
        void renderCollision();
        void createEnemies();
        void checkCollision();
        bool running() { return isRunning; }
        bool hasCollided(SDL_Rect *destRect1, SDL_Rect *destRect2);
        void leaderboard();
        void storeScore();
        void change_scene();
    private:
        int maxEnemies = 10;
        int game_score;
        std::string name;
        bool write_name;
        int record_count;
};

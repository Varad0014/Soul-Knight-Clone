#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Map.h"
#include "MenuObject.h"
#include "scoreboard.h"
#include <fstream>
#include <vector>
#include <SDL2/SDL.h> //
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
using namespace std;

Player *player;
GameObject *start_menu_background,*game_over_background,*instr_background,*leaderboard_background,*background;
GameObject *score,*enter_name,*leaderboard_text;
MenuObject *start_menu,*pause_menu;
Map* map;
vector<Enemy*> enemies;
Game::Game() {}
void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen)
{
    scene_state = START_MENU;
    windowWidth = width;
    windowHeight = height;
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() != -1)
    {
        cout << "Subsystem Initialised\n";

        window = SDL_CreateWindow(title, x, y, width, height, flags);
        if (window)
            cout << "Window Created\n";
        else {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created\n";
        }
        else {
            cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        }
        isRunning = true;
    }
    else
        isRunning = false;
    TextureManager::setRenderer(renderer);
    player = new Player("Images/Character1SpritesWalking.png", 400, 320, 44, 66, 24, 4, 6, 3);
    map = new Map("Images/NewMap.png", 256, 208, windowWidth, windowHeight, 1, 1, 1);
    leaderboard_background = new GameObject("Images/Menu_Background.jpeg", 275, 0, 250, windowHeight, 1, 1, 1);
    instr_background = new GameObject("Images/finalins.png", 0, 0, windowWidth, windowHeight, 1, 1, 1);
    start_menu_background = new GameObject("Images/Start_Background.png", 0, 0, windowWidth, windowHeight, 1, 1, 1);
    game_over_background = new GameObject("Images/GameOver.jpeg", 0, 0, windowWidth, windowHeight, 1, 1, 1);
    start_menu = new MenuObject("Images/Start_Menu.jpeg",windowWidth/2 - 90,350,180,200,1,1,1,4);
    pause_menu = new MenuObject("Images/Pause_Menu.jpeg",windowWidth/2 - 90,250,180,160,1,1,1,2);
    leaderboard_text = new GameObject("TTF/Yagora.ttf",50,"Leaderboard",{255,255,255},300,50,windowWidth - 600,50);

    background = start_menu_background;
    score = NULL;
    enter_name = NULL;
    name = "Enter Name";
    game_score = 0;
    record_count = 9;
    write_name = false;
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    bool scene_change = false;
    int which_option;

    if(scene_state == START_MENU)
    {
        switch(event.type)
        {
            case SDL_QUIT:
            isRunning = false;
            break;

            case SDL_KEYDOWN:
            if(keyState[SDL_SCANCODE_ESCAPE] != 0)
                isRunning = false;
            else if(keyState[SDL_SCANCODE_DOWN] != 0)
            {
                start_menu->move_option_down();
            }
            else if(keyState[SDL_SCANCODE_UP] != 0)
            {
                start_menu->move_option_up();
            }
            if(write_name == false)
            {
                if(keyState[SDL_SCANCODE_Z] != 0 || keyState[SDL_SCANCODE_KP_ENTER])
                {
                    switch(start_menu->keyboard_check())
                    {
                        case 1: // GAMEPLAY
                        scene_state = GAMEPLAY;
                        scene_change = true;
                        break;

                        case 2: // INSTRUCTIONS
                        scene_state = INSTRUCTIONS;
                        scene_change = true;
                        break;

                        case 3: // LEADERBOARD
                        scene_state = LEADERBOARD;
                        scene_change = true;
                        break;

                        case 4: // EXIT
                        isRunning = false;
                        break;

                        default:
                        break;
                    }
                }
            }
            else
            {
                // taking input of name
                if(name == " ")
                    name = "";
                if(keyState[SDL_SCANCODE_BACKSPACE] != 0 && name.length() > 0)
                {
                    name.pop_back();
                }
                else if(keyState[SDL_SCANCODE_A])
                    name += 'a';
                else if(keyState[SDL_SCANCODE_B])
                    name += 'b';
                else if(keyState[SDL_SCANCODE_C])
                    name += 'c';
                else if(keyState[SDL_SCANCODE_D])
                    name += 'd';
                else if(keyState[SDL_SCANCODE_E])
                    name += 'e';
                else if(keyState[SDL_SCANCODE_F])
                    name += 'f';
                else if(keyState[SDL_SCANCODE_G])
                    name += 'g';
                else if(keyState[SDL_SCANCODE_H])
                    name += 'h';
                else if(keyState[SDL_SCANCODE_I])
                    name += 'i';
                else if(keyState[SDL_SCANCODE_J])
                    name += 'j';
                else if(keyState[SDL_SCANCODE_K])
                    name += 'k';
                else if(keyState[SDL_SCANCODE_L])
                    name += 'l';
                else if(keyState[SDL_SCANCODE_M])
                    name += 'm';
                else if(keyState[SDL_SCANCODE_N])
                    name += 'n';
                else if(keyState[SDL_SCANCODE_O])
                    name += 'o';
                else if(keyState[SDL_SCANCODE_P])
                    name += 'p';
                else if(keyState[SDL_SCANCODE_Q])
                    name += 'q';
                else if(keyState[SDL_SCANCODE_R])
                    name += 'r';
                else if(keyState[SDL_SCANCODE_S])
                    name += 's';
                else if(keyState[SDL_SCANCODE_T])
                    name += 't';
                else if(keyState[SDL_SCANCODE_U])
                    name += 'u';
                else if(keyState[SDL_SCANCODE_V])
                    name += 'v';
                else if(keyState[SDL_SCANCODE_W])
                    name += 'w';
                else if(keyState[SDL_SCANCODE_X])
                    name += 'x';
                else if(keyState[SDL_SCANCODE_Y])
                    name += 'y';
                else if(keyState[SDL_SCANCODE_Z])
                    name += 'z';
                else if(keyState[SDL_SCANCODE_SPACE])
                    name += " ";
                if(name == "")
                    name = " ";
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            int mouse_x,mouse_y;
            SDL_GetGlobalMouseState(&mouse_x,&mouse_y);
            if((250 <= mouse_x && 250 + 300 >= mouse_x) && (100 <= mouse_y && 150 >= mouse_y))
            {
                if(name == "Enter Name")
                    name = " ";
                write_name = true;
            }
            else
            {
                if(name == " " && name == "")
                    name = "Enter Name";
                write_name = false;
            }
            switch(start_menu->mouse_check(mouse_x,mouse_y))
            {
                case 1: // GAMEPLAY
                scene_state = GAMEPLAY;
                scene_change = true;
                break;

                case 2: // INSTRUCTIONS
                scene_state = INSTRUCTIONS;
                scene_change = true;
                break;

                case 3: // LEADERBOARD
                scene_state = LEADERBOARD;
                scene_change = true;
                break;

                case 4: // EXIT
                isRunning = false;
                break;

                default:
                break;
            }
            break;

            case SDL_MOUSEMOTION:
            int x,y;
            SDL_GetGlobalMouseState(&x,&y);
            start_menu->mouse_motion_option(x,y);
            break;

            default:
            break;
        }
    }
    else if(scene_state == INSTRUCTIONS)
    {
        switch(event.type)
        {
            case SDL_QUIT:
            isRunning = false;
            break;

            case SDL_KEYDOWN:
            if(keyState[SDL_SCANCODE_X] || keyState[SDL_SCANCODE_Z] || keyState[SDL_SCANCODE_KP_ENTER])
            {
                scene_state = START_MENU;
                scene_change = true;
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            scene_state = START_MENU;
            scene_change = true;
            break;

            default:
            break;
        }
    }
    else if(scene_state == LEADERBOARD)
    {
        switch(event.type)
        {
            case SDL_QUIT:
            isRunning = false;
            break;

            case SDL_KEYDOWN:
            if(keyState[SDL_SCANCODE_X] || keyState[SDL_SCANCODE_Z] || keyState[SDL_SCANCODE_KP_ENTER])
            {
                scene_state = START_MENU;
                scene_change = true;
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            scene_state = START_MENU;
            scene_change = true;
            break;

            default:
            break;
        }
    }
    else if(scene_state == GAMEPLAY)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            if(keyState[SDL_SCANCODE_ESCAPE] != 0)
                isRunning = false;
            else if(keyState[SDL_SCANCODE_X] != 0)
            {
                scene_state = PAUSE_MENU;
                scene_change = true;
            }
            else
                handleKeyDownEvents();
            break;

        default:
            break;
        }
    }
    else if(scene_state == PAUSE_MENU)
    {
        switch(event.type)
        {
            case SDL_QUIT:
            isRunning = false;
            break;

            case SDL_KEYDOWN:
            if(keyState[SDL_SCANCODE_ESCAPE] != 0)
                isRunning = false;
            else if(keyState[SDL_SCANCODE_Z] != 0 || keyState[SDL_SCANCODE_KP_ENTER])
            {
                switch(pause_menu->keyboard_check())
                {
                    case 1: // GAMEPLAY
                    scene_state = GAMEPLAY;
                    scene_change = true;
                    break;

                    case 2: // MAIN MENU
                    scene_state = START_MENU;
                    scene_change = true;
                    break;

                    default:
                    break;
                }
            }
            else if(keyState[SDL_SCANCODE_DOWN] != 0)
            {
                pause_menu->move_option_down();
            }
            else if(keyState[SDL_SCANCODE_UP] != 0)
            {
                pause_menu->move_option_up();
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            int mouse_x,mouse_y;
            SDL_GetGlobalMouseState(&mouse_x,&mouse_y);
            switch(pause_menu->mouse_check(mouse_x,mouse_y))
            {
                case 1: // GAMEPLAY
                scene_state = GAMEPLAY;
                scene_change = true;
                break;

                case 2: // MAIN MENU
                scene_state = START_MENU;
                scene_change = true;
                break;

                default:
                break;
            }
            break;

            case SDL_MOUSEMOTION:
            int x,y;
            SDL_GetGlobalMouseState(&x,&y);
            pause_menu->mouse_motion_option(x,y);
            break;

            default:
            break;
        }
    }
    else if(scene_state == GAME_OVER)
    {
        switch(event.type)
        {
            case SDL_QUIT:
            isRunning = false;
            break;

            case SDL_KEYDOWN:
            if(keyState[SDL_SCANCODE_ESCAPE] != 0)
            {
                isRunning = false;
            }
            else if(keyState[SDL_SCANCODE_Z] != 0 || keyState[SDL_SCANCODE_KP_ENTER] || keyState[SDL_SCANCODE_X])
            {
                scene_state = START_MENU;
                scene_change = true;
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            scene_state = START_MENU;
            scene_change = true;
            break;

            default:
            break;
        }
    }

    if(scene_change)
        change_scene();
    counter++;
}

void Game::handleKeyDownEvents() {

    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_LEFT]) {
        pair<int, int> flags = player->getFlags();
        player->setFlipFlag(true);
        player->setRowControl(1, flags.second);
        map->updatePX(-1);
        for(int i=0 ; i<enemies.size() ; i++)
        {
            if(enemies[i]) 
                enemies[i] -> addRelX(1);
        }
    }
    
    if(keyState[SDL_SCANCODE_RIGHT]) {
        pair<int, int> flags = player->getFlags();
        player->setFlipFlag(false);
        player->setRowControl(1, flags.second);
        map->updatePX(1);
        for(int i=0 ; i<enemies.size() ; i++)
        {
            if(enemies[i]) 
                enemies[i] -> addRelX(-1);
        }
        
    }

    if(keyState[SDL_SCANCODE_UP]) {
        pair<int, int> flags = player->getFlags();
        player->setRowControl(flags.first, 1);
        map->updatePY(-1);
        for(int i=0 ; i<enemies.size() ; i++)
        {
            if(enemies[i]) 
                enemies[i] -> addRelY(1);
        }
    }
    
    if(keyState[SDL_SCANCODE_DOWN]) {
        pair<int, int> flags = player->getFlags();
        player->setRowControl(flags.first, 0);
        map->updatePY(1);
        for(int i=0 ; i<enemies.size() ; i++)
        {
            if(enemies[i]) 
                enemies[i] -> addRelY(-1);
        }
    }

    if (!keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_UP])
    {
        player->setRowControl(0, 0);
    }

    if(keyState[SDL_SCANCODE_SPACE])
    {
        if(counter >= 30)
        {
            cout << "player shoot" << endl;
            counter = 0;
            player->shootBullet(enemies);
            Mix_Chunk* bul1= Mix_LoadWAV("Music/bullet.wav");
            Mix_PlayChannel(0, bul1, 0);
        }
    }
    
}

void Game::render()
{
    SDL_RenderClear(renderer);
    if(scene_state == START_MENU)
    {
        background->Render();
        start_menu->Render();
        SDL_Rect option = {250,100,300,50};
        SDL_SetRenderDrawColor(TextureManager :: renderer,140,146,172,255);
        if(SDL_RenderDrawRect(TextureManager :: renderer,&option) != 0)
        {
            cout << "Not able to draw rectangle border " << SDL_GetError() << endl;
        }
        if(enter_name != NULL)
            delete(enter_name);
        enter_name = new GameObject("TTF/Yagora.ttf",50,name,{255,255,255},250,100,300,50);
        enter_name->Render();
    }
    else if(scene_state == INSTRUCTIONS)
    {
        background->Render();
    }
    else if(scene_state == LEADERBOARD)
    {
        background->Render();
        leaderboard_background->Render();
        leaderboard_text->Render();
        leaderboard();
    }
    else if(scene_state == GAMEPLAY)
    {
        map->Render();
        player->Render();
        for(int i=0;i<enemies.size();i++)
        {
            if(enemies[i])
                enemies[i]->Render();
        }
        if(score != NULL)
            delete(score);
        score = new GameObject("TTF/Yagora.ttf",30,"Score: " + to_string(game_score),{255,255,255},675,50,100,100); 
        score->Render();
    }
    else if(scene_state == PAUSE_MENU)
    {
        map->Render();
        player->Render();
        for(int i=0;i<enemies.size();i++)
        {
            if(enemies[i])
                enemies[i]->Render();
        }
        score->Render();
        pause_menu->Render();
    }
    else if(scene_state == GAME_OVER)
    {
        background->Render();
        score->Render();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    delete(player);
    delete(map);
    delete(leaderboard_background);
    delete(instr_background);
    delete(start_menu_background);
    delete(game_over_background);
    delete(start_menu);
    delete(pause_menu);
    delete(leaderboard_text);

    player = NULL;
    map = NULL;
    leaderboard_background = NULL;
    instr_background = NULL;
    start_menu_background = NULL;
    game_over_background = NULL;
    start_menu = NULL;
    pause_menu = NULL;
    leaderboard_text = NULL;

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_QUIT;
    cout << "Game Cleaned\n";
}

void Game::update()
{
    if(player -> getHealth() == 0)
    {
        scene_state = GAME_OVER;
        change_scene();
    }

    if(scene_state == START_MENU)
    {
        background->update();
        start_menu->update();
    }
    else if(scene_state == INSTRUCTIONS)
    {
        background->update();
    }
    else if(scene_state == LEADERBOARD)
    {
        background->update();
        instr_background->update();
    }
    else if(scene_state == GAMEPLAY)
    {
        player->update();
        map->update();
        createEnemies();
        checkCollision();
        for(int i=0;i<enemies.size();i++)
        {
            if(enemies[i])
                enemies[i]->update();
        }
        score->update();
    }
    else if(scene_state == PAUSE_MENU)
    {
        pause_menu->update();
    }
    else if(scene_state == GAME_OVER)
    {
        background->update();
        score->update();
    }
}

void Game :: change_scene()
{
    if(scene_state == START_MENU)
    {
        background = start_menu_background;
        player->reset();
        map->reset();
        for(int i = 0;i < enemies.size();i++)
        {
            if(enemies[i] != NULL)
                delete(enemies[i]);
        }
        enemies.clear();
    }
    else if(scene_state == INSTRUCTIONS)
    {
        background = instr_background;
    }
    else if(scene_state == LEADERBOARD)
    {
        background = start_menu_background;
    }
    else if(scene_state == GAMEPLAY)
    {
        if(score != NULL)
            delete(score);
        score = new GameObject("TTF/Yagora.ttf",30,"Score: " + to_string(game_score),{255,255,255},675,50,100,100);
    }
    else if(scene_state == GAME_OVER)
    {
        background = game_over_background;
        if(score != NULL)
            delete(score);
        score = new GameObject("TTF/Yagora.ttf",40,"Score: " + to_string(game_score),{255,255,255},350,350,100,100); // need to get final score to display
        storeScore();
    }
}

void Game :: leaderboard()
{
    int x = 300;
    int y = 50;
    int width = windowWidth - 2*x;
    int height = 50;
    int stepsize = 50;
    int count = 1;
    scoreboard temp;
    ifstream rf;
    rf.open("Data/Scoreboard.dat",ios::binary | ios::in);
    if(!rf)
    {
        return;
    }

    while(rf.read((char*)&temp,sizeof(temp)))
    {
        string hmm = temp.name;
        GameObject hi("TTF/Yagora.ttf",50,to_string(count) + ") " + hmm + " - " + to_string(temp.score),{255,255,255},x,y + count*stepsize,width,height);
        hi.Render();
        count++;
    }
    rf.close();
}

void Game :: storeScore()
{
    scoreboard temp;
    scoreboard old[9];
    for(int i = 0;i < sizeof(temp.name)/sizeof(char);i++)
    {
        temp.name[i] = name[i];
    }
    temp.rank = 1;
    temp.score = game_score;
    ifstream rf;
    rf.open("Data/Scoreboard.dat",ios::binary | ios::in);
    int i = 0;
    while(rf.read((char*)&old[i],sizeof(temp)))
    {
        i++;
    }
    rf.close();

    int count = 0;
    while(count < i)
    {
        if(temp.score >= old[count].score)
        {
            break;
        }
        count++;
    }
    temp.rank = count + 1;

    ofstream wf;
    wf.open("Data/Scoreboard.dat",ios::binary | ios::out);
    if(!wf)
    {
        return;
    }
    for(int j = 0;j < record_count && j <= i;j++)
    {
        if(j < count)
        {
            wf.write((char*)&old[j],sizeof(temp));
        }
        else if(j == count)
        {
            wf.write((char*)&temp,sizeof(temp));
        }
        else
        {
            wf.write((char*)&old[j-1],sizeof(temp));
        }
    }
    wf.close();
}

void Game::createEnemies()
{
    static int counter = 0;
    if(enemies.size() < maxEnemies && counter >= 180)
    {
        enemies.push_back(Enemy::generateEnemy(player, 300, 300));
        counter = 0;
    }
    counter++;
}


void Game::checkCollision()
{
    vector<Bullet*>& bullets = player -> getBullets();
    if(enemies.size()>=2)
    {
        int s = enemies.size();
        for(int i=0;i<s;i++){
            for(int j=0;j<s;j++){
                if(j!=i){
                    if(enemies[i]&&enemies[j]){
                        if(hasCollided(enemies[i] -> getDestRect(), enemies[j] -> getDestRect())){
                     
                            pair<int, int> coord1 = enemies[i] -> GetCoords();
                            pair<int, int> coord2 = enemies[j] -> GetCoords();
                            
                            pair<int, int> dim1 = enemies[i] -> GetDims();
                            pair<int, int> dim2 = enemies[j] -> GetDims();

                            int x1, x2, y1, y2, w1, w2, h1, h2, w, h, sc1, sc2;
                            w1 = dim1.first;
                            h1 = dim1.second;
                            sc1 = enemies[i] -> getScaleCount();
                            w2 = dim2.first;
                            h2 = dim2.second;
                            sc2 = enemies[i] -> getScaleCount();
                            w = (w1>w2)? w1 : w2;
                            h = (h1>h2)? h1 : h2;
                            w*=1.4; 
                            h*=1.4;
                           
                            Enemy *enemynew = new Enemy("Images/EnemySprite.png", (coord1.first + coord2.first)/2, (coord1.second + coord2.second)/2, w, h, 4, 1, 4, 4, sc1+sc2, player); 
                            vector<Bullet*> newBullets;
                            vector<Bullet*> &enemy1Bullets = enemies[i] -> getBullets();
                            vector<Bullet*> &enemy2Bullets = enemies[j] -> getBullets();
                            for(int k=0 ; k<enemy1Bullets.size() ; k++)
                            {
                                if(enemy1Bullets[k])
                                    newBullets.push_back(enemy1Bullets[k]);
                            }
                            for(int k=0 ; k<enemy2Bullets.size() ; k++)
                            {
                                if(enemy2Bullets[k])
                                    newBullets.push_back(enemy2Bullets[k]);
                            }

                            enemynew -> setBullets(newBullets);

                            delete(enemies[i]);
                            delete(enemies[j]);

                            enemies[i] = NULL;
                            enemies[j] = NULL;
                            enemies.push_back(enemynew);
                        }    

                    }
                }
            }
            
            
        }
        
    }

    if(enemies.size()>0)
    {
        for(int i=0 ; i<enemies.size() ; i++)
        {
            if(enemies[i])
            {
                
                vector<Bullet*> &enemyBullets = enemies[i] -> getBullets();
                for(int j=0 ; j<enemyBullets.size() ; j++)
                {
                    if(enemyBullets[j])
                    {
                        if(hasCollided(enemyBullets[j] -> getDestRect(), player -> getDestRect()))
                        {
                            delete(enemyBullets[j]);
                            enemyBullets[j] = NULL;
                            player -> reduceHealth();
                           
                           
                        }
                    }
                }
                for(int j=0 ; j<bullets.size() ; j++)
                {

                    if(bullets[j])
                    {
                        if(hasCollided(enemies[i] -> getDestRect() , bullets[j] -> getDestRect()))
                        {
                            delete(bullets[j]);
                            bullets[j] = NULL;
                            enemies[i] -> reduceHealth(enemies, i);
                            if(enemies[i] -> getHealth() == 0)
                            {
                                game_score+= enemies[i] -> getScaleCount();
                                delete(enemies[i]);
                                enemies[i] = NULL;
                            }
                        }
                    }
                }

                
            }
        }
    }
    for(int i=0 ; i<bullets.size() ; i++)
    {
        if(bullets[i])
        {
            if(bullets[i] -> exceededMaxTime() || bullets[i] -> reachDest())
            {
                delete(bullets[i]);
                bullets[i] = NULL;
            }
        }
    }

    for(int i=0 ; i<enemies.size() ; i++)
    {
        if(enemies[i])
        {
            vector<Bullet*> &enemyBullets = enemies[i] -> getBullets();
            for(int j=0 ; j<enemyBullets.size() ; j++)
            {
                if(enemyBullets[j])
                {
                    if(enemyBullets[j] -> exceededMaxTime() || enemyBullets[j] -> reachDest()) 
                    {
                        delete(enemyBullets[j]);
                        enemyBullets[j] = NULL;
                    }
                }
            }
        }
    }

    for(int i=0 ; i<enemies.size() ; i++)
    {
        if(enemies[i])
        {
            if(hasCollided(enemies[i] -> getDestRect() , player -> getDestRect()))
            {
                scene_state = GAME_OVER;
                change_scene();
            }
        }
    }
    
}

bool Game::hasCollided(SDL_Rect *destRect1, SDL_Rect *destRect2)
{
    bool collided = !(destRect2->x > (destRect1->x + (destRect1->w)) || 
           (destRect2->x + (destRect2->w)) < destRect1->x || 
           destRect2->y > (destRect1->y + (destRect1->h)) ||
           (destRect2->y + (destRect2->h)) < destRect1->y);
    return(collided);
}

void Game::renderCollision() {
    TextureManager *texture = new TextureManager();
    texture->loadTexture("Images/FiniteMap.png", 1, 1, 1);
    SDL_Rect temp;
    int scale_factor = 2;
    int xpos = map->PX - windowWidth/(2*scale_factor);
    int ypos = map->PY - windowHeight/(2*scale_factor);
    xpos /= 16;
    ypos /= 16;
    int finalX = xpos + 400;
    int finalY = ypos + 320;

    for(int i = xpos;i < finalX;i++) {
        for(int j = ypos;j < finalY;j++) {
            if(map->CollisionArray[i][j] != 0) {
                temp = {j*16, i*16, 32, 32};
                texture->render(&temp);
            }
        }
    }
}
#ifndef BASE_FUCTION_H
#define BASE_FUCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <fstream>
#include "BaseObject.h"
#include <vector>
#include <windows.h>
#include <time.h>

//screen
const int FRAME_PER_SECOND = 30;// fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int COLOR_KEY_R=167;
const int COLOR_KEY_G=175;
const int COLOR_KEY_B=180;
const int RENDER_DRAW_COLOR=0xff;


static  SDL_Window* g_window = NULL;
static  SDL_Renderer* g_screen = NULL;

static  SDL_Event g_event;

static Mix_Chunk* g_sound_jump;
static Mix_Chunk* g_sound_shoot;
static Mix_Chunk* g_back_sound;
static Mix_Chunk* g_lose_game;
static Mix_Chunk* g_win_game;
static Mix_Chunk* g_hit;
static Mix_Chunk* g_get_hit;
static Mix_Chunk* g_coin;
//Map
#define TILE_SIZE 64
#define MAP_MAX_X 400
#define MAP_MAX_Y 10

#define STATE_MONEY 4
//Tile
#define BLANK_TILE 0
#define HEAD_TILE 14
struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAP_MAX_Y][MAP_MAX_X]; 
//  char* file_name_;
};

struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int fire_;
};

namespace SDLBasefuction
{
    bool  CheckColli(const SDL_Rect& object1,const SDL_Rect& object2 );
    bool  CheckMousePos(const int& x,const int& y,const SDL_Rect& Obj_);
    bool  Menu(SDL_Renderer* g_screen);
}

#endif
#include "game_map.h"

//load thong tin tu file name vao tile
void GameMap::LoadMap(std::string name) // Load map data from file
{
    std::ifstream file(name);
    if (!file.is_open())
    {
        std::cout << "Can't not open file "<< name <<" to load map"  << std::endl;
        return;
    }
    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;
    for (int i = 0; i < MAP_MAX_Y; i++)
    {
        for (int j = 0; j < MAP_MAX_X; j++)
        {
            file >> game_map_.tile[i][j];
            int val = game_map_.tile[i][j];
            if (val > 0)
            {
                // thiet lap max x va max y
                if (j > game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }

                if (i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
    }
    //chuyen ve dang pixel , cong them mot de cho map to hon map goc, khi load len man hinh se k bi thieu anh 
    game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    file.close();
}
//nhap du lieu anh cho tung o
void GameMap::LoadTiles(SDL_Renderer *screen)  //load map to texture
{
    char file_img[30];
    FILE *fp = NULL;

    for (int i = 0; i < MAX_TILE; i++)
    {
        sprintf(file_img, "map//%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if (fp == NULL)
        {
            continue;
        }
        fclose(fp);

        tile_mat[i].LoadImg(file_img, screen);
    }
}
//ve len man hinh
void GameMap::DrawMap(SDL_Renderer *screen) // Render map
{
    // vi tri  de load anh
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_ / TILE_SIZE;
    x1 = (game_map_.start_x_ % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y_ / TILE_SIZE;
    y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_ / TILE_SIZE;
        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];
            if (val > 0)
            {
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);
            }
            map_x++;
        }
        map_y++;
    }
}
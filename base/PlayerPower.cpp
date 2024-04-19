#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
    number_ = 0;   
}
PlayerPower::~PlayerPower()
{
   
}

void PlayerPower::Add_pos(const int& xp)
{
    pos_list.push_back(xp);
}

void PlayerPower::Init(SDL_Renderer* screen)
{
    LoadImg("img//hp.png", screen);
    number_ = 3;
    if(pos_list.size() > 0)
    {
        pos_list.clear();
    }

    Add_pos(30);
    Add_pos(70);
    Add_pos(120);
}

void PlayerPower::Decrease()
{
    number_--;
    pos_list.pop_back();
}

void PlayerPower::Increase()
{
    number_++;
    int last_pos = pos_list.back();
    last_pos += 40;
    pos_list.push_back(last_pos);
}

void PlayerPower::Show(SDL_Renderer* screen)
{
    for(int i = 0;i  < pos_list.size(); i++)
    {
        rect_.x = pos_list.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

Coin::Coin()
{
    x_pos = 0;
    y_pos = 0;
}

Coin::~Coin()
{
    
}

void Coin::Init(SDL_Renderer* screen,std::string path)
{
    LoadImg(path,screen);
}


void Coin::Show(SDL_Renderer* screen)
{
    rect_.x  = x_pos;
    rect_.y = y_pos;
    Render(screen);
}
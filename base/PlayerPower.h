#ifndef PLAYER_POWER_H_
#define PLAYER_POWER_H_
#include "basefuction.h"
#include "BaseObject.h"

class PlayerPower : public BaseObject
{
public:
    PlayerPower();
    ~PlayerPower();

    void Set_Num(const int &num) {number_ = num;}
    void Add_pos(const int &num);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void Increase();
    void Decrease();

private:
    int number_;
    std::vector<int> pos_list;
};

class Coin : public BaseObject
{
public:
    Coin();
    ~Coin();
    
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen, std::string path);
    void Set_Pos(const int& x, const  int& y) {x_pos = x, y_pos = y;}
private:
    int x_pos;
    int y_pos;
};

#endif
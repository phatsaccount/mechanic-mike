#include "Bullet.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = SEED_BULLET;
}

BulletObject::~BulletObject()
{
    
}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if(bullet_type_ == SEED_BULLET)
    {
       ret =  LoadImg("img//bullet.png",des);
    }
    else if(bullet_type_ == YELLOW_BULLET)
    {
        //ret = LoadImg("img//bullet.png",des);
    }
    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if(bullet_dir_ == DIR_RIGHT)
    {
        rect_.x += x_val_;
        
        if(rect_.x  > x_border)
        {
            is_move_ = false;
        }
    }
    else if(bullet_dir_ == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if(rect_.x  < 0 )
        {
            is_move_ = false;
        }
    }
}
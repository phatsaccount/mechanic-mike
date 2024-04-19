#include "DeathAnimation.h"

LoadAnimation::LoadAnimation()
{
    width_frame_  = 0;
    height_frame_ = 0;
    frame_ = 0;
    animation_loop_ = 0;
}

LoadAnimation::~LoadAnimation()
{

}

bool LoadAnimation::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if(ret == true)
    {
        width_frame_ = rect_.w/EX_FRAME_NUM;
        height_frame_ = rect_.h;

    }
    return ret;
}

void LoadAnimation::set_clips() //frame
{
    if(width_frame_ > 0 && height_frame_ >0) 
    {
        for(int i = 0; i < EX_FRAME_NUM; i++)
            {
                frame_clip_[i].x = i*width_frame_;
                frame_clip_[i].y = 0;
                frame_clip_[i].w = width_frame_;
                frame_clip_[i].h = height_frame_;
            }
    }
}


void LoadAnimation::Show(SDL_Renderer* screen)
{   
    SDL_Rect* current_clip = &frame_clip_[frame_];
    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;
    if(frame_ >= EX_FRAME_NUM)
    {
        frame_ = 0;
        animation_loop_++ ;
    }
    SDL_Rect RenderQuard = {rect_.x,rect_.y,width_frame_,height_frame_};
    SDL_RenderCopy(screen, p_object_, current_clip, &RenderQuard);
    frame_++;
}
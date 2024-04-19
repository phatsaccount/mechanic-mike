#ifndef LOAD_ANMIATION_H
#define LOAD_ANMIATION_H
#include "basefuction.h"

#define EX_FRAME_NUM 12
class LoadAnimation : public BaseObject
{
public: 
    LoadAnimation();
    ~LoadAnimation();

    void set_clips();
    virtual bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);

    void set_frame(const int& fr){frame_ = fr;}
    int get_frame() const {return frame_;}

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    void set_x_val(const float& xVal){x_val_ = xVal;}
    void set_y_val(const float& yVal){y_val_ = yVal;}
    void set_x_pos(const float& xPos){x_pos_ = xPos;}
    void set_y_pos(const float& yPos){y_pos_ = yPos;}

    float get_x_val() const {return x_val_;}
    float get_y_val() const {return y_val_;}
    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}

    void SetMapXY(const int& mp_x,const int& mp_y){map_x_ = mp_x,map_y_ = mp_y;}

    int get_animation_loop() const {return animation_loop_;}
protected:
    int width_frame_;
    int height_frame_;
    int frame_;

    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;
    int map_x_;
    int map_y_;
    int animation_loop_;
    SDL_Rect frame_clip_[EX_FRAME_NUM];
};
#endif


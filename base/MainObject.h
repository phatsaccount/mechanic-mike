#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include <vector>
#include "basefuction.h"
#include "BaseObject.h"
#include "Bullet.h"

#define MAX_FALL_SPEED 15
#define GRAVITY_SPEED 2
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 30

class MainObject : public  BaseObject
{
public:
    MainObject();
    ~MainObject();
    enum WalkType
    {
        WALK_NONE =  0,
        WALK_RIGHT = 1,
        WALK_LEFT  = 2,
    };
    virtual bool LoadImg(std::string path,SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events,SDL_Renderer* screen,Mix_Chunk* g_sound_jump,Mix_Chunk* g_sound_shoot);
    void set_clips();
    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x,const int map_y){map_x_ = map_x; map_y_ = map_y; };
    void CenterEntityOnMap(Map& map_data);
    void UpdateImagePlayer(SDL_Renderer *des);
    bool get_on_ground() const{ return on_ground;}
    void set_on_ground(bool on) { on_ground = on;}
    void set_come_back_time(const int& cb ) {come_back_time_ = cb;}
    void set_status_() {status_ = WALK_NONE;}
    void set_input_right(int ip) {input_type_.right_ = ip;}
    void set_input_left(int ip) {input_type_.left_ = ip;}
    SDL_Rect GetRectFrame();


    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void set_x_pos(float px) { x_pos_ = px;}
    void set_y_pos(float py) { y_pos_ = py;}
    void set_y_val(float py) { y_val_ = py;}

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;} 
    void HandeleBullet(SDL_Renderer* des);
    void RemoveBullet(const int& idx);
    void IncreaseMoney();
    void DecreaseBullet();
    void IncreaseBullet();
    int GetMoney() const {return money_count;}
    int GetBullet() const {return bullet_count;}

    void SetBullet(int bl) { bullet_count =  bl;}
    void SetMoney(int mn) { money_count = mn;}

    int Get_hurted()const {return hurted;}
    void Set_hurted(int h) { hurted =h;}
private:
    int bullet_count;
    int money_count;
    int hurted;
    int shoot;
    std::vector<BulletObject*> p_bullet_list_;
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[12];
    Input input_type_;
    int frame_;
    int frame_delay;
    int status_;
    bool on_ground;

    int map_x_;
    int map_y_;
    int come_back_time_;
};
#endif
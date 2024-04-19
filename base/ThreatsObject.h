#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include"basefuction.h"
#include"BaseObject.h"
#include"Bullet.h"


#define THREAT_MAX_FALL_SPEED 10
#define THREAT_GRAVITY_SPEED 2
#define THREAT_FRAME_NUM 12
#define THREAT_SPEED 4

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
        FLY_THREAT = 2,
        SAW_THREAT = 3,
        FALL_THREAT = 4,
        JUMB_THREAT = 5,
        WIN = 6,
    };

    enum WalkType
    {
        WALK_NONE =  0,
        WALK_RIGHT = 1,
        WALK_LEFT  = 2,
    };

    void set_x_val(const float& xval) {x_val_ = xval;}
    void set_y_val(const float& yval) {y_val_ = yval;}


    void set_x_pos(const float& xp) { x_pos_ = xp;}
    void set_y_pos(const float& yp)  {y_pos_ = yp;}
    float get_x_pos() const{return x_pos_;}
    float get_y_pos() const{return y_pos_;}
    void SetMapXY(const int& mp_x,const int& mp_y) {map_x_ = mp_x ; map_y_ = mp_y;}

    void set_clip();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    void BeeDoPlayer(Map& gMap);
    void DoPlayer(Map& gMap);
    void FlyDoPlayer(Map& gMap);
    void FallDoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);




    void InitThreats();
    void set_type_move(const int& typemove) {type_move = typemove;}
    int get_type_move(){ return type_move;}
    bool get_on_ground() {return on_ground_;}
    void setAnimationPos(const int& pos_a ,const int& pos_b) { animation_a_ = pos_a,animation_b_ = pos_b;}
    void Set_input_left(const int& ipleft) { input_type.left_ = ipleft;}
    void Set_input_down(const int& ipdown) { input_type.down_ = ipdown;}
    void Set_input_jumb(const int& ipj) { input_type.jump_ = ipj;}
    void ImpMoveType(SDL_Renderer* screen, Map& map_data);
    void SetDisappear(int d) {disappear = d;}
    SDL_Rect GetRectFrame();

    std::vector<BulletObject*> get_bullet_list() const{return bullet_list;}
    void set_bullet_list(const std::vector<BulletObject*>& bl_list) {bullet_list = bl_list;}

    void InitBullet(BulletObject* p_bullet,SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen , const int& x_limit, const& y_limit );
    void RemoveBullet(const int& idx);

private:

    int check_left;
    int check_right;
    int check_up;
    int check_down;
    int map_x_;
    int map_y_;
    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;
    bool on_ground_;
    int come_back_time_;
    int disappear;
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;

    int type_move;
    int status_;
    int animation_a_;
    int animation_b_;
    Input input_type;

    std::vector<BulletObject*> bullet_list;

};




#endif
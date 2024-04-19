#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include"BaseObject.h"
#include"basefuction.h"

class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum BuletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        // DIR_UP = 22,
        // DIR_UP_LEFT = 23,
        // DIR_UP_RIGHT = 24,
        // DIR_DOWN_LEFT = 25, 
        // DIR_DOWN_RIGHT = 26,
    };

    enum BulletType
    {
        SEED_BULLET = 50,
        YELLOW_BULLET = 51,
    };

    void set_x_val(const int& xVal) {x_val_ = xVal;}
    void set_y_val(const int& yVal) {y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}
    
    void set_is_move(const bool& ismove) {is_move_ = ismove;}
    bool get_is_move() const {return is_move_;}

    void set_bullet_dir(const unsigned int&bulletDir) {bullet_dir_ = bulletDir;}

    void set_bullet_type(const unsigned int& bullettype) { bullet_type_ = bullettype;}
    unsigned int get_bullet_type() const { return bullet_type_;}


    void HandleMove(const int& x_border, const int& y_border);

    bool LoadImgBullet(SDL_Renderer* des);
private:
    int x_val_;
    int y_val_;

    bool is_move_;
    unsigned int bullet_dir_;
    unsigned int bullet_type_;

};

 #endif
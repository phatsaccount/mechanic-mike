#include"ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    check_right = 0;
    check_left = 0;
    check_up = 0;
    check_down = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_  = 0.0;
    y_val_ =0.0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    on_ground_ = 0;
    come_back_time_ = 0;
    frame_ = 0;
    disappear = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type.left_ = 0;
    input_type.jump_ = 0;
    type_move = STATIC_THREAT;

}

ThreatsObject::~ThreatsObject()
{
    
}



bool ThreatsObject::LoadImg(std::string path,SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if(ret)
    {
        width_frame_ = rect_.w/THREAT_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w =  width_frame_;
    rect.h = height_frame_;
    return rect;
}

void ThreatsObject::set_clip()
{
    if(width_frame_ > 0 && height_frame_ > 0)
    {
        for(int i=0; i < 12;i++)
        {
        frame_clip_[i].x = i*width_frame_;
        frame_clip_[i].y = 0;
        frame_clip_[i].w = width_frame_;
        frame_clip_[i].h = height_frame_;
        }
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if(come_back_time_ == 0)
    {
        rect_.x = x_pos_  - map_x_;
        rect_.y = y_pos_  - map_y_;
        frame_++;
        if(frame_ >= 12)
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect rendQuad = {rect_.x , rect_.y,width_frame_,height_frame_};
        SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
    }
}

void ThreatsObject::FallDoPlayer(Map& gMap)
{
    if(come_back_time_ == 0)
    {
        x_val_ = 0;
        
        if(input_type.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if( input_type.right_ == 1)
        {
            x_val_ += THREAT_SPEED;//
        }

        if( input_type.up_ == 1)
        {
            y_val_ = -5;
        }
        else if(input_type.down_ == 1)
        {
            y_val_ += 5;
        }

        CheckToMap(gMap);
    }
    else if(come_back_time_ > 0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
           InitThreats();
        }
    }
    // if(disappear > 0)
    // {
    //     disappear--;
    //     if(disappear == 0)
    //     {
    //         Free();
    //     }
    // }
}

void ThreatsObject::FlyDoPlayer(Map& gMap)
{
    if(come_back_time_ == 0)
    {
        x_val_ = 0;
        
        if(input_type.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if( input_type.right_ == 1)
        {
            x_val_ += THREAT_SPEED;//
        }

        if( input_type.up_ == 1)
        {
            y_val_ = -8;
        }
        else if(input_type.down_ == 1)
        {
            y_val_ = 8;
        }

        CheckToMap(gMap);
    }
    else if(come_back_time_ > 0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
            InitThreats();//
        }
    }
}

void ThreatsObject::DoPlayer(Map& gMap)
{
    if(come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += THREAT_GRAVITY_SPEED;
        if(y_val_ >= THREAT_MAX_FALL_SPEED)
        {
            y_val_ = THREAT_MAX_FALL_SPEED;
        }

        if(input_type.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if( input_type.right_ == 1)
        {
            x_val_ += THREAT_SPEED;//
        }
        else if(input_type.up_ == 1)
        {

        }

        CheckToMap(gMap);
    }
    else if(come_back_time_ > 0)
    {
        come_back_time_--;
        if(come_back_time_ == 0)
        {
            InitThreats();
        }
    }

}

void ThreatsObject::InitThreats()
{
    x_val_ = 0;
    y_val_ = 0;
    if(x_pos_ > 256)
    {
        x_pos_ += 256;
        animation_a_ += 256;
        animation_b_ += 256;
    }
    else
    {
        x_pos_ = 0;
    }
    y_pos_ = 0;
    come_back_time_ = 0;
    input_type.left_ = 0;//hehe
}

void ThreatsObject::CheckToMap(Map& map_data) //xu li va cham
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;


    //Check hoz

    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    x1 = (x_pos_ + x_val_ - 1)/TILE_SIZE;
    x2 = (x_pos_ + x_val_+ width_frame_ -1)/TILE_SIZE;//
    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min -1)/TILE_SIZE;//





    if(x1 >=0 && x2<= MAP_MAX_X && y1 >= 0 && y2 <= MAP_MAX_Y)
    {
        if(x_val_ > 0)
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

                if((val1 != BLANK_TILE && val1 != STATE_MONEY)||( val2 != STATE_MONEY && val2 != BLANK_TILE ))
                {
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_ + 1 ;
                    x_val_ = 0;
                    check_right = 1;
                }
                else check_right = 0;
        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

                if((val1 != BLANK_TILE && val1 != STATE_MONEY)||( val2 != STATE_MONEY && val2 != BLANK_TILE ))
                {
                    x_pos_ = (x1 + 1)*TILE_SIZE;//
                    x_val_ = 0;
                    check_left = 1;
                }
                else check_left = 0;
        }
    }

    //Check ver

    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_ + width_frame_* 0.1)/TILE_SIZE;
    x2 = (x_pos_ + width_frame_  - width_frame_*0.1)/TILE_SIZE;
    y1 = (y_pos_ + y_val_ + height_frame_*0.1)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ -1)/TILE_SIZE;

    

    if(x1 >=0 && x2<= MAP_MAX_X && y1 >= 0 && y2 <= MAP_MAX_Y)
    {
        if(y_val_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            
                //if(y2 == MAP_MAX_Y) check_up = 1;
                if((val1 != BLANK_TILE && val1 != STATE_MONEY)||( val2 != STATE_MONEY && val2 != BLANK_TILE ))
                {
                    y_pos_ = y2*TILE_SIZE;
                    y_pos_ -= height_frame_+1;//
                    y_val_ = 0;
                    on_ground_ = true;
                    check_up = 0;
                    check_down = 1;
                }
                else
                {
                    check_down = 0;
                }
            

            
        }
        else if(y_val_ < 0)
        {
                int val1 = map_data.tile[y1][x1];
                int val2 = map_data.tile[y1][x2];
                
                if((val1 != BLANK_TILE && val1 != STATE_MONEY)||( val2 != STATE_MONEY && val2 != BLANK_TILE ))
                {
                    y_pos_ = (y1 + 1) * TILE_SIZE;//
                    y_val_ = 0;
                    
                }
                //else on_ground_ = false;
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;
    
    // goc trai goc phai
    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ -1;
    }

    if(y_pos_ >= map_data.max_y_ - 65)
    {
        come_back_time_ = 100;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen, Map& map_data)
{
    // int x1 = 0;
    // int x2 = 0;

    // int y1 = 0;
    // int y2 = 0;


    // //Check hoz

    // int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
    // x1 = (x_pos_ + x_val_)/TILE_SIZE;
    // x2 = (x_pos_ + x_val_+ width_frame_ -1)/TILE_SIZE;//
    // y1 = (y_pos_)/TILE_SIZE;
    // y2 = (y_pos_ + height_min -1)/TILE_SIZE;//

    // int val1 = map_data.tile[y1][x2];
    // int val2 = map_data.tile[y2][x2];
    // int val3 = map_data.tile[y1][x1];
    // int val4 = map_data.tile[y2][x1];

    if(type_move ==  STATIC_THREAT)
    {
        ;//
    }
    else if(type_move == MOVE_IN_SPACE_THREAT)
    {
        if(on_ground_ ==  true)
        {

            if(x_pos_ > animation_b_ || check_right == 1)
            {
                input_type.left_ = 1;
                input_type.right_ = 0;
                LoadImg("img//redpig.png",screen);
            }
            else if(x_pos_ < animation_a_ || check_left == 1 || x_pos_ <= 0)
            {
                input_type.left_ = 0;
                input_type.right_ = 1;
                LoadImg("img//redpig_right.png",screen);
            }
            
        }else
            {
                if(input_type.left_ == 1 )
                {
                    LoadImg("img//redpig.png",screen);
                }
            }
    }
    else if(type_move == FLY_THREAT)
    {
        if(on_ground_ !=  true)
        {
            if(x_pos_ > animation_b_ || check_right == 1)
            {
                input_type.left_ = 1;
                input_type.right_ = 0;
                LoadImg("img//bee.png",screen);
            }
            else if(x_pos_ < animation_a_ || check_left == 1)
            {
                input_type.left_ = 0;
                input_type.right_ = 1;
                LoadImg("img//bee.png",screen);
            }
            
        }
        
        
        else
            {
                if(input_type.left_ == 1 )
                {
                    LoadImg("img//bee.png",screen);
                }
            }
    }
    else if(type_move == SAW_THREAT)
    {
        
            if( y_pos_ > animation_b_)
            {
                input_type.up_ = 1;
                input_type.down_ = 0;
                LoadImg("img//rolling_saw.png",screen);
            }
            else if(y_pos_ < animation_a_)
            {   input_type.up_ = 0;
                input_type.down_ = 1;   
                LoadImg("img//rolling_saw.png",screen);
            }
        
    }
    else if(type_move == JUMB_THREAT)
    {
        if(input_type.jump_ == 1)
        {
            if(on_ground_ == true)
            {
                y_val_ = -20;
            
            }
                on_ground_ = false;
                input_type.jump_ = 0;
        }
    }
    
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if(p_bullet != NULL)
    {
        p_bullet->set_bullet_type(BulletObject::SEED_BULLET);
        bool ret = p_bullet->LoadImgBullet(screen);
        if(ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(rect_.x + 10, rect_.y + 10);
            p_bullet->set_x_val(10);
            bullet_list.push_back(p_bullet);
        }
        
    }
}


void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for(int i = 0;i < bullet_list.size();i++)
    {
        BulletObject* p_bullet = bullet_list.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move())
            {
                int bullet_dis = rect_.x - p_bullet->GetRect().x;
                if(bullet_dis < 300 )
                {
                    p_bullet->HandleMove(x_limit,y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                    
                }
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(this->rect_.x+ 10, this->rect_.y + 10);
            }
            
        }
    }
}

void ThreatsObject::RemoveBullet(const int& idx)
{
    int size = bullet_list.size();
    if(size > 0 && idx < size)
    {
        BulletObject* p_bullet = bullet_list.at(idx);
        bullet_list.erase(bullet_list.begin() + idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
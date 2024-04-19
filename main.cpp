#include "base/basefuction.h"
#include "base/game_map.h"
#include "base/MainObject.h"
#include "base/ImpTimer.h"
#include "base/ThreatsObject.h"
#include "base/ExplosionObject.h"
#include "base/DeathAnimation.h"
#include "base/TextObject.h"
#include "base/PlayerPower.h"

BaseObject g_background;
BaseObject g_menu_screen;
BaseObject g_win_screen;
BaseObject g_lose_screen;

TTF_Font* font_time = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window=SDL_CreateWindow("contra fake",SDL_WINDOWPOS_UNDEFINED
                                               ,SDL_WINDOWPOS_UNDEFINED
                                               ,SCREEN_WIDTH
                                               ,SCREEN_HEIGHT
                                               ,SDL_WINDOW_SHOWN);
    if(g_window == NULL)
    {
        success = false;
        std::cout << "Can't not creat window \n";
    }
    else
    {
        g_screen = SDL_CreateRenderer (g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
        {
            success = false;
            std::cout << "Can't not creat render\n";
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen ,RENDER_DRAW_COLOR
                                            ,RENDER_DRAW_COLOR
                                            ,RENDER_DRAW_COLOR
                                            ,RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&&imgFlags))
                success=false;
        }

        if(TTF_Init() == -1)success = false;

        font_time = TTF_OpenFont("font//cute_font.ttf", 20);
        
        
        if(font_time == NULL)
        {
            success = false;
        }


        if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)== -1)
        {
            success = false;
        }
        g_sound_jump = Mix_LoadWAV("sound//jump.wav");
        g_sound_shoot = Mix_LoadWAV("sound//shoot.wav");
        g_back_sound = Mix_LoadWAV("sound//back_song.wav");
        g_hit = Mix_LoadWAV("sound//hit.wav");
        g_get_hit = Mix_LoadWAV("sound//get_hit.wav");
        g_lose_game = Mix_LoadWAV("sound//lose_game.wav");
        g_win_game = Mix_LoadWAV("sound//win_game.wav");

        if( g_sound_shoot == NULL || 
        g_sound_jump == NULL || 
        g_back_sound == NULL  ||
        g_hit == NULL ||
        g_get_hit == NULL ||
        g_lose_game == NULL ||
        g_win_game == NULL
        )
        {
            success = false;
        }
        
    }
    return success;
}
bool LoadBackground(){
    bool ret = g_background.LoadImg("img//backg.png",g_screen);
    bool ret2 = g_menu_screen.LoadImg("img//backg.png",g_screen);
    if(!ret || !ret2)
        return false;
    return true;
}

void close(){
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    IMG_Quit();
    SDL_Quit();
}


std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*> list_threats;

    ThreatsObject* win_flag = new ThreatsObject;
    if(win_flag != NULL)
    {
        win_flag->LoadImg("img//flag.png",g_screen);
        win_flag->set_clip();
        win_flag->set_type_move(ThreatsObject::WIN);
        win_flag->set_x_pos(225*64);//hehe
        win_flag->set_y_pos(20);
        list_threats.push_back(win_flag);
    }

    ThreatsObject* jumb_dyna_threats = new ThreatsObject[20];
    for(int i = 0 ; i < 20 ; i++)
    {
        ThreatsObject* jumb_threat = (jumb_dyna_threats + i);//
        if(jumb_threat != NULL)
        {
            jumb_threat->LoadImg("img//bunny.png",g_screen);
            jumb_threat->set_clip();
            jumb_threat->set_type_move(ThreatsObject::JUMB_THREAT);
            srand(time(NULL));
            jumb_threat->set_x_pos(500 + i*600);
            jumb_threat->set_y_pos(-100);
            list_threats.push_back(jumb_threat);
        }
    }

    ThreatsObject* fall_dyna_threats = new ThreatsObject[20];
    for(int i = 0 ; i < 20 ; i++)
    {
        ThreatsObject* fall_threat = (fall_dyna_threats + i);//
        if(fall_threat != NULL)
        {
            fall_threat->LoadImg("img//fall_flat.png",g_screen);
            fall_threat->set_clip();
            fall_threat->set_type_move(ThreatsObject::FALL_THREAT);
            srand(time(NULL));
            fall_threat->set_x_pos(4500 + i*600);
            fall_threat->set_y_pos(20);
            list_threats.push_back(fall_threat);
        }
    }

    ThreatsObject* saw_dyna_threats = new ThreatsObject[30];
    for(int i = 0 ; i < 30 ; i++)
    {
        ThreatsObject* saw_threat = (saw_dyna_threats + i);//
        if(saw_threat != NULL)
        {
            saw_threat->LoadImg("img//rolling_saw.png",g_screen);
            saw_threat->set_clip();
            saw_threat->set_type_move(ThreatsObject::SAW_THREAT);
            srand(time(NULL));
            saw_threat->set_x_pos(400 + i*5000);
            saw_threat->set_y_pos(200);

            int pos1 = saw_threat->get_y_pos() - 60;
            int pos2 = saw_threat->get_y_pos() + 150;
            saw_threat->setAnimationPos(50,pos2);
            saw_threat->Set_input_down(1);

            list_threats.push_back(saw_threat);
        }
    }

    ThreatsObject* bee_dyna_threats = new ThreatsObject[20];
    for(int i = 0 ; i < 20 ; i++)
    {
        ThreatsObject* bee_threat = (bee_dyna_threats + i);//
        if(bee_threat != NULL)
        {
            bee_threat->LoadImg("img//bee.png",g_screen);
            bee_threat->set_clip();
            bee_threat->set_type_move(ThreatsObject::FLY_THREAT);
            srand(time(NULL));
            bee_threat->set_x_pos(1000 + i*3600);
            bee_threat->set_y_pos(200);

            int pos1 = bee_threat->get_x_pos() - 60;
            int pos2 = bee_threat->get_x_pos() + 60;
            bee_threat->setAnimationPos(pos1,pos2);
            bee_threat->Set_input_left(1);

            list_threats.push_back(bee_threat);
        }
    }

    ThreatsObject* dynamic_threats = new ThreatsObject[30];
    for(int i = 0; i < 30;i++)// doi tuong di chuyen
    {
        ThreatsObject* p_threat = (dynamic_threats + i);//
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img//redpig.png",g_screen);
            p_threat->set_clip();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(200 + i*2500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->setAnimationPos(pos1,pos2);
            p_threat->Set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }


    ThreatsObject* threats_objs = new ThreatsObject[20]; // so doi tuong tren ban do

    for(int i = 0; i < 20 ;i++)// doi tuong k di chuyen
   {
        ThreatsObject* p_threat = (threats_objs + i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("img//plant.png",g_screen);
            p_threat->set_clip();
            p_threat->set_x_pos(700 + i*1500);//vi tri quai
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->Set_input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}




 
int main(int argc, char* args[]){

    bool real_quit = false;
    std::vector<LoadAnimation*> exp_list;

    ImpTimer fps_timer;

    if(!InitData()) return -1;
    if(!LoadBackground()) return -1;


    GameMap game_map;
    game_map.LoadMap("map/map02.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("img//runright.png", g_screen);
    p_player.set_clips();

    PlayerPower p_power;
    p_power.Init(g_screen);

    Coin coin;
    coin.Init(g_screen,"img//coin.png");
    coin.Set_Pos(SCREEN_WIDTH*0.5 - 300, 8);

    Coin bullet;
    bullet.Init(g_screen, "img//bullet.png");
    bullet.Set_Pos(SCREEN_WIDTH*0.5 - 600, 80);

    //std::vector<ThreatsObject*> threats_list = MakeThreatList();
    
    ExplosionObject exp_threat;
    bool t_ret = exp_threat.LoadImg("img//disappear.png",g_screen);
    if(!t_ret) return -1;
    
    exp_threat.set_clips();

    

    //text
    // TextObject time_game;
    // time_game.SetColor(TextObject::BLACK_TEXT);
    // TextObject mark_game;
    // mark_game.SetColor(TextObject::BLACK_TEXT);
    // UINT mark_value = 0;
// diem cao nhat
    TextObject best_score;
    best_score.SetColor(TextObject::BLACK_TEXT);

    TextObject money_game;
    money_game.SetColor(TextObject::BLACK_TEXT);

    TextObject bullet_game;
    bullet_game.SetColor(TextObject::BLACK_TEXT);

    



    BaseObject StartButton[2];
	BaseObject ExitButton[2];
	BaseObject ContinueButton[2];
	StartButton[0].LoadImg("img//menu//play_up.png",g_screen);
	StartButton[1].LoadImg("img//menu//play_down.png",g_screen);
	ExitButton[0].LoadImg("img//menu//exit_up.png",g_screen);
	ExitButton[1].LoadImg("img//menu//Exit_down.png",g_screen);
	
	SDL_Rect Button = StartButton[0].GetRect();
	StartButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2);
	StartButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2);
	
	Button = ExitButton[0].GetRect();
	ExitButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*1.5);
	ExitButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*1.5);

	Button = ContinueButton[0].GetRect();
	ContinueButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h*1.5);
	ContinueButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 - Button.h*1.5);
    int MousePosX = 0;
    int MousePosY = 0;


    bool quit_ = false;
    
    while(!quit_)
    {
        Mix_VolumeChunk(g_back_sound, MIX_MAX_VOLUME / 2);
        Mix_PlayChannel(1,g_back_sound,-1);
        p_player.set_x_pos(0);//hehe
        p_player.set_y_pos(64*2);
        p_player.set_status_();
        p_player.set_input_right(0);
        p_player.set_input_left(0);
        p_player.SetBullet(0);
        p_player.SetMoney(0);

        

        std::vector<ThreatsObject*> threats_list = MakeThreatList();
        
        bool menu_quit = false;
        bool is_quit = false;
        int num_die = 1;
        
        p_power.Init(g_screen);

        while(!menu_quit)
        {
            
            SDL_RenderClear(g_screen);
            g_menu_screen.Render(g_screen, NULL);
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_MOUSEMOTION)
                {
                    MousePosX = g_event.motion.x;
                    MousePosY = g_event.motion.y;
                }
                if(g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,StartButton[0].GetRect()) == true)
                        {
                            menu_quit = true;
                            
                        }
                        if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true )
                        {
                            menu_quit = true;
                            is_quit = true;
                            real_quit = true;
                            quit_ = true;
                            
                        }
                        
                    }
                }
            }
            if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,StartButton[0].GetRect()) == true)
            {
                StartButton[1].Render(g_screen);
            }
            else
            {
                StartButton[0].Render(g_screen);
            }
            if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
            {
                ExitButton[1].Render(g_screen);
            }
            else
            {
                ExitButton[0].Render(g_screen);
            }
            SDL_RenderPresent(g_screen);
            SDL_Delay(100);
        }
        
        while(!is_quit)
        {
            
            
            bool win_game  = false;
    

            fps_timer.start();
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                    quit_ = true;
                }
                else if(g_event.type == SDL_KEYDOWN)
                {
                    if(g_event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        fps_timer.paused();
                        is_quit = SDLBasefuction::Menu(g_screen);
                        fps_timer.unpaused();
                    }
                    
                    
                }
                p_player.HandelInputAction(g_event,g_screen,g_sound_jump,g_sound_shoot);
                
            }
            SDL_SetRenderDrawColor(g_screen ,RENDER_DRAW_COLOR
                                            ,RENDER_DRAW_COLOR
                                            ,RENDER_DRAW_COLOR
                                            ,RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);
            g_background.Render(g_screen, NULL);

            game_map.DrawMap(g_screen); //map
            Map map_data = game_map.getMap();

            p_player.HandeleBullet(g_screen);
            p_player.SetMapXY(map_data.start_x_,map_data.start_y_);
            p_player.DoPlayer(map_data);
            p_player.Show(g_screen); //player
            
            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);

            p_power.Show(g_screen);
            coin.Show(g_screen);
            bullet.Show(g_screen);


            for(int i = 0;i < threats_list.size() ;i++)
            {
                ThreatsObject* p_threat = threats_list.at(i);

                
                if(p_threat != NULL )
                {
                    p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                    p_threat->ImpMoveType(g_screen,map_data);
                    if(p_threat->get_type_move() == ThreatsObject::FLY_THREAT   || p_threat->get_type_move() == ThreatsObject::SAW_THREAT)
                    {
                        p_threat->FlyDoPlayer(map_data);
                    }
                    else if(p_threat->get_type_move() == ThreatsObject::FALL_THREAT)
                    {
                        p_threat->FallDoPlayer(map_data);
                    }
                    else p_threat->DoPlayer(map_data);
                    
                    
                    p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                    p_threat->Show(g_screen);

                    if(p_threat->get_type_move() == ThreatsObject::FALL_THREAT)
                    {
                    float pos =  p_threat->get_x_pos() - p_player.get_x_pos();
                    
                    if (pos < 100)
                    {
                            
                            p_threat->Set_input_down(1);
                    }
                    }


                    if(p_threat->get_type_move() == ThreatsObject::JUMB_THREAT)
                    {
                    float pos =  p_threat->get_x_pos() - p_player.get_x_pos();
                    
                    if ((pos < 500 && pos > -400))
                    {
                            
                            p_threat->Set_input_left(1);
                            p_threat->Set_input_jumb(1);

                            
                    }
                    else
                    {
                        p_threat->Set_input_left(0);
                    }
                    }

                    SDL_Rect rect_player = p_player.GetRectFrame();
                    bool bCol1  = false;
                    std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                    for(int jj =  0; jj < tBullet_list.size(); jj++)
                    {
                        BulletObject* pt_bullet  = tBullet_list.at(jj);
                        if(pt_bullet != NULL)
                        {
                            SDL_Rect rect_bullet = pt_bullet->GetRect();
                            bCol1 = SDLBasefuction::CheckColli(rect_bullet, rect_player) && pt_bullet->get_is_move();
                            if(bCol1)
                                {
                                    
                                    pt_bullet->set_is_move(false);
                                    //break;
                                    LoadAnimation* newExp = new LoadAnimation();
                                    newExp->LoadImg("img//disappear.png",g_screen);
                                    newExp->set_clips();
                                    newExp->set_x_pos(p_player.get_x_pos());
                                    newExp->set_y_pos(p_player.get_y_pos());
                                    exp_list.push_back(newExp);
                                    //
                                }
                        }

                    }
                    SDL_Rect rect_threat = p_threat->GetRectFrame();

                    bool bCol2 = SDLBasefuction::CheckColli(rect_threat,rect_player);
                    
                    
                            
                    
                    if(bCol2 || bCol1)
                    {
                        


                        if((rect_player.y + rect_player.h >= rect_threat.y && rect_player.y + rect_player.h  <= rect_threat.y + rect_threat.h) && p_player.get_on_ground() != true)
                            {
                                if(p_threat->get_type_move() == ThreatsObject::WIN)
                                {
                                    g_lose_screen.LoadImg("img//winn.png",g_screen);
                                    g_lose_screen.Render(g_screen);
                                    SDL_RenderPresent(g_screen);
                                    g_lose_screen.Free();
                                    win_game = true;
                                    Mix_HaltChannel(1);
                                    Mix_PlayChannel(-1 ,g_win_game, 0);
                                    //fps_timer.paused();
                                    SDL_Delay(7000);
                                    is_quit = true;
                                }
                                else
                                {
                                    Mix_PlayChannel(-1,g_hit,0);
                                    p_player.IncreaseBullet();
                                    p_player.IncreaseMoney();
                                    p_player.set_y_val(-20);
                                    LoadAnimation* newExp = new LoadAnimation();
                                    newExp->LoadImg("img//disappear.png",g_screen);
                                    newExp->set_clips();
                                    newExp->set_x_pos(p_player.get_x_pos());
                                    newExp->set_y_pos(p_player.get_y_pos());
                                    exp_list.push_back(newExp);
                                    p_threat->Free();
                                    threats_list.erase(threats_list.begin() + i);

                                }

                                
                            }
                            else
                            {
                                
                                num_die++;
                                if(num_die <= 3)
                                {   Mix_PlayChannel(-1 , g_get_hit, 0);
                                     p_player.SetRect(0,0);
                                     p_player.set_come_back_time(60);
                                     p_power.Decrease();
                                     p_power.Render(g_screen);
                                     continue;
                                }
                                else
                                {
                                    //load you die
                                    g_lose_screen.LoadImg("img//losee.png",g_screen);
                                    g_lose_screen.Render(g_screen);
                                    SDL_RenderPresent(g_screen);
                                    g_lose_screen.Free();
                                    Mix_HaltChannel(1);
                                    Mix_PlayChannel(-1 ,g_lose_game, 0);
                                    //fps_timer.paused();
                                    SDL_Delay(3000);
                                    is_quit = true;
                                }
                            }
                    }
                    
                }
            }
            
            // va cham map
            if(p_player.Get_hurted() == 1)
            {
                num_die++;
                if(p_player.Get_hurted() == 1 && num_die <= 3)
            {
                Mix_PlayChannel(-1 , g_get_hit, 0);
                p_player.SetRect(0,0);
                p_player.set_come_back_time(60);
                p_player.Set_hurted(0);
                p_power.Decrease();
                p_power.Render(g_screen);
                
                continue;
            }
            else if( p_player.Get_hurted() == 1 && num_die > 3)
            {
                p_player.Set_hurted(0);
                g_lose_screen.LoadImg("img//losee.png",g_screen);
                g_lose_screen.Render(g_screen);
                SDL_RenderPresent(g_screen);
                g_lose_screen.Free();
                Mix_HaltChannel(1);
                Mix_PlayChannel(-1 ,g_lose_game, 0);
                //fps_timer.paused();
                SDL_Delay(3000);
                is_quit = true;
            }
                
            }
            


            int frame_exp_width = exp_threat.get_frame_width();
            int frame_exp_height = exp_threat.get_frame_height();
            std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
            for(int r = 0; r < bullet_arr.size() ;r++)
            {
                BulletObject* p_bullet = bullet_arr.at(r);
                if(p_bullet != NULL)
                {
                    for(int t = 0; t < threats_list.size(); t++)
                    {
                        ThreatsObject* obj_threat = threats_list.at(t);
                        if(obj_threat != NULL)
                        {
                            SDL_Rect tRect;
                            tRect.x = obj_threat->GetRect().x;
                            tRect.y = obj_threat->GetRect().y;
                            tRect.w = obj_threat->get_width_frame();
                            tRect.h = obj_threat->get_height_frame();

                            SDL_Rect bRect = p_bullet->GetRect();

                            bool bCol = SDLBasefuction::CheckColli(bRect, tRect);
                            

                            if(bCol)
                            {

                                if(obj_threat->get_type_move() == ThreatsObject::WIN)
                                {
                                    g_lose_screen.LoadImg("img//winn.png",g_screen);
                                    g_lose_screen.Render(g_screen);
                                    SDL_RenderPresent(g_screen);
                                    g_lose_screen.Free();
                                    win_game = true;
                                    Mix_HaltChannel(1);
                                    Mix_PlayChannel(-1 ,g_win_game, 0);
                                    //fps_timer.paused();
                                    SDL_Delay(7000);
                                    is_quit = true;
                                }
                                Mix_PlayChannel(-1 , g_hit, 0);
                                p_player.IncreaseMoney();
                                for(int ex = 0;ex < NUM_FRAME_EXP;ex++ )
                                {
                                    int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
                                    int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;
                                    exp_threat.set_frame(ex);
                                    exp_threat.SetRect(x_pos,y_pos);
                                    exp_threat.Show(g_screen);
                                }
                                
                                p_player.RemoveBullet(r);
                                obj_threat->Free();
                                threats_list.erase( threats_list.begin() + t);
                            }
                        }
                    }
                    
                }
            }

            for(int k = 0; k < exp_list.size();k++ )
            {
                LoadAnimation* new_exp = exp_list.at(k);
                if(new_exp!= NULL)
                {
                    new_exp->SetMapXY(map_data.start_x_,map_data.start_y_);
                    new_exp->Show(g_screen);
                    if(new_exp->get_animation_loop() > 0 )
                    {
                        new_exp->Free();
                        exp_list.erase(exp_list.begin() + k);
                    }
                }
            }

            int money_count = p_player.GetMoney();
            std::string money_str = std::to_string(money_count);

            

            money_game.SetText(money_str);
            money_game.LoadFromRenderText(font_time,g_screen);
            money_game.RenderText(g_screen,SCREEN_WIDTH*0.5 - 250,15);

            int bullet_count = p_player.GetBullet();

            std::string bullet_str = std::to_string(bullet_count);

            bullet_game.SetText(bullet_str);
            bullet_game.LoadFromRenderText(font_time,g_screen);
            bullet_game.RenderText(g_screen,SCREEN_WIDTH*0.5 - 560,80);

            std::ifstream file("highscore.txt");
            int bscore;
            file >> bscore;
            std::string b_score = std::to_string(bscore);
		    std::string strb_score("BEST: ");
		    strb_score += b_score;
            if(money_count > bscore)
            {
                bscore = money_count;
				b_score = std::to_string(bscore);
				strb_score = "BEST: ";
				strb_score += b_score;
            }
            best_score.SetText(strb_score);
			best_score.LoadFromRenderText(font_time, g_screen);
			best_score.RenderText(g_screen, 0 , 120);
            std::ofstream outfile("highscore.txt");
            outfile << bscore;
            outfile.close();

            best_score.Free();
            bullet_game.Free();
            money_game.Free();

            if(num_die <= 3 && win_game == false)
            {
                SDL_RenderPresent(g_screen); //show
            }
            
            int real_imp_time = fps_timer.get_ticks();
            int time_one_frame = 1000/FRAME_PER_SECOND;//tinh theo mili giay

            if(real_imp_time < time_one_frame)
            {
                int delay_time = time_one_frame - real_imp_time;
                if(delay_time >= 0)
                    SDL_Delay(delay_time);
            }
        }

    for(int i = 0; i < threats_list.size();i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        
        if(p_threat )//
        {
            p_threat->Free();
            p_threat= NULL;
        }
    }
    threats_list.clear();
    SDL_Delay(500);
    }   
    close();
    return 0;
}
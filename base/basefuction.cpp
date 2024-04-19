#include"basefuction.h"
#include "TextObject.h"

//ham check va cham(check theo hinh chu nhat)
bool SDLBasefuction::CheckColli(const SDL_Rect& object1, const SDL_Rect& object2)
{
    return (object1.x < object2.x + object2.w &&
            object1.x + object1.w > object2.x &&
            object1.y < object2.y + object2.h &&
            object1.y + object1.h > object2.y);
}
//kiem tra vi tri cua chuot so voi nut
bool SDLBasefuction::CheckMousePos(const int& x,const int& y,const SDL_Rect& Obj_)
{
	return (x >= Obj_.x && x <= Obj_.x + Obj_.w && y>= Obj_.y && y <= Obj_.y + Obj_.h);
}

// ham menu giua game
bool SDLBasefuction::Menu(SDL_Renderer* g_screen)
{

  TTF_Font* font_menu = NULL;
  font_menu = TTF_OpenFont("font//cute_font.ttf", 100);
  TextObject Menu_game;
  Menu_game.SetColor(TextObject::RED_TEXT);
  std::string Menu_str = "Mechanic Mike";

  BaseObject Back_Button[2];
  BaseObject Back_Button2[2];
	BaseObject ExitButton[2];
  BaseObject Help_Button[2];
 
  BaseObject Help;

	Back_Button[0].LoadImg("img//menu//back_up.png",g_screen);
	Back_Button[1].LoadImg("img//menu//back_down.png",g_screen);
  Back_Button2[0].LoadImg("img//menu//back_up.png",g_screen);
	Back_Button2[1].LoadImg("img//menu//back_down.png",g_screen);
	ExitButton[0].LoadImg("img//menu//exit_up.png",g_screen);
	ExitButton[1].LoadImg("img//menu//exit_down.png",g_screen);
  Help_Button[0].LoadImg("img//menu//help_up.png",g_screen);
	Help_Button[1].LoadImg("img//menu//help_down.png",g_screen);

	SDL_Rect Button = Back_Button[0].GetRect();

  Help_Button[0].SetRect(SCREEN_WIDTH/2 - Button.w + 2,SCREEN_HEIGHT/2);
	Help_Button[1].SetRect(SCREEN_WIDTH/2 - Button.w + 2,SCREEN_HEIGHT/2);

	Back_Button[0].SetRect(SCREEN_WIDTH/5 - Button.w/2,SCREEN_HEIGHT*0.8);
	Back_Button[1].SetRect(SCREEN_WIDTH/5 - Button.w/2,SCREEN_HEIGHT*0.8);
	
  Back_Button2[0].SetRect(SCREEN_WIDTH/5 - Button.w/2,SCREEN_HEIGHT*0.2);
	Back_Button2[1].SetRect(SCREEN_WIDTH/5 - Button.w/2,SCREEN_HEIGHT*0.2);

	Button = ExitButton[0].GetRect();
	ExitButton[0].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*1.5);
	ExitButton[1].SetRect(SCREEN_WIDTH/2 - Button.w/2,SCREEN_HEIGHT/2 + Button.h*1.5);

  
  int x_pos = SCREEN_WIDTH/2 - Button.w/2;
  int y_pos = SCREEN_HEIGHT/3 - Button.h/2;
  
  SDL_Event g_event;


  int MousePosX = 0;
  int MousePosY = 0;
  bool menu_quit = false;
  int help = 0;
  while(!menu_quit)
        {
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_KEYDOWN)
                {
                  if(g_event.key.keysym.sym == SDLK_ESCAPE)
                  {
                    menu_quit = true;
                  }
                }
                if(g_event.type == SDL_MOUSEMOTION)
                {
                    MousePosX = g_event.motion.x;
                    MousePosY = g_event.motion.y;
                }
                if(g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,Back_Button[0].GetRect()) == true)
                        {
                            menu_quit = true;
                        }
                        if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true )
                        {
                            menu_quit = true;
                            return true;
                        }
                        if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,Help_Button[0].GetRect()) == true)
                        {
                            Help.LoadImg("img//qqq.png",g_screen);
                            help = 1;
                        }
                        if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,Back_Button2[0].GetRect()) == true)
                        {
                            menu_quit = true;
                        }
                    }
                }
            }

            Menu_game.SetText(Menu_str);
            Menu_game.LoadFromRenderText(font_menu,g_screen);
            Menu_game.RenderText(g_screen,SCREEN_WIDTH*0.5 - 500,150);

            Menu_game.Free();

            
            if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,Back_Button[0].GetRect()) == true)
            {
                Back_Button[1].Render(g_screen);
            }
            else
            {
                Back_Button[0].Render(g_screen);
            }
            if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
            {
                ExitButton[1].Render(g_screen);
            }
            else
            {
                ExitButton[0].Render(g_screen);
            }
            if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,Help_Button[0].GetRect()) == true)
            {
                Help_Button[1].Render(g_screen);
            }
            else
            {
                Help_Button[0].Render(g_screen);
            }

            if(help == 1 )
            {
              Help.Render(g_screen);
              if(SDLBasefuction::CheckMousePos(MousePosX,MousePosY,Back_Button2[0].GetRect()) == true)
              {
                  Back_Button2[1].Render(g_screen);
              }
              else
              {
                  Back_Button2[0].Render(g_screen);
              }
            }


            SDL_RenderPresent(g_screen);
            SDL_Delay(100);
        }
      return false;
}
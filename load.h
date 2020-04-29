//define the screen W and H
#ifndef WINDOW_W
#define WINDOW_W 800
#endif

#ifndef WINDOW_H
#define WINDOW_H 600
#endif

#ifndef EXTRA_X
#define EXTRA_X 50
#endif

//include the header files
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
using namespace std;

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

//include my files
#include "class.h"

//Set up our main player
Player Player1;

//Set up the computer player
Player Player2;

//Set up the background
SDL_Surface *Bg;
SDL_Surface *Bottom;

//Init the SDL surfaces
SDL_Surface *back;  
SDL_Surface *screen;

//The font that's going to be used 
TTF_Font *font = NULL;
SDL_Color textColor = { 0, 0, 0 };

//The HP realted stuff
SDL_Surface *hpTitle,*yourHP; //hpTitle will be text and yourHP will be the bar

//Our keys handler
Uint8* keys;
bool keyDown = false;

//Our additional score per seocnd
int AddScorePerSec;

//Our main loops handler
int done=0;

//our score variables
int score;
char ScoreText[100];

//Our handler for if the rocket is on
bool RocketOn;

//Our SDL_Event handler
SDL_Event event;

//Functions are refferenced from file to file. To avoid going though DoD include hierarchy, define all functions here
int MainLoop(), GetKeys(), Movement(), Collision(), Draw(), Loose(),ScrollBG(),ItemEffects(int),ItemEventCheck(),ItemDeployment();

//This an insance of DrawIMG for system use, so we dont have to redeclare it
Display SystemUse;

//Set up our movement timer
Timer delta;
int StartTime, EndTime, DelayTime,timeDif,lastUpdate;
int clockTimer;

//Set up our wall
Wall wall1,wall2,wall3,wall4;

//Set our menu items
menuItem menuPlay, menuQuit;
int menu=0;



//C++ does not allow you run a function or set a class instance in inline code. 
//This will also be used to reset the game
int SetInstances()
{   
    //Start the timer
    StartTime            = time(NULL);
    //Set up player 1
    Player1.rotFace[0]   = SDL_LoadBMP("images//tank-u.bmp");
    Player1.rotFace[1]   = SDL_LoadBMP("images//tank-r.bmp");
    Player1.rotFace[2]   = SDL_LoadBMP("images//tank-d.bmp");
    Player1.rotFace[3]   = SDL_LoadBMP("images//tank-l.bmp");
    Player1.direction    = 0;
    Player1.xpos         = 50;
    Player1.ypos         = 50;
    Player1.xspeed       = 0;
    Player1.yspeed       = 0;
    Player1.xvel         = 300; //Velocity is the maximum potental speed of the block. It is measured in pixes per second
    Player1.yvel         = 325;
    Player1.status       = 1;
    Player1.x            = 36;
    Player1.y            = 44;
    Player1.roundCap     = 3; //Number is zero initializing.
    Player1.damage       = 4;
    Player1.originalHP   = 15;
    Player1.regen        = .2; //This is measured in HP per second
    Player1.HP           = Player1.originalHP;
    Player1.coolDown     = 1000;
    Player1.shotDelayT   = 0; // Humans are limited by theirselves, this is to limit the computer
    SDL_SetColorKey(Player1.rotFace[0], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player1.rotFace[0]->format, 0, 0, 1));
    SDL_SetColorKey(Player1.rotFace[1], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player1.rotFace[1]->format, 0, 0, 1));
    SDL_SetColorKey(Player1.rotFace[2], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player1.rotFace[2]->format, 0, 0, 1));
    SDL_SetColorKey(Player1.rotFace[3], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player1.rotFace[3]->format, 0, 0, 1));
    
    
    yourHP               = SDL_LoadBMP("images//healthbar.bmp");
    
    
    //Set up player 2
    Player2.rotFace[0]   = SDL_LoadBMP("images//tank-u.bmp");
    Player2.rotFace[1]   = SDL_LoadBMP("images//tank-r.bmp");
    Player2.rotFace[2]   = SDL_LoadBMP("images//tank-d.bmp");
    Player2.rotFace[3]   = SDL_LoadBMP("images//tank-l.bmp");
    Player2.direction    = 0;
    Player2.xpos         = 450;
    Player2.ypos         = 450;
    Player2.xspeed       = 0;
    Player2.yspeed       = 0;
    Player2.xvel         = 150; //Velocity is the maximum potental speed of the block. It is measured in pixes per second
    Player2.yvel         = 150;
    Player2.status       = 1;
    Player2.x            = 36;
    Player2.y            = 44;
    Player2.roundCap     = 1; //Number is zero initializing.
    Player2.damage       = 3;
    Player2.originalHP   = 15;
    Player2.HP           = Player2.originalHP;
    Player2.coolDown     = 1000;
    Player2.shotDelayT   = 100; //Measured in milliseconds. This is aproximately a human response time.
    SDL_SetColorKey(Player2.rotFace[0], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player2.rotFace[0]->format, 0, 0, 1));
    SDL_SetColorKey(Player2.rotFace[1], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player2.rotFace[1]->format, 0, 0, 1));
    SDL_SetColorKey(Player2.rotFace[2], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player2.rotFace[2]->format, 0, 0, 1));
    SDL_SetColorKey(Player2.rotFace[3], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(Player2.rotFace[3]->format, 0, 0, 1));
    Bg                   = SDL_LoadBMP("images//bg.bmp");
    
    //Set up the wall
    wall1.face           = SDL_LoadBMP("images//wall.bmp");
    wall1.x              = 50;
    wall1.y              = 50;
    wall1.xpos           = 300;
    wall1.ypos           = 400;
    wall1.HP             = 25;
    
    //Set up the other wall
    wall2.face           = SDL_LoadBMP("images//wall.bmp");
    wall2.x              = 50;
    wall2.y              = 50;
    wall2.xpos           = 600;
    wall2.ypos           = 200;
    wall2.HP             = 25;
    
    
    //Set up the other wall
    wall3.face           = SDL_LoadBMP("images//wall.bmp");
    wall3.x              = 50;
    wall3.y              = 50;
    wall3.xpos           = 150;
    wall3.ypos           = 500;
    wall3.HP             = 25;
    
    
    //Set up the other wall
    wall4.face           = SDL_LoadBMP("images//wall.bmp");
    wall4.x              = 50;
    wall4.y              = 50;
    wall4.xpos           = 300;
    wall4.ypos           = 100;
    wall4.HP             = 25;
    
    
    for(int i=Player1.roundCap;i>=0;i--)
    {
        Player1.Ammo[i].xpos = 0;
        Player1.Ammo[i].ypos = 0;
        Player1.Ammo[i].xvel = 800;
        Player1.Ammo[i].yvel = 800;
        Player1.Ammo[i].face = SDL_LoadBMP("images//bullet.bmp");
        Player1.Ammo[i].x = 10;
        Player1.Ammo[i].y = 10;
    }
    
    for(int i=Player2.roundCap;i>=0;i--)
    {
        Player2.Ammo[i].xpos = 0;
        Player2.Ammo[i].ypos = 0;
        Player2.Ammo[i].xvel = 800;
        Player2.Ammo[i].yvel = 800;
        Player2.Ammo[i].face = SDL_LoadBMP("images//bullet.bmp");
        Player2.Ammo[i].x = 10;
        Player2.Ammo[i].y = 10;
    }
    
    //Our handler for the status of the mouse
    RocketOn = false;
    
    StartTime = time(NULL);
    
    
    //Initialize SDL_ttf 
    if( TTF_Init() == -1 ) 
    { 
        return false; 
    }
    font = TTF_OpenFont( "ariblk.ttf", 18 );
    if( font == NULL ) { MessageBox(NULL, TTF_GetError(), "Looser", MB_OK); }
    SDL_WM_SetCaption( "Tank Battle", NULL );
    
    
    //Set the text
    hpTitle = TTF_RenderText_Solid(font, "Health:" , textColor );
    
    
    Bg                   = SDL_LoadBMP("images//bg.bmp");
    Bottom               = SDL_LoadBMP("images//bottom.bmp");
    
    
    menuPlay.faceOut   = SDL_LoadBMP("images//play.bmp");
    menuPlay.faceIn    = SDL_LoadBMP("images//playLight.bmp");
    menuPlay.face      = menuPlay.faceOut;
    menuPlay.hilighted = false;
    menuPlay.w         = 120;
    menuPlay.h         = 26;
    menuPlay.xpos      = (WINDOW_W/2)-(menuPlay.w/2);
    menuPlay.ypos      = 200;
    
    
    menuQuit.faceOut   = SDL_LoadBMP("images//quit.bmp");
    menuQuit.faceIn    = SDL_LoadBMP("images//quitLight.bmp");
    menuQuit.face      = menuQuit.faceOut;
    menuQuit.hilighted = false;
    menuQuit.w         = 120;
    menuQuit.h         = 26;
    menuQuit.xpos      = (WINDOW_W/2)-(menuPlay.w/2);
    menuQuit.ypos      = (300-menuPlay.h)-15;
    
   
    return 0;
}

//Our program specific include files (most require the above code to properly execute)

#include "input.h"
#include "ai.h"
#include "movement.h"
#include "cosmetics.h"
#include "draw.h"
#include "menu.h"
#include "MainLoop.h"

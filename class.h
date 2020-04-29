//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
    public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();    
};

Timer::Timer() 
{ 
           //Initialize the variables 
           startTicks = 0; 
           pausedTicks = 0; 
           paused = false; 
           started = false; 
}

void Timer::start() 
{ 
     //Start the timer 
     started = true; 
     //Unpause the timer 
     paused = false; 
     //Get the current clock time 
     startTicks = SDL_GetTicks(); 
}

void Timer::stop() 
{ 
     //Stop the timer 
     started = false; 
     //Unpause the timer 
     paused = false; 
}

int Timer::get_ticks() 
{ 
    //If the timer is running 
    if( started == true ) 
    { 
        //If the timer is paused 
        if( paused == true ) 
        { 
            //Return the number of ticks when the timer was paused 
            return pausedTicks; 
        } 
        else 
        {
              //Return the current time minus the start time 
              return SDL_GetTicks() - startTicks; 
        } 
    } //If the timer isn't running 
return 0; 
}

void Timer::pause() 
{ 
     //If the timer is running and isn't already paused 
     if( ( started == true ) && ( paused == false ) ) 
     { 
         //Pause the timer 
         paused = true; 
         //Calculate the paused ticks 
         pausedTicks = SDL_GetTicks() - startTicks; 
     } 
}

void Timer::unpause() 
{ 
     //If the timer is paused 
     if( paused == true ) 
     { 
         //Unpause the timer 
         paused = false; 
         //Reset the starting ticks 
         startTicks = SDL_GetTicks() - pausedTicks; 
         //Reset the paused ticks
          pausedTicks = 0; 
     } 
}

bool Timer::is_started() 
{ 
     return started; 
} 
bool Timer::is_paused() 
{ 
     return paused; 
}


class menuItem
{
    public:
        SDL_Surface *faceOut, *faceIn, *face;
        int xpos,ypos,w,h;
        bool hilighted;
};
        


class Display
{
public:
    int DrawIMG(SDL_Surface*,float,float,SDL_Surface*), DrawIMG(SDL_Surface *, int, int,
                                int, int, int, int,SDL_Surface*);
    int status;
    float xpos,ypos,xspeed,yspeed,calcXSpeed,calcYSpeed,xvel,yvel,x,y;
    float xspeedDec,yspeedDec;
    SDL_Surface *face;
};


int Display::DrawIMG(SDL_Surface *img, float x, float y, SDL_Surface *screen)
{
  SDL_Rect dest;
  dest.x = (int)x;
  dest.y = (int)y;
  SDL_BlitSurface(img, NULL, screen, &dest);
  return 0;
}

int Display::DrawIMG(SDL_Surface *img, int x, int y,
                                int w, int h, int x2, int y2, SDL_Surface* screen)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest2, screen, &dest);
  return 0;
}



class Bullet: public Display
{
      public:
      int damage;
      float hp,hpLeft;
      bool active;
};





class Player: public Display
{
public:
    int Draw(SDL_Surface*),Move(Uint32 deltaTicks),fire(), drawBullets(SDL_Surface *), stop(),
         damage,direction,roundCap;
    float originalHP,HP,regen;
    SDL_Surface *rotFace[4];
    Bullet Ammo[4];
    SDL_Surface *coolDownS;
    int coolDown,coolDownT;
    //For direction: 0=up 1=right 2=down 3=left 4=nothing, (3 wont show without 4).
    
    int shotDelay, shotDelayT; //For AI use, has no purpose if a human controls the player
};

int Player::drawBullets(SDL_Surface *screen)
{
    for(int i=Player::roundCap;i>=0;i--)
    {
            
            if(Player::Ammo[i].active == true)
            {
                Player::DrawIMG(Player::Ammo[i].face, Player::Ammo[i].xpos, Player::Ammo[i].ypos, screen);
            }
    }
    return 0;
}

int Player::stop()
{
    Player::xspeed = 0;
    Player::yspeed = 0;
    return 0;
}

int Player::fire()
{
    //see if it has been long enough to fire again
    if(Player::coolDownT < Player::coolDown)
    {
        return 0;
    }
    else
    {
        Player::coolDownT = 0;
    }
    //evaluate which round we will deploy
    int round = -1;
    for(int i=Player::roundCap;i>=0;i--)
    {
            if(Player::Ammo[i].active == false)
            {
                 round = i;
                 break;
            }
    }
    if(round==-1)
    {
         return 1;
    }
    
    if(Player::direction == 0)
    {
         Player::Ammo[round].yspeed       = -Player::Ammo[round].yvel;
         Player::Ammo[round].xspeed       = 0;
         Player::Ammo[round].ypos         = Player::ypos;
         Player::Ammo[round].xpos         = Player::xpos+(Player::x/2)-(Player::Ammo[round].x/2);
    }
    
    if(Player::direction == 1)
    {
         Player::Ammo[round].yspeed       = 0;
         Player::Ammo[round].xspeed       = Player::Ammo[round].xvel;
         Player::Ammo[round].ypos         = Player::ypos+(Player::y/2)-(Player::Ammo[round].y/2);
         Player::Ammo[round].xpos         = Player::xpos+Player::x;
    }
    
    if(Player::direction == 2)
    {
         Player::Ammo[round].yspeed       = Player::Ammo[round].yvel;
         Player::Ammo[round].ypos         = Player::ypos+Player::y;
         Player::Ammo[round].xpos         = Player::xpos+(Player::x/2)-(Player::Ammo[round].x/2);
         Player::Ammo[round].xspeed       = 0;
    }
    
    if(Player::direction == 3)
    {
         Player::Ammo[round].yspeed       = 0;
         Player::Ammo[round].xspeed       = -Player::Ammo[round].xvel;
         Player::Ammo[round].ypos         = Player::ypos+(Player::y/2)-(Player::Ammo[round].y/2);
         Player::Ammo[round].xpos         = Player::xpos-(Player::Ammo[round].x/2);
    }
    Player::Ammo[round].active = true;
    return 0;
}

int Player::Draw(SDL_Surface *screen)
{
    Player::DrawIMG(Player::rotFace[Player::direction],(int)Player::xpos,(int)Player::ypos,screen);
    return 0;
}

int Player::Move(Uint32 deltaTicks)
{
    //I assign these later on for collision detection reasons
    calcXSpeed = Player::xspeed * ( deltaTicks / 1000.f );
    calcYSpeed = Player::yspeed * ( deltaTicks / 1000.f );
    
    Player::xpos += Player::xspeed * ( deltaTicks / 1000.f );
    Player::ypos += Player::yspeed * ( deltaTicks / 1000.f );
    for(int i=Player::roundCap;i>=0;i--)
    {
            if(Player::Ammo[i].active == true)
            {
                Player::Ammo[i].xpos += Player::Ammo[i].xspeed * ( deltaTicks / 1000.f );
                Player::Ammo[i].ypos += Player::Ammo[i].yspeed * ( deltaTicks / 1000.f );
            }
    }
    return 0;
}




class Wall: public Display
{
      public:
      int originalHP,HP,Draw(SDL_Surface *);
};

int Wall::Draw(SDL_Surface *screen)
{
    Wall::DrawIMG(Wall::face,(int)Wall::xpos,(int)Wall::ypos,screen);
    return 0;
}

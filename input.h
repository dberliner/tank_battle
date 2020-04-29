int GetKeys()
{
    while ( SDL_PollEvent(&event) )
    {
        if ( event.type == SDL_QUIT )  {  done = 1;  }
        
        if ( event.type == SDL_KEYDOWN )
        {
            if ( event.key.keysym.sym == SDLK_ESCAPE ) { done = 1; }
            
            
            if ( event.key.keysym.sym == SDLK_SPACE )
            {
               Player1.fire();
            }
        }
    }

    //reset the speeds
    Player1.yspeed = 0;
    Player1.xspeed = 0;
    keyDown = false;
    
    //This gets the state of a key opposed to decting when one was pressed.
    Uint8 *keystate = SDL_GetKeyState(NULL);

     if(keystate[SDLK_UP] && keyDown==false)
     {
        //alter the dimentions if the tank has moved anything but 180 degrees
        if(Player1.direction == 1 || Player1.direction == 3)
        {
             float dirTemp = Player1.x;
             Player1.x = Player1.y;
             Player1.y = dirTemp;
        }
        Player1.direction = 0;
        Player1.yspeed = -Player1.yvel;
        Player1.xspeed = 0;
        keyDown=true;
     }
      
    else if(keystate[SDLK_RIGHT] && keyDown==false)
    { 
       //alter the dimentions if the tank has moved anything but 180 degrees
       if(Player1.direction == 0 || Player1.direction == 2)
       {
           float dirTemp = Player1.x;
           Player1.x = Player1.y;
           Player1.y = dirTemp;
       }
       Player1.direction = 1;
       Player1.xspeed = Player1.yvel; 
       Player1.yspeed = 0;
       keyDown=true;
    }
    
    else if(keystate[SDLK_DOWN] && keyDown==false)
    {
        //alter the dimentions if the tank has moved anything but 180 degrees
        if(Player1.direction == 1 || Player1.direction == 3)
        {
             float dirTemp = Player1.x;
             Player1.x = Player1.y;
             Player1.y = dirTemp;
        }
        Player1.direction = 2;
        Player1.yspeed = Player1.yvel;
        Player1.xspeed = 0;
        keyDown=true;
    }
    
    else if(keystate[SDLK_LEFT] && keyDown==false)
    {
        //alter the dimentions if the tank has moved anything but 180 degrees
        if(Player1.direction == 0 || Player1.direction == 2)
        {
             float dirTemp = Player1.x;
             Player1.x = Player1.y;
             Player1.y = dirTemp;
        }
        
        Player1.direction = 3;
        Player1.xspeed = -Player1.yvel;
        Player1.yspeed = 0;
        keyDown=true;
    }

    return 0;
}


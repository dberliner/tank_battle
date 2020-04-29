int menuLoop()
{
    int x,y;
    bool mouseDown = false;
    menu = 0;
    while (menu==0)
    {
        while ( SDL_PollEvent(&event) )
        {
            if ( event.type == SDL_QUIT )  {  done = 1; menu = 1;  }
            
            
            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    if(menuPlay.hilighted == true)
                    {
                        menu =1;
                        return 0;
                    }
                    
                    if(menuQuit.hilighted == true)
                    {
                        menu =1;
                        done = 1;
                        return 0;
                    }
                }
            }
            
            if ( event.type == SDL_MOUSEMOTION )
            {
                x = event.motion.x; 
                y = event.motion.y;
                //If the mouse is over the button 
                if( ( x > menuPlay.xpos ) && ( x < menuPlay.xpos + menuPlay.w ) && ( y > menuPlay.ypos ) && 
                        ( y < menuPlay.ypos + menuPlay.h ) ) 
                { 
                    menuPlay.face = menuPlay.faceIn; 
                    menuPlay.hilighted = true;
                }
                else
                {
                    menuPlay.face = menuPlay.faceOut;
                    menuPlay.hilighted = false;
                }
                
                
                //If the mouse is over the button 
                if( ( x > menuQuit.xpos ) && ( x < menuQuit.xpos + menuPlay.w ) && ( y > menuQuit.ypos ) && 
                        ( y < menuQuit.ypos + menuQuit.h ) ) 
                { 
                    //Set the button sprite 
                    menuQuit.face = menuQuit.faceIn; 
                    menuQuit.hilighted = true;
                }
                else
                {
                    menuQuit.face = menuQuit.faceOut;
                    menuQuit.hilighted = false;
                }
            }
        }
        draw();
        SystemUse.DrawIMG(menuPlay.face,menuPlay.xpos,menuPlay.ypos,screen);
        SystemUse.DrawIMG(menuQuit.face,menuQuit.xpos,menuQuit.ypos,screen);
        SDL_Flip(screen);
    }
    return 0;
}
    

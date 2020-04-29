int MainLoop()
{   
    menuLoop();
    while(done==0)
    {
        Collision();
        GetKeys();
        
        //Draw everything
        draw();
        
        //Movement();
        Player1.Move( delta.get_ticks() );
        AI(Player2,(int)Player1.xpos,(int)Player1.ypos);
        Player2.Move( delta.get_ticks() );
        
        
       //If we are cooling down, add to the time.
       if(Player1.coolDownT < Player1.coolDown)
            Player1.coolDownT  += delta.get_ticks();
           
       if(Player2.coolDownT < Player2.coolDown)
            Player2.coolDownT  += delta.get_ticks();
            
       
       clockTimer += delta.get_ticks();
       
        //reset the timer
        delta.start();
       
       
       if(Player1.HP <= 0)
       {
            MessageBox(NULL, "You are a Losser","Looser",MB_ICONEXCLAMATION);
            SetInstances();
            menuLoop();
       }
       
       if(Player2.HP <= 0)
       {
            MessageBox(NULL, "You are a Winner","Winner",MB_ICONEXCLAMATION);
            SetInstances();
            menuLoop();
       }
       
        if((int)Player1.HP < (int)Player1.originalHP)
        {
            Player1.HP += Player1.regen * ( delta.get_ticks() / 1000.f );
        }
       
        SDL_Flip(screen);
    }
    
    return 0;
}

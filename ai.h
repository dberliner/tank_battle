int changeComputerDir(int dir)
{
    if(dir == 0)
    {
        //alter the dimentions if the tank has moved anything but 180 degrees
        if(Player2.direction == 1 || Player2.direction == 3)
        {
             float dirTemp = Player2.x;
             Player2.x = Player2.y;
             Player2.y = dirTemp;
        }
        Player2.direction = 0;
        Player2.yspeed = -Player2.yvel;
        Player2.xspeed = 0;
        keyDown=true;
    }
  
  
    if(dir == 1)
    {
        //alter the dimentions if the tank has moved anything but 180 degrees
        if(Player2.direction == 0 || Player2.direction == 2)
        {
           float dirTemp = Player2.x;
           Player2.x = Player2.y;
           Player2.y = dirTemp;
        }
        Player2.direction = 1;
        Player2.xspeed = Player2.yvel; 
        Player2.yspeed = 0;
        keyDown=true;
    }

    if(dir == 2)
    {
        //alter the dimentions if the tank has moved anything but 180 degrees
        if(Player2.direction == 1 || Player2.direction == 3)
        {
             float dirTemp = Player2.x;
             Player2.x = Player2.y;
             Player2.y = dirTemp;
        }
        Player2.direction = 2;
        Player2.yspeed = Player2.yvel;
        Player2.xspeed = 0;
        keyDown=true;
    }

    if(dir == 3)
    {
        //alter the dimentions if the tank has moved anything but 180 degrees
        if(Player2.direction == 0 || Player2.direction == 2)
        {
             float dirTemp = Player2.x;
             Player2.x = Player2.y;
             Player2.y = dirTemp;
        }
        
        Player2.direction = 3;
        Player2.xspeed = -Player2.yvel;
        Player2.yspeed = 0;
        keyDown=true;
    }
}

int AI(Player &computer, int x, int y)
{
    int xDist =  (int)x - (int)computer.xpos;
    int yDist =  (int)y - (int)computer.ypos;
    
    
        
    // Remember the first rule of warfare: Shoot first, ask questions later.
    if(abs(xDist) < 10)
    {
        computer.shotDelay += delta.get_ticks();

        if(yDist < 0)
        {
                 changeComputerDir(0);
        }
        if(yDist > 0)
        {
                 changeComputerDir(2);
        }
        if(computer.shotDelay > computer.shotDelayT)
        {
                 computer.shotDelay =0;
                 computer.fire();
        }
    }
    
    // If we have a line of fire
    if(abs(yDist) < 10)
    {
        computer.shotDelay += delta.get_ticks();
        if(xDist > 0)
        {
                 changeComputerDir(1);
        }
        if(xDist < 0)
        {
                 changeComputerDir(3);
        }
        if(computer.shotDelay > computer.shotDelayT)
        {
                 computer.shotDelay =0;
                 computer.fire();
        }
    }
    
    
    // In order to change direction, we need to first ordain that it is worthwhile.
    //  Since the most effieint path changed many times a second we need to keep it heading one direction
    //  until that diection is not only less effecient, it has to be counterproductive.
    // If any one of the next four conditions are true, it is still heading the right way.
    if(computer.direction == 0)
    {
         if((Player1.ypos-Player1.y)> computer.ypos)
         {
              return 0;
         }
    }
    
    if(computer.direction == 1)
    {
         if((Player1.xpos)> computer.xpos+computer.x)
         {
              return 0;
         }
    }
    
    if(computer.direction == 2)
    {
         if((Player1.ypos-Player1.y)> computer.ypos)
         {
              return 0;
         }
    }
    
    if(computer.direction == 3)
    {
         if((Player1.xpos+Player1.x)< computer.x)
         {
              return 0;
         }
    }
    
    //we pass though the above, the tank is NOT heading in a direction that goes towards Player1
    if(abs(xDist) > abs(yDist) )
    {
        //If it is a closer drive on the X axis
        if(xDist > 0)
        {
                 if(computer.direction != 1)
                   changeComputerDir(1);
        }
        if(0> xDist )
        {
              if(computer.direction != 3)
                 changeComputerDir(3);
        }
    }
    
    
    else if(abs(xDist) < abs(yDist))
    {
        if(yDist < 0)
        {
              if(computer.direction != 0)
                 changeComputerDir(0);
        }
        if(yDist > 0)
        {
              if(computer.direction != 2)
                 changeComputerDir(2);
        }
    }
}

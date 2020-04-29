int Movement()
{
    return 0;
}

int collide(Player &player, Wall &wall)
{
    if(wall.HP > 0)
    {
        if(player.ypos+player.y > wall.ypos && player.ypos < wall.ypos+wall.y &&  
             player.xpos+player.x > wall.xpos && player.xpos < wall.xpos+wall.x)
        {
            player.xpos = player.xpos - player.calcXSpeed;
            player.ypos = player.ypos - player.calcYSpeed;
        }
    
        for(int i=player.roundCap;i>=0;i--)
        {
            if(player.Ammo[i].active == true)
            {
                 if(player.Ammo[i].xpos+player.Ammo[i].x > wall.xpos && player.Ammo[i].xpos < wall.xpos+wall.x && 
                      player.Ammo[i].ypos+player.Ammo[i].y > wall.ypos && player.Ammo[i].ypos < wall.ypos+wall.y)
                 {
                      player.Ammo[i].active = false;
                      wall.HP -= player.damage;
                 }
                 
                 
                 //check if our player's bullet has colided with the boundaries
                if(player.Ammo[i].ypos > WINDOW_H-player.Ammo[i].y)
                {
                     player.Ammo[i].active = false;
                }
                if(player.Ammo[i].ypos <= 0)
                {
                     player.Ammo[i].active = false;
                }
                
                if(player.Ammo[i].xpos > WINDOW_W-player.Ammo[i].x)
                {
                     player.Ammo[i].active = false;
                }
                if(player.Ammo[i].xpos <= 0)
                {
                     player.Ammo[i].active = false;
                }
            }
        }
    }
    return 0;
}


int collide(Player &player, Player &player2)
{
    if(player2.HP > 0)
    {
        //if player is heading up or down
        if(player.direction == 0 || player.direction == 2)
        {
            if(player.ypos+player.y > player2.ypos && player.ypos < player2.ypos+player2.y &&  
                 player.xpos+player.x > player2.xpos && player.xpos < player2.xpos+player2.x)
            {
                 player2.stop();
                 player.stop();
            }
        }
        
        //if player is heading right or left
        if(player.direction == 1 || player.direction == 3)
        {
            if(player.xpos+player.x > player2.xpos && player.xpos < player2.xpos+player2.x &&  
                 player.ypos+player.y > player2.ypos && player.ypos < player2.ypos+player2.y)
            {
                 player2.stop();
                 player.stop();
            }
        }
        
        for(int i=player.roundCap;i>=0;i--)
        {
            if(player.Ammo[i].active == true)
            {
                 if(player.Ammo[i].xpos+player.Ammo[i].x > player2.xpos && player.Ammo[i].xpos < player2.xpos+player2.x && 
                      player.Ammo[i].ypos+player.Ammo[i].y > player2.ypos && player.Ammo[i].ypos < player2.ypos+player2.y)
                 {
                      player.Ammo[i].active = false;
                      player2.HP -= player.damage;
                 }
                 
                 
                 //check if our player has colided with the walls
                if(player.Ammo[i].ypos > WINDOW_H-player.Ammo[i].y)
                {
                     player.Ammo[i].active = false;
                }
                if(player.Ammo[i].ypos <= 0)
                {
                     player.Ammo[i].active = false;
                }
                
                if(player.Ammo[i].xpos > WINDOW_W-player.Ammo[i].x)
                {
                     player.Ammo[i].active = false;
                }
                if(player.Ammo[i].xpos <= 0)
                {
                     player.Ammo[i].active = false;
                }
            }
        }
    }
    return 0;
}



int checkHit(Player &player, Player &player2)
{
    for(int i=player.roundCap;i>=0;i--)
    {
        if(player.Ammo[i].active == true)
        {
             if(player.Ammo[i].xpos+player.Ammo[i].x > player2.xpos && player.Ammo[i].xpos < player2.xpos+player2.x && 
                  player.Ammo[i].ypos+player.Ammo[i].y > player2.ypos && player.Ammo[i].ypos < player2.ypos+player2.y)
             {
                  player.Ammo[i].active = false;
                  player2.HP -= player.damage;
             }
        }
    }
    return 0;
}



int collideEnd(Player &player)
{
    if(player.ypos > WINDOW_H-player.y)
    {
         player.ypos = WINDOW_H-player.y;
    }
    if(player.ypos <= 0)
    {
         player.ypos = 0;
    }
    
    if(player.xpos > WINDOW_W-player.x)
    {
         player.xpos =  WINDOW_W-player.x;
    }
    if(player.xpos <= 0)
    {
         player.xpos = 0;
    }
    return 0;
}

int Collision()
{
    collideEnd(Player1);
    collideEnd(Player2);
    
    collide(Player1,wall1);
    collide(Player1,wall2);
    collide(Player1,wall3);
    collide(Player1,wall4);
    
    
    collide(Player2,wall1);
    collide(Player2,wall2);
    collide(Player2,wall3);
    collide(Player2,wall4);
    
    checkHit(Player1,Player2);
    checkHit(Player2,Player1);
    
    //check collision with walls
    return 0;
}



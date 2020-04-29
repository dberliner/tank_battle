int showInfo()
{
       
       //show your helth bar
       SystemUse.DrawIMG(hpTitle,0,WINDOW_H-5,screen);
       float width = Player1.HP/Player1.originalHP;
       
       SystemUse.DrawIMG(yourHP, 90 , WINDOW_H+1 ,
                            (int)(width*125), 20, 0, 0,
                            screen);
        if(Player1.coolDownT < Player1.coolDown)
        {
            Player1.coolDownS = TTF_RenderText_Solid(font, "Weapons Status: Cooling..." , textColor );
        }
        else
        {
            Player1.coolDownS = TTF_RenderText_Solid(font, "Weapons Status: Ready to fire!" , textColor );
        }
        
        SystemUse.DrawIMG(Player1.coolDownS,250,WINDOW_H-5,screen);
    return 0;
}

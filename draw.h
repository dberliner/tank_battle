int draw()
{
    SystemUse.DrawIMG(Bg,0,0,screen);
    SystemUse.DrawIMG(Bottom,0,WINDOW_H,screen);
    Player1.Draw(screen);
    Player2.Draw(screen);
    Player1.drawBullets(screen);
    Player2.drawBullets(screen);
    
    if(wall1.HP > 0)
        wall1.Draw(screen);
    if(wall2.HP > 0)
        wall2.Draw(screen);
    if(wall3.HP > 0)
        wall3.Draw(screen);
    if(wall4.HP > 0)
        wall4.Draw(screen);
    
    showInfo();
    
}

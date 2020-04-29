#include "load.h"

int main(int argc, char *argv[])
{
    //set the instances
    SetInstances();
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {

        //MessageBox(NULL,"Cant init SDL.","Fatal Error",MB_OK | MB_ICONINFORMATION);
        exit(1);
    }
    atexit(SDL_Quit);
    atexit(TTF_Quit);
    screen=SDL_SetVideoMode(WINDOW_W,WINDOW_H+EXTRA_X,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        //MessageBox(NULL,"Cant init video","Fatal Error",MB_OK | MB_ICONINFORMATION);
        exit(1);
    }
    
    delta.start();
    MainLoop();
    return 0;
}

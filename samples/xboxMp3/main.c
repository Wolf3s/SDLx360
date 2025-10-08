#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include <stdio.h>
#include <SDL.h>

#define WIDTH 640
#define HEIGHT 480
#define BPP 2
#define DEPTH 16

static void setpixel(SDL_Surface* screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    Uint16 * __restrict pixmem32;
    Uint16 colour;  
 
    colour = SDL_MapRGB( screen->format, r, g, b );
  
    pixmem32 = (Uint16*) screen->pixels  + y + x;
    *pixmem32 = colour;
}


void DrawScreen(SDL_Surface* __restrict  screen, int h)
{ 
    int x, y, ytimesw;
  
    if(SDL_MUSTLOCK(screen)) 
    {
        if(SDL_LockSurface(screen) < 0) return;
    }

    for(y = 0; y < screen->h; y++ ) 
    {
        ytimesw = y*screen->pitch>>1;
        for( x = 0; x < screen->w; x++ ) 
        {
            setpixel(screen, x, ytimesw, (x<<2)>>8+y+h, (y<<2)>>8+x+h, h);
        }
    }

    if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  
    SDL_Flip(screen); 
}


int main()
{
    SDL_Surface * __restrict screen;
//    SDL_Event event;
  
    int keypress = 0;
    int h=0; 
	Mix_Music *mus;
  
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) return 1;
   
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_FULLSCREEN|SDL_HWSURFACE|SDL_DOUBLEBUF)))
    {
        SDL_Quit();
        return 1;
    }
  
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return -1;
	
	mus = Mix_LoadMUS("D:\\Teste.mp3");

	Mix_PlayMusic(mus, -1);
	
	while(!keypress) 
    {
         DrawScreen(screen,h++);
    }

    SDL_Quit();
  
    return 0;
}

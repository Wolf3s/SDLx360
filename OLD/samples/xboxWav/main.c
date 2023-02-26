#include <SDL.h>
#include <SDL_mixer.h>

#define WIDTH 1280
#define HEIGHT 720
#define BITS 32

int main(int args, char *argv[])
{
	SDL_Surface *screen;
	SDL_Surface *chalice;
	Mix_Music *chalice_mus;

	SDL_Init(SDL_INIT_EVERYTHING);

#ifdef WIP
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	  return 0;
#endif
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BITS, SDL_SWSURFACE);

	chalice = SDL_LoadBMP("Calice.bmp");

#ifdef WIP
	chalice_mus = Mix_LoadMUS("Calice.wav");
#endif

	SDL_BlitSurface(chalice, NULL, screen, NULL);

	SDL_Flip(screen);

	SDL_Delay(300000);

	SDL_FreeSurface(chalice);

	SDL_Quit();

}
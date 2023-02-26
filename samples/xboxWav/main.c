#include <SDL.h>

#define WIDTH 1280
#define HEIGHT 720
#define BITS 32

int main(int args, char *argv[])
{
	SDL_Surface * __restrict screen; *screen, *chalice;

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BITS, SDL_FULLSCREEN|SDL_HWSURFACE|SDL_DOUBLEBUF);

	chalice = SDL_LoadBMP("Hello.bmp");

	SDL_BlitSurface(chalice, NULL, screen, NULL);

	SDL_ShowCursor(SDL_DISABLE);

	SDL_Flip(screen);

	SDL_Delay(2000);

	SDL_FreeSurface(chalice);

	SDL_Quit();

	return 0;
}
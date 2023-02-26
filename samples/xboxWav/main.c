#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#define WIDTH 1280
#define HEIGHT 720
#define BITS 32

SDL_Surface * __restrict screen;
SDL_Surface *chalice;
Mix_Music *mus;

int main(int args, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096);

	mus = Mix_LoadMUS("Teste.wav");

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BITS, SDL_FULLSCREEN|SDL_HWSURFACE);

	chalice = SDL_LoadBMP("hello.bmp");

	SDL_BlitSurface(chalice, NULL, screen, NULL);

	Mix_PlayMusic(mus, -1);

	SDL_ShowCursor(SDL_DISABLE);

	SDL_Flip(screen);

	SDL_Delay(2000);

	SDL_FreeSurface(chalice);

	SDL_Quit();

	return 0;
}
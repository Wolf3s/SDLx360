/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_systimer.c,v 1.1 2003/07/18 15:19:33 lantus Exp $";
#endif

#include <xtl.h>
#include "SDL_timer.h"
#include "SDL_timer_c.h"
#include "SDL_error.h"


#define TIME_WRAP_VALUE	(~(DWORD)0)

/* The first (low-resolution) ticks value of the application */
static DWORD start;

#ifndef USE_GETTICKCOUNT
/* Store if a high-resolution performance counter exists on the system */
static BOOL hires_timer_available;
/* The first high-resolution ticks value of the application */
static LARGE_INTEGER hires_start_ticks;
/* The number of ticks per second of the high-resolution performance counter */
static LARGE_INTEGER hires_ticks_per_second;
#endif

void SDL_StartTicks(void)
{
	/* Set first ticks value */
	if (QueryPerformanceFrequency(&hires_ticks_per_second) == TRUE)
	{
		hires_timer_available = TRUE;
		QueryPerformanceCounter(&hires_start_ticks);
	}
}

Uint32 SDL_GetTicks(void)
{
	DWORD now, ticks;
	LARGE_INTEGER hires_now;

	if (hires_timer_available)
	{
		QueryPerformanceCounter(&hires_now);

		hires_now.QuadPart -= hires_start_ticks.QuadPart;
		hires_now.QuadPart *= 1000;
		hires_now.QuadPart /= hires_ticks_per_second.QuadPart;

		return (DWORD)hires_now.QuadPart;
	}

	if ( now < start ) {
		ticks = (TIME_WRAP_VALUE-start) + now;
	} else {
		ticks = (now - start);
	}
	return(ticks);
}

void SDL_Delay(Uint32 ms)
{
	Sleep(ms);
}

int SDL_SYS_TimerInit(void)
{
	return(0);
}

void SDL_SYS_TimerQuit(void)
{
	return;
}

int SDL_SYS_StartTimer(void)
{
	return(-1);
}

void SDL_SYS_StopTimer(void)
{

}


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
 "@(#) $Id: SDL_yuv.c,v 1.1 2003/07/18 15:19:33 lantus Exp $";
#endif

/* This is the implementation of the YUV video surface support */

#include <stdlib.h>
#include <string.h>

#include "SDL_getenv.h"
#include "SDL_video.h"
#include "SDL_sysvideo.h"
#include "SDL_yuvfuncs.h"
#include "SDL_yuv_sw_c.h"


SDL_Overlay *SDL_CreateYUVOverlay(int w, int h, Uint32 format,
                                  SDL_Surface *display)
{
	SDL_VideoDevice *video = current_video;
	SDL_VideoDevice *this  = current_video;
	const char *yuv_hwaccel;
	SDL_Overlay *overlay;

	overlay = NULL;

	/* Display directly on video surface, if possible */

	if ( (display == SDL_PublicSurface) &&
	     ((SDL_VideoSurface->format->BytesPerPixel == 2) ||
	      (SDL_VideoSurface->format->BytesPerPixel == 4)) ) {
		display = SDL_VideoSurface;
	}
 
 
	yuv_hwaccel = 1;

	if ((display == SDL_VideoSurface) && video->CreateYUVOverlay)  
    {
		overlay = video->CreateYUVOverlay(this, w, h, format, display);
	}
	/* If hardware YUV overlay failed ... */

	yuv_hwaccel = 0;
	if ( overlay == NULL ) {
		overlay = SDL_CreateYUV_SW(this, w, h, format, display);
	}
	return overlay;
}

int SDL_LockYUVOverlay(SDL_Overlay *overlay)
{
	return overlay->hwfuncs->Lock(current_video, overlay);
}

void SDL_UnlockYUVOverlay(SDL_Overlay *overlay)
{
	overlay->hwfuncs->Unlock(current_video, overlay);
}

int SDL_DisplayYUVOverlay(SDL_Overlay *overlay, SDL_Rect *dstrect)
{
 	SDL_Rect src, dst;
	int srcx, srcy, srcw, srch;
	int dstx, dsty, dstw, dsth;

	if ( overlay == NULL || dstrect == NULL ) {
		SDL_SetError("Passed NULL overlay or dstrect");
		return -1;
	}

	/* Clip the rectangle to the screen area */
	srcx = 0;
	srcy = 0;
	srcw = overlay->w;
	srch = overlay->h;
	dstx = dstrect->x;
	dsty = dstrect->y;
	dstw = dstrect->w;
	dsth = dstrect->h;
	if ( dstx < 0 ) {
		srcw += (dstx * overlay->w) / dstrect->w;
		dstw += dstx;
		srcx -= (dstx * overlay->w) / dstrect->w;
		dstx = 0;
	}
	if ( (dstx+dstw) > current_video->screen->w ) {
		int extra = (dstx+dstw - current_video->screen->w);
		srcw -= (extra * overlay->w) / dstrect->w;
		dstw -= extra;
	}
	if ( dsty < 0 ) {
		srch += (dsty * overlay->h) / dstrect->h;
		dsth += dsty;
		srcy -= (dsty * overlay->h) / dstrect->h;
		dsty = 0;
	}
	if ( (dsty+dsth) > current_video->screen->h ) {
		int extra = (dsty+dsth - current_video->screen->h);
		srch -= (extra * overlay->h) / dstrect->h;
		dsth -= extra;
	}
	if ( srcw <= 0 || srch <= 0 ||
	     srch <= 0 || dsth <= 0 ) {
		return 0;
	}
	/* Ugh, I can't wait for SDL_Rect to be int values */
	src.x = srcx;
	src.y = srcy;
	src.w = srcw;
	src.h = srch;
	dst.x = dstx;
	dst.y = dsty;
	dst.w = dstw;
	dst.h = dsth;

	return overlay->hwfuncs->Display(current_video, overlay, &src, &dst);
}

void SDL_FreeYUVOverlay(SDL_Overlay *overlay)
{
	if ( overlay ) {
		if ( overlay->hwfuncs ) {
			overlay->hwfuncs->FreeHW(current_video, overlay);
		}
		free(overlay);
	}
}

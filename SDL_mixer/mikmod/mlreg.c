/*	MikMod sound library
	(c) 1998, 1999 Miodrag Vallat and others - see file AUTHORS for
	complete list.

	This library is free software; you can redistribute it and/or modify
	it under the terms of the GNU Library General Public License as
	published by the Free Software Foundation; either version 2 of
	the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
	02111-1307, USA.
*/

/*==============================================================================

  $Id: mlreg.c,v 1.1 2003/07/18 15:13:05 lantus Exp $

  Routine for registering all loaders in libmikmod for the current platform.

==============================================================================*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mikmod_internals.h"

void MikMod_RegisterAllLoaders_internal(void)
{
#if 1
	_mm_registerloader(&load_it);
	_mm_registerloader(&load_mod);
	_mm_registerloader(&load_s3m);
	_mm_registerloader(&load_xm);
#else
	_mm_registerloader(&load_669);
	_mm_registerloader(&load_amf);
	_mm_registerloader(&load_dsm);
	_mm_registerloader(&load_far);
	_mm_registerloader(&load_gdm);
	_mm_registerloader(&load_it);
	_mm_registerloader(&load_imf);
	_mm_registerloader(&load_mod);
	_mm_registerloader(&load_med);
	_mm_registerloader(&load_mtm);
	_mm_registerloader(&load_s3m);
	_mm_registerloader(&load_stm);
	_mm_registerloader(&load_stx);
	_mm_registerloader(&load_ult);
	_mm_registerloader(&load_uni);
	_mm_registerloader(&load_xm);

	_mm_registerloader(&load_m15);
#endif
}

void MikMod_RegisterAllLoaders(void)
{
	MUTEX_LOCK(lists);
	MikMod_RegisterAllLoaders_internal();
	MUTEX_UNLOCK(lists);
}

void MikMod_UnregisterAllLoaders(void)
{
	MUTEX_LOCK(lists);
	_mm_unregisterloaders();
	MUTEX_UNLOCK(lists);
}

/* ex:set ts=4: */

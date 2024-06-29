/*
========================================================================

                               DOOM Retro
         The classic, refined DOOM source port. For Windows PC.

========================================================================

  Copyright © 1993-2022 by id Software LLC, a ZeniMax Media company.
  Copyright © 2013-2022 by Brad Harding <mailto:brad@doomretro.com>.

  DOOM Retro is a fork of Chocolate DOOM. For a list of acknowledgments,
  see <https://github.com/bradharding/doomretro/wiki/ACKNOWLEDGMENTS>.

  This file is a part of DOOM Retro.

  DOOM Retro is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation, either version 3 of the license, or (at your
  option) any later version.

  DOOM Retro is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DOOM Retro. If not, see <https://www.gnu.org/licenses/>.

  DOOM is a registered trademark of id Software LLC, a ZeniMax Media
  company, in the US and/or other countries, and is used without
  permission. All other trademarks are the property of their respective
  holders. DOOM Retro is in no way affiliated with nor endorsed by
  id Software.

========================================================================
*/

#pragma once

#include "doomtype.h"
#include "SDL.h"

#define MAX_MOUSE_BUTTONS   8

#define GAMMALEVELS         21

bool MouseShouldBeGrabbed(void);
void I_InitKeyboard(void);
void I_ShutdownKeyboard(void);
bool GetCapsLockState(void);

// Called by D_DoomLoop,
// called before processing each tic in a frame.
// Quick synchronous operations are performed here.
// Can call D_PostEvent.
void I_StartTic(void);

// Called by D_DoomMain,
// determines the hardware configuration
// and sets up the video mode
void I_InitGraphics(void);
void I_RestartGraphics(bool recreatewindow);
void I_CapFPS(int cap);

void GetWindowPosition(void);
void GetWindowSize(void);
void GetScreenResolution(void);

// Takes full 8 bit values.
void I_SetPalette(byte *playpal);
void I_SetExternalAutomapPalette(void);
void I_SetSimplePalette(byte *playpal);
void I_SetPaletteWithBrightness(byte *playpal, double brightness);

void I_UpdateBlitFunc(bool shake);
bool I_CreateExternalAutomap(void);
void I_DestroyExternalAutomap(void);

void I_ToggleFullscreen(void);
void I_SetPillarboxes(void);
void I_SetMotionBlur(int percent);

void I_SetGamma(float value);

#if defined(_WIN32)
void I_WindowResizeBlit(void);
#endif

extern void (*blitfunc)(void);
extern void (*mapblitfunc)(void);

extern bool         sendpause;
extern bool         waspaused;

extern int          keydown;

extern int          gammaindex;
extern const float  gammalevels[GAMMALEVELS];

extern int          windowx;
extern int          windowy;
extern int          windowheight;
extern int          windowwidth;
extern int          windowborderwidth;
extern int          windowborderheight;

extern bool         windowfocused;

extern SDL_Window   *window;
extern SDL_Renderer *renderer;

extern SDL_Window   *mapwindow;
extern SDL_Renderer *maprenderer;
extern byte         *mapscreen;

extern byte         *PLAYPAL;

extern bool         altdown;

extern int          framespersecond;
extern int          refreshrate;
extern uint64_t     starttime;
extern int          frames;

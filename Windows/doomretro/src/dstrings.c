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

#include "d_deh.h"
#include "dstrings.h"

char **endmsg[] =
{
    // DOOM1
    &s_QUITMSG,
    &s_QUITMSG1,
    &s_QUITMSG2,
    &s_QUITMSG3,
    &s_QUITMSG4,
    &s_QUITMSG5,
    &s_QUITMSG6,
    &s_QUITMSG7,

    // QuitDOOM II messages
    &s_QUITMSG,
    &s_QUITMSG8,
    &s_QUITMSG9,
    &s_QUITMSG10,
    &s_QUITMSG11,
    &s_QUITMSG12,
    &s_QUITMSG13,
    &s_QUITMSG14
};

char *devendmsg[] =
{
    DEVQUITMSG1,
    DEVQUITMSG2,
    DEVQUITMSG3,
    DEVQUITMSG4,
    DEVQUITMSG5,
    DEVQUITMSG6,
    DEVQUITMSG7,
    DEVQUITMSG8
};

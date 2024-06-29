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

#include "c_console.h"
#include "doomstat.h"
#include "i_gamecontroller.h"
#include "m_config.h"

static SDL_GameController   *gamecontroller;
static bool                 gamecontrollerconnected;
static bool                 gamecontrollerrumbles;

int                         gamecontrollerbuttons = 0;
short                       gamecontrollerthumbLX = 0;
short                       gamecontrollerthumbLY = 0;
short                       gamecontrollerthumbRX = 0;
short                       gamecontrollerthumbRY = 0;
float                       gamecontrollerhorizontalsensitivity;
float                       gamecontrollerverticalsensitivity;
short                       gamecontrollerleftdeadzone;
short                       gamecontrollerrightdeadzone;

int                         damagerumbletics = 0;
int                         barrelrumbletics = 0;
int                         weaponrumbletics = 0;
int                         idlechainsawrumblestrength;
int                         restoredrumblestrength;
static int                  currentstrength;

void I_InitGameController(void)
{
    if (gamecontrollerconnected)
        return;

#if (SDL_MAJOR_VERSION == 2 && SDL_PATCHLEVEL >= 18) || SDL_MAJOR_VERSION > 2
    SDL_SetHintWithPriority(SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE, "1", SDL_HINT_OVERRIDE);
    SDL_SetHintWithPriority(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE, "1", SDL_HINT_OVERRIDE);
#endif

    SDL_SetHintWithPriority(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1", SDL_HINT_OVERRIDE);

    if (devparm)
        SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");

    for (int i = 0, numjoysticks = SDL_NumJoysticks(); i < numjoysticks; i++)
        if (SDL_IsGameController(i))
        {
            const char  *name;
            bool        repeated;

            gamecontroller = SDL_GameControllerOpen(i);

            gamecontrollerconnected = true;

            if ((name = SDL_GameControllerName(gamecontroller)))
                repeated = C_OutputNoRepeat("A controller called \"%s\" is connected.", name);
            else
                repeated = C_OutputNoRepeat("A controller is connected.");

            if (SDL_GameControllerHasRumble(gamecontroller))
                gamecontrollerrumbles = true;
            else if (!repeated && (joy_rumble_damage || joy_rumble_barrels || joy_rumble_weapons))
                C_Warning(1, "This controller doesn't rumble.");

            I_SetGameControllerLeftDeadZone();
            I_SetGameControllerRightDeadZone();
            I_SetGameControllerHorizontalSensitivity();
            I_SetGameControllerVerticalSensitivity();

            SDL_GameControllerSetLED(gamecontroller, 255, 0, 0);

            return;
        }
}

void I_ShutdownGameController(void)
{
    if (!gamecontroller)
        return;

    SDL_GameControllerSetLED(gamecontroller, 0, 0, 255);

    gamecontrollerconnected = false;
    gamecontrollerrumbles = false;

    SDL_GameControllerClose(gamecontroller);
}

void I_GameControllerRumble(int strength)
{
    if (!gamecontrollerrumbles)
        return;

    if (!strength
        || (lasteventtype == ev_controller
            && (strength == idlechainsawrumblestrength || strength >= currentstrength)))
    {
        currentstrength = strength;
        SDL_GameControllerRumble(gamecontroller, currentstrength, currentstrength, UINT32_MAX);
    }
}

void I_UpdateGameControllerRumble(void)
{
    if (gamecontrollerrumbles
        && ((weaponrumbletics && !--weaponrumbletics && !damagerumbletics && !barrelrumbletics)
            || (damagerumbletics && !--damagerumbletics && !barrelrumbletics)
            || (barrelrumbletics && !--barrelrumbletics))
        && lasteventtype == ev_controller)
    {
        currentstrength = idlechainsawrumblestrength;
        SDL_GameControllerRumble(gamecontroller, currentstrength, currentstrength, UINT32_MAX);
    }
}

void I_StopGameControllerRumble(void)
{
    if (!gamecontrollerrumbles)
        return;

    SDL_GameControllerRumble(gamecontroller, 0, 0, 0);
}

void I_SetGameControllerHorizontalSensitivity(void)
{
    gamecontrollerhorizontalsensitivity = (!joy_sensitivity_horizontal ? 0.0f :
        4.0f * joy_sensitivity_horizontal / joy_sensitivity_horizontal_max + 0.2f);
}

void I_SetGameControllerVerticalSensitivity(void)
{
    gamecontrollerverticalsensitivity = (!joy_sensitivity_vertical ? 0.0f :
        4.0f * joy_sensitivity_vertical / joy_sensitivity_vertical_max + 0.2f);
}

void I_SetGameControllerLeftDeadZone(void)
{
    gamecontrollerleftdeadzone = (short)(joy_deadzone_left * SHRT_MAX / 100.0f);
}

void I_SetGameControllerRightDeadZone(void)
{
    gamecontrollerrightdeadzone = (short)(joy_deadzone_right * SHRT_MAX / 100.0f);
}

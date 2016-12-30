/*
 * This file is part of vacation-cruft
 *
 * Copyright © 2016 Ikey Doherty <ikey@solus-project.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

#include <SDL.h>
#include <stdbool.h>

#include "player.h"
#include "sprite.h"
#include "tilesheet.h"
#include "util.h"

/**
 * Global state for the application
 */
typedef struct SnakeApp {
        SDL_Window *window;
        SDL_Renderer *render;
        bool running;
        bool fullscreen;
        TileSheet *sheet;
        Player *player;
} SnakeApp;

/**
 * Construct a new SnakeApp instance and perform any early setup
 */
SnakeApp *snake_app_new(void);

/**
 * Teardown the SnakeApp and return any resources
 */
void snake_app_free(SnakeApp *self);

/**
 * Handle events and update the game state
 */
void snake_app_update(SnakeApp *self, FrameInfo *frame);

/**
 * Render the current game state
 */
void snake_app_draw(SnakeApp *self, FrameInfo *frame);

/**
 * Set the application to be full screen (fake mode)
 */
void snake_app_set_fullscreen(SnakeApp *self, bool fullscreen);

/**
 * Run the main loop of the application
 */
int snake_app_run(SnakeApp *self);

DEF_AUTOFREE(SnakeApp, snake_app_free)

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */

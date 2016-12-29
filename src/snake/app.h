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

#include "util.h"

/**
 * Global state for the application
 */
typedef struct SnakeApp {
        SDL_Window *window;
        SDL_Renderer *render;
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

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

#include <SDL.h>

#include "app.h"

SnakeApp *snake_app_new()
{
        SnakeApp *ret = NULL;

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
                return NULL;
        }

        ret = calloc(1, sizeof(SnakeApp));

        /** TODO: Init resources! */
        return ret;
}

void snake_app_free(SnakeApp *app)
{
        if (!app) {
                return;
        }
        free(app);

        fprintf(stderr, "debug: Closing SDL\n");

        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit();
}

int snake_app_run(SnakeApp *app)
{
        return EXIT_FAILURE;
}

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

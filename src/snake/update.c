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

#include "app.h"

void snake_app_update(SnakeApp *self)
{
        SDL_Event event = { 0 };

        /* TODO: Handle keyboard events and whatnot */
        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_KEYDOWN:
                        /* Q = quit */
                        if (event.key.keysym.sym == SDLK_q) {
                                self->running = false;
                                return;
                        }
                        break;
                case SDL_KEYUP:
                        /* Alt+Enter = toggle full screen */
                        if (event.key.keysym.sym == SDLK_RETURN &&
                            (event.key.keysym.mod & KMOD_ALT)) {
                                snake_app_set_fullscreen(self, !self->fullscreen);
                                return;
                        }
                        break;
                /* Immediately quit */
                case SDL_QUIT:
                        self->running = false;
                        return;
                }
        }
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

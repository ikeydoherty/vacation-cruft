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

/**
 * Handle updates from keyboard input
 */
void snake_app_update_keyboard(SnakeApp *self, SDL_KeyboardEvent *event)
{
        /* Handle pressed events */
        if (event->state == SDL_PRESSED) {
                if (event->keysym.sym == SDLK_q) {
                        self->running = false;
                }
                return;
        }

        /* Handle released events */
        if (event->keysym.sym == SDLK_RETURN && (event->keysym.mod & KMOD_ALT)) {
                snake_app_set_fullscreen(self, !self->fullscreen);
        }
}

void snake_app_update(SnakeApp *self, RenderTarget *target)
{
        SDL_Event event = { 0 };

        /* Handle all events in this update */
        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                        snake_app_update_keyboard(self, &event.key);
                        break;
                /* Immediately quit */
                case SDL_QUIT:
                        self->running = false;
                        return;
                default:
                        break;
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

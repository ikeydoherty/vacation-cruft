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
        switch (event->keysym.sym) {
        /* Player direction */
        case SDLK_UP:
                player_set_direction(self->player, DIR_UP);
                break;
        case SDLK_DOWN:
                player_set_direction(self->player, DIR_DOWN);
                break;
        case SDLK_LEFT:
                player_set_direction(self->player, DIR_LEFT);
                break;
        case SDLK_RIGHT:
                player_set_direction(self->player, DIR_RIGHT);
                break;
        /* Full screen */
        case SDLK_RETURN:
                if (event->keysym.mod & KMOD_ALT && event->state == SDL_RELEASED) {
                        snake_app_set_fullscreen(self, !self->fullscreen);
                }
                break;
        /* Quit */
        case SDLK_q:
                if (event->state == SDL_PRESSED) {
                        self->running = false;
                }
                break;
        }
}

void snake_app_update(SnakeApp *self, FrameInfo *frame)
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

        /* Update the player */
        player_update(self->player, frame);
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

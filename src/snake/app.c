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
#include "sprite.h"

SnakeApp *snake_app_new()
{
        SnakeApp *ret = NULL;

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
                return NULL;
        }

        ret = calloc(1, sizeof(SnakeApp));
        if (!ret) {
                return ret;
        }

        /* create the window */
        ret->window = SDL_CreateWindow("Snake",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       800,
                                       600,
                                       SDL_WINDOW_HIDDEN);
        if (!ret->window) {
                goto bail;
        }

        /* create a 2d renderer */
        ret->render = SDL_CreateRenderer(ret->window,
                                         -1,
                                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!ret->render) {
                goto bail;
        }

        return ret;

/* Something disastrous happened */
bail:
        snake_app_free(ret);
        return NULL;
}

void snake_app_free(SnakeApp *self)
{
        if (!self) {
                return;
        }

        /* Free our resources */
        SDL_DestroyWindow(self->window);
        SDL_DestroyRenderer(self->render);
        free(self);

        /* Free SDL resources */
        fprintf(stderr, "debug: Closing SDL\n");
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_Quit();
}

int snake_app_run(SnakeApp *self)
{
        int ret = EXIT_SUCCESS;
        FrameInfo frame = {.render = self->render,
                           .rect = (SDL_Rect){
                               .x = 0, .y = 0, .w = 800, .h = 600,
                           } };

        /* Get us on screen */
        SDL_ShowWindow(self->window);

        self->running = true;

        /* Handle main loop */
        while (self->running) {
                snake_app_update(self, &frame);
                snake_app_draw(self, &frame);

                /* TODO: cap fps */
        }

        return ret;
}

void snake_app_set_fullscreen(SnakeApp *self, bool fullscreen)
{
        if (self->fullscreen == fullscreen) {
                return;
        }

        self->fullscreen = fullscreen;
        SDL_SetWindowFullscreen(self->window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
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

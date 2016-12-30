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

#include <SDL_image.h>

#include "tilesheet.h"
#include "util.h"

DEF_AUTOFREE(SDL_Surface, SDL_FreeSurface)

static SDL_Texture *load_texture(const char *path, SDL_Renderer *ren, SDL_Window *window)
{
        autofree(SDL_Surface) *img_surface = NULL, *opt_surface = NULL;
        SDL_Surface *win_surface = NULL;

        img_surface = IMG_Load(path);
        if (!img_surface) {
                fprintf(stderr, "Failed to load %s: %s\n", path, IMG_GetError());
                return NULL;
        }

        /* Mask magenta as transparent */
        SDL_SetColorKey(img_surface, SDL_TRUE, 0xFF00FF);

        /* If the window has no surface, we can't optimize it */
        win_surface = SDL_GetWindowSurface(window);
        if (!win_surface) {
                return SDL_CreateTextureFromSurface(ren, img_surface);
        }

        /* Try to optimize it */
        opt_surface = SDL_ConvertSurface(img_surface, win_surface->format, 0);
        if (!opt_surface) {
                fprintf(stderr, "Failed to optimize surface %s: %s\n", path, SDL_GetError());
                return SDL_CreateTextureFromSurface(ren, img_surface);
        }
        return SDL_CreateTextureFromSurface(ren, opt_surface);
}

TileSheet *tile_sheet_new(const char *path, int tile_size, SDL_Renderer *render, SDL_Window *window)
{
        SDL_Texture *texture = NULL;
        TileSheet *ret = NULL;

        texture = load_texture(path, render, window);
        if (!texture) {
                return NULL;
        }

        ret = calloc(1, sizeof(TileSheet));
        if (!ret) {
                SDL_DestroyTexture(texture);
                return NULL;
        }
        ret->texture = texture;
        ret->tile_size = tile_size;
        return ret;
}

void tile_sheet_render(TileSheet *self, int column, int row, SDL_Renderer *render, SDL_Rect target)
{
        SDL_Rect source = {.x = self->tile_size * column,
                           .y = self->tile_size * row,
                           .w = self->tile_size,
                           .h = self->tile_size };
        SDL_RenderCopy(render, self->texture, &source, &target);
}

void tile_sheet_free(TileSheet *self)
{
        if (!self) {
                return;
        }
        SDL_DestroyTexture(self->texture);
        free(self);
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

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

#include "player.h"

Player *player_new(TileSheet *sheet)
{
        Player p = {.sheet = sheet, .dir = DIR_RIGHT, .speed = 7 };
        Player *ret = NULL;

        ret = calloc(1, sizeof(Player));
        if (!ret) {
                return NULL;
        }
        *ret = p;
        return ret;
}

void player_free(Player *self)
{
        if (!self) {
                return;
        }
        free(self);
}

void player_set_direction(Player *self, PlayerDirection direction)
{
        /* Forbid inversing the direction */
        switch (direction) {
        case DIR_UP:
                if (self->dir == DIR_DOWN) {
                        return;
                }
                break;
        case DIR_DOWN:
                if (self->dir == DIR_UP) {
                        return;
                }
                break;
        case DIR_LEFT:
                if (self->dir == DIR_RIGHT) {
                        return;
                }
                break;
        case DIR_RIGHT:
        default:
                if (self->dir == DIR_LEFT) {
                        return;
                }
                break;
        }
        self->dir = direction;
}

void player_update(Player *self, FrameInfo *frame)
{
        double in_second = (frame->ticks - frame->prev_ticks) / 1000.0;
        if (in_second > 1.0) {
                return;
        }
        int distance = (int)((32 * self->speed) * in_second);

        switch (self->dir) {
        case DIR_UP:
                self->y -= distance;
                break;
        case DIR_DOWN:
                self->y += distance;
                break;
        case DIR_LEFT:
                self->x -= distance;
                break;
        case DIR_RIGHT:
        default:
                self->x += distance;
                break;
        }
}

void player_draw(Player *self, FrameInfo *info)
{
        /* DEMO CODE */
        SDL_Rect rect = {.x = self->x, .y = self->y, .w = 32, .h = 32 };
        double angle = 0.0;
        switch (self->dir) {
        case DIR_UP:
                angle = -90.0;
                break;
        case DIR_DOWN:
                angle = 90.0;
                break;
        case DIR_LEFT:
                angle = -180.0;
                break;
        case DIR_RIGHT:
        default:
                angle = 0.0;
                break;
        }
        tile_sheet_render_ex(self->sheet, 1, 0, info->render, rect, angle, NULL, SDL_FLIP_NONE);
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

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
        Player p = {.sheet = sheet, .dir = DIR_RIGHT, .speed = 4 };
        Player *ret = NULL;
        PlayerSegment *segments = NULL;

        /* Limit to 60 segments of the snake for now */
        segments = calloc(60, sizeof(PlayerSegment));
        if (!segments) {
                return NULL;
        }

        ret = calloc(1, sizeof(Player));
        if (!ret) {
                free(segments);
                return NULL;
        }
        p.segments = segments;
        p.n_segments = 0;
        *ret = p;
        /* Add one element */
        player_grow(ret);
        return ret;
}

void player_free(Player *self)
{
        if (!self) {
                return;
        }
        free(self->segments);
        free(self);
}

void player_set_direction(Player *self, PlayerDirection direction)
{
        /* Forbid inversing the direction */
        int tile_size = 32;
        int rows = 600 / tile_size;
        int cols = 800 / tile_size;

        fprintf(stderr, "Have %d rows, %d columns\n", rows, cols);

        /* Current row/column */
        int row = (int)floor((int)floor(self->segments[0].y) % rows);
        int col = (int)floor((int)floor(self->segments[0].x) % cols);

        switch (direction) {
        case DIR_UP:
                if (self->dir == DIR_DOWN) {
                        return;
                }
                row--;
                break;
        case DIR_DOWN:
                if (self->dir == DIR_UP) {
                        return;
                }
                row++;
                break;
        case DIR_LEFT:
                if (self->dir == DIR_RIGHT) {
                        return;
                }
                col--;
                break;
        case DIR_RIGHT:
        default:
                if (self->dir == DIR_LEFT) {
                        return;
                }
                col++;
                break;
        }
        self->dir = direction;
        self->segments[0].target_x = col * tile_size;
        self->segments[0].target_y = row * tile_size;

        fprintf(stderr,
                "Target: C: %d R: %d (X: %d Y: %d)\n",
                col,
                row,
                self->segments[0].target_x,
                self->segments[0].target_y);
}

void player_update(Player *self, FrameInfo *frame)
{
        /*
        double in_second = (frame->ticks - frame->prev_ticks) / 1000.0;
        if (in_second > 1.0) {
                return;
        }
        int distance = (int)((32 * self->speed) * in_second);

        switch (self->dir) {
        case DIR_UP:
                self->segments[0].y -= distance;
                break;
        case DIR_DOWN:
                self->segments[0].y += distance;
                break;
        case DIR_LEFT:
                self->segments[0].x -= distance;
                break;
        case DIR_RIGHT:
        default:
                self->segments[0].x += distance;
                break;
        }

        for (int i = self->n_segments; i > 0; i--) {
                self->segments[i].x = self->segments[i - 1].x;
                self->segments[i].y = self->segments[i - 1].y;
        }
        */
}

void player_draw(Player *self, FrameInfo *info)
{
        /* DEMO CODE */
        SDL_Rect rect = {.x = 0, .y = 0, .w = 32, .h = 32 };
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

        for (int i = 0; i < self->n_segments; i++) {
                int tile_no = i == 0 ? 1 : 0;
                rect.x = self->segments[i].x;
                rect.y = self->segments[i].y;
                tile_sheet_render_ex(self->sheet,
                                     tile_no,
                                     0,
                                     info->render,
                                     rect,
                                     angle,
                                     NULL,
                                     SDL_FLIP_NONE);
        }
}

void player_grow(Player *self)
{
        PlayerSegment *segment = NULL;
        if (self->n_segments + 1 > 60) {
                return;
        }

        self->n_segments++;
        int seg = self->n_segments - 1;
        segment = &self->segments[seg];

        segment->x = self->segments[seg].x;
        segment->y = self->segments[seg].y;
        /* Currently unused */
        segment->dir = self->dir;
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

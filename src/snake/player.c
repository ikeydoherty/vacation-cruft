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
        Player p = {.sheet = sheet, .dir = -1 };
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

static inline double clamp(double v, double min, double max)
{
        return ((v < min ? min : v) > max ? max : (v < min ? min : v));
}

static inline float clampf(float v, float min, float max)
{
        return ((v < min ? min : v) > max ? max : (v < min ? min : v));
}

void player_set_direction(Player *self, PlayerDirection direction)
{
        /* Forbid inversing the direction */
        int tile_size = 32;
        int rows = 600 / tile_size;
        int cols = 800 / tile_size;

        if (direction == self->dir) {
                return;
        }

        /* Current row/column */
        int row = (int)(self->segments[0].y / tile_size) % (rows);
        int col = (int)(self->segments[0].x / tile_size) % (cols);

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

        if (self->moving) {
                return;
        }

        self->moving = true;

        self->segments[0].start_x = self->segments[0].x;
        self->segments[0].start_y = self->segments[0].y;
        self->segments[0].target_x = col * tile_size;
        self->segments[0].target_y = row * tile_size;
        self->segments[0].dir = direction;
}

void player_update(Player *self, FrameInfo *frame)
{
        PlayerSegment *head = NULL;

        head = &self->segments[0];

        if (!self->moving) {
                return;
        }

        /* Reset tick start for the new frame */
        if (self->tick_start < 1) {
                self->tick_start = frame->ticks;
        }

        /* Find out the completion for movement over .2 seconds to move one block */
        double elapsed = (double)(frame->ticks - self->tick_start);
        float factor = clampf((float)(elapsed / 200.0), 0.0f, 1.0f);

        /* Animation finished */
        if (factor == 1.0f) {
                head->start_x = head->x = head->target_x;
                head->start_y = head->y = head->target_y;
                self->tick_start = 0;
                /* Continue movement in current direction */
                PlayerDirection dir = self->dir;
                self->dir = -1;
                self->moving = false;
                player_set_direction(self, dir);

                /* Clone segment behaviour */
                for (int i = self->n_segments; i > 0; i--) {
                        self->segments[i] = self->segments[i - 1];
                }
                return;
        }

        double deltaX = (double)(head->target_x - head->start_x) * factor;
        double deltaY = (double)(head->target_y - head->start_y) * factor;

        head->x = (int)(head->start_x + deltaX);
        head->y = (int)(head->start_y + deltaY);
}

void player_draw(Player *self, FrameInfo *info)
{
        /* DEMO CODE */
        SDL_Rect rect = {.x = 0, .y = 0, .w = 32, .h = 32 };

        for (int i = 0; i < self->n_segments; i++) {
                double angle = 0.0;
                switch (self->segments[i].dir) {
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

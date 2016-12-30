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
        Player p = {.sheet = sheet };
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
        self->dir = direction;
}

void player_update(Player *self, FrameInfo *frame)
{
        /* Currently a no-op */
}

void player_draw(Player *self, FrameInfo *info)
{
        /* DEMO CODE */
        SDL_Rect rect = {.x = 0, .y = 0, .w = 32, .h = 32 };
        tile_sheet_render(self->sheet, 1, 0, info->render, rect);
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

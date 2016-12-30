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

#include "tilesheet.h"

TileSheet *tile_sheet_new(const char *path, int tile_size, SDL_Renderer *render, SDL_Window *window)
{
        return NULL;
}

void tile_sheet_render(TileSheet *sheet, int column, int row, SDL_Renderer *render, SDL_Rect target)
{
}

void tile_sheet_free(TileSheet *self)
{
        if (!self) {
                return;
        }
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

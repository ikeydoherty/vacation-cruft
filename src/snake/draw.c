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

void snake_app_draw(SnakeApp *self, FrameInfo *frame)
{
        /* Clear the background */
        SDL_SetRenderDrawColor(self->render, 169, 203, 152, 255);
        SDL_RenderClear(self->render);

        /* Draw the player */
        player_draw(self->player, frame);

        /* Derpy - draw "high score" */
        SDL_Rect rect = { .x = 0, .y = 0, .w = 32, .h = 32};
        tile_sheet_render(self->sheet, 0, 2, self->render, rect);
        rect.x += 32;
        tile_sheet_render(self->sheet, 2, 2, self->render, rect);
        rect.x += 32;
        tile_sheet_render(self->sheet, 7, 2, self->render, rect);
        rect.x += 32;
        tile_sheet_render(self->sheet, 6, 2, self->render, rect);

        /* Flip to screen */
        SDL_RenderPresent(self->render);
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

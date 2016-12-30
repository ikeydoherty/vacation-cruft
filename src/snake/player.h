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

#pragma once

#include "tilesheet.h"

/**
 * A Player is the actual human controlled snake on screen
 */
typedef struct Player {
        TileSheet *sheet;
} Player;

/**
 * Construct a new player using the given tilesheet
 */
Player *player_new(TileSheet *sheet);

/**
 * Cleanup a previously created player
 */
void player_free(Player *player);

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
